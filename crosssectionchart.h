#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#ifndef CROSSSECTIONCHART_H
#define CROSSSECTIONCHART_H

#include "vchart.h"
//#include "../models/crosssectionseries.h"

#include "hcglobaldefs.h"

class CrossSectionChart : public VChart
{
    Q_OBJECT
public:
    explicit CrossSectionChart(QGraphicsItem *parent = nullptr);

    virtual void addSeries(const DGCrossSectionSurvey &series);
    virtual void clearSeries();

private:
    QList<DGCrossSectionSurvey> _lCrossSectionSeries;

    // QGraphicsItem interface
public:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

};

#endif // CROSSSECTIONCHART_H
