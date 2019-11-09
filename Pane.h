// C++ BattleShip 프로젝트
// 작성 일자 : 2018-05-15
// 학번 : 20171646 이름: 안희운
#include <ncurses.h>
#pragma once
#include <vector>
#include "Ship.h"
class Pane{
    //나머지 헤더파일의 include 는 Cpp에서
protected:
    int pheight;
    int pwidth;
    int px;
    int py;
    WINDOW* pWindow;
public:
    ~Pane();
    Pane(int x, int y, int width , int height);
    virtual void Draw();
};