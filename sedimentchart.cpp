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
    ProcessChart::paintPoints(painter);

    painter->drawText(0, option->fontMetrics.height(), tr("沙量过程线"));

    ProcessChart::paint(painter, option, widget);
}

ProcessMap &SedimentChart::currentMap(SpProcessSeries series)
{
    return series->mSediments();
}

QMap<QDateTime, QPair<QString, QString> > SedimentChart::currentPoints(SpProcessSeries series)
{
    QMap<QDateTime, QPair<QString, QString> > map;
    auto mds = series->measuredSedimentDischargeMap();
    for (auto key: mds.keys()) {
        auto md = mds.value(key);
        auto pair = QPair<QString, QString>(md.sn, md.crossSectionalMeanSedimentConcentration);
        map.insert(key, pair);
    }
    return map;
}

void SedimentChart::updateData()
{
    for (auto series: _seriesMap)
    {
        series->genSedimentMap();
        series->genMeasuredSedimentDischargeMap();
    }
}
