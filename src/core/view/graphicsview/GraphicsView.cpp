#include "GraphicsView.h"
#include "AbstractTool.h"
#include "Define.h"
#include "Editor.h"
#include "PluginLoader.h"
#include "Project.h"
#include "ProjectParser.h"
#include "SystemConfig.h"
#include <QFileInfo>
#include <QKeyEvent>
#include <QMimeData>
#include <QMouseEvent>
#include <QTimeLine>
#include <QWheelEvent>

GraphicsView::GraphicsView(QWidget* parent)
    : QGraphicsView(parent), m_isControlPressed(false), m_numScheduledScalings(0) {
  setRenderHint(QPainter::Antialiasing);
  setAlignment(Qt::AlignCenter);
  setMouseTracking(true);
  setDragMode(RubberBandDrag);
  setBackgroundBrush(QBrush(QColor(systemConfig(SystemConfig::backgroundColor).toString())));
  qreal initScale = 1;
  scale(initScale, initScale);
  setAcceptDrops(true);
}

GraphicsView::~GraphicsView() {
}

void GraphicsView::mousePressEvent(QMouseEvent* event) {
  QGraphicsView::mousePressEvent(event);
}

void GraphicsView::mouseMoveEvent(QMouseEvent* event) {
  if (!Editor::getInstance()->activeTool()->isSelectable()) {
    setDragMode(NoDrag);
  }
  QGraphicsView::mouseMoveEvent(event);
}

void GraphicsView::mouseReleaseEvent(QMouseEvent* event) {
  QGraphicsView::mouseReleaseEvent(event);
  setDragMode(RubberBandDrag);
}

void GraphicsView::wheelEvent(QWheelEvent* event) {
  if (!m_isControlPressed) {
    QGraphicsView::wheelEvent(event);
    return;
  }

  int numDegrees = event->delta() / 8;
  int numSteps = numDegrees / 15;

  m_numScheduledScalings += numSteps;
  // reset scaling when wheel rotate direction changed
  if (m_numScheduledScalings * numSteps < 0) {
    m_numScheduledScalings = numSteps;
  }

  QTimeLine* anim = new QTimeLine(350, this);
  anim->setUpdateInterval(20);

  connect(anim, &QTimeLine::valueChanged, this, &GraphicsView::onScalingTime);
  connect(anim, &QTimeLine::finished, this, &GraphicsView::onAnimFinished);
  anim->start();

  QGraphicsView::wheelEvent(event);
}

void GraphicsView::keyPressEvent(QKeyEvent* event) {
  if (Qt::Key_Control == event->key()) {
    m_isControlPressed = true;
  }

  QGraphicsView::keyPressEvent(event);
}

void GraphicsView::keyReleaseEvent(QKeyEvent* event) {
  if (Qt::Key_Control == event->key()) {
    m_isControlPressed = false;
  }

  QGraphicsView::keyReleaseEvent(event);
}

void GraphicsView::dragEnterEvent(QDragEnterEvent* event) {
  // accept only APP_EXTENSION extension file drag enter.
  // and GraphicsScene::dragEnterEvent not need to call.
  // so do not call QGraphicsView::dragEnterEvent function.
  if (event->mimeData()->hasFormat("text/uri-list")) {
    QFileInfo info(event->mimeData()->urls().first().toLocalFile());
    if (APP_EXTENSION == info.suffix()) {
      event->acceptProposedAction();
    }
  }
}

void GraphicsView::dragMoveEvent(QDragMoveEvent* event) {
  // GraphicsScene::dragMoveEvent not need to call.
  // so do not call QGraphicsView::dragMoveEvent function.
  Q_UNUSED(event);
}

void GraphicsView::dropEvent(QDropEvent* event) {
  // GraphicsScene::dropEvent not need to call.
  // so do not call QGraphicsView::dropEvent function.
  Project* lastProject = Editor::getInstance()->project();

  QString filePath = event->mimeData()->urls().first().toLocalFile();
  QFile f(filePath);
  if (!f.open(QIODevice::ReadOnly)) {
    return;
  }

  ProjectParser parser;
  QByteArray data = f.readAll();
  Project* newProject = parser.parse(data, lastProject);

  delete lastProject;
  lastProject->setFilePath(filePath);
  Editor::getInstance()->changeProject(newProject);
  PluginLoader::getInstance()->reset();

  newProject->setActiveSheet(newProject->sheets().first());
  newProject->changeActiveSheet(0);
}

void GraphicsView::onScalingTime(qreal x) {
  Q_UNUSED(x);

  int scrollDirection = 1;
  systemConfig(SystemConfig::mouseScrollDirection).toInt();
  qreal factor = 1.0 + qreal(scrollDirection * m_numScheduledScalings) / 300.0;
  scale(factor, factor);
}

void GraphicsView::onAnimFinished() {
  if (m_numScheduledScalings > 0) {
    --m_numScheduledScalings;
  } else {
    ++m_numScheduledScalings;
  }
  sender()->~QObject();
}
