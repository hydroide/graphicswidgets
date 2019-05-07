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
    ProcessChart::paintPoints(painter);

    painter->drawText(0, option->fontMetrics.height(), tr("水位过程线"));

    ProcessChart::paint(painter, option, widget);
}

ProcessMap &StageChart::currentMap(SpProcessSeries series)
{
    return series->mStages();
}

QMap<QDateTime, QPair<QString, QString> > StageChart::currentPoints(SpProcessSeries series)
{
    QMap<QDateTime, QPair<QString, QString> > map;
    auto mds = series->measuredDischargeMap();
    for (auto key: mds.keys()) {
        auto md = mds.value(key);
        auto pair = QPair<QString, QString>(md.sn, md.stage);
        map.insert(key, pair);
    }
    return map;
}

void StageChart::updateData()
{
    for (auto series: _seriesMap)
    {
        series->genStageMap();
        series->genMeasuredDischargeMap();
    }
}
