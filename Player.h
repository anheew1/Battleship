// C++ BattleShip 프로젝트
// 작성 일자 : 2018-05-15
// 학번 : 20171646 이름: 안희운
#pragma once
#include "Common.h"
#include <vector>
#include "Ship.h"
#include "Map.h"
#include "StatPane.h"
class Player{
    private:
    vector<Ship*> Ships;
    Map *map;
    public:
    Player(Map *pmap);
    ~Player();
    Hittype Attack(position pos);
    void Mapset(Map *map);
    void Render(StatPane *pane,int turn);
    void SetHitResult(position pos, Hittype phit);
    void SetupShip(vector<Ship*> &vships);
    Shiptype setDestroy(Player *Defender, position pos);
};