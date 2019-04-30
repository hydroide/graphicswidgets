#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#include "relationcurvenotationlinkitem.h"

#include "stagedischargerelationcurveitem.h"

RelationCurveNotationLinkItem::RelationCurveNotationLinkItem(QGraphicsItem *parent)
    : QGraphicsLineItem(parent)
{
    auto relationCurve = qgraphicsitem_cast<StageDischargeRelationCurveItem *>(parent);
    if (relationCurve) {
        relationCurve->setNotationLinkItem(this);
    }
}

void RelationCurveNotationLinkItem::updatePosition()
{
    QLineF line;
    auto p1 = _notationItem->sceneBoundingRect().center();
    line.setP1(p1);
    auto *parent = qgraphicsitem_cast<StageDischargeRelationCurveItem *>(this->parentItem());
    if (parent != nullptr)
    {
        auto p2 = parent->getLinePoint(p1.x(), p1.y());
//        if (p1.x() > p2.x())
//        {
//            line.setP1(QPointF(_notationItem->sceneBoundingRect().left(), p2.y()));
//        }
//        else
//        {
//            line.setP1(QPointF(_notationItem->sceneBoundingRect().right(), p2.y()));
//        }
        line.setP2(p2);
    }
    else
    {
        line.setP2(line.p1());
    }
    setLine(line);
}

QColor RelationCurveNotationLinkItem::color() const
{
    return _color;
}

void RelationCurveNotationLinkItem::setColor(const QColor &color)
{
    _color = color;
}

qreal RelationCurveNotationLinkItem::penWidth() const
{
    return _penWidth;
}

void RelationCurveNotationLinkItem::setPenWidth(const qreal &penWidth)
{
    _penWidth = penWidth;
}
RelationCurveNotationItem *RelationCurveNotationLinkItem::notationItem() const
{
    return _notationItem;
}

void RelationCurveNotationLinkItem::setNotationItem(RelationCurveNotationItem *notationItem)
{
    _notationItem = notationItem;
}


QRectF RelationCurveNotationLinkItem::boundingRect() const
{
    return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
                                      line().p2().y() - line().p1().y()))
            .normalized();
}

void RelationCurveNotationLinkItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    updatePosition();
    painter->setPen(QPen(QBrush(_color), _penWidth, Qt::DotLine));
    painter->drawLine(line());
}
