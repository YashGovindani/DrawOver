#include "loadingview.h"
#include <QApplication>
#include "bubblebutton.h"
#include "glassboard.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(QString(":/global/images/d.icns")));
    LoadingView *loadingView = new LoadingView(nullptr);
    loadingView->show();
    loadingView->setInfo(QString("Initiating"));
    BubbleButton *bubbleButton = BubbleButton::get(loadingView);
    bubbleButton->setA(&a);
    GlassBoard *glassBoard = GlassBoard::get(loadingView);
    loadingView->setCompleted();
    glassBoard->show();
    return a.exec();
}
