#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#ifndef PROCESSCHART_H
#define PROCESSCHART_H

#include "vchart.h"
#include "models/processseries.h"
//#include "models/processpoints.h"

class ProcessChart : public VChart
{
    Q_OBJECT
public:
    explicit ProcessChart(QGraphicsItem *parent = nullptr);

    QDateTime startDateTime() const;
    void setStartDateTime(const QDateTime &startDateTime);

    QDateTime endDateTime() const;
    void setEndDateTime(const QDateTime &endDateTime);

    QStringList stcds() const;

    virtual QString drawType() const = 0;

    virtual void addSeries(SpProcessSeries series);
    virtual void addSeries(QString stcd, SpProcessSeries series);
    virtual void removeSeries(QString stcd);
    virtual void clearSeries();

    void updateUnits();

protected:
    virtual ProcessMap &currentMap(SpProcessSeries series);

    virtual void paintSeries(QPainter *painter);
    virtual void paintPoints(QPainter *painter);

//    QList<SpProcessSeries> _seriesList;
    QMap<QString, SpProcessSeries> _seriesMap;
//    QList<ProcessPoints> _lProcessPoints;

private:
    QDateTime _startDateTime;
    QDateTime _endDateTime;
    double _maxY{0};
    double _minY{0};
    qreal hourFromPosX(qreal posX);
    qreal posXFromHour(qreal hour);
    qreal _startHour{-1};
    qreal _endHour{-1};

public Q_SLOTS:
    void changeSelection(qreal startHour, qreal endHour);

Q_SIGNALS:
    void selectionChanging(qreal startHour, qreal _endHour);
    void selectionChanged(qreal startHour, qreal _endHour);
    void yUnitChanged(qreal min, qreal max, qreal unitLength);

    // QGraphicsItem interface
public:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);


    // QGraphicsWidget interface
protected:
    void resizeEvent(QGraphicsSceneResizeEvent *event);

    // QGraphicsItem interface
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
};

#endif // PROCESSCHART_H
