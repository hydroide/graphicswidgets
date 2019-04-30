#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#ifndef VIEW_H
#define VIEW_H

#include <QtGui>
#include <QtWidgets>

#include "vchart.h"

#include "processxaxis.h"
#include "processyaxis.h"
#include "processxaxiswidget.h"
#include "processyaxiswidget.h"

#include "vchart.h"
#include "stagechart.h"
#include "dischargechart.h"
#include "sedimentchart.h"
#include "relationchart.h"
#include "crosssectionchart.h"

#include "relationchartperiodtableitem.h"
#include "dischargemeasurementpointitem.h"
#include "stagedischargerelationcurveitem.h"
#include "relationcurvenotationitem.h"
#include "relationcurvenotationlinkitem.h"
#include "processpointitem.h"

class View : public QGraphicsView
{
    Q_OBJECT
public:
    explicit View(QWidget *parent = nullptr);
    explicit View(VChart *chart, QWidget *parent = nullptr);

    void zoomToFit();

    VChart *chart() const;
    void setChart(VChart *chart);

protected:
    void resizeEvent(QResizeEvent *event);
    void initialize();

    VChart *_chart = nullptr;

Q_SIGNALS:
    void mouseMovePosX(int posX);
    void mouseMovePosY(int posY);

    // QWidget interface
protected:
    void mouseMoveEvent(QMouseEvent *);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
};

#endif // VIEW_H
