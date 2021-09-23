#ifndef GLASSBOARD_H
#define GLASSBOARD_H

#include <QLabel>
#include <QMouseEvent>
#include <QPen>
#include <QColor>
#include <QPainter>

class GlassBoard:public QLabel
{
private:
    static GlassBoard *glassBoard;
    GlassBoard(QWidget *loadingView);
    QPixmap *fixedDrawing;
    int startX;
    int startY;
    int endX;
    int endY;
    QPen *eraser;
    QPen *pen;
    QPen *highLighter;
    QPen *toBeUsed;
    QPainter::CompositionMode painterCompositionMode;
public:
    static GlassBoard * get(QWidget *loadingView = nullptr);
    void mousePressEvent(QMouseEvent *ev) override;
    void mouseMoveEvent(QMouseEvent *ev) override;
    void mouseReleaseEvent(QMouseEvent *ev) override;
    void acceptInput();
    void ignoreInput();
    void clearAction();
    void usePen();
    void useEraser();
    void useHighLighter();
    ~GlassBoard();
};

#endif // GLASSBOARD_H
