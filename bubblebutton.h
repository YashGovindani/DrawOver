#ifndef BUBBLEBUTTON_H
#define BUBBLEBUTTON_H

#include "minibubblebutton.h"
#include <QPushButton>
#include <QGraphicsDropShadowEffect>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QApplication>

class BubbleButton:public QPushButton
{
private:
    BubbleButton(QWidget *loadingView = nullptr);
    static BubbleButton *bubbleButton;
    int startX;
    int startY;
    int buttonX;
    int buttonY;
    bool moved;
    bool expanded;
    QString cornerRadius;
    MiniBubbleButton penButton;
    MiniBubbleButton highLighterButton;
    MiniBubbleButton backToWorkButton;
    MiniBubbleButton clearButton;
    MiniBubbleButton eraserButton;
    MiniBubbleButton expandButton;
    QApplication *a;
public:
    static BubbleButton * get(QWidget *loadingView = nullptr);
    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void onClick();
    ~BubbleButton();
    QApplication *getA() const;
    void setA(QApplication *value);
    void compressAction();
};

#endif // BUBBLEBUTTON_H
