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

ViewerWindow::ViewerWindow(QWidget *viewer, QWidget *parent)
    : QMainWindow(parent)
{
//    auto viewer = qobject_cast<Viewer *>(widget);
    if (viewer) {
        viewer->setParent(this);
        this->setCentralWidget(viewer);
    }
}
