#ifndef LOADINGVIEW_H
#define LOADINGVIEW_H

#include <QMainWindow>

namespace Ui {
class LoadingView;
}

class LoadingView : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoadingView(QWidget *parent = nullptr);
    ~LoadingView();

private:
    Ui::LoadingView *ui;
};

#endif // LOADINGVIEW_H
