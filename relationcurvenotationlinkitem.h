#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#ifndef RELATIONCURVENOTATIONLINKITEM_H
#define RELATIONCURVENOTATIONLINKITEM_H

#include <QtCore>
#include <QtGui>
#include <QtWidgets>

#include "hcglobaldefs.h"
#include "relationcurvenotationitem.h"

class RelationCurveNotationLinkItem : public QGraphicsLineItem
{
    // QGraphicsItem interface
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public:
    RelationCurveNotationLinkItem(QGraphicsItem *parent);

    void updatePosition();

    QColor color() const;
    void setColor(const QColor &color);

    qreal penWidth() const;
    void setPenWidth(const qreal &penWidth);

    RelationCurveNotationItem *notationItem() const;
    void setNotationItem(RelationCurveNotationItem *notationItem);

protected:
    QColor _color;
    qreal _penWidth;

    RelationCurveNotationItem *_notationItem;
};

#endif // RELATIONCURVENOTATIONLINKITEM_H
