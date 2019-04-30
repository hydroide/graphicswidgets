#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#ifndef VCHART_H
#define VCHART_H

#include <QtCore>
#include <QtGui>
#include <QtWidgets>

class VChart : public QGraphicsWidget
{
    Q_OBJECT
public:
    explicit VChart(QGraphicsItem *parent = nullptr);

    qreal xUnitLength();
    qreal yUnitLength();
    qreal xOffset();
    qreal yOffset();

protected:
    qreal _xUnitLength;
    qreal _yUnitLength;
    qreal _xOffset;
    qreal _yOffset;

    // QGraphicsItem interface
public:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // VCHART_H
