#include "drawover.h"
#include "loadingview.h"

#include <QApplication>
#include "bubblebutton.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoadingView *loadingView = new LoadingView(nullptr);
    loadingView->show();
    loadingView->setInfo(QString("Initiating"));
    //DrawOver w;
    BubbleButton *bubbleButton = BubbleButton::get(loadingView);
    bubbleButton->setA(&a);
    loadingView->setInfo(QString("Ready to go !!!!\nClick Here to continue"));
    loadingView->setCompleted();
    return a.exec();
}
