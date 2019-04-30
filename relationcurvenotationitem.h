#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#ifndef RELATIONCURVENOTATIONITEM_H
#define RELATIONCURVENOTATIONITEM_H

#include <QtCore>
#include <QtGui>
#include <QtWidgets>

#include "globaldefines.h"
#include "vchart.h"

class RelationCurveNotationLinkItem;

class RelationCurveNotationItem : public QGraphicsItem
{
    // QGraphicsItem interface
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    // QGraphicsItem interface
protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

public:
    RelationCurveNotationItem(QGraphicsItem *parent);

    qreal diameter() const;
    void setDiameter(const qreal &diameter);
    qreal penWidth() const;
    void setPenWidth(const qreal &penWidth);
    QPointF ratioPair() const;
    void setRatioPair(const QPointF &ratioPair);
    QColor color() const;
    void setColor(const QColor &color);
    int getYear() const;
    void setYear(int year);
    int curve_id() const;
    void set_curve_id(int curve_id);

    QPointF getTopLeft() const;

    RelationCurveNotationLinkItem *getLinkItem() const;
    void setLinkItem(RelationCurveNotationLinkItem *value);

protected:
    qreal _diameter;
    qreal _penWidth;
    QPointF _ratioPair;
    QColor _color;
    int _year;
    int _curve_id;

    RelationCurveNotationLinkItem *_linkItem;

};

#endif // RELATIONCURVENOTATIONITEM_H
