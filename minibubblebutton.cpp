#include "minibubblebutton.h"
#include "bubblebutton.h"
#include <QApplication>

MiniBubbleButton::MiniBubbleButton():QPushButton()
{
    this->clickEvent = nullptr;
    connect(this,&MiniBubbleButton::clicked,this, &MiniBubbleButton::onClick);
}

void MiniBubbleButton::onClick()
{
    if(clickEvent) clickEvent();
}

void MiniBubbleButton::setClickEvent(void (*clickEvent)())
{
    this->clickEvent = clickEvent;
}
