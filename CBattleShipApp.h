// C++ BattleShip 프로젝트
// 작성 일자 : 2018-05-15
// 학번 : 20171646 이름: 안희운
#pragma once
#include "StatPane.h"
#include "Map.h"
#include "InputPane.h"
#include "GameManager.h"
#include "ModePane.h"
class CBattleShipApp{
    private:
    InputPane* pInputPane;
    StatPane* pStatPane;
    ModePane* modepane;
    Map* Attackmap;
    Map* Defendmap;
    GameManager* Manager;
    GameMode gamemode;
    public:
    ~CBattleShipApp(){};
    CBattleShipApp(){};
    void SelectGamemode();
    void Destroy();
    void Init();
    void Play();
    void Render();
    void Update();
};