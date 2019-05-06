#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#ifndef SEDIMENTCHART_H
#define SEDIMENTCHART_H


#include "processchart.h"

class SedimentChart : public ProcessChart
{
    Q_OBJECT
public:
    explicit SedimentChart(QGraphicsItem *parent = nullptr);
    inline QString drawType() const
    {
        return "sediment";
    }

    // QGraphicsItem interface
public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    // ProcessChart interface
protected:
    ProcessMap &currentMap(SpProcessSeries series);
    void updateData();
};

#endif // SEDIMENTCHART_H
