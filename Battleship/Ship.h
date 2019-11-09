// C++ BattleShip 프로젝트
// 작성 일자 : 2018-05-15
// 학번 : 20171646 이름: 안희운
#pragma once
#include "Common.h"
#include <iostream>
#include <string>
using namespace std;

class Ship{
public:
Ship(int size,Shiptype type);
virtual ~Ship();
string Getname();
vector<position> GetPosition();
vector<position> GetnPosition();
void ClearPosition();
int Getsize();
Shiptype Gettype();
Hittype HitCheck(const position& pos);
void SetPosition(int index,position &ppos);
void AddPosition(position &ppos);
bool ContainPosition(position &ppos);
protected:
    int HP;
    int size;
    string name;
    vector<position> pos;
    vector<position> npos;
    Shiptype type;
};
