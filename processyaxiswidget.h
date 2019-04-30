#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#ifndef PROCESSYAXISWIDGET_H
#define PROCESSYAXISWIDGET_H

#include <QtWidgets>

class ProcessYAxisWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ProcessYAxisWidget(QWidget *parent = nullptr);
    ~ProcessYAxisWidget();

public Q_SLOTS:
    void mouseMovePosY(int posY);
    void unitChange(qreal min, qreal max, qreal unit);

private:
    int _latestMousePosY{-1};
    qreal _min;
    qreal _max;
    qreal _unit;

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
};

#endif // PROCESSYAXISWIDGET_H
