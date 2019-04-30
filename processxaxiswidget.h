#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#ifndef PROCESSXAXISWIDGET_H
#define PROCESSXAXISWIDGET_H

#include <QtCore>
#include <QtWidgets>

#include "globaldefines.h"

class ProcessXAxisWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ProcessXAxisWidget(QWidget *parent = nullptr);
    enum DisplayFlag {
        DisplayDay = 0x0001,
        DisplayMonth = 0x0002,
        DisplayYear = 0x0004,
        DisplayAll = DisplayDay | DisplayMonth | DisplayYear,
    };

    QDateTime startDateTime() const;
    void setStartDateTime(const QDateTime &startDateTime);

    QDateTime endDateTime() const;
    void setEndDateTime(const QDateTime &endDateTime);

    QDateTime viewStartDateTime() const;
    void setViewStartDateTime(const QDateTime &viewStartDateTime);

    QDateTime viewEndDateTime() const;
    void setViewEndDateTime(const QDateTime &viewEndDateTime);


    void updateHours();
    void updateDisplayHours();

Q_SIGNALS:
    void viewChanged(const QDateTime &start, const QDateTime &end);

private:
    void updateUnitWidth();
    void moveAxis(qreal hourPos);
    QDateTime getMinDateTime();
    QDateTime getMaxDateTime();

    int _displayLevel{DisplayDay};
    int _hours;
    qint64 _mSecs;
    qreal _displayHours;
    qreal _scale{1.f};
    qreal _unitWidth;
    int _latestMousePosX{-1};
    QPoint _lastPos;
    qreal _scaleFactor{1.1f};
    QDateTime _startDateTime{QDateTime(QDate(2012, 1, 1), QTime(0, 0))};
    QDateTime _endDateTime{QDateTime(QDate(2012, 2, 1), QTime(0, 0))};
    QDateTime _viewStartDateTime;
    QDateTime _viewEndDateTime;

public Q_SLOTS:
    void mouseMovePosX(int posX);

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *e);
    void wheelEvent(QWheelEvent *e);
    void dragMoveEvent(QDragMoveEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void enterEvent(QEvent *e);
    void leaveEvent(QEvent *e);
};

#endif // PROCESSXAXISWIDGET_H
