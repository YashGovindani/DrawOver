#include "bubblebutton.h"
#include "loadingview.h"
#include <QScreen>
#include <QRect>
#include <QIcon>
#include <QPixmap>
#include <QSize>
#include <QGuiApplication>
#include <QPainter>
#include <QPropertyAnimation>
#include <QTimer>
#include <math.h>
#include <QDebug>
#include "glassboard.h"

void onClearButtonClicked()
{
    GlassBoard::get()->clearAction();
}

void onBackToWorkButtonClicked()
{
    GlassBoard::get()->ignoreInput();
}

void onHighLighterButtonClicked()
{
    GlassBoard *glassBoard = GlassBoard::get();
    glassBoard->useHighLighter();
    glassBoard->acceptInput();
}

void onEraserButtonClicked()
{
    GlassBoard *glassBoard = GlassBoard::get();
    glassBoard->useEraser();
    glassBoard->acceptInput();
}

void onPencButtonClicked()
{
    GlassBoard *glassBoard = GlassBoard::get();
    glassBoard->usePen();
    glassBoard->acceptInput();
}

void onExpandButtonClicked()
{
    // to be changed in phase 2
    BubbleButton::get()->getA()->quit();
}

BubbleButton * BubbleButton::bubbleButton = nullptr;

BubbleButton::BubbleButton(QWidget *loadingView):QPushButton()
{
    this->setToolTip(QString("DrawOver"));
    LoadingView *loadingViewPointer = (LoadingView *)loadingView;
    if(loadingViewPointer) loadingViewPointer->setInfo(QString("Creating bubble view"));
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setAttribute(Qt::WA_Hover);
    if(loadingViewPointer) loadingViewPointer->setInfo(QString("Extracting screen info"));
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int desktopWidth = screenGeometry.width();
    int desktopHeight = screenGeometry.height();
    if(loadingViewPointer) loadingViewPointer->setInfo(QString("Got screen info"));
    if(loadingViewPointer) loadingViewPointer->setInfo(QString("Setting bubble view geometry"));
    int windowHeight = (desktopHeight<desktopWidth)?desktopHeight/20:desktopWidth/20;
    if(windowHeight % 2 != 0) windowHeight+=1;
    int windowWidth = windowHeight;
    int radius = windowHeight/2;
    cornerRadius = QString::number(radius);
    this->setGeometry(desktopWidth - windowWidth -5, desktopHeight/2 - windowHeight/2, windowWidth, windowHeight);
    if(loadingViewPointer) loadingViewPointer->setInfo(QString("Adding shadow to view"));
    if(loadingViewPointer) loadingViewPointer->setInfo(QString("Setting buttons for bubble view"));
    this->setStyleSheet(QString("QPushButton{border-top-left-radius : ") + cornerRadius + QString("; border-top-right-radius : ") + cornerRadius + QString("; border-bottom-right-radius : ") + cornerRadius + QString("; border-bottom-left-radius : ") + cornerRadius + QString("; background-color : rgb(32, 33, 36);} QPushButton:hover{background-color : rgb(255, 255, 255)}"));
    this->setIcon(QIcon(QPixmap(QString(":/global/images/logo.png"))));
    this->setIconSize(QSize(30,30));
    this->setText(QString(""));
    if(loadingViewPointer) loadingViewPointer->setInfo(QString("Bubble view created"));
    connect(this, &BubbleButton::clicked, this, &BubbleButton::onClick);
    int smallButtonRadius = (radius*2)/3;
    int smallButtonWidth = smallButtonRadius*2;
    int smallButtonHeight = smallButtonWidth;
    int smallButtonX = x() + radius - smallButtonRadius;
    int smallButtonY = y() + radius -smallButtonRadius;
    QString smallButtonCornerRadius = QString::number(smallButtonRadius);
    QString smallButtonStyleSheet = QString("QPushButton{border-top-left-radius : ") + smallButtonCornerRadius + QString("; border-top-right-radius : ") + smallButtonCornerRadius + QString("; border-bottom-right-radius : ") + smallButtonCornerRadius + QString("; border-bottom-left-radius : ") + smallButtonCornerRadius + QString("; background-color : rgb(32, 33, 36);} QPushButton:hover{background-color : rgb(255, 255, 255)} QPushButton:pressed{background-color : rgb(23, 100, 189)}");
    penButton.setStyleSheet(smallButtonStyleSheet);
    penButton.setIcon(QIcon(QPixmap(QString(":/bubble/images/pen.png"))));
    penButton.setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    penButton.setAttribute(Qt::WA_TranslucentBackground);
    penButton.setGeometry(smallButtonX, smallButtonY, smallButtonWidth, smallButtonHeight);
    penButton.setClickEvent(onPencButtonClicked);
    highLighterButton.setStyleSheet(smallButtonStyleSheet);
    highLighterButton.setIcon(QIcon(QPixmap(QString(":/bubble/images/highLighter.png"))));
    highLighterButton.setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    highLighterButton.setAttribute(Qt::WA_TranslucentBackground);
    highLighterButton.setGeometry(smallButtonX, smallButtonY, smallButtonWidth, smallButtonHeight);
    highLighterButton.setClickEvent(onHighLighterButtonClicked);
    backToWorkButton.setStyleSheet(smallButtonStyleSheet);
    backToWorkButton.setIcon(QIcon(QPixmap(QString(":/bubble/images/backToWork.png"))));
    backToWorkButton.setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    backToWorkButton.setAttribute(Qt::WA_TranslucentBackground);
    backToWorkButton.setGeometry(smallButtonX, smallButtonY, smallButtonWidth, smallButtonHeight);
    backToWorkButton.setClickEvent(onBackToWorkButtonClicked);
    clearButton.setStyleSheet(smallButtonStyleSheet);
    clearButton.setIcon(QIcon(QPixmap(QString(":/bubble/images/clear.png"))));
    clearButton.setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    clearButton.setAttribute(Qt::WA_TranslucentBackground);
    clearButton.setGeometry(smallButtonX, smallButtonY, smallButtonWidth, smallButtonHeight);
    clearButton.setClickEvent(onClearButtonClicked);
    eraserButton.setStyleSheet(smallButtonStyleSheet);
    eraserButton.setIcon(QIcon(QPixmap(QString(":/bubble/images/eraser.png"))));
    eraserButton.setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    eraserButton.setAttribute(Qt::WA_TranslucentBackground);
    eraserButton.setGeometry(smallButtonX, smallButtonY, smallButtonWidth, smallButtonHeight);
    eraserButton.setClickEvent(onEraserButtonClicked);
    expandButton.setStyleSheet(smallButtonStyleSheet);
    //expandButton.setIcon(QIcon(QPixmap(QString(":/bubble/images/expand.png"))));
    expandButton.setIcon(QIcon(QPixmap(QString(":/bubble/images/close.png"))));
    expandButton.setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    expandButton.setAttribute(Qt::WA_TranslucentBackground);
    expandButton.setGeometry(smallButtonX, smallButtonY, smallButtonWidth, smallButtonHeight);
    expandButton.setClickEvent(onExpandButtonClicked);
    expanded = false;
}

void BubbleButton::compressAction()
{
    int radius = width()/2;
    int smallButtonRadius = eraserButton.width()/2;
    int startX = x() + radius - smallButtonRadius;
    int startY = y() + radius - smallButtonRadius;
    int smallButtonWidth = eraserButton.width();
    int smallButtonHeight = eraserButton.height();
    QRect startRect(startX, startY, smallButtonWidth, smallButtonHeight);
    QPropertyAnimation *animation = new QPropertyAnimation(&backToWorkButton, "geometry", this);
    animation->setDuration(100);
    animation->setStartValue(clearButton.geometry());
    animation->setEndValue(startRect);
    animation->start(QPropertyAnimation::DeleteWhenStopped);
    QTimer::singleShot(100, this, [=](){
        backToWorkButton.close();
        QPropertyAnimation *animation = new QPropertyAnimation(&clearButton, "geometry", this);
        animation->setDuration(100);
        animation->setStartValue(clearButton.geometry());
        animation->setEndValue(startRect);
        animation->start(QPropertyAnimation::DeleteWhenStopped);
        QTimer::singleShot(100, this, [=](){
            clearButton.close();
            QPropertyAnimation *animation = new QPropertyAnimation(&penButton, "geometry", this);
            animation->setDuration(100);
            animation->setStartValue(penButton.geometry());
            animation->setEndValue(startRect);
            animation->start(QPropertyAnimation::DeleteWhenStopped);
            QTimer::singleShot(100, this, [=](){
                penButton.close();
                QPropertyAnimation *animation = new QPropertyAnimation(&highLighterButton, "geometry", this);
                animation->setDuration(100);
                animation->setStartValue(highLighterButton.geometry());
                animation->setEndValue(startRect);
                animation->start(QPropertyAnimation::DeleteWhenStopped);
                QTimer::singleShot(100, this, [=](){
                    highLighterButton.close();
                    QPropertyAnimation *animation = new QPropertyAnimation(&eraserButton, "geometry", this);
                    animation->setDuration(100);
                    animation->setStartValue(eraserButton.geometry());
                    animation->setEndValue(startRect);
                    animation->start(QPropertyAnimation::DeleteWhenStopped);
                    QTimer::singleShot(100, this, [=](){
                        eraserButton.close();
                        QPropertyAnimation *animation = new QPropertyAnimation(&expandButton, "geometry", this);
                        animation->setDuration(100);
                        animation->setStartValue(eraserButton.geometry());
                        animation->setEndValue(startRect);
                        animation->start(QPropertyAnimation::DeleteWhenStopped);
                        QTimer::singleShot(100, this, [=](){expandButton.close();});
                    });
                });
            });
        });
    });
    expanded = false;
}

QApplication *BubbleButton::getA() const
{
    return a;
}

void BubbleButton::setA(QApplication *value)
{
    a = value;
}

BubbleButton *BubbleButton::get(QWidget *loadingView)
{
    if(!bubbleButton) bubbleButton = new BubbleButton(loadingView);
    return bubbleButton;
}

void BubbleButton::mousePressEvent(QMouseEvent *mouseEvent)
{
    startX = mouseEvent->x();
    startY = mouseEvent->y();
    buttonX = x();
    buttonY = y();
    moved = false;
    this->setStyleSheet(QString("QPushButton{border-top-left-radius : ") + cornerRadius + QString("; border-top-right-radius : ") + cornerRadius + QString("; border-bottom-right-radius : ") + cornerRadius + QString("; border-bottom-left-radius : ") + cornerRadius + QString("; background-color : rgb(23, 100, 189);}"));
}

void BubbleButton::mouseMoveEvent(QMouseEvent *mouseEvent)
{
    moved = true;
    if(expanded) return;
    buttonX += mouseEvent->x() - startX;
    buttonY += mouseEvent->y() - startY;
    move(buttonX, buttonY);
}

void BubbleButton::mouseReleaseEvent(QMouseEvent *)
{
    this->setStyleSheet(QString("QPushButton{border-top-left-radius : ") + cornerRadius + QString("; border-top-right-radius : ") + cornerRadius + QString("; border-bottom-right-radius : ") + cornerRadius + QString("; border-bottom-left-radius : ") + cornerRadius + QString("; background-color : rgb(32, 33, 36);} QPushButton:hover{background-color : rgb(255,255, 255)}"));
    if(!moved)
    {
        clicked();
        return;
    }
    if(expanded) return;
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int desktopWidth = screenGeometry.width();
    int newX = (this->x()>=desktopWidth/2)?desktopWidth - width() - 5: 5;
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry", this);
    animation->setDuration(500);
    animation->setStartValue(this->geometry());
    animation->setEndValue(QRect(newX, y(), width(), height()));
    animation->start();
    QTimer::singleShot(500, this, [=](){
        delete animation;
    });
}

void BubbleButton::onClick()
{
    if(!expanded)
    {
        QScreen *screen = QGuiApplication::primaryScreen();
        QRect screenGeometry = screen->geometry();
        int desktopWidth = screenGeometry.width();
        int invert = (this->x()>=desktopWidth/2)?1:-1;
        int radius = width()/2;
        int smallButtonRadius = eraserButton.width()/2;
        int expandedRadius = radius + 25 + smallButtonRadius;
        int startX = x() + radius - smallButtonRadius;
        int startY = y() + radius - smallButtonRadius;
        int smallButtonWidth = eraserButton.width();
        int smallButtonHeight = eraserButton.height();
        QRect startRect(startX, startY, smallButtonWidth, smallButtonHeight);
        int endX = startX + invert*((int)(((double)expandedRadius)*cos(((double)(4*22))/(double)(9*7))));
        int endY = startY - (int)(((double)expandedRadius)*sin(((double)(4*22))/(double)(9*7)));
        QPropertyAnimation *animation = new QPropertyAnimation(&backToWorkButton, "geometry", this);
        animation->setDuration(100);
        animation->setStartValue(startRect);
        animation->setEndValue(QRect(endX, endY, smallButtonWidth, smallButtonHeight));
        animation->start(QPropertyAnimation::DeleteWhenStopped);
        backToWorkButton.show();
        QTimer::singleShot(100, this, [=](){
            int endX = startX + invert*((int)(((double)expandedRadius)*cos(((double)(2*22))/(double)(3*7))));
            int endY = startY - (int)(((double)expandedRadius)*sin(((double)(2*22))/(double)(3*7)));
            QPropertyAnimation *animation = new QPropertyAnimation(&clearButton, "geometry", this);
            animation->setDuration(100);
            animation->setStartValue(startRect);
            animation->setEndValue(QRect(endX, endY, smallButtonWidth, smallButtonHeight));
            animation->start(QPropertyAnimation::DeleteWhenStopped);
            clearButton.show();
            QTimer::singleShot(100, this, [=](){
                int endX = startX + invert*((int)(((double)expandedRadius)*cos(((double)(8*22))/(double)(9*7))));
                int endY = startY - (int)(((double)expandedRadius)*sin(((double)(8*22))/(double)(9*7)));
                QPropertyAnimation *animation = new QPropertyAnimation(&penButton, "geometry", this);
                animation->setDuration(100);
                animation->setStartValue(startRect);
                animation->setEndValue(QRect(endX, endY, smallButtonWidth, smallButtonHeight));
                animation->start(QPropertyAnimation::DeleteWhenStopped);
                penButton.show();
                QTimer::singleShot(100, this, [=](){
                    int endX = startX + invert*((int)(((double)expandedRadius)*cos(((double)(10*22))/(double)(9*7))));
                    int endY = startY - (int)(((double)expandedRadius)*sin(((double)(10*22))/(double)(9*7)));
                    QPropertyAnimation *animation = new QPropertyAnimation(&highLighterButton, "geometry", this);
                    animation->setDuration(100);
                    animation->setStartValue(startRect);
                    animation->setEndValue(QRect(endX, endY, smallButtonWidth, smallButtonHeight));
                    animation->start(QPropertyAnimation::DeleteWhenStopped);
                    highLighterButton.show();
                    QTimer::singleShot(100, this, [=](){
                        int endX = startX + invert*((int)(((double)expandedRadius)*cos(((double)(4*22))/(double)(3*7))));
                        int endY = startY - (int)(((double)expandedRadius)*sin(((double)(4*22))/(double)(3*7)));
                        QPropertyAnimation *animation = new QPropertyAnimation(&eraserButton, "geometry", this);
                        animation->setDuration(100);
                        animation->setStartValue(startRect);
                        animation->setEndValue(QRect(endX, endY, smallButtonWidth, smallButtonHeight));
                        animation->start(QPropertyAnimation::DeleteWhenStopped);
                        eraserButton.show();
                        QTimer::singleShot(100, this, [=](){
                            int endX = startX + invert*((int)(((double)expandedRadius)*cos(((double)(14*22))/(double)(9*7))));
                            int endY = startY - (int)(((double)expandedRadius)*sin(((double)(14*22))/(double)(9*7)));
                            QPropertyAnimation *animation = new QPropertyAnimation(&expandButton, "geometry", this);
                            animation->setDuration(100);
                            animation->setStartValue(startRect);
                            animation->setEndValue(QRect(endX, endY, smallButtonWidth, smallButtonHeight));
                            animation->start(QPropertyAnimation::DeleteWhenStopped);
                            expandButton.show();
                        });
                    });
                });
            });
        });
        expanded = true;
    }else compressAction();
}

BubbleButton::~BubbleButton()
{
}
