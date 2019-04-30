#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#ifndef RELATIONCHART_H
#define RELATIONCHART_H

#include "modules/curvestructs.h"

#include "vchart.h"

#include "globaldefines.h"

class RelationChart : public VChart
{
    Q_OBJECT
public:
    explicit RelationChart(QGraphicsItem *parent = nullptr);

    void insertCurve(const QString &key, const RelationCurve &curve);

    void removeCurve(const QString &key);

    void clearCurves();

    void refresh();

    void refreshGeometry();

protected:
    QMap<QString, RelationCurve> _mCurves;

    // QGraphicsItem interface
public:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // RELATIONCHART_H
