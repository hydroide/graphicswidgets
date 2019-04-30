#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#ifndef PROCESSYAXIS_H
#define PROCESSYAXIS_H

#include <QtWidgets>

class ProcessYAxis : public QGraphicsWidget
{
    Q_OBJECT
public:
    explicit ProcessYAxis(QGraphicsItem *parent = nullptr);

};
#endif // PROCESSYAXIS_H
