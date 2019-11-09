/* 소프트웨어 학부 20171646 안희운*/
#include "StatPane.h"
#include <stdlib.h>
#include <iostream>
StatPane::StatPane(int x, int y,int width, int height)
:Pane(x,y,width,height)
{
    mvwprintw(pWindow,0,4, "< STATUS >");
}
StatPane::~StatPane()
{
    
}
void StatPane::SetTurn(int turn)
{
    this->turn = turn;
}
char* Shiptostr(Ship *ship)
{
    char* str = new char[ship->Getsize()+1];
    char Shiptochar;
    int Dlen;
    strcpy(str,"");
    Shiptype stype = ship->Gettype();
    if(stype == AIRCRAFT) 
    {
        strcpy(str,"AIRCRAFT : ");
        Shiptochar = 'A';
        Dlen=5;
    }
    if(stype == BATTLESHIP) {
        strcpy(str,"BATTLESHIP : ");
        Shiptochar = 'B';
        Dlen=4;
    }
    if(stype == CRUSIER) {
        strcpy(str,"CRUISER : ");
        Shiptochar = 'C';
        Dlen=3;
    }
    int length =strlen(str);
    for(int i=0;i<ship->Getsize();i++)
    {
        str[i+length]=Shiptochar;
    }
    for(int i=0;i<Dlen;i++)
    {
        str[i+ship->Getsize()+length] =' ';
    }
    return str;
}
void StatPane::Draw()
{
    wattron(pWindow,COLOR_PAIR(2));
    mvwprintw(pWindow,1,2, "TURN : 0");
    mvwprintw(pWindow,2,2, "AIRCRAFT : AAAAA");
    mvwprintw(pWindow,3,2, "BATTLESHIP : BBBB");
    mvwprintw(pWindow,4,2, "CRUISER : CCC");
    mvwprintw(pWindow ,5,2, "DESTROYER : DD DD");
    wattroff(pWindow,COLOR_PAIR(2));
    wrefresh(pWindow);

}
void StatPane::ShipDraw(vector<Ship*> &ships)
{
    wattron(pWindow , COLOR_PAIR(2));
    char tstr[20]="TURN : ";
    char buff[3];
    mvwprintw(pWindow,1,2,"         ");
    wrefresh(pWindow);
    sprintf(buff,"%d",turn);
    strcat(tstr, buff);
    mvwprintw(pWindow, 1,2,tstr);
    char *str="";
    for(int i=0;i<3;i++)
    {
        str = Shiptostr(ships[i]);
        mvwprintw(pWindow,i+2,2,str);
    }
   mvwprintw(pWindow,5,2,"DESTROYER : ");
   char sn[10]="";
     for(int i=0;i<ships[3]->Getsize();i++)
     {
          strcat(sn,"D");
     }
    for(int i=0;i<2-ships[3]->Getsize();i++)
    {
        strcat(sn," ");
    }
    strcat(sn," ");
    for(int i=0;i<ships[4]->Getsize();i++)
    {
        strcat(sn, "D");
    }
    for(int i=0;i<2-ships[4]->Getsize();i++)
    {
        strcat(sn, " ");
    }
    mvwprintw(pWindow,5,14,sn);
    mvwprintw(pWindow,2,18,"           ");
    mvwprintw(pWindow,3,19 ,"        ");
    mvwprintw(pWindow,4,15,"              ");
    wattroff(pWindow , COLOR_PAIR(2));
    wrefresh(pWindow);
    
}
