#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#include "crosssectionchart.h"

CrossSectionChart::CrossSectionChart(QGraphicsItem *parent) : VChart(parent)
{

}

void CrossSectionChart::addSeries(const DGCrossSectionSurvey &series)
{
    _lCrossSectionSeries.append(series);
}

void CrossSectionChart::clearSeries()
{
    _lCrossSectionSeries.clear();
}

void
CrossSectionChart::paint(
        QPainter *painter,
        const QStyleOptionGraphicsItem *option,
        QWidget *widget)
{
    qreal maxDistance;
    qreal minDistance;
    auto distanceRange = [&](){
        return maxDistance - minDistance;
    };
    auto distanceUnitLength = [&]() {
        if (distanceRange() == 0) {
            return 1.;
        }
        return this->geometry().width()/distanceRange();
    };

    qreal maxElevation;
    qreal minElevation;
    auto elevationRange = [&](){
        return maxElevation - minElevation;
    };

    auto elevationUnitLength = [&]() {
        if (elevationRange() == 0) {
            return 1.;
        }
        return this->geometry().height()/elevationRange();
    };

    bool initialized = false;

    QMap<int, qreal> minDistances;
    QMap<int, qreal> maxDistances;

    for (auto s : _lCrossSectionSeries)
    {
        qreal maxDistanceInner;
        qreal minDistanceInner;
        bool initializedInner = false;
        for (auto v : s.verticals)
        {
            auto distance = v.distance.toDouble();
            auto elevation = v.elevation.toDouble();
            if (!initialized)
            {
                minDistance = distance;
                maxDistance = distance;
                minElevation = elevation;
                maxElevation = elevation;
                initialized = true;
            }
            if (!initializedInner)
            {
                minDistanceInner = distance;
                maxDistanceInner = distance;
                initializedInner = true;
            }

            if (distance < minDistance)
            {
                minDistance = distance;
            }
            if (distance > maxDistance)
            {
                maxDistance = distance;
            }
            if (distance < minDistanceInner)
            {
                minDistanceInner = distance;
            }
            if (distance > maxDistanceInner)
            {
                maxDistanceInner = distance;
            }
            if (elevation < minElevation)
            {
                minElevation = elevation;
            }
            if (elevation > maxElevation)
            {
                maxElevation = elevation;
            }
        }
        minDistances.insert(s.survey_id, minDistanceInner);
        maxDistances.insert(s.survey_id, maxDistanceInner);
    }

    for (auto s : _lCrossSectionSeries)
    {
        painter->setPen(s.color);
        bool first = true;
        QPointF lstPoint;
        auto getStage = [&](){
            QRegExp r = QRegExp("^(.+)([mM])$");
            r.indexIn(s.stage);
            if (r.captureCount() == 2)
            {
                QString strVal = r.cap(1);
                QString unit = r.cap(2);
                bool ok = false;
                double value = strVal.toDouble(&ok);
                if (!ok)
                {
                    return s.stage.toDouble();
                }
                //            if (unit = "m")
                //            {

                //            }
                return value;
            }
        };
        auto stage = getStage();
        auto stageUnits = maxElevation - stage;
        auto stageY = stageUnits*elevationUnitLength();
        auto minDistanceOfSurvey = minDistances[s.survey_id];
        auto maxDistanceOfSurvey = maxDistances[s.survey_id];
        auto minDistanceOfSurveyUnits = minDistanceOfSurvey - minDistance;
        auto maxDistanceOfSurveyUnits = maxDistanceOfSurvey - minDistance;

        auto left = minDistanceOfSurveyUnits*distanceUnitLength();
        auto right = maxDistanceOfSurveyUnits*distanceUnitLength();

        QPointF p1(left, stageY);
        QPointF p2(right, stageY);
        painter->drawLine(p1, p2);
        painter->drawText(left,
                          stageY - option->fontMetrics.descent(),
                          tr("日期：%1，测次：%2，位置：%3，水位：%4")
                          .arg(s.date.toString(tr("yyyy年M月d日")))
                          .arg(s.survey_id)
                          .arg(s.location)
                          .arg(s.stage));
        for (auto v : s.verticals)
        {
            auto distance = v.distance.toDouble();
            auto distanceUnits = distance - minDistance;
            auto elevation = v.elevation.toDouble();
            auto elevationUnits = maxElevation - elevation;
            QPointF point(distanceUnits*distanceUnitLength(),
                          elevationUnits*elevationUnitLength());
            painter->drawEllipse(point, 1.f, 1.f);
            if (!first)
            {
                painter->drawLine(lstPoint, point);
            }
            lstPoint = point;
            first = false;
        }
    }

    painter->drawText(0, option->fontMetrics.height(),
                      tr("最高：%1").arg(maxElevation));
    painter->drawText(0,
                      this->geometry().height() - option->fontMetrics.descent(),
                      tr("最低：%1").arg(minElevation));
}
