#include "drawover.h"
#include "loadingview.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoadingView *loadingView = new LoadingView(nullptr);
    loadingView->show();
    loadingView->setInfo(QString("Initiating"));
    //DrawOver w;
    loadingView->setInfo(QString("Ready to go !!!!\nClick Here to continue"));
    loadingView->setCompleted(nullptr);
    return a.exec();
}
