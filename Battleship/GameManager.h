// C++ BattleShip 프로젝트
// 작성 일자 : 2018-05-15
// 학번 : 20171646 이름: 안희운
#pragma once
#include "Player.h"
#include "Common.h"
#include "Ship.h"
#include "StatPane.h"
class GameManager{
private:
    Player *Attacker;
    Player *Defender;
    GameMode pGamemode;
    vector<Ship*> Ships;
    Map *amap,*dmap;
    int turn;
    StatPane *pane;
    vector<position> shoot;
    int destroyed;
    void Targetting(position startpos);
public:
    GameManager();
    ~GameManager();
    void Init();
    void Setmode(GameMode mode);
    int GetTurn();
    void SetTurn(int t);
    void AddTurn();
    void AttackByInput(string str);
    void AttackByRandom();
    void AttackByAI();
    
    void SetMap(Map *attack,Map *defend);
    void SetStat(StatPane *pane);
    int GetDestroyed();
};