#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#include "vchart.h"

VChart::VChart(QGraphicsItem *parent)
    : QGraphicsWidget(parent)
{
}

qreal VChart::xUnitLength()
{
    return _xUnitLength;
}

qreal VChart::yUnitLength()
{
    return _yUnitLength;
}

qreal VChart::xOffset()
{
    return _xOffset;
}

qreal VChart::yOffset()
{
    return _yOffset;
}


void VChart::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
}
