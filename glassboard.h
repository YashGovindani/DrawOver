#ifndef GLASSBOARD_H
#define GLASSBOARD_H

#include <QLabel>
#include <QMouseEvent>

class GlassBoard:public QLabel
{
private:
    GlassBoard(QWidget *loadingView);
public:
    GlassBoard * get(QWidget *loadingView = nullptr);
    void mousePressEvent(QMouseEvent *ev) override;
    void mouseMoveEvent(QMouseEvent *ev) override;
};

#endif // GLASSBOARD_H
