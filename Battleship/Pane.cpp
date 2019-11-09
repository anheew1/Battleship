/* 소프트웨어 학부 20171646 안희운*/
#include "Pane.h"
Pane::Pane(int x, int y, int width, int height)
:px(x), py(y), pwidth(width) , pheight(height)
{
    pWindow = newwin(height,width,y,x);
    box(pWindow,0,0);
    wrefresh(pWindow);
}
Pane::~Pane()
{
    delwin(pWindow);
}
void Pane::Draw()
{
    box(pWindow,0,0);
    wrefresh(pWindow);
}