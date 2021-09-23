#include "glassboard.h"
#include "loadingview.h"

#include <QGuiApplication>
#include <QScreen>
#include <QRect>
#include <QPainter>
#include <QColor>

GlassBoard * GlassBoard::glassBoard = nullptr;

GlassBoard::GlassBoard(QWidget *loadingView):QLabel(nullptr)
{
    LoadingView *lv = (LoadingView *)loadingView;
    lv->setInfo(QString("Initiating Glass Board"));
    QScreen *screen = QGuiApplication::primaryScreen();
    this->setGeometry(screen->geometry());
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::WindowDoesNotAcceptFocus | Qt::WindowTransparentForInput);
    this->setStyleSheet(QString("background-color : rgba(30, 30, 30, 100);"));
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->fixedDrawing = new QPixmap(screen->geometry().width(), screen->geometry().height());
    this->fixedDrawing->fill(Qt::transparent);
    this->setPixmap(*(this->fixedDrawing));
    lv->setInfo(QString("Initiated Glass Board"));
}

GlassBoard *GlassBoard::get(QWidget *loadingView)
{
    if(!glassBoard) glassBoard = new GlassBoard(loadingView);
    return glassBoard;
}

void GlassBoard::mousePressEvent(QMouseEvent *ev)
{
    startX = ev->x();
    startY = ev->y();
}

void GlassBoard::mouseMoveEvent(QMouseEvent *ev)
{
    endX = ev->x();
    endY = ev->y();
    QPainter painter(fixedDrawing);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawLine(startX, startY, endX, endY);
    painter.end();
    startX = endX;
    startY = endY;
    setPixmap(*fixedDrawing);
}

GlassBoard::~GlassBoard()
{
    delete fixedDrawing;
}
