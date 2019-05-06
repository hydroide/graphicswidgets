#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#include "dischargemeasurementpointitem.h"

DischargeMeasurementPointItem::DischargeMeasurementPointItem(
        QGraphicsItem *parent)
    : QGraphicsItem(parent)
{
//    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

VChart *DischargeMeasurementPointItem::pChart() const
{
    return _pChart;
}

void DischargeMeasurementPointItem::setPChart(VChart *chart)
{
    _pChart = chart;
}

DGMeasuredDischarge DischargeMeasurementPointItem::measuredDischarge() const
{
    return _measuredDischarge;
}

void DischargeMeasurementPointItem::setMeasuredDischarge(const DGMeasuredDischarge &measuredDischarge)
{
    _measuredDischarge = measuredDischarge;
}

QColor DischargeMeasurementPointItem::getColor() const
{
    return _color;
}

void DischargeMeasurementPointItem::setColor(const QColor &color)
{
    _color = color;
}


QPointF DischargeMeasurementPointItem::getPoint() const
{
    if (_pChart != nullptr)
    {
        qreal x = _measuredDischarge.discharge.toDouble()*_pChart->xUnitLength()
                + _pChart->xOffset();
        qreal y = _measuredDischarge.stage.toDouble()*_pChart->yUnitLength()
                + _pChart->yOffset();
        y = _pChart->geometry().height() - y;
        return QPointF(x, y);
    }
    return QPointF();
}


QRectF DischargeMeasurementPointItem::boundingRect() const
{
    return QRectF(getPoint(), QSizeF(5.f, 5.f));
}

void DischargeMeasurementPointItem::paint(
        QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(QBrush(_color), 2.f));
    painter->drawPoint(getPoint());
    painter->setPen(QPen(QBrush(_color), 1.f));
    painter->drawEllipse(getPoint(), 5.f, 5.f);
    auto textPoint = boundingRect().topRight();
//    textPoint.setX(textPoint.x() - 2.f);
//    textPoint.setY(textPoint.y() - 2.f);
    painter->setFont(QFont(DEFAULT_NUMERIAL_FONTFAMILTY, 10));
    painter->drawText(textPoint, QString("%1").arg(_measuredDischarge.sn));
}

SedimentDischargeMeasurementPointItem::SedimentDischargeMeasurementPointItem(QGraphicsItem *parent)
    : DischargeMeasurementPointItem(parent)
{

}

DGMeasuredSedimentDischarge SedimentDischargeMeasurementPointItem::measuredSedimentDischarge() const
{
    return _measuredSedimentDischarge;
}

void SedimentDischargeMeasurementPointItem::setMeasuredSedimentDischarge(const DGMeasuredSedimentDischarge &measuredSedimentDischarge)
{
    _measuredSedimentDischarge = measuredSedimentDischarge;
    _measuredDischarge.sn = measuredSedimentDischarge.sn;
}

QPointF SedimentDischargeMeasurementPointItem::getPoint() const
{
    if (_pChart != nullptr)
    {
        qreal x = _measuredSedimentDischarge.crossSectionalMeanSedimentConcentration.toDouble()*_pChart->xUnitLength()
                + _pChart->xOffset();
        qreal y = _measuredSedimentDischarge.singleSampleSedimentConcentration.toDouble()*_pChart->yUnitLength()
                + _pChart->yOffset();
        y = _pChart->geometry().height() - y;
        return QPointF(x, y);
    }
    return QPointF();
}
