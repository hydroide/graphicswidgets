#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#ifndef DISCHARGEMEASUREMENTPOINTITEM_H
#define DISCHARGEMEASUREMENTPOINTITEM_H

#include <QtCore>
#include <QtGui>
#include <QtWidgets>

#include "globaldefines.h"
#include "modules/curvestructs.h"
#include "vchart.h"

class DischargeMeasurementPointItem : public QGraphicsItem
{
public:
    DischargeMeasurementPointItem(QGraphicsItem *parent = nullptr);

    VChart *pChart() const;
    void setPChart(VChart *pChart);

    DGMeasuredDischarge measuredDischarge() const;
    void setMeasuredDischarge(const DGMeasuredDischarge &measuredDischarge);

    QColor getColor() const;
    void setColor(const QColor &color);

protected:
    VChart *_pChart;
    DGMeasuredDischarge _measuredDischarge;
    QColor _color;

    virtual QPointF getPoint() const;

    // QGraphicsItem interface
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class SedimentDischargeMeasurementPointItem : public DischargeMeasurementPointItem
{
public:
    SedimentDischargeMeasurementPointItem(QGraphicsItem *parent = nullptr);

    DGMeasuredSedimentDischarge measuredSedimentDischarge() const;
    void setMeasuredSedimentDischarge(const DGMeasuredSedimentDischarge &measuredSedimentDischarge);

protected:
    virtual QPointF getPoint() const;

    DGMeasuredSedimentDischarge _measuredSedimentDischarge;
};

#endif // DISCHARGEMEASUREMENTPOINTITEM_H
