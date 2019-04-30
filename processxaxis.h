#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#ifndef PROCESSXAXIS_H
#define PROCESSXAXIS_H

#include <QtWidgets>

class ProcessXAxis : public QGraphicsWidget
{
    Q_OBJECT
public:
    explicit ProcessXAxis(QGraphicsItem *parent = nullptr);

};

#endif // PROCESSXAXIS_H
