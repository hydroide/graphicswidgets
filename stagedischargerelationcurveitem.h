#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#ifndef STAGEDISCHARGERELATIONCURVEITEM_H
#define STAGEDISCHARGERELATIONCURVEITEM_H

#include <QtCore>
#include <QtGui>
#include <QtWidgets>

#include "globaldefines.h"
#include "modules/curvestructs.h"
#include "vchart.h"

class RelationCurveNotationItem;

class RelationCurveNotationLinkItem;

class StageDischargeRelationCurveItem : public QGraphicsItem
{
public:
    StageDischargeRelationCurveItem(QGraphicsItem *parent = nullptr, int curveType = 0);

    VChart *pChart() const;
    void setPChart(VChart *pChart);
    QColor color() const;
    void setColor(const QColor &color);
    RelationCurve curve() const;
    void setCurve(const RelationCurve &curve);

    QPointF getLinePoint(qreal x, qreal y);

protected:
    int _curveType{0};
    VChart *_pChart;
    QColor _color;
    RelationCurve _curve;
    qreal _minStage;
    qreal _maxStage;
    qreal _minDischarge;
    qreal _maxDischarge;
    QMap<int, QPointF> _realPoints;
    QList<QPolygonF> _polygons;
    QList<QPainterPath> _painterPathes;
    QPolygonF _outerPolygon;
    QPainterPath _allPath;
    int _plottingMethod;
    RelationCurveNotationItem *_notationItem{nullptr};
    RelationCurveNotationLinkItem *_notationLinkItem{nullptr};

    QPointF getPointFromCurveNode(const RelationCurveNode &n) const;
    QPointF reversePoint(const QPointF &point) const;
    QPointF getPoint(qreal stage, qreal discharge) const;
    QSizeF getSizeF();

    // QGraphicsItem interface
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);


    qreal getMinStage() const;
    void setMinStage(const qreal &minStage);
    qreal getMaxStage() const;
    void setMaxStage(const qreal &maxStage);
    qreal getMinDischarge() const;
    void setMinDischarge(const qreal &minDischarge);
    qreal getMaxDischarge() const;
    void setMaxDischarge(const qreal &maxDischarge);
    int getPlottingMethod() const;
    void setPlottingMethod(int plottingMethod);

    RelationCurveNotationItem *getNotationItem() const;
    void setNotationItem(RelationCurveNotationItem *notationItem);

    RelationCurveNotationLinkItem *getNotationLinkItem() const;
    void setNotationLinkItem(RelationCurveNotationLinkItem *notationLinkItem);

protected:
    // QGraphicsItem interface
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    QPainterPath shape() const;
};

#endif // STAGEDISCHARGERELATIONCURVEITEM_H
