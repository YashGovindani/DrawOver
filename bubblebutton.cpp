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

void onBackToApplicationButtonClicked()
{
    BubbleButton *bubbleButton = BubbleButton::get();
    bubbleButton->compressAction();
    QTimer::singleShot(400, bubbleButton, [=](){
        bubbleButton->close();
        //Presentation::get(bubble)->showFullScreenView();
    });
}

void onScreenshotButtonClicked()
{}

void onHighLighterButtonClicked()
{}

void onQuitButtonClicked()
{
    BubbleButton::get()->getA()->quit();
}

void onPencButtonClicked()
{}

BubbleButton * BubbleButton::bubbleButton = nullptr;

BubbleButton::BubbleButton(QWidget *loadingView):QPushButton()
{
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
    screenshotButton.setStyleSheet(smallButtonStyleSheet);
    screenshotButton.setIcon(QIcon(QPixmap(QString(""))));
    screenshotButton.setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    screenshotButton.setAttribute(Qt::WA_TranslucentBackground);
    screenshotButton.setGeometry(smallButtonX, smallButtonY, smallButtonWidth, smallButtonHeight);
    screenshotButton.setClickEvent(onScreenshotButtonClicked);
    backToApplicationButton.setStyleSheet(smallButtonStyleSheet);
    backToApplicationButton.setIcon(QIcon(QPixmap(QString(""))));
    backToApplicationButton.setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    backToApplicationButton.setAttribute(Qt::WA_TranslucentBackground);
    backToApplicationButton.setGeometry(smallButtonX, smallButtonY, smallButtonWidth, smallButtonHeight);
    backToApplicationButton.setClickEvent(onBackToApplicationButtonClicked);
    quitButton.setStyleSheet(smallButtonStyleSheet);
    quitButton.setIcon(QIcon(QPixmap(QString(":/bubble/images/quit.png"))));
    quitButton.setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    quitButton.setAttribute(Qt::WA_TranslucentBackground);
    quitButton.setGeometry(smallButtonX, smallButtonY, smallButtonWidth, smallButtonHeight);
    quitButton.setClickEvent(onQuitButtonClicked);
    button6.setStyleSheet(smallButtonStyleSheet);
    button6.setIcon(QIcon(QPixmap(QString(":/bubble/images/board.png"))));
    button6.setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    button6.setAttribute(Qt::WA_TranslucentBackground);
    button6.setGeometry(smallButtonX, smallButtonY, smallButtonWidth, smallButtonHeight);
    expanded = false;
}

void BubbleButton::compressAction()
{
    int radius = width()/2;
    int smallButtonRadius = quitButton.width()/2;
    int startX = x() + radius - smallButtonRadius;
    int startY = y() + radius - smallButtonRadius;
    int smallButtonWidth = quitButton.width();
    int smallButtonHeight = quitButton.height();
    QRect startRect(startX, startY, smallButtonWidth, smallButtonHeight);
    QPropertyAnimation *animation = new QPropertyAnimation(&screenshotButton, "geometry", this);
    animation->setDuration(100);
    animation->setStartValue(backToApplicationButton.geometry());
    animation->setEndValue(startRect);
    animation->start(QPropertyAnimation::DeleteWhenStopped);
    QTimer::singleShot(100, this, [=](){
        penButton.close();
        QPropertyAnimation *animation = new QPropertyAnimation(&backToApplicationButton, "geometry", this);
        animation->setDuration(100);
        animation->setStartValue(backToApplicationButton.geometry());
        animation->setEndValue(startRect);
        animation->start(QPropertyAnimation::DeleteWhenStopped);
        QTimer::singleShot(100, this, [=](){
            backToApplicationButton.close();
            QPropertyAnimation *animation = new QPropertyAnimation(&penButton, "geometry", this);
            animation->setDuration(100);
            animation->setStartValue(screenshotButton.geometry());
            animation->setEndValue(startRect);
            animation->start(QPropertyAnimation::DeleteWhenStopped);
            QTimer::singleShot(100, this, [=](){
                screenshotButton.close();
                QPropertyAnimation *animation = new QPropertyAnimation(&highLighterButton, "geometry", this);
                animation->setDuration(100);
                animation->setStartValue(highLighterButton.geometry());
                animation->setEndValue(startRect);
                animation->start(QPropertyAnimation::DeleteWhenStopped);
                QTimer::singleShot(100, this, [=](){
                    highLighterButton.close();
                    QPropertyAnimation *animation = new QPropertyAnimation(&quitButton, "geometry", this);
                    animation->setDuration(100);
                    animation->setStartValue(quitButton.geometry());
                    animation->setEndValue(startRect);
                    animation->start(QPropertyAnimation::DeleteWhenStopped);
                    QTimer::singleShot(100, this, [=](){
                        quitButton.close();
                        QPropertyAnimation *animation = new QPropertyAnimation(&button6, "geometry", this);
                        animation->setDuration(100);
                        animation->setStartValue(quitButton.geometry());
                        animation->setEndValue(startRect);
                        animation->start(QPropertyAnimation::DeleteWhenStopped);
                        QTimer::singleShot(100, this, [=](){button6.close();});
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
        int smallButtonRadius = quitButton.width()/2;
        int expandedRadius = radius + 25 + smallButtonRadius;
        int startX = x() + radius - smallButtonRadius;
        int startY = y() + radius - smallButtonRadius;
        int smallButtonWidth = quitButton.width();
        int smallButtonHeight = quitButton.height();
        QRect startRect(startX, startY, smallButtonWidth, smallButtonHeight);
        int endX = startX + invert*((int)(((double)expandedRadius)*cos(((double)(4*22))/(double)(9*7))));
        int endY = startY - (int)(((double)expandedRadius)*sin(((double)(4*22))/(double)(9*7)));
        QPropertyAnimation *animation = new QPropertyAnimation(&screenshotButton, "geometry", this);
        animation->setDuration(100);
        animation->setStartValue(startRect);
        animation->setEndValue(QRect(endX, endY, smallButtonWidth, smallButtonHeight));
        animation->start(QPropertyAnimation::DeleteWhenStopped);
        penButton.show();
        QTimer::singleShot(100, this, [=](){
            int endX = startX + invert*((int)(((double)expandedRadius)*cos(((double)(2*22))/(double)(3*7))));
            int endY = startY - (int)(((double)expandedRadius)*sin(((double)(2*22))/(double)(3*7)));
            QPropertyAnimation *animation = new QPropertyAnimation(&backToApplicationButton, "geometry", this);
            animation->setDuration(100);
            animation->setStartValue(startRect);
            animation->setEndValue(QRect(endX, endY, smallButtonWidth, smallButtonHeight));
            animation->start(QPropertyAnimation::DeleteWhenStopped);
            backToApplicationButton.show();
            QTimer::singleShot(100, this, [=](){
                int endX = startX + invert*((int)(((double)expandedRadius)*cos(((double)(8*22))/(double)(9*7))));
                int endY = startY - (int)(((double)expandedRadius)*sin(((double)(8*22))/(double)(9*7)));
                QPropertyAnimation *animation = new QPropertyAnimation(&penButton, "geometry", this);
                animation->setDuration(100);
                animation->setStartValue(startRect);
                animation->setEndValue(QRect(endX, endY, smallButtonWidth, smallButtonHeight));
                animation->start(QPropertyAnimation::DeleteWhenStopped);
                screenshotButton.show();
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
                        QPropertyAnimation *animation = new QPropertyAnimation(&quitButton, "geometry", this);
                        animation->setDuration(100);
                        animation->setStartValue(startRect);
                        animation->setEndValue(QRect(endX, endY, smallButtonWidth, smallButtonHeight));
                        animation->start(QPropertyAnimation::DeleteWhenStopped);
                        quitButton.show();
                        QTimer::singleShot(100, this, [=](){
                            int endX = startX + invert*((int)(((double)expandedRadius)*cos(((double)(14*22))/(double)(9*7))));
                            int endY = startY - (int)(((double)expandedRadius)*sin(((double)(14*22))/(double)(9*7)));
                            QPropertyAnimation *animation = new QPropertyAnimation(&button6, "geometry", this);
                            animation->setDuration(100);
                            animation->setStartValue(startRect);
                            animation->setEndValue(QRect(endX, endY, smallButtonWidth, smallButtonHeight));
                            animation->start(QPropertyAnimation::DeleteWhenStopped);
                            button6.show();
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
