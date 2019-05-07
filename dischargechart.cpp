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
    ProcessChart::paintPoints(painter);

    painter->drawText(0, option->fontMetrics.height(), tr("流量过程线"));

    ProcessChart::paint(painter, option, widget);
}

ProcessMap &DischargeChart::currentMap(SpProcessSeries series)
{
    return series->mDischarges();
}

QMap<QDateTime, QPair<QString, QString> > DischargeChart::currentPoints(
        SpProcessSeries series)
{
    QMap<QDateTime, QPair<QString, QString> > map;
    auto mds = series->measuredDischargeMap();
    for (auto key: mds.keys()) {
        auto md = mds.value(key);
        auto pair = QPair<QString, QString>(md.sn, md.discharge);
        map.insert(key, pair);
    }
    return map;
}

void DischargeChart::updateData()
{
    for (auto series: _seriesMap)
    {
        series->genDischargeMap();
        series->genMeasuredDischargeMap();
    }
}
