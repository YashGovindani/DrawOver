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
    this->setStyleSheet(QString("background-color : rgba(0, 0, 0, 0);"));
    this->fixedDrawing = new QPixmap(screen->geometry().width(), screen->geometry().height());
    this->fixedDrawing->fill(Qt::transparent);
    this->setPixmap(*(this->fixedDrawing));
    lv->setInfo(QString("Initiated Glass Board"));
    this->eraser = new QPen(Qt::transparent);
    this->eraser->setWidth(15);
    this->eraser->setCapStyle(Qt::RoundCap);
    this->eraser->setJoinStyle(Qt::RoundJoin);
    this->pen = new QPen(Qt::red);
    this->pen->setWidth(5);
    this->pen->setCapStyle(Qt::RoundCap);
    this->pen->setJoinStyle(Qt::RoundJoin);
    this->highLighter = new QPen(QColor(237, 98,160, 30));
    this->highLighter->setWidth(15);
    this->highLighter->setJoinStyle(Qt::RoundJoin);
    this->toBeUsed = this->pen;
    this->painterCompositionMode = QPainter::CompositionMode_SourceOver;
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
    painter.setPen(*this->toBeUsed);
    painter.setCompositionMode(this->painterCompositionMode);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawLine(startX, startY, endX, endY);
    painter.end();
    startX = endX;
    startY = endY;
    setPixmap(*fixedDrawing);
}

void GlassBoard::mouseReleaseEvent(QMouseEvent *)
{
    this->close();
    this->show();
}

void GlassBoard::acceptInput()
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->close();
    this->show();
}

void GlassBoard::ignoreInput()
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::WindowDoesNotAcceptFocus | Qt::WindowTransparentForInput);
    this->close();
    this->show();
}

void GlassBoard::clearAction()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    QPixmap *newPixMap = new QPixmap(screen->geometry().width(), screen->geometry().height());
    newPixMap->fill(Qt::transparent);
    this->setPixmap(*newPixMap);
    delete this->fixedDrawing;
    this->fixedDrawing = newPixMap;
    this->close();
    this->show();
}

void GlassBoard::usePen()
{
    this->toBeUsed = this->pen;
    this->painterCompositionMode = QPainter::CompositionMode_SourceOver;
}

void GlassBoard::useEraser()
{
    this->toBeUsed = this->eraser;
    this->painterCompositionMode = QPainter::CompositionMode_Clear;
}

void GlassBoard::useHighLighter()
{
    this->toBeUsed = this->highLighter;
    this->painterCompositionMode = QPainter::CompositionMode_Xor;
}

GlassBoard::~GlassBoard()
{
    delete fixedDrawing;
    delete eraser;
}
