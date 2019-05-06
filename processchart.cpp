#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#include "processchart.h"

#include "hcglobaldefs.h"

ProcessChart::ProcessChart(QGraphicsItem *parent)
    : VChart(parent)
{

}

QDateTime ProcessChart::startDateTime() const
{
    return _startDateTime;
}

void ProcessChart::setStartDateTime(const QDateTime &startDateTime)
{
    _startDateTime = startDateTime;
    for (auto series: _seriesMap)
    {
        if (startDateTime < series->startDateTime() || startDateTime > series->endDateTime())
        {
            series->setStartDateTime(startDateTime);
            this->updateData();
        }
    }
    update();
}

QDateTime ProcessChart::endDateTime() const
{
    return _endDateTime;
}

void ProcessChart::setEndDateTime(const QDateTime &endDateTime)
{
    _endDateTime = endDateTime;
    for (auto series: _seriesMap)
    {
        if (endDateTime < series->startDateTime() || endDateTime > series->endDateTime())
        {
            series->setEndDateTime(endDateTime);
            this->updateData();
        }
    }
    update();
}

QStringList ProcessChart::stcds() const
{
    QStringList list;
    for (auto series: _seriesMap)
    {
        if (!list.contains(series->stcd()))
        {
            list.append(series->stcd());
        }
    }
    return list;
}

void ProcessChart::addSeries(SpProcessSeries series)
{
//    series->setDrawType(drawType());

//    series->generateMap();
//    _seriesList.append(series);
//    prepareGeometryChange();
//    update();
}


void ProcessChart::addSeries(QString stcd, SpProcessSeries series)
{
    if (!stcd.isEmpty())
    {
        _seriesMap[stcd] = series;
    }
//    update();
}

void ProcessChart::removeSeries(QString stcd)
{
    if (!stcd.isEmpty())
    {
        _seriesMap.remove(stcd);
    }
//    update();
}

void ProcessChart::clearSeries()
{
    _seriesMap.clear();
}

void ProcessChart::updateUnits()
{
    auto totalHours = (qreal)(endDateTime().toMSecsSinceEpoch()
                               - startDateTime().toMSecsSinceEpoch())
            /INT_MSECS_PER_HOURS;
    _xUnitLength = this->geometry().width()/totalHours;
    _xOffset = -startDateTime().toMSecsSinceEpoch()/INT_MSECS_PER_HOURS*_xUnitLength;

    _maxY = -std::numeric_limits<double>::infinity();
    _minY = std::numeric_limits<double>::infinity();
    for (auto &series : _seriesMap)
    {
        auto max = currentMap(series).maxValue().toDouble();
        if (max > _maxY)
        {
            _maxY = max;
        }
        auto min = currentMap(series).minValue().toDouble();
        if (min < _minY)
        {
            _minY = min;
        }
    }

    auto range = _maxY - _minY;

    _yUnitLength = this->geometry().height()/range;
    _yOffset = -_minY*_yUnitLength;
    Q_EMIT this->yUnitChanged(_minY, _maxY, _yUnitLength);
}

ProcessMap &ProcessChart::currentMap(SpProcessSeries series)
{
    return series->mStages();
}

void ProcessChart::paintSeries(QPainter *painter)
{
    updateUnits();
    for (auto series : _seriesMap)
    {
        QPointF lastDrawPoint;
        int i = 0;
        painter->setPen(series->lineColor());
        auto data = currentMap(series).data();
        auto drawPoint = [&] (const QDateTime &key) {
            qreal val = data.value(key).toDouble();
            auto hours = (qreal)(key.toMSecsSinceEpoch()
                                 - startDateTime().toMSecsSinceEpoch())
                    /INT_MSECS_PER_HOURS;
            auto units = _maxY - val;
            QPointF point(hours*_xUnitLength, units*_yUnitLength);
            painter->drawEllipse(point, 1.f, 1.f);
            if (i != 0)
            {
                painter->drawLine(lastDrawPoint, point);
            }
            lastDrawPoint = point;
            i++;
        };

        for (auto key : data.keys())
        {
            // draw one more days
            if (key < _startDateTime.addMSecs(-24*INT_MSECS_PER_HOURS)
                || key > _endDateTime.addMSecs(24*INT_MSECS_PER_HOURS))
            {
                continue;
            }
            drawPoint(key);
        }
    }
}

void ProcessChart::paintPoints(QPainter *painter)
{

}

qreal ProcessChart::hourFromPosX(qreal posX)
{
    if (_xUnitLength > 0)
    {
        return _startDateTime.toMSecsSinceEpoch()/INT_MSECS_PER_HOURS +
                posX/_xUnitLength;
    }
    return 0;
}

qreal ProcessChart::posXFromHour(qreal hour)
{
    return (hour -
            _startDateTime.toMSecsSinceEpoch()/INT_MSECS_PER_HOURS) *
            _xUnitLength;
}

void ProcessChart::changeSelection(qreal startHour, qreal endHour)
{
    bool changed = false;
    if (_startHour != startHour)
    {
        _startHour = startHour;
        changed = true;
    }
    if (_endHour != endHour)
    {
        _endHour = endHour;
        changed = true;
    }
    if (changed)
    {
        this->update();
    }
}

void ProcessChart::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//    if (_startDateTime.isValid())
//    {
//        painter->drawText(0, option->fontMetrics.height()*2,
//                          tr("起始时间：%1").arg(_startDateTime.toString("yyyy-MM-dd hh:mm")));
//    }
//    if (_endDateTime.isValid())
//    {
//        painter->drawText(0, option->fontMetrics.height()*3,
//                          tr("结束时间：%1").arg(_endDateTime.toString("yyyy-MM-dd hh:mm")));
//    }

    // paint selection
    if (_startHour > -1 && _endHour > 1)
    {
        auto bkpBrush = painter->brush();
        auto bkpPen = painter->pen();
        painter->setBrush(QBrush(QColor(255, 255, 0, 128)));
        painter->setPen(Qt::NoPen);
        auto startX = posXFromHour(_startHour);
        auto endX = posXFromHour(_endHour);
        painter->drawRect(QRectF(QPointF(startX, 0),
                                 QPointF(endX, this->boundingRect().height())));
        painter->setBrush(bkpBrush);
        painter->setPen(bkpPen);
    }
    VChart::paint(painter, option, widget);
}


void ProcessChart::resizeEvent(QGraphicsSceneResizeEvent *event)
{
    update();
}

void ProcessChart::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        if (_startHour != -1 && _endHour != -1) // undo selection
        {
            _startHour = -1;
            _endHour = -1;
        }
        else
        {
            _startHour = hourFromPosX(event->pos().x());
        }
        this->update();
    }

    // comment out following when item is not selectable or movable,
    // or item will not receive further mouseMoveEvent or mouseReleaseEvent
//    VChart::mousePressEvent(event);
}

void ProcessChart::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        if (_startHour != -1)
        {
            _endHour = hourFromPosX(event->pos().x());
        }
        Q_EMIT this->selectionChanging(_startHour, _endHour);
        this->update();
    }
//    VChart::mouseMoveEvent(event);
}

void ProcessChart::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    // if start end equals do not regard as selection
    if (_startHour == _endHour)
    {
        _startHour = -1;
        _endHour = -1;
    }
    Q_EMIT this->selectionChanged(_startHour, _endHour);
    this->update();
    //    VChart::mousePressEvent(event);
}

void ProcessChart::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    auto hour = hourFromPosX(event->pos().x());
    if (hour >= _startHour && hour <= _endHour)
    {
        QMenu menu;
        menu.addAction(tr("选中"), []() {

        });
        menu.exec(event->screenPos());
        return;
    }
    VChart::contextMenuEvent(event);
}
