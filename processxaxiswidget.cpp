#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#include "processxaxiswidget.h"

ProcessXAxisWidget::ProcessXAxisWidget(QWidget *parent) : QWidget(parent)
{
    setMouseTracking(true);
    setStyleSheet("color: blue; background-color: yellow;");
    updateHours();
    updateDisplayHours();
}

QDateTime ProcessXAxisWidget::startDateTime() const
{
    return _startDateTime;
}

void ProcessXAxisWidget::setStartDateTime(const QDateTime &startDateTime)
{
    _startDateTime = startDateTime;
    _scale = 1;
    setViewStartDateTime(startDateTime);
}

QDateTime ProcessXAxisWidget::endDateTime() const
{
    return _endDateTime;
}

void ProcessXAxisWidget::setEndDateTime(const QDateTime &endDateTime)
{
    _endDateTime = endDateTime;
    _scale = 1;
    setViewEndDateTime(endDateTime);
}


QDateTime ProcessXAxisWidget::viewStartDateTime() const
{
    return _viewStartDateTime;
}

void ProcessXAxisWidget::setViewStartDateTime(const QDateTime &viewStartDateTime)
{
    _viewStartDateTime = viewStartDateTime;
    updateDisplayHours();
    this->moveAxis(0);
}

QDateTime ProcessXAxisWidget::viewEndDateTime() const
{
    return _viewEndDateTime;
}

void ProcessXAxisWidget::setViewEndDateTime(const QDateTime &viewEndDateTime)
{
    _viewEndDateTime = viewEndDateTime;
    updateDisplayHours();
    this->moveAxis(0);
}

void ProcessXAxisWidget::updateHours()
{
    _mSecs = _endDateTime.toMSecsSinceEpoch() - _startDateTime.toMSecsSinceEpoch();
    _hours = _mSecs/INT_MSECS_PER_HOURS;
}

void ProcessXAxisWidget::updateDisplayHours()
{
    qint64 diff = getMaxDateTime().toMSecsSinceEpoch()
                - getMinDateTime().toMSecsSinceEpoch();
    _displayHours = (qreal)diff/INT_MSECS_PER_HOURS/_scale;
    update();
}

void ProcessXAxisWidget::updateUnitWidth()
{
    _unitWidth = (qreal)this->width()/_displayHours;
}

void ProcessXAxisWidget::moveAxis(qreal hourPos)
{
    auto differ = (qint64)(      hourPos * INT_MSECS_PER_HOURS);
    auto period = (qint64)(_displayHours * INT_MSECS_PER_HOURS);

    if (_viewStartDateTime.addMSecs(differ) < getMinDateTime())
    {
        // 左头超界
        _viewStartDateTime = getMinDateTime();
        _viewEndDateTime   = _viewStartDateTime.addMSecs(period);
    }
    else if (_viewStartDateTime.addMSecs(differ + period) > getMaxDateTime())
    {
        // 右头超界
        _viewEndDateTime   = getMaxDateTime();
        _viewStartDateTime = _viewEndDateTime.addMSecs(-period);
    }
    else
    {
        // 不超界
        _viewStartDateTime = _viewStartDateTime.addMSecs(differ);
        _viewEndDateTime   = _viewStartDateTime.addMSecs(period);
    }
    Q_EMIT viewChanged(_viewStartDateTime, _viewEndDateTime);
}

QDateTime ProcessXAxisWidget::getMinDateTime()
{
    return QDateTime(_startDateTime.date());
}

QDateTime ProcessXAxisWidget::getMaxDateTime()
{
    if (_endDateTime.time() != QTime(0, 0))
    {
        return QDateTime(_endDateTime.date().addDays(1));
    }
    return _endDateTime;
}

void ProcessXAxisWidget::mouseMovePosX(int posX)
{
    _latestMousePosX = posX;
    update();
}

void ProcessXAxisWidget::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    if (_latestMousePosX > 0)
    {
        auto penBefore = painter.pen();
        painter.setPen(QColor(38, 227, 234));
        painter.drawLine(_latestMousePosX, 0,
                         _latestMousePosX, this->height());
        painter.setPen(penBefore);
    }
    this->updateUnitWidth();
    if (_displayHours <= 0)
    {
        return;
    }
//    _unitWidth = (qreal)e->rect().width()/_displayHours;
    this->updateUnitWidth();
    bool noSpaceForDay = false;
    bool noSpaceFor_6_18 = false;
    bool noSpaceFor_0_6_12_18 = false;
    auto fontHeight = fontMetrics().height();
    auto dayWidth = 24*_unitWidth;
    if (dayWidth < fontMetrics().width(tr("31")))
    {
        noSpaceForDay = true;
    }
    if (dayWidth < fontMetrics().width(tr("0612180")))
    {
        if (dayWidth < fontMetrics().width(tr("0120")))
        {
            noSpaceFor_0_6_12_18 = true;
        }
        else
        {
            noSpaceFor_6_18 = true;
        }
    }
    auto yearLabelWidth = fontMetrics().width(tr("1234年"));
    auto monthLabelWidth = fontMetrics().width(tr("12月"));
    if (!_viewStartDateTime.isValid())
    {
        _viewStartDateTime = getMinDateTime();
    }
    if (!_viewEndDateTime.isValid())
    {
        _viewEndDateTime = getMaxDateTime();
    }
    int currentMonth = {0};
    int currentYear{0};
    if (noSpaceForDay) {
        for (auto dt = _viewStartDateTime;
             dt.date() < _viewEndDateTime.date().addDays(1);
             dt = dt.addYears(1)) {
            auto differ = (qreal)(
                        QDateTime(QDate(dt.date().year(),
                                        1,
                                        1)).toMSecsSinceEpoch()
                                  - _viewStartDateTime.toMSecsSinceEpoch())
                                /INT_MSECS_PER_HOURS;
            auto yearWidth = dayWidth*dt.date().daysInYear();
            QRectF rect(differ*_unitWidth, 0, yearWidth, fontHeight);

            if (!(yearWidth < yearLabelWidth)) {
                painter.drawRect(rect);
                painter.drawText(rect,
                                 Qt::AlignCenter,
                                 tr("%1年").arg(dt.date().year()));
            }
//            auto yearButton = new QPushButton(tr("%1年").arg(dt.date().year()), this);
//            yearButton->setGeometry(rect.toRect());
        }
        for (auto dt = _viewStartDateTime;
             dt.date() < _viewEndDateTime.date().addDays(1); dt = dt.addMonths(1)) {
            auto differ = (qreal)(
                        QDateTime(QDate(dt.date().year(),
                                        dt.date().month(),
                                        1)).toMSecsSinceEpoch()
                                  - _viewStartDateTime.toMSecsSinceEpoch())
                                /INT_MSECS_PER_HOURS;
            auto monthWidth = dayWidth*dt.date().daysInMonth();
            QRectF rect(differ*_unitWidth, fontHeight, monthWidth, fontHeight);

            if (!(monthWidth < monthLabelWidth)) {
                painter.drawRect(rect);
                painter.drawText(rect,
                                 Qt::AlignCenter,
                                 tr("%1月").arg(dt.date().month()));
            }
//            auto yearButton = new QPushButton(tr("%1月").arg(dt.date().month()), this);
//            yearButton->setGeometry(rect.toRect());
        }
    }
    else for (auto dt = _viewStartDateTime;
         dt.date() < _viewEndDateTime.date().addDays(1); dt = dt.addDays(1))
    {
        auto differ = (qreal)(QDateTime(dt.date()).toMSecsSinceEpoch()
                              - _viewStartDateTime.toMSecsSinceEpoch())
                            /INT_MSECS_PER_HOURS;
        auto differDecimals = differ - (int)differ;
        QString head;
        if (_displayLevel & DisplayYear || dt.date().year() != currentYear)
        {
            head += tr("%1-").arg(dt.date().year());
            currentYear = dt.date().year();
        }
        if (_displayLevel & DisplayMonth || dt.date().month() != currentMonth)
        {
            head += tr("%1-").arg(dt.date().month());
            currentMonth = dt.date().month();
        }
        if (differDecimals != 0 && differ < 0) {
            currentYear = 0;
            currentMonth = 0;
        }
        if (!noSpaceForDay) {
            painter.setBrush(Qt::white);
            painter.drawRect(QRectF(differ*_unitWidth, 0, dayWidth, fontHeight));
            painter.drawText(QRectF(differ*_unitWidth, 0, dayWidth, fontHeight),
                             Qt::AlignCenter,
                             head + tr("%1").arg(dt.date().day()));
            painter.drawLine(QPointF(differ*_unitWidth, 0),
                             QPointF(differ*_unitWidth, 40));
        }
    }
    for (auto dt = _viewStartDateTime;
         dt <= _viewEndDateTime.addMSecs(INT_MSECS_PER_HOURS); // add an hour
         dt = dt.addMSecs(INT_MSECS_PER_HOURS))
    {
        auto minus = (qreal)(
                    dt.toMSecsSinceEpoch()
                    /INT_MSECS_PER_HOURS*INT_MSECS_PER_HOURS // round to hours
                    - _viewStartDateTime.toMSecsSinceEpoch())
                /INT_MSECS_PER_HOURS;
        int hour = dt.time().hour();
        if (hour%6 != 0)
        {
            int remain = hour%6;
            if (remain == 3 && _unitWidth > 2)
            {
                painter.drawLine(QPointF(minus*_unitWidth, 30),
                                 QPointF(minus*_unitWidth, 40));
            }
            else if (_unitWidth > 6) // remain is 1 or 2 or 4 or 5
            {
                painter.drawLine(QPointF(minus*_unitWidth, 35),
                                 QPointF(minus*_unitWidth, 40));
            }
            continue;
        }
        else if (hour%12 != 0 && noSpaceFor_6_18)
        {
            continue;
        }
        else if (noSpaceFor_0_6_12_18)
        {
            continue;
        }
        if (minus*_unitWidth >= 8)
        {
            painter.drawText(QRectF(minus*_unitWidth - 8, fontHeight,
                                    16, fontHeight),
                             tr("%1").arg(hour),
                             Qt::AlignCenter|Qt::AlignVCenter);
        }
        painter.drawLine(QPointF(minus*_unitWidth, 2*fontHeight),
                         QPointF(minus*_unitWidth, 40));
    }
    QWidget::paintEvent(e);
}



void ProcessXAxisWidget::wheelEvent(QWheelEvent *e)
{
    if (e->delta() > 0)
    {
        _scale *= _scaleFactor;
        if (_scale > 30.f)
        {
            _scale = 30;
        }
    }
    else
    {
        if (_scale != 1.f)
        {
            _scale /= _scaleFactor;
            if (_scale < _scaleFactor)
            {
                _scale = 1.f;
            }
        }
    }
    auto hourDiff = e->pos().x()/_unitWidth;
    updateDisplayHours();
    updateUnitWidth();
    auto hourDiff2 = e->pos().x()/_unitWidth;
    moveAxis(hourDiff - hourDiff2);
    update();

}

void ProcessXAxisWidget::dragMoveEvent(QDragMoveEvent *e)
{
    QWidget::dragMoveEvent(e);
}

void ProcessXAxisWidget::mousePressEvent(QMouseEvent *e)
{
    if (e->buttons() & Qt::LeftButton)
    {
        setCursor(Qt::ClosedHandCursor);
//        _lastPos = e->pos();
    }
    QWidget::mousePressEvent(e);
}

void ProcessXAxisWidget::mouseMoveEvent(QMouseEvent *e)
{
    if (e->buttons() & Qt::LeftButton)
    {
        auto hourPos = (qreal)( _latestMousePosX - e->pos().x())/_unitWidth;
        moveAxis(hourPos);
    }
    _latestMousePosX = e->pos().x();
    update();
    QWidget::mouseMoveEvent(e);
}

void ProcessXAxisWidget::mouseReleaseEvent(QMouseEvent *e)
{
//    if (e->buttons() & Qt::LeftButton)
    {
        setCursor(Qt::ArrowCursor);
    }
    QWidget::mouseReleaseEvent(e);
}

void ProcessXAxisWidget::enterEvent(QEvent *e)
{
    update();
    QWidget::enterEvent(e);
}

void ProcessXAxisWidget::leaveEvent(QEvent *e)
{
    _latestMousePosX = -1;
    update();
    QWidget::leaveEvent(e);
}
