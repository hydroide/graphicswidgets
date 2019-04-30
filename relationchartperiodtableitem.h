#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#ifndef RELATIONCHARTPERIODTABLEITEM_H
#define RELATIONCHARTPERIODTABLEITEM_H

#include <QtCore>
#include <QtGui>
#include <QtWidgets>

#include "globaldefines.h"
#include "vchart.h"

class RelationChartPeriodTableItem : public QGraphicsTextItem
{
public:
    RelationChartPeriodTableItem(QGraphicsItem *parent = nullptr);

    void insertPeriod(const QDateTime &key,
                      const QString &html);

    void removePeriod(const QDateTime &key);

    void refresh();

private:
    QString _html = "<table>"
                    "  <tr>"
                    "    <th>时段</th>"
                    "    <th>起始时间</th>"
                    "    <th>结束时间</th>"
                    "    <th>线号</th>"
                    "    <th>实测点</th>"
                    "  </tr>"
                    "%1"
                    "</table>";
    QMap<QDateTime, QString> _periods;
};
#endif // RELATIONCHARTPERIODTABLEITEM_H
