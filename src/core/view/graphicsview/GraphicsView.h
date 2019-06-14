#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>

class QWheelEvent;
class QKeyEvent;

class GraphicsView : public QGraphicsView {
public:
  GraphicsView(QWidget* parent = Q_NULLPTR);
  virtual ~GraphicsView();

  virtual void mousePressEvent(QMouseEvent* event);
  virtual void mouseMoveEvent(QMouseEvent* event);
  virtual void mouseReleaseEvent(QMouseEvent* event);

  virtual void wheelEvent(QWheelEvent* event);

  virtual void keyPressEvent(QKeyEvent* event);
  virtual void keyReleaseEvent(QKeyEvent* event);

private slots:
  void onScalingTime(qreal x);
  void onAnimFinished();

private:
  bool m_isControlPressed;
  int m_numScheduledScalings;
};

#endif // GRAPHICSVIEW_H
