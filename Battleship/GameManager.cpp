/* 소프트웨어 학부 20171646 안희운*/
#include "GameManager.h"
#include "Player.h"
#include "Common.h"
#include "cstring"
#include "vector"
#include "StatPane.h"
#include <algorithm>
#include <ctime>

#define NOTFOUND -1
GameManager::GameManager(){
    Attacker = NULL;
    Defender = NULL;
    amap=NULL;
    dmap=NULL;
    pane = NULL;
    shoot.reserve(65);
};
GameManager::~GameManager(){
    if(Attacker)
        delete Attacker;
    if(Defender)
        delete Defender; 
};
void GameManager::SetMap(Map *attack,Map *defend)
{
    amap = attack;
    dmap= defend;
}
void GameManager::SetStat(StatPane *pane)
{
    this->pane = pane;
}
void GameManager::Setmode(GameMode mode)
{
    pGamemode = mode;
}
int GameManager::GetTurn()
{
    return turn;
}
void GameManager::SetTurn(int t)
{
    turn = t;
}
void GameManager::AddTurn()
{
    turn++;
}
int GameManager::GetDestroyed(){
    return destroyed;
}
void GameManager::Init(){
    Attacker = new Player(amap);
    Defender = new Player(dmap);
    turn = 1;
    destroyed=0;

    std::vector<Ship*> vecship;
    vecship.push_back(new Ship(5,AIRCRAFT));
    vecship.push_back(new Ship(4,BATTLESHIP));
    vecship.push_back(new Ship(3,CRUSIER));
    vecship.push_back(new Ship(2,DESTROYER));
    vecship.push_back(new Ship(2,DESTROYER));

    Defender->SetupShip(vecship);
};
void GameManager::AttackByInput(string str)
{
    if(str.length()>2) return;
    int px = NOTFOUND,py = NOTFOUND;
    for(int i=0;i<MAP_SIZE;i++) 
    {
        
        if(str[0] == (char)('A'+i)){
            px = i;
            break;
        }
    }
    if(px == NOTFOUND) return;
    py = str[1]-'1';
    if(py<0 || py>=MAP_SIZE) return;
    move(20,40);
    position pos;
    pos.x=px;pos.y=py;
    for(int i=0;i<shoot.size();i++){
        if(pos == shoot[i]) return;
    }
    Hittype htype =Defender->Attack(pos);
    if(htype == DESTROY) destroyed++;
    shoot.push_back(pos);
    Attacker->SetHitResult(pos,htype);
    if(htype == DESTROY)
    {
        Attacker->setDestroy(Defender,pos);
        amap->Draw();
    }
    Defender->Render(pane,turn);
   // Hittype hit =Defender->Attack(px,py);// 디펜더에 공격해서 맞추는지
    //Attacker->SetHitResult(px,py,hit);// 맞췄다면 표시
    AddTurn();// 턴 증가
}
void shuffle(int* arr, int size){ 
   srand(time(NULL)); 
   for(int i = size-1; i > 0; i--){ 
         int j = rand() % (i+1); 
         swap(arr[i], arr[j]);
   } 
}

void GameManager::AttackByRandom()
{
    int *randpos = new int[MAP_SIZE*MAP_SIZE];
    for(int i=0;i<MAP_SIZE*MAP_SIZE;i++)
    {
        randpos[i] = i;
    }
    shuffle(randpos,MAP_SIZE*MAP_SIZE);
    while(true){
    delay_output(50);
    position pos(randpos[turn-1]%MAP_SIZE,randpos[turn-1]/MAP_SIZE);
    Hittype htype =Defender->Attack(pos);
    if(htype == DESTROY) destroyed++;
    
    shoot.push_back(pos);
    Attacker->SetHitResult(pos,htype);
    if(htype == DESTROY)
    {
        Attacker->setDestroy(Defender,pos);
        amap->Draw();
    }
    Defender->Render(pane,turn);
    if (destroyed==5) break;
    AddTurn();// 턴 증가
    }
    delete randpos;
}
int twotoone(const position &pos)
{
    int sum=0;
    sum += pos.x;
    sum += MAP_SIZE*pos.y;
    return sum;
}
position onetotwo(int n)
{
    position pos;
    pos.y = n/MAP_SIZE;
    pos.x = n%MAP_SIZE;
    return pos;
}
void GameManager::Targetting(position startpos)
{
    delay_output(100);
    position pos(startpos.x,startpos.y-1);
    int dir;
    Hittype hit=MISS;
    if(amap->isNone(pos))
        hit = Defender->Attack(pos);
    if(hit != MISS) 
    {
        dir=0;
    }
    else {
    pos.x= startpos.x+1;
    pos.y = startpos.y;
    if(amap->isNone(pos))
        hit = Defender->Attack(pos);

    if(hit != MISS ) dir=1;
    else {
    
    pos.x = startpos.x;
    pos.y = startpos.y+1;
    if(amap->isNone(pos))
        hit = Defender->Attack(pos);
    if(hit != MISS ) dir=2;
    else{
        pos.x = startpos.x-1;
        pos.y = startpos.y;
        if(amap->isNone(pos))
            hit =Defender->Attack(pos);
        dir=3;
        }
     }
    }
    Attacker->SetHitResult(pos,hit);
    if(hit == DESTROY){
        Attacker->setDestroy(Defender,pos);
        destroyed++;
    }
    Defender->Render(pane,turn);
    AddTurn();
    if(hit == DESTROY) return;
    Hittype htype;
    int count=0;
    while(true)
    {
        if(count>3) return;
        position normalpos = pos;
        delay_output(300);
        if(dir == 0)
        {
            pos.y = pos.y-1; 
        }
        else if(dir == 1)
        {
            pos.x = pos.x+1;
        }
        else if(dir ==2 )
        {
            pos.y = pos.y+1;
        }
        else
        {
            pos.x = pos.x-1;
        }
        if(!amap->isNone(pos)) {
            if(count %2 == 0)
            dir=(dir+2)%4;
            else
            dir=(dir+1)%4;
            count++;
            pos = startpos;
            continue;
        }
        htype = Defender->Attack(pos);
        Attacker->SetHitResult(pos,htype);
        if(htype == DESTROY){
            Attacker->setDestroy(Defender,pos);
            destroyed++;
        }
        Defender->Render(pane,turn);
        AddTurn();
        // Destroy 의 예외의 경우는 겹쳐있을 때  처음이 BattleShip인데
        //두번째가 Cruiser여서 파괴되는 경우가 존재한다 이때는 Start로 돌아가서 해야된다.

        /*
        그보다도 MISS 의 예외경우는 양쪽 둘 다 갔는데 없을 경우 양옆으로 존재한다는 뜻
        */
        if(htype == DESTROY)
        {
            for(int i=0;i<MAP_SIZE*MAP_SIZE;i++)
            {
                position ppos(i%MAP_SIZE,i/MAP_SIZE);
                if(amap->isHIT(ppos))
                    Targetting(ppos);
            }
            
            break;
        }
        if(htype == MISS)
        {
            if(count %2 == 0)
            dir=(dir+2)%4;
            else
            dir=(dir+1)%4;
            count++;
            pos = startpos;
        }
    }
}

void GameManager::AttackByAI()
{
    srand(time(NULL));
    position pos;
    position startpos;
    int *randpos = new int[MAP_SIZE*MAP_SIZE];
    for(int i=0;i<MAP_SIZE*MAP_SIZE;i++){
        randpos[i] = i;
    }
    int randcount=0;
    shuffle(randpos,MAP_SIZE*MAP_SIZE);
    while(true)
    {
        delay_output(100);
        pos = onetotwo(randpos[randcount]);
        randcount++;
        if(!amap->isNone(pos)) continue;
        Hittype htype =Defender->Attack(pos);
        if(htype == DESTROY) destroyed++;
        Attacker->SetHitResult(pos,htype);
        if(htype == DESTROY)
        {
            Attacker->setDestroy(Defender,pos);
            amap->Draw();
        }
        Defender->Render(pane,turn);
        if (destroyed==5) break;
        AddTurn();
        if(htype == HIT)
        {
            Targetting(pos);
        }   
    }
    delete[] randpos;

}
