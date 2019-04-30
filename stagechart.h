#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#ifndef STAGECHART_H
#define STAGECHART_H

#include "processchart.h"

class StageChart : public ProcessChart
{
    Q_OBJECT
public:
    explicit StageChart(QGraphicsItem *parent = nullptr);
    inline QString drawType() const
    {
        return "stage";
    }

    // QGraphicsItem interface
public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    // ProcessChart interface
protected:
    ProcessMap &currentMap(SpProcessSeries series);
};

#endif // STAGECHART_H
