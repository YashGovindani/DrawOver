#include "loadingview.h"
#include "ui_loadingview.h"

LoadingView::LoadingView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoadingView)
{
    ui->setupUi(this);
}

LoadingView::~LoadingView()
{
    delete ui;
}
