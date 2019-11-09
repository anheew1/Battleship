// C++ BattleShip 프로젝트
// 작성 일자 : 2018-05-15
// 학번 : 20171646 이름: 안희운
#include "Common.h"
#include "Player.h"
#include <ctime>

Player::Player(Map *pmap):map(pmap){
}
void Player::Mapset(Map *map)
{
    this -> map = map;
}
Hittype Player::Attack(position pos)
{
    bool bSucess=false;
    for(int k=0;k<Ships.size();k++)
    {
        Ship* vship = Ships[k];
       Hittype htype=vship->HitCheck(pos);
       if(htype != MISS) return htype;
    }
    return MISS;
}
Shiptype Player::setDestroy(Player *Defender,position pos)
{
    Shiptype type;
    for(int i=0;i<Defender->Ships.size();i++)
    {
        if(Defender->Ships[i]->ContainPosition(pos))
        {
            type = Defender->Ships[i]->Gettype();
            for(int j=0;j<Defender->Ships[i]->GetnPosition().size();j++)
            {
               map->setData(type,Defender->Ships[i]->GetnPosition()[j]);
            }
            return type;
        }
    }
    map->Draw();
}
void Player::SetHitResult(position pos,Hittype htype)
{
    Shiptype stype;
    if(pos.x<0 || pos.x>=MAP_SIZE || pos.y< 0 || pos.y >= MAP_SIZE)
        return;
    if(htype == MISS) 
    {
        stype = MISSPOINT;
    }
    else {
        stype = HITPOINT;
    }
    map->setData(stype,pos);
    map->Draw();
}
void Player::Render(StatPane *pane,int turn)
{
    pane->SetTurn(turn);
    pane->ShipDraw(Ships);
}
Player::~Player(){
    delete map;
    for (int i=0;i<Ships.size();i++)
    {
        Ship *pship = Ships[i];
        if(pship)
        delete pship;
    }
    Ships.clear();
}
void Player::SetupShip(vector<Ship*> &vships)
{

    
    srand((unsigned int)time(NULL));
    Ships = vships;
    for(int k=0;k<Ships.size();k++)
    {
        
        Ship *pship = Ships[k];
        position pos;
        pos.x = rand() % MAP_SIZE;
        pos.y = rand() % MAP_SIZE;
        // 배에다 공격하는 식으로
        int interval = rand()%5>0?0:1;
        while(true)
        {
            
            Shiptype dataType = map ->GetData(pos);
            if(dataType != SHIP_NONE){
                 pos.x = rand() % MAP_SIZE;
                 pos.y = rand() % MAP_SIZE;
                continue;
            }
            position dir;
            if(rand()%2)
                dir.x = rand() %2 ? -1:1;
            else
                dir.y = rand() %2 ? -1:1;
            bool bSucess = true;
            pship->SetPosition(0,pos);
           for(int i=interval;i<pship->Getsize();i++)
           {
               
               pos = pos + dir;
               if(pos.x >= MAP_SIZE || pos.x<0 ||pos.y >= MAP_SIZE || pos.y<0)
               {
                   bSucess=false;
                   break;
               }
               
               dataType = map->GetData(pos);
               if(dataType != SHIP_NONE){
                   bSucess =false;
                   break;
               }
               pship->SetPosition(i,pos);
           }
           if(bSucess == true)
           {
               //배치완료
               for(int i=0;i<pship->Getsize();i++)
               {
                   map->setData(pship->Gettype(),pship->GetPosition()[i]);
               }
               break;
           }
           else
           {
               pos.x = rand()%MAP_SIZE;
               pos.y = rand()%MAP_SIZE;
           }
        }
    }
}