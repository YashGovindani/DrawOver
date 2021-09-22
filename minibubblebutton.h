#ifndef MINIBUBBLEBUTTON_H
#define MINIBUBBLEBUTTON_H

#include <QPushButton>

class MiniBubbleButton:public QPushButton
{
private:
    void (*clickEvent)();
public:
    MiniBubbleButton();
    void onClick();
    void setClickEvent(void (*clickEvent)());
};

#endif // MINIBUBBLEBUTTON_H
