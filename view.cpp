#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#include "view.h"
//include "../graphics/verticaltextitem.h"

View::View(QWidget *parent)
    : QGraphicsView(new QGraphicsScene(), parent)
{
    initialize();
}

View::View(VChart *chart, QWidget *parent)
    : QGraphicsView(new QGraphicsScene(), parent)
{
    initialize();

//    scene()->setSceneRect(0, 0, 790, 540);


//    {
//        QGraphicsTextItem *gti1 = new QGraphicsTextItem;
////        gti1->setBoundingRect(10, 20 - 5, 10, 100);
//        gti1->setPos(10, 20);
//        gti1->setTextWidth(10);
////        gti1->setText(tr("水位 Z (m)"));
//        gti1->setHtml(tr("水位</td><td>Z (m)</td></tr>"));
//        scene()->addItem(gti1);
//    }

//    {
//        QGraphicsTextItem *gti2 = new QGraphicsTextItem;
////        gti2->setBoundingRect(10, 480/3 + 20 + 10 - 5, 10, 100);
//        gti2->setPos(10, 480/3 + 20 + 10 - 5);
//        gti2->setTextWidth(10);
//        gti2->setHtml(tr("流量<br>Q (m³/s)"));
//        scene()->addItem(gti2);
//    }

//    {
//        QGraphicsTextItem *gti3 = new QGraphicsTextItem;
////        gti3->setBoundingRect(10, 480/3*2 + 20 + 10*2 - 5, 10, 100);
//        gti3->setPos(10, 480/3*2 + 20 + 10*2 - 5);
//        gti3->setTextWidth(10);
//        gti3->setHtml(tr("含沙量<br>SQ (kg/m³)"));
//        scene()->addItem(gti3);
//    }

//    {
//        VerticalTextItem *vti = new VerticalTextItem;
//        vti->setBoundingRect(770, 20, 10, 500);
//        vti->setText(tr("水位流量含沙量过程线"));
//        scene()->addItem(vti);
//    }

//    for (int i = 20; i < 745 + 20; i += 6)
//    {
//        QGraphicsTextItem *gtii = new QGraphicsTextItem;
//        gtii->setPos(i, 480/3*3 + 20 + 5);
////        gtii->setTextWidth(2);
//        gtii->setHtml(tr("%1").arg((i - 20)%24));
//        scene()->addItem(gtii);
//    }

//    for (int i = 20; i < 744 + 20; i += 24)
//    {
//        QGraphicsTextItem *gtii = new QGraphicsTextItem;
//        gtii->setPos(i + 12, 480/3*3 + 20 + 10);
//        gtii->setHtml(tr("%1").arg((i - 20)/24 + 1));
//        scene()->addItem(gtii);
//    }

//    VChart *vchart = new VChart();
//    vchart->setPos(20, 20);
//    scene()->addItem(vchart);

    _chart = chart;
    if (scene())
    {
        scene()->addItem(chart);
    }
}

void View::zoomToFit()
{
    fitInView(scene()->sceneRect());
}

void View::resizeEvent(QResizeEvent *event)
{
    if (scene() && _chart != nullptr) {
        scene()->setSceneRect(QRect(QPoint(0, 0), event->size()));
//        fitInView(scene()->sceneRect());//, Qt::KeepAspectRatio);
         _chart->resize(event->size());
//         m_coordX->setPos(m_chart->size().width()/2 - 50, m_chart->size().height() - 20);
//         m_coordY->setPos(m_chart->size().width()/2 + 50, m_chart->size().height() - 20);
    }
    QGraphicsView::resizeEvent(event);
}

void View::initialize()
{
    setMouseTracking(true);
    setRenderHint(QPainter::Antialiasing);
//    setCursor(Qt::IBeamCursor);
}

VChart *View::chart() const
{
    return _chart;
}

void View::setChart(VChart *chart)
{
    _chart = chart;
}

void View::mouseMoveEvent(QMouseEvent *event)
{
//    qDebug() << e->pos();
    if (event->buttons() & Qt::LeftButton)
    {

    }
    Q_EMIT mouseMovePosX(event->x());
    Q_EMIT mouseMovePosY(event->y());
    QGraphicsView::mouseMoveEvent(event);
}

void View::enterEvent(QEvent *event)
{
    QGraphicsView::enterEvent(event);
}

void View::leaveEvent(QEvent *event)
{
    // do not show the line when mouse left
    Q_EMIT mouseMovePosX(-1);
    Q_EMIT mouseMovePosY(-1);
    QGraphicsView::leaveEvent(event);
}
