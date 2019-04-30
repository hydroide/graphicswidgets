#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#include "processpointitem.h"

QRectF ProcessPointItem::boundingRect() const
{
    return QRectF(getPoint(), QSizeF(5.f, 5.f));
}

void ProcessPointItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPoint(getPoint());
    qDebug() << getPoint();
    painter->drawEllipse(getPoint(), 5.f, 5.f);

    auto textPoint = boundingRect().topRight();
    painter->drawText(textPoint, _text);
}

ProcessPointItem::ProcessPointItem(QGraphicsItem *parent)
    : QGraphicsItem(parent)
{

}

QPointF ProcessPointItem::getPoint() const
{
    if (_pChart != nullptr)
    {
        qreal x = _dateTime.toMSecsSinceEpoch()/INT_MSECS_PER_HOURS*_pChart->xUnitLength()
                + _pChart->xOffset();
        qreal y = _value.toDouble()*_pChart->yUnitLength()
                + _pChart->yOffset();
        y = _pChart->geometry().height() - y;
        return QPointF(x, y);
    }
    return QPointF();
}

QString ProcessPointItem::value() const
{
    return _value;
}

void ProcessPointItem::setValue(const QString &value)
{
    _value = value;
}

QDateTime ProcessPointItem::dateTime() const
{
    return _dateTime;
}

void ProcessPointItem::setDateTime(const QDateTime &dateTime)
{
    _dateTime = dateTime;
}

VChart *ProcessPointItem::pChart() const
{
    return _pChart;
}

void ProcessPointItem::setPChart(VChart *pChart)
{
    _pChart = pChart;
}

QString ProcessPointItem::text() const
{
    return _text;
}

void ProcessPointItem::setText(const QString &text)
{
    _text = text;
}


