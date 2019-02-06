#include "GraphicsView.h"
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include <QTimeLine>

GraphicsView::GraphicsView(QWidget* parent):QGraphicsView(parent),
    m_isControlPressed(false),
    m_numScheduledScalings(0)
{
    setRenderHint(QPainter::Antialiasing);
    setAlignment(Qt::AlignCenter);
    setMouseTracking(true);

    qreal initScale = 1;
    scale(initScale, initScale);
}

GraphicsView::~GraphicsView()
{
}

void GraphicsView::wheelEvent(QWheelEvent* event)
{
    if(!m_isControlPressed){
        QGraphicsView::wheelEvent(event);
        return;
    }

    int numDegrees = event->delta() / 8;
    int numSteps   = numDegrees / 15;

    m_numScheduledScalings += numSteps;
    // reset scaling when wheel rotate direction changed
    if (m_numScheduledScalings * numSteps < 0){
        m_numScheduledScalings = numSteps;
    }

    QTimeLine* anim = new QTimeLine(350, this);
    anim->setUpdateInterval(20);

    connect(anim, &QTimeLine::valueChanged, this, &GraphicsView::onScalingTime);
    connect(anim, &QTimeLine::finished,     this, &GraphicsView::onAnimFinished);
    anim->start();

    QGraphicsView::wheelEvent(event);
}

void GraphicsView::keyPressEvent(QKeyEvent* event)
{
    if(Qt::Key_Control == event->key()){
        m_isControlPressed = true;
    }

    QGraphicsView::keyPressEvent(event);
}

void GraphicsView::keyReleaseEvent(QKeyEvent* event)
{
    if(Qt::Key_Control == event->key()){
        m_isControlPressed = false;
    }

    QGraphicsView::keyReleaseEvent(event);
}

void GraphicsView::onScalingTime(qreal x)
{
    Q_UNUSED(x);

    int scrollDirection = 1;
    qreal factor = 1.0 + qreal(scrollDirection * m_numScheduledScalings) / 300.0;
    scale(factor, factor);
}

void GraphicsView::onAnimFinished()
{
    if (m_numScheduledScalings > 0){
        --m_numScheduledScalings;
    }
    else{
        ++m_numScheduledScalings;
    }
    sender()->~QObject();
}
