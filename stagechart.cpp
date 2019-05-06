#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#include "stagechart.h"

#include <QPainter>

StageChart::StageChart(QGraphicsItem *parent)
    : ProcessChart(parent)
{

}

void StageChart::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    ProcessChart::paintSeries(painter);

    painter->drawText(0, option->fontMetrics.height(), tr("水位过程线"));
    ProcessChart::paint(painter, option, widget);
}

ProcessMap &StageChart::currentMap(SpProcessSeries series)
{
    return series->mStages();
}

void StageChart::updateData()
{
    for (auto series: _seriesMap)
    {
        series->genStageMap();
    }
}
