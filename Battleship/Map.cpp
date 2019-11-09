// C++ BattleShip 프로젝트
// 작성 일자 : 2018-05-15
// 학번 : 20171646 이름: 안희운
#include "string"
#include "Map.h"
#include "Common.h"
#include <ncurses.h>
Shiptype Map::GetData(const position &pos)
{
        if(pos.x<0 || pos.x>=MAP_SIZE || pos.y<0 || pos.y>=MAP_SIZE)
            return DATA_ERROR;
        return mData[pos.x][pos.y];
};
void Map::setData(Shiptype ship,const position &pos){
    mData[pos.x][pos.y] = ship;
}
Shiptype Map::GetData(int x, int y)
{
    if(x<0 || x>=MAP_SIZE || y<0 || y>=MAP_SIZE)
        return DATA_ERROR;
    return mData[x][y];

}
bool Map::isNone(position &pos)
{
    if(pos.x<0 || pos.x>=MAP_SIZE || pos.y<0 || pos.y>=MAP_SIZE)
        return false;
    return (mData[pos.x][pos.y] == SHIP_NONE);
}
bool Map::isHIT(position &pos)
{
    if(pos.x<0 || pos.x>=MAP_SIZE || pos.y<0 || pos.y>=MAP_SIZE)
        return false;
    return (mData[pos.x][pos.y] == HITPOINT);
}
Map::Map(int x, int y, std::string name):Pane(x,y,MAP_SIZE+2 ,MAP_SIZE+2)
{
    for(int i=0;i<MAP_SIZE;i++)
    {
        for(int j=0;j<MAP_SIZE;j++)
        {
            mData[i][j] = SHIP_NONE;
        }
    }
    for(int i=0;i <MAP_SIZE;++i)
    {
        mvprintw(i+1+py,px-1,"%c", 'A'+i);
        mvprintw(py+pheight,px+i+1,"%d",1+i);
    }
    mvwprintw(pWindow,0,1, name.c_str());
};
Map::~Map()
{
    wclear(pWindow);
    wrefresh;
}
char Map::ShipTochar(Shiptype ship)
{
    if(ship == SHIP_NONE) return '0';
    if(ship == AIRCRAFT) return 'A';
    if(ship == BATTLESHIP) return 'B';
    if(ship == CRUSIER) return 'C';
    if(ship == DESTROYER) return 'D';
    if(ship == HITPOINT) return 'H';
    if(ship == MISSPOINT) return 'M';
    return 'E';
}
void Map::Draw()
{
    
    for(int i=0;i<MAP_SIZE;i++)
    {
        for(int j=0;j<MAP_SIZE;j++)
        {
            
            char type = ShipTochar(mData[i][j]);
            if(type == 'A' || type == 'B' || type=='C' || type =='D' ||type=='E')
            {
                wattron(pWindow,COLOR_PAIR(5));
                mvwprintw(pWindow,i+1,j+1, "%c" , type);
                wattroff(pWindow,COLOR_PAIR(5));
            }
            else if(type=='H')
            {
                wattron(pWindow,COLOR_PAIR(6));
                mvwprintw(pWindow,i+1,j+1, "%c" , type);
                wattroff(pWindow,COLOR_PAIR(6));
            }
            else if(type == 'M')
            {
                wattron(pWindow,COLOR_PAIR(7));
                mvwprintw(pWindow,i+1,j+1, "%c" , type);
                wattroff(pWindow, COLOR_PAIR(7));
            }
            else
            {
                wattron(pWindow,COLOR_PAIR(1));
                mvwprintw(pWindow,i+1,j+1, "%c" , type);
                wattroff(pWindow, COLOR_PAIR(1));
            }
        }
    }
    
    wrefresh(pWindow);
}
