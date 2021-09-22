#ifndef LOADINGVIEW_H
#define LOADINGVIEW_H

#include <QMainWindow>
#include <QGraphicsDropShadowEffect>
#include <QTimerEvent>

namespace Ui {
class LoadingView;
}

class LoadingView : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoadingView(QWidget *parent = nullptr);
    void setInfo(QString);
    void timerEvent(QTimerEvent *);
    void setCompleted();
    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    ~LoadingView();

private:
    Ui::LoadingView *ui;
    QGraphicsDropShadowEffect *shadow_effect;
    int timerId;
    int runTimeDuration;
    bool isCompleted;
    int timerEventTime;
    bool moved;
    QString cornerRadius;
};

#endif // LOADINGVIEW_H
