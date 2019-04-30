#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#include "relationcurvenotationitem.h"

#include "relationcurvenotationlinkitem.h"

#include "stagedischargerelationcurveitem.h"

RelationCurveNotationItem::RelationCurveNotationItem(QGraphicsItem *parent)
    : QGraphicsItem(parent)
{
    _ratioPair.setX(qrand()%100/100./2);
    _ratioPair.setY(qrand()%100/100./2);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    this->setZValue(100);
    auto relationCurve = qgraphicsitem_cast<StageDischargeRelationCurveItem *>(parent);
    if (relationCurve) {
        relationCurve->setNotationItem(this);
    }
}
QColor RelationCurveNotationItem::color() const
{
    return _color;
}

void RelationCurveNotationItem::setColor(const QColor &color)
{
    _color = color;
}
int RelationCurveNotationItem::curve_id() const
{
    return _curve_id;
}

void RelationCurveNotationItem::set_curve_id(int curve_id)
{
    _curve_id = curve_id;
}

QPointF RelationCurveNotationItem::getTopLeft() const
{
    if (this->parentItem() != nullptr)
    {
        auto rect = this->parentItem()->boundingRect();
        auto x = rect.width()*_ratioPair.x();
        auto y = rect.height()*_ratioPair.y();
        if (_curve_id % 2 == 0)
        {
            return rect.bottomRight() - QPointF(x, y);
        }
        return rect.topLeft() + QPointF(x, y);
    }
    return QPointF();
}
RelationCurveNotationLinkItem *RelationCurveNotationItem::getLinkItem() const
{
    return _linkItem;
}

void RelationCurveNotationItem::setLinkItem(RelationCurveNotationLinkItem *value)
{
    _linkItem = value;
}

int RelationCurveNotationItem::getYear() const
{
    return _year;
}

void RelationCurveNotationItem::setYear(int year)
{
    _year = year;
}



QPointF RelationCurveNotationItem::ratioPair() const
{
    return _ratioPair;
}

void RelationCurveNotationItem::setRatioPair(const QPointF &ratioPair)
{
    _ratioPair = ratioPair;
}

qreal RelationCurveNotationItem::penWidth() const
{
    return _penWidth;
}

void RelationCurveNotationItem::setPenWidth(const qreal &penWidth)
{
    _penWidth = penWidth;
}

qreal RelationCurveNotationItem::diameter() const
{
    return _diameter;
}

void RelationCurveNotationItem::setDiameter(const qreal &diameter)
{
    _diameter = diameter;
}

QRectF RelationCurveNotationItem::boundingRect() const
{
    return QRectF(getTopLeft(), QSizeF(_diameter, _diameter));
}

void RelationCurveNotationItem::paint(
        QPainter *painter, const QStyleOptionGraphicsItem *option,
        QWidget *widget)
{
    painter->setPen(QPen(QBrush(_color), _penWidth, Qt::DotLine));
    painter->setBrush(Qt::white);
    painter->drawEllipse(boundingRect());

    auto rect = QRectF(getTopLeft(), QSizeF(_diameter, diameter()*.6));

    auto font = painter->font();
    font.setFamily("Arial");
    font.setBold(true);
    painter->setFont(font);
    painter->drawText(rect, Qt::AlignCenter | Qt::AlignBottom,
                      QString("%1").arg(_curve_id));

    rect.setTop(rect.bottom());
    rect.setHeight(diameter()*.3);
    font.setPointSizeF(font.pointSizeF()*.6);
    painter->setFont(font);
    painter->drawText(rect, Qt::AlignCenter | Qt::AlignTop,
                      QString("%1").arg(_year));

    this->parentItem()->update();
}

QVariant RelationCurveNotationItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionChange)
    {
        if (_linkItem)
        {
            _linkItem->updatePosition();
        }
    }
    return value;
}

