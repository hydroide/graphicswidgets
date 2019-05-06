#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#include "sedimentchart.h"

SedimentChart::SedimentChart(QGraphicsItem *parent)
    : ProcessChart(parent)
{

}


void SedimentChart::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    ProcessChart::paintSeries(painter);

    painter->drawText(0, option->fontMetrics.height(), tr("沙量过程线"));
    ProcessChart::paint(painter, option, widget);
}

ProcessMap &SedimentChart::currentMap(SpProcessSeries series)
{
    return series->mSediments();
}

void SedimentChart::updateData()
{
    for (auto series: _seriesMap)
    {
        series->genSedimentMap();
        series->genMeasuredSedimentDischargeMap();
    }
}
