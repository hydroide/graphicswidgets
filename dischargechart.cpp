#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#include "dischargechart.h"

#include <QPainter>

DischargeChart::DischargeChart(QGraphicsItem *parent)
    : ProcessChart(parent)
{

}


void DischargeChart::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    ProcessChart::paintSeries(painter);

    painter->drawText(0, option->fontMetrics.height(), tr("流量过程线"));

    ProcessChart::paint(painter, option, widget);
}

ProcessMap &DischargeChart::currentMap(SpProcessSeries series)
{
    return series->mDischarges();
}
