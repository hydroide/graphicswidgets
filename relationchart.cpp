#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#include "relationchart.h"

//#include "../interpolation.h"

#include "stagedischargerelationcurveitem.h"

RelationChart::RelationChart(QGraphicsItem *parent)
    : VChart(parent)
{

}

void RelationChart::insertCurve(const QString &key, const RelationCurve &curve)
{
    _mCurves.insert(key, curve);
    refresh();
}

void RelationChart::removeCurve(const QString &key)
{
    _mCurves.remove(key);
    refresh();
}

void RelationChart::clearCurves()
{
    _mCurves.clear();
    refresh();
}

void RelationChart::refresh()
{
    qreal maxDischarge;
    qreal minDischarge;

    auto DischargeRange = [&] {
        return maxDischarge - minDischarge;
    };

    auto DischargeUnitLength = [&] {
        if (DischargeRange() == 0) {
            return 1.;
        }
        return this->geometry().width()/DischargeRange();
    };

    qreal maxStage;
    qreal minStage;

    auto StageRange = [&] {
        return maxStage - minStage;
    };

    auto StageUnitLength = [&] {
        if (StageRange() == 0) {
            return 1.;
        }
        return this->geometry().height()/StageRange();
    };

    bool initialized = false;

    for (auto const &s : _mCurves.values())
    {
        for (auto const &n : s.nodes)
        {
            auto stage = n.y.toDouble();
            auto discharge = n.x.toDouble();
            if (!initialized)
            {
                minStage = stage;
                maxStage = stage;
                minDischarge = discharge;
                maxDischarge = discharge;
                initialized = true;
            }
            if (stage < minStage)
            {
                minStage = stage;
            }
            if (stage > maxStage)
            {
                maxStage = stage;
            }
            if (discharge < minDischarge)
            {
                minDischarge = discharge;
            }
            if (discharge > maxDischarge)
            {
                maxDischarge  = discharge;
            }
        }

    }

    _xUnitLength = DischargeUnitLength();
    _yUnitLength = StageUnitLength();

    _xOffset = -minDischarge*_xUnitLength;
    _yOffset = -minStage*_yUnitLength;

}

void RelationChart::refreshGeometry()
{
    qreal maxDischarge;
    qreal minDischarge;

    auto DischargeRange = [&] {
        return maxDischarge - minDischarge;
    };

    auto DischargeUnitLength = [&] {
        if (DischargeRange() == 0) {
            return 1.;
        }
        return this->geometry().width()/DischargeRange();
    };

    qreal maxStage;
    qreal minStage;

    auto StageRange = [&] {
        return maxStage - minStage;
    };

    auto StageUnitLength = [&] {
        if (StageRange() == 0) {
            return 1.;
        }
        return this->geometry().height()/StageRange();
    };

    bool initialized = false;

    for (auto *item: this->childItems())
    {
        auto *sdrcItem = qgraphicsitem_cast<StageDischargeRelationCurveItem *>
                (item);
        if (nullptr != sdrcItem)
        {
            if (initialized == false)
            {
                minStage = sdrcItem->getMinStage();
                maxStage = sdrcItem->getMaxStage();
                minDischarge = sdrcItem->getMinDischarge();
                maxDischarge = sdrcItem->getMaxDischarge();
                initialized = true;
            }
            if (sdrcItem->getMinStage() < minStage)
            {
                minStage = sdrcItem->getMinStage();
            }
            if (sdrcItem->getMaxStage() > maxStage)
            {
                maxStage = sdrcItem->getMaxStage();
            }
            if (sdrcItem->getMinDischarge() < minDischarge)
            {
                minDischarge = sdrcItem->getMinDischarge();
            }
            if (sdrcItem->getMaxDischarge() > maxDischarge)
            {
                maxDischarge = sdrcItem->getMaxDischarge();
            }
        }
    }
    _xUnitLength = DischargeUnitLength()*0.618;
    _yUnitLength = StageUnitLength()    *0.618;

    _xOffset = -(minDischarge - DischargeRange()*0.191)*_xUnitLength;
    _yOffset = -(minStage     - StageRange()    *0.191)*_yUnitLength;
}


void RelationChart::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    refreshGeometry();
    //    painter->setRenderHint(QPainter::Antialiasing, true);

//    qDebug() << "Current: "
//             << _xUnitLength << _yUnitLength
//             << _xOffset << _yOffset;


//    QPainterPath p;
//    for (auto const &s : _lSeries)
//    {
//        painter->setPen(s.color);
//        bool first = true;
//        QPointF lstPoint;
//        QVector<QPointF> points;
//        std::vector<QPointF> originalPoints;
//        for (auto const &n : s.nodes)
//        {
//            auto discharge = n.discharge.toDouble();
//            auto dischargeUnits = discharge - minDischarge;
//            auto stage = n.stage.toDouble();
//            auto stageUnits = maxStage - stage;
//            originalPoints.push_back(QPointF(stage, discharge));
//            QPointF point(dischargeUnits*_xUnitLength,
//                          stageUnits*_yUnitLength);
//            painter->drawEllipse(point, 1.f, 1.f);
//            //            p.addEllipse(point, 1.f, 1.f);
////            if (first)
////            {
////                p.moveTo(point);
////            }
////            else
////            {
////                painter->drawLine(lstPoint, point);
////                //                p.lineTo(point);
////            }
//            points.append(point);
//            lstPoint = point;
//            first = false;
//        }
//        //        painter->drawPath(p);
//        auto zFirst = originalPoints.front().x();
//        auto zLast = originalPoints.back().x();
//        auto z = zFirst;

//        auto inc = 0.01;
//        first = true;
//        while (z < zLast)
//        {
//            QPointF originalPoint(z, s_p_i_a(originalPoints, z));
//            QPointF point((originalPoint.y() - minDischarge)*_xUnitLength,
//                          (maxStage - originalPoint.x())*_yUnitLength);
//            if (!first)
//            {
//                painter->drawLine(lstPoint, point);
//            }
//            z += inc;
//            first = false;
//            lstPoint = point;
//        }
//    }

}
