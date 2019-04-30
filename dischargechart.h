#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#ifndef DISCHARGECHART_H
#define DISCHARGECHART_H

#include "processchart.h"

class DischargeChart : public ProcessChart
{
    Q_OBJECT
public:
    explicit DischargeChart(QGraphicsItem *parent = nullptr);
    inline QString drawType() const
    {
        return "discharge";
    }

    // QGraphicsItem interface
public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    // ProcessChart interface
protected:
    ProcessMap &currentMap(SpProcessSeries series);
};

#endif // DISCHARGECHART_H
