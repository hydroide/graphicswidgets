#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#ifndef VIEWER_H
#define VIEWER_H

#include <QtCore>
#include <QtWidgets>

#include "view.h"

class ViewerWindow;

class Viewer : public QWidget
{
    Q_OBJECT
public:
    explicit Viewer(QWidget *parent = nullptr);

    virtual void loadToolBar();

protected:
    View *_view;

    // page right begin
    QWidget *_vbox20Widget;
    QVBoxLayout *_vbox20;

    QWidget *_hbox21Widget;
    QHBoxLayout *_hbox21;

    QLabel *_label_station2;
    QComboBox *_cb_station2;
    QLabel *_label_selectYear2;
    QSpinBox *_sb_selectYear2;
    QPushButton *_pbDraw;
    QPushButton *_pbRefresh;
    QPushButton *_pbExport;
    QSpacerItem *_spacer21;

    QSplitter *_splitter20;
    View *_view20;

    View *_crossSectionChartView;
    // page right end
};

class ViewerWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit ViewerWindow(Viewer *viewer, QWidget *parent = nullptr);

protected:
    Viewer *_viewer {nullptr};

};
#endif // VIEWER_H
