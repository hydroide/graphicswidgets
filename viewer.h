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

    // page left begin
    QWidget *_vbox10Widget;
    QVBoxLayout *_vbox10;
    QHBoxLayout *_hbox11;
    QWidget *_hbox11Widget;
    QSpacerItem *_spacer11;

    QLabel *_label_selectYear;
    QSpinBox *_sb_selectYear;
    QPushButton *_pb_selectYear;

    QLabel *_label_selectMonth;
    QSpinBox *_sb_selectMonth;
    QPushButton *_pb_selectMonth;

    QLabel *_label_startDateTime;
    QDateTimeEdit* _dte_startDateTime;

    QLabel *_label_endDateTime;
    QDateTimeEdit* _dte_endDateTime;

    QPushButton *_viewOption;
    QPushButton *_insertTo;
    QPushButton *_generate;

    QGridLayout *_grid;
    QWidget *_gridWidget;

    QSplitter *_splitter11;

    QPushButton *_buttonPlus1;
    ProcessXAxisWidget *_xAxis1;

    QList<View *> _views;
    QList<ProcessChart *> _processCharts;

    QToolBar *_toolBar;

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
