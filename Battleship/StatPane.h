// C++ BattleShip 프로젝트
// 작성 일자 : 2018-05-15
// 학번 : 20171646 이름: 안희운
#pragma once
#include "Pane.h"
#include "Common.h"
#include "Ship.h"
#include <vector>
#include "cstring"
class StatPane: Pane
{
public:
    StatPane(int x, int y, int width, int height);
    ~StatPane();
    void Draw();
    void ShipDraw(vector<Ship*> &ships);
    void SetTurn(int turn);
private:
    int turn;
};