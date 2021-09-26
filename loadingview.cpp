#include "loadingview.h"
#include "ui_loadingview.h"
#include "bubblebutton.h"

#include <QScreen>
#include <QRect>
#include <QGraphicsDropShadowEffect>
#include <QTimer>
#include <QDebug>
#include <QPropertyAnimation>

LoadingView::LoadingView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoadingView)
{
    ui->setupUi(this);
    int shadowRadius = 30;
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int desktopWidth = screenGeometry.width();
    int desktopHeight = screenGeometry.height();
    int windowHeight = desktopHeight/10;
    int windowWidth = desktopWidth/4;
    int windowX = desktopWidth/2 - windowWidth/2;
    int windowY = desktopHeight/2 - windowHeight/2;
    this->setGeometry(windowX - shadowRadius, windowY - shadowRadius, windowWidth + (shadowRadius*2), windowHeight + (shadowRadius*2));
    this->ui->frame->setGeometry( shadowRadius, shadowRadius, windowWidth, windowHeight);
    shadow_effect=new QGraphicsDropShadowEffect(this);
    shadow_effect->setOffset(0, 0);
    shadow_effect->setColor(QColor(0, 0, 0, 255));
    shadow_effect->setBlurRadius(shadowRadius);
    this->ui->centralwidget->setGraphicsEffect(shadow_effect);
    cornerRadius = QString::number(windowHeight/2);
    this->ui->frame->setStyleSheet(QString("border-top-left-radius : ") + cornerRadius + QString("; border-top-right-radius : ") + cornerRadius + QString("; border-bottom-right-radius : ") + cornerRadius + QString("; border-bottom-left-radius : ") + cornerRadius + QString("; background-color : rgb(32, 33, 36); "));
    this->ui->frame->setGeometry(shadowRadius, shadowRadius, windowWidth, windowHeight);
    this->ui->frame->setStyleSheet(QString("QFrame{border-top-left-radius : ") + cornerRadius + QString("; border-top-right-radius : ") + cornerRadius + QString("; border-bottom-right-radius : ") + cornerRadius + QString("; border-bottom-left-radius : ") + cornerRadius + QString("; background-color : rgb(32, 33, 36);} QFrame:hover{background-color : rgb(25, 25, 25);}"));
    this->ui->logoLabel->setGeometry(0, 0, (windowWidth*2)/5, windowHeight - (windowHeight/6));
    this->ui->logoLabel->setAlignment(Qt::AlignCenter);
    this->ui->logoLabel->setPixmap(QPixmap(QString(":/global/images/logo.png")).scaled((windowHeight*2)/3, (windowHeight*2)/3));
    this->ui->logoLabel->setStyleSheet(QString("background-color : rgba(1, 1, 1, 0)"));
    this->ui->nameLabel->setGeometry(0, ((windowHeight*5)/6) - 10, (windowWidth*2)/5, windowHeight/5);
    this->ui->nameLabel->setAlignment(Qt::AlignCenter);
    this->ui->nameLabel->setStyleSheet(QString("background-color : rgba(1, 1, 1, 0)"));
    this->ui->nameLabel->setFont(QFont(QString(), windowHeight/6));
    this->ui->nameLabel->setText(QString("DrawOver"));
    this->ui->infoLabel->setGeometry((windowWidth*2)/5, 0, (windowWidth*3)/5, windowHeight);
    this->ui->infoLabel->setStyleSheet(QString("background-color : rgba(1, 1, 1, 0)"));
    this->ui->infoLabel->setText(QString(""));
    this->isCompleted = false;
    this->timerId = startTimer(2000);
    this->runTimeDuration = 0;
    this->timerEventTime = 0;
    this->moved = false;
}

void LoadingView::setInfo(QString str)
{
    QTimer::singleShot(this->runTimeDuration, this, [=](){this->ui->infoLabel->setText(str);});
    this->runTimeDuration += 200;
}

void LoadingView::timerEvent(QTimerEvent *)
{
    this->timerEventTime += 2000;
    if(this->isCompleted && this->timerEventTime > this->runTimeDuration)
    {
        this->ui->infoLabel->setText(QString("Ready to go !!!!\nClick Here to continue"));
        killTimer(this->timerId);
    }
}

void LoadingView::setCompleted()
{
    this->isCompleted = true;
}

void LoadingView::mousePressEvent(QMouseEvent *)
{
    this->ui->frame->setStyleSheet(QString("border-top-left-radius : ") + cornerRadius + QString("; border-top-right-radius : ") + cornerRadius + QString("; border-bottom-right-radius : ") + cornerRadius + QString("; border-bottom-left-radius : ") + cornerRadius + QString("; background-color : rgb(23, 100, 189); "));
    moved = false;
}

void LoadingView::mouseMoveEvent(QMouseEvent *)
{
    moved = true;
}

void LoadingView::mouseReleaseEvent(QMouseEvent *)
{
    this->ui->frame->setStyleSheet(QString("border-top-left-radius : ") + cornerRadius + QString("; border-top-right-radius : ") + cornerRadius + QString("; border-bottom-right-radius : ") + cornerRadius + QString("; border-bottom-left-radius : ") + cornerRadius + QString("; background-color : rgb(32, 33, 36); "));
    if(moved || !isCompleted || this->timerEventTime <= this->runTimeDuration) return;
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int desktopWidth = screenGeometry.width();
    int desktopHeight = screenGeometry.height();
    int windowHeight = desktopHeight/10;
    int windowWidth = desktopWidth/4;
    int windowX = desktopWidth/2 - windowWidth/2;
    int windowY = desktopHeight/2 - windowHeight/2;
    this->setGeometry(0, 0, desktopWidth, desktopHeight);
    this->ui->frame->setGeometry(windowX, windowY, windowWidth, windowHeight);
    BubbleButton *bubbleButton = BubbleButton::get();
    QPropertyAnimation *animation = new QPropertyAnimation(this->ui->frame, "geometry", this);
    animation->setDuration(500);
    animation->setStartValue(this->ui->frame->geometry());
    animation->setEndValue(bubbleButton->geometry());
    animation->start(QPropertyAnimation::DeleteWhenStopped);
    QTimer::singleShot(500, this, [=](){
        this->close();
        bubbleButton->show();
        delete this;
    });
}

LoadingView::~LoadingView()
{
    delete this->shadow_effect;
    delete ui;
}
