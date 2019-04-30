#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#ifndef PROCESSPOINTITEM_H
#define PROCESSPOINTITEM_H

#include <QtCore>
#include <QtGui>
#include <QtWidgets>

#include "globaldefines.h"
#include "vchart.h"

class ProcessPointItem : public QGraphicsItem
{
    // QGraphicsItem interface
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public:
    ProcessPointItem(QGraphicsItem *parent = nullptr);
    QPointF getPoint() const;

    QString value() const;
    void setValue(const QString &value);

    QDateTime dateTime() const;
    void setDateTime(const QDateTime &dateTime);

    VChart *pChart() const;
    void setPChart(VChart *pChart);

    QString text() const;
    void setText(const QString &text);

protected:
    VChart *_pChart;
    QString _value;
    QString _text;
    QDateTime _dateTime;


};

#endif // PROCESSPOINTITEM_H
