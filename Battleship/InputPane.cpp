/* 소프트웨어 학부 20171646 안희운*/
#include "InputPane.h"
#include <ncurses.h>

InputPane::InputPane(int x, int y, int width, int height)
:Pane(x,y,width,height)
{
    mvwprintw(pWindow, 0 , 3 , "< INPUT > ");
};

InputPane::~InputPane()
{

}
std::string InputPane::GetInput()
{
   std::string input;
   move(17,40);
   nocbreak();
   echo();
   int ch = getch();
   refresh();
   int count=0;
   while( ch!= '\n')
   {
       count++;
       input.push_back(ch);
       ch = getch();
       refresh();
   }
   move(17,40);
   for(int i=0;i< count ; i++)
   printw(" ");
   refresh();
   return input;
}

void InputPane::Draw()
{
    wattron(pWindow, COLOR_PAIR(3));
    mvwprintw(pWindow, 1, 2, "Input position ...(ex A3)");
    mvwprintw(pWindow, 2, 2 , "Input : ");
    wattroff(pWindow,COLOR_PAIR(3));
    wrefresh(pWindow);
}