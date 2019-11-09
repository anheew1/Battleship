// C++ BattleShip 프로젝트
// 작성 일자 : 2018-05-15
// 학번 : 20171646 이름: 안희운
#pragma once
#include "Common.h"
#include "Pane.h"
#include "string"
class Map:Pane{
    public:
    Map(int x,int y, std::string name);
    ~Map();
    Shiptype GetData(const position &pos);
    Shiptype GetData(int x, int y);
    void Draw();
    void setData(Shiptype ship,const position &pos);
    char ShipTochar(Shiptype ship);
    void setDestroy(Map *Attack, Ship* ship);
    bool isNone(position &pos);
    bool isHIT(position &pos);
    void clear();
protected:
    Shiptype mData[MAP_SIZE][MAP_SIZE];
};