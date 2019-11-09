// C++ BattleShip 프로젝트
// 작성 일자 : 2018-05-15
// 학번 : 20171646 이름: 안희운
#pragma once
#include "Pane.h"
#include <string>
#include <stdlib.h>
class InputPane: public Pane{
    public:
    ~InputPane();
    void Draw();
    InputPane(int x, int y , int width, int height);
    void Printresult();
    std::string GetInput();
};