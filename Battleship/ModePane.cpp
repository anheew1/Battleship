#include "ModePane.h"
#include <ncurses.h>



ModePane::ModePane(int x, int y,int width, int height)
:Pane(x, y,width,height)
{
   mvwprintw(pWindow,0,5,"GAME MODE");
}
ModePane::~ModePane()
{
   
}
void ModePane::Draw()
{
    init_pair(6, COLOR_YELLOW, COLOR_BLACK);
    wattron(pWindow,COLOR_PAIR(6));
    mvwprintw(pWindow,1,3, "Select gamemode you want!");
    mvwprintw(pWindow,3,3 ," 1. Attack by input");
    mvwprintw(pWindow,5,3, " 2. Attack by Random");
    mvwprintw(pWindow,7,3, " 3. Attack by AI");
    wattroff(pWindow,COLOR_PAIR(6));
    wrefresh(pWindow);
}
GameMode ModePane::GetInput()
{   
    while(true){
    std::string input;
   move(15, 9);
   int ch = getch();
   nocbreak();
   refresh();
   int count=0;
   while( ch!= '\n')
   {
       count++;
       input.push_back(ch);
       ch = getch();
       refresh();
   }
   move(15, 9);
   for(int i=0;i< count ; i++)
   printw(" "); 
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
   if(input.size()>=2)
   continue;
   char answer =input[0];
   refresh();
   if(answer == '1')
       return PLAY_INPUT;
   if(answer == '2')
        return PLAY_RANDOM;
    if(answer == '3')
        return PLAY_FOLLOW_AI;
    }
}
void ModePane::clear()
{
    wclear(pWindow);
    wrefresh(pWindow);
}