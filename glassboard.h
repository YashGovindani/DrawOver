#ifndef GLASSBOARD_H
#define GLASSBOARD_H

#include <QLabel>
#include <QMouseEvent>

class GlassBoard:public QLabel
{
private:
    static GlassBoard *glassBoard;
    GlassBoard(QWidget *loadingView);
    QPixmap *fixedDrawing;
public:
    static GlassBoard * get(QWidget *loadingView = nullptr);
    void mousePressEvent(QMouseEvent *ev) override;
    void mouseMoveEvent(QMouseEvent *ev) override;
    ~GlassBoard();
};

#endif // GLASSBOARD_H
