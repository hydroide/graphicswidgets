#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#include "processyaxiswidget.h"

ProcessYAxisWidget::ProcessYAxisWidget(QWidget *parent) : QWidget(parent)
{
    setMouseTracking(true);
}

ProcessYAxisWidget::~ProcessYAxisWidget()
{

}

void ProcessYAxisWidget::mouseMovePosY(int posY)
{
    _latestMousePosY = posY;
    update();
}

void ProcessYAxisWidget::unitChange(qreal min, qreal max, qreal unit)
{
    _min = min;
    _max = max;
    _unit = unit;
    this->update();
}

void ProcessYAxisWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    if (_latestMousePosY > 0)
    {
        auto penBefore = painter.pen();
        painter.setPen(QColor(128, 35, 23));
        painter.drawLine(0, _latestMousePosY,
                         this->width(), _latestMousePosY);
        auto height = painter.fontMetrics().height();
        painter.drawText(QRect(0, _latestMousePosY - height, width(), height), tr("%1").arg(_max - _latestMousePosY / _unit));
        painter.setPen(penBefore);
    }
}

void ProcessYAxisWidget::mouseMoveEvent(QMouseEvent *event)
{
    _latestMousePosY = event->pos().y();
    update();
    QWidget::mouseMoveEvent(event);
}

void ProcessYAxisWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        setCursor(Qt::ClosedHandCursor);
    }
    QWidget::mousePressEvent(event);
}

void ProcessYAxisWidget::mouseReleaseEvent(QMouseEvent *event)
{
    setCursor(Qt::ArrowCursor);
    QWidget::mouseReleaseEvent(event);
}

void ProcessYAxisWidget::enterEvent(QEvent *event)
{
    QWidget::enterEvent(event);
}

void ProcessYAxisWidget::leaveEvent(QEvent *event)
{
    _latestMousePosY = -1;
    update();
    QWidget::leaveEvent(event);
}

