#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif
#include "viewer.h"

#include <boost/make_shared.hpp>

Viewer::Viewer(QWidget *parent)
    : QWidget(parent)
{
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

    setStyleSheet("QSplitter::handle { background-color: grey; }");
}

void Viewer::loadToolBar()
{

}

ViewerWindow::ViewerWindow(Viewer *viewer, QWidget *parent)
    : QMainWindow(parent)
{
    if (viewer) {
        viewer->setParent(this);
//        viewer->setWindow(this);
        _viewer = viewer;
        this->setCentralWidget(_viewer);
    }
}
