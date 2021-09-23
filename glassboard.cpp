#include "glassboard.h"
#include "loadingview.h"

#include <QGuiApplication>
#include <QScreen>
#include <QRect>
#include <QPainter>

GlassBoard * GlassBoard::glassBoard = nullptr;

GlassBoard::GlassBoard(QWidget *loadingView):QLabel(nullptr)
{
    this->setGeometry(QGuiApplication::primaryScreen()->geometry());
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::WindowDoesNotAcceptFocus | Qt::WindowTransparentForInput);
    this->setStyleSheet(QString("background-color : rgba(30, 30, 30, 100);"));
    this->setAttribute(Qt::WA_TranslucentBackground);
}

GlassBoard *GlassBoard::get(QWidget *loadingView)
{
    if(!glassBoard) glassBoard = new GlassBoard(loadingView);
    return glassBoard;
}

void GlassBoard::mousePressEvent(QMouseEvent *ev)
{

}

void GlassBoard::mouseMoveEvent(QMouseEvent *ev)
{

}
