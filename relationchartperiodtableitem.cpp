#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#include "relationchartperiodtableitem.h"

RelationChartPeriodTableItem::RelationChartPeriodTableItem(
        QGraphicsItem *parent)
    : QGraphicsTextItem(parent)
{
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);

    setHtml(_html.arg(""
                      "<tr></tr>"
                      "<tr></tr>"
                      "<tr></tr>"
                      ""));
}

void RelationChartPeriodTableItem::insertPeriod(const QDateTime &key, const QString &html)
{
    _periods.insert(key, html);
    refresh();
}

void RelationChartPeriodTableItem::removePeriod(const QDateTime &key)
{
    _periods.remove(key);
    refresh();
}

void RelationChartPeriodTableItem::refresh()
{
    auto list = QStringList(_periods.values());
    setHtml(_html.arg(list.join("")));
}


