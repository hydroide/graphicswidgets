#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#include "stagedischargerelationcurveitem.h"

#include "relationcurvenotationitem.h"
#include "relationcurvenotationlinkitem.h"

#include "helpers/mathhelper.h"

StageDischargeRelationCurveItem::StageDischargeRelationCurveItem(QGraphicsItem *parent, int curveType)
    : QGraphicsItem(parent), _curveType(curveType)
{
    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
}

RelationCurve StageDischargeRelationCurveItem::curve() const
{
    return _curve;
}

QPointF StageDischargeRelationCurveItem::getPointFromCurveNode(
        const RelationCurveNode &n) const
{
    auto stage = n.y.toDouble();
    auto discharge = n.x.toDouble();
    return getPoint(stage, discharge);
}

void StageDischargeRelationCurveItem::setCurve(const RelationCurve &curve)
{
    _curve = curve;
    bool initialized = false;
    for (auto const &node : _curve.nodes)
    {
        auto stage = node.y.toDouble();
        auto discharge = node.x.toDouble();
        if (!initialized)
        {
            _minStage = stage;
            _maxStage = stage;
            _minDischarge = discharge;
            _maxDischarge = discharge;
            initialized = true;
        }
        if (stage < _minStage)
        {
            _minStage = stage;
        }
        if (stage > _maxStage)
        {
            _maxStage = stage;
        }
        if (discharge < _minDischarge)
        {
            _minDischarge = discharge;
        }
        if (discharge > _maxDischarge)
        {
            _maxDischarge  = discharge;
        }
    }
//    auto n = _curve.nodes.count();
//    if (n > 0)
//    {
//        while (i + 2 < n)
//        {
//            BezierCurve curve;
//            curve._startPoint = getPointFromCurveNode(_curve.nodes[i]);
////            curve._midPoint = getPointFromCurveNode(_curve.nodes[i + 1]);
//            curve._endPoint = getPointFromCurveNode(_curve.nodes[i + 2]);


//            ++i;
//        }
//    }
}


QPointF StageDischargeRelationCurveItem::getLinePoint(qreal x, qreal y)
{
    QPointF max = getPoint(_maxStage, _maxDischarge);
    QPointF min = getPoint(_minStage, _maxDischarge);

    if (y < max.y())
    {
        y = max.y();
    }
    if (y > min.y())
    {
        y = min.y();
    }
    auto rect = boundingRect();
    rect.setTop(y);
    rect.setHeight(1);
    QPainterPath path;
    path.addRect(rect);
    auto intersection = _allPath.intersected(path);
    auto left = intersection.boundingRect().left();
    if (x <= left)
    {
        return QPointF(left, y);
    }
    auto right = intersection.boundingRect().right();
    return QPointF(right, y);
//    QPointF point(_realPoints.value(y).x(), y);
//    return point;
}

RelationCurveNotationLinkItem *StageDischargeRelationCurveItem::getNotationLinkItem() const
{
    return _notationLinkItem;
}

void StageDischargeRelationCurveItem::setNotationLinkItem(RelationCurveNotationLinkItem *notationLinkItem)
{
    _notationLinkItem = notationLinkItem;
}

RelationCurveNotationItem *StageDischargeRelationCurveItem::getNotationItem() const
{
    return _notationItem;
}

void StageDischargeRelationCurveItem::setNotationItem(RelationCurveNotationItem *notationItem)
{
    _notationItem = notationItem;
}

int StageDischargeRelationCurveItem::getPlottingMethod() const
{
    return _plottingMethod;
}

void StageDischargeRelationCurveItem::setPlottingMethod(int plottingMethod)
{
    _plottingMethod = plottingMethod;
}

void StageDischargeRelationCurveItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
//    auto effect = new QGraphicsOpacityEffect;
//    effect->setStrength(0.5);
//    this->setGraphicsEffect(effect);
}

void StageDischargeRelationCurveItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
//    this->setGraphicsEffect(nullptr);
}

QVariant StageDischargeRelationCurveItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemSelectedHasChanged) {
        if (this->isSelected()) {
            if (_notationItem) {
                _notationItem->setZValue(10000001);
            }
        } else {
            if (_notationItem) {
                _notationItem->setZValue(1000);
            }
        }
    }
    return QGraphicsItem::itemChange(change, value);
}

QPainterPath StageDischargeRelationCurveItem::shape() const
{
    return _allPath;
}

QPointF StageDischargeRelationCurveItem::reversePoint(const QPointF &point) const
{
    return QPointF(-point.y(), point.x());
}

qreal StageDischargeRelationCurveItem::getMaxDischarge() const
{
    return _maxDischarge;
}

void StageDischargeRelationCurveItem::setMaxDischarge(const qreal &maxDischarge)
{
    _maxDischarge = maxDischarge;
}

qreal StageDischargeRelationCurveItem::getMinDischarge() const
{
    return _minDischarge;
}

void StageDischargeRelationCurveItem::setMinDischarge(const qreal &minDischarge)
{
    _minDischarge = minDischarge;
}

qreal StageDischargeRelationCurveItem::getMaxStage() const
{
    return _maxStage;
}

void StageDischargeRelationCurveItem::setMaxStage(const qreal &maxStage)
{
    _maxStage = maxStage;
}

qreal StageDischargeRelationCurveItem::getMinStage() const
{
    return _minStage;
}

void StageDischargeRelationCurveItem::setMinStage(const qreal &minStage)
{
    _minStage = minStage;
}


QColor StageDischargeRelationCurveItem::color() const
{
    return _color;
}

void StageDischargeRelationCurveItem::setColor(const QColor &color)
{
    _color = color;
}

VChart *StageDischargeRelationCurveItem::pChart() const
{
    return _pChart;
}

void StageDischargeRelationCurveItem::setPChart(VChart *pChart)
{
    _pChart = pChart;
}

QPointF StageDischargeRelationCurveItem::getPoint(qreal stage, qreal discharge) const
{
    if (_pChart != nullptr)
    {
        qreal x = discharge*_pChart->xUnitLength() + _pChart->xOffset();
        qreal y = stage*_pChart->yUnitLength() + _pChart->yOffset();
        y = _pChart->geometry().height() - y;
        return QPointF(x, y);
    }
    return QPointF();
}

QRectF StageDischargeRelationCurveItem::boundingRect() const
{
    QRectF rect;
    rect.setTopRight(getPoint(_maxStage, _maxDischarge));
    rect.setBottomLeft(getPoint(_minStage, _minDischarge));
    return rect;
}

void StageDischargeRelationCurveItem::paint(
        QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(_color);
    if (this->isSelected())
    {
        painter->setPen(QPen(_color, 1.5));
    }
    else
    {
        painter->setPen(QPen(_color, 1));
    }
    if (_curveType == 1)
    {
        painter->setPen(_color);
        _painterPathes.clear();
        bool first = true;
        QPainterPath path;
        for (auto const &n : _curve.nodes)
        {
            auto point = getPoint(n.x.toDouble(), n.y.toDouble());
            if (first)
            {
                path.moveTo(point);
                first = false;
            }
            else
            {
                path.lineTo(point);
            }
            painter->drawEllipse(point, 1.f, 1.f);
        }
        painter->drawPath(path);
        _allPath = path;
        return;
    }
    QPointF prevPoint;
    _realPoints.clear();
    _polygons.clear();
    _painterPathes.clear();
    QVector<QPointF> reversedPoints;
    QVector<QPointF> originalPoints;
    int pointIndex = 1;
    painter->setFont(QFont(DEFAULT_NUMERIAL_FONTFAMILTY, 9));
    for (auto const &n : _curve.nodes)
    {
        auto discharge = n.x.toDouble();
        auto stage = n.y.toDouble();
        QPointF point = getPoint(stage, discharge);
        painter->drawEllipse(point, 1.f, 1.f);
        painter->drawText(point, QString("%1").arg(pointIndex));
        originalPoints.push_back(point);
        reversedPoints.push_back(reversePoint(point));
        pointIndex++;
    }

    auto rx = reversedPoints.front().x();
    auto rxLast = reversedPoints.back().x();

    if (_plottingMethod == METHOD_BEZIER_Q)
    {

        auto n = originalPoints.size();
        int i = 0;
        if (n > 0)
        {
            while (i + 2 < n)
            {
                QPainterPath path;
                auto startPoint = originalPoints[i];
                auto midPoint = originalPoints[i + 1];
                auto endPoint = originalPoints[i + 2];
                path.moveTo(startPoint);
                auto controlPoint = MathHelper::QBCCP(startPoint, midPoint, endPoint);
                path.quadTo(controlPoint, endPoint);
                _polygons.append(path.toFillPolygon());
                _painterPathes.append(path);
                painter->drawEllipse(controlPoint, 2.f, 2.f);
                painter->drawPath(path);
                ++i;
            }
        }

    //    QPolygonF outerPolygon;
    //    for (auto polygon: _polygons)
    //    {
    //        outerPolygon = outerPolygon.united(polygon);
    //    }
    //    painter->drawPolygon(outerPolygon);
    //    _outerPolygon = outerPolygon;

        QPainterPath allPath;
        for (auto path: _painterPathes)
        {
            allPath = allPath.united(path);
        }
    //    painter->drawPath(allPath);
        _allPath = allPath;
    }
    else if (_plottingMethod == METHOD_PLPI_TPA)
    {
        auto inc = 1;
        {
            prevPoint = QPointF(MathHelper::PLPI_TPA(reversedPoints, rx), -rx);
            _realPoints.insert(-rx, prevPoint);
            rx += inc;
        }
        QPainterPath path;
        bool first = true;
        while (rx < rxLast + inc)
        {
            QPointF point(MathHelper::PLPI_TPA(reversedPoints, rx), -rx);
            if (first)
            {
                path.moveTo(prevPoint);
            }
            first = false;
            path.lineTo(point);
            rx += inc;
            prevPoint = point;
            _realPoints.insert(-rx, point);
        }
        painter->drawPath(path);
        _allPath = path;
    }
    else if (_plottingMethod == METHOD_PLPI_LWS)
    {
        auto inc = 1;
        {
            prevPoint = QPointF(MathHelper::PLPI_LWS(reversedPoints, rx), -rx);
            _realPoints.insert(-rx, prevPoint);
            rx += inc;
        }
        QPainterPath path;
        bool first = true;
        while (rx < rxLast + inc)
        {
            QPointF point(MathHelper::PLPI_LWS(reversedPoints, rx), -rx);
            if (first)
            {
                path.moveTo(prevPoint);
            }
            first = false;
            path.lineTo(point);
            rx += inc;
            prevPoint = point;
            _realPoints.insert(-rx, point);
        }
        painter->drawPath(path);
        _allPath = path;
    }
    else if (_plottingMethod == METHOD_PLPI_MPS)
    {
        auto inc = 1;
        {
            prevPoint = QPointF(MathHelper::PLPI_MPS(reversedPoints, rx), -rx);
            _realPoints.insert(-rx, prevPoint);
            rx += inc;
        }
        QPainterPath path;
        bool first = true;
        while (rx < rxLast + inc)
        {
            QPointF point(MathHelper::PLPI_MPS(reversedPoints, rx), -rx);
            if (first)
            {
                path.moveTo(prevPoint);
            }
            first = false;
            path.lineTo(point);
            rx += inc;
            prevPoint = point;
            _realPoints.insert(-rx, point);
        }
        painter->drawPath(path);
        _allPath = path;
    }
    else if (_plottingMethod == METHOD_PLPI_AMP)
    {
        auto n = originalPoints.size();
        int i = 0;
        if (n > 2)
        {
            QVector<QPointF> addedPoints;
            for (auto j = 0; j < n - 1; ++j)
            {
                auto x = (reversedPoints[j].x() + reversedPoints[j + 1].x()) / 2; // stage
                auto addPoint = QPointF(MathHelper::PLPI_MPS(reversedPoints, x), -x);
                addedPoints.push_back(addPoint);
            }
            while (i + 2 < n)
            {
                QPainterPath path;
                auto startPoint = addedPoints[i];
                if (i == 0)
                {
                    startPoint = originalPoints[i];
                }
                auto midPoint = originalPoints[i + 1];
                auto endPoint = addedPoints[i + 1];
                if (i == n - 3)
                {
                    endPoint = originalPoints[i + 2];
                }
                path.moveTo(startPoint);
                auto controlPoint = MathHelper::QBCCP(startPoint, midPoint, endPoint, .5f);
                path.quadTo(controlPoint, endPoint);
                _polygons.append(path.toFillPolygon());
                _painterPathes.append(path);
                painter->drawEllipse(controlPoint, 2.f, 2.f);
                painter->drawPath(path);
                ++i;
            }
        }
    }
    else if (_plottingMethod == METHOD_LPI)
    {
        auto inc = 1;
        {
            prevPoint = QPointF(MathHelper::LPI(reversedPoints, rx), -rx);
            _realPoints.insert(-rx, prevPoint);
            rx += inc;
        }
        QPainterPath path;
        bool first = true;
        while (rx < rxLast + inc)
        {
            QPointF point(MathHelper::LPI(reversedPoints, rx), -rx);
            if (first)
            {
                path.moveTo(prevPoint);
            }
            first = false;
            path.lineTo(point);
            rx += inc;
            prevPoint = point;
            _realPoints.insert(-rx, point);
        }
        painter->drawPath(path);
        _allPath = path;
    }
}
