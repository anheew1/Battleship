/* 소프트웨어 학부 20171646 안희운*/
#include "CBattleShipApp.h"
#include "ModePane.h"
#include <ncurses.h>

void CBattleShipApp::Init()
{
   

    //컬러 세팅
    init_pair(1, COLOR_GREEN, COLOR_BLUE);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);
    init_pair(3, COLOR_RED,COLOR_BLACK);
    init_pair(4, COLOR_BLUE,COLOR_BLACK);
    init_pair(5, COLOR_GREEN, COLOR_WHITE);
    init_pair(6, COLOR_GREEN, COLOR_RED);
    init_pair(7, COLOR_GREEN, COLOR_YELLOW);



    Attackmap = new Map(2,15,"Attacker");
    Defendmap = new Map(2,4,"Defender");
    
    if(gamemode == PLAY_INPUT){
    pStatPane = new StatPane(30, 3, 30 ,7);
    pInputPane = new InputPane(30,15,30,4);
    }
    else 
     pStatPane = new StatPane(30, 10, 30 ,7);
    Manager = new GameManager();
    Manager->Setmode(gamemode);
    Manager->SetMap(Attackmap,Defendmap);
    Manager->SetStat(pStatPane);
    Manager->Init();
}

void CBattleShipApp::Update()
{
    
       if(gamemode == PLAY_INPUT)
       {
           while(true)
           {
            string input =pInputPane->GetInput();
            Manager->AttackByInput(input);
            if(Manager->GetDestroyed()==5) break;
            }
       }
        if(gamemode == PLAY_RANDOM)
        {
            vector<int> turnstime;
            for(int i=0;i<10;i++)
            {
                Manager->AttackByRandom();
                int turn = Manager->GetTurn()-1;
                turnstime.push_back(turn);
                Attackmap = new Map(2,15,"Attacker");
                Defendmap = new Map(2,4,"Defender");
                Manager->SetMap(Attackmap,Defendmap);
                Manager->Init();
                Render();
            }
            float sum=0;
            for(int i=0;i<10;i++)
            {
                sum+= turnstime[i];
            }
            move(20,15);
            printw("  Average Turn is : %6.3f" , sum/10);
        }
        if(gamemode == PLAY_FOLLOW_AI)
        {
            vector<int> turnstime;
            for(int i=0;i<10;i++)
            {
                Manager->AttackByAI();
                int turn = Manager->GetTurn()-1;
                turnstime.push_back(turn);
                Attackmap = new Map(2,15,"Attacker");
                Defendmap = new Map(2,4,"Defender");
                Manager->SetMap(Attackmap,Defendmap);
                Manager->Init();
                Render();
            }
            float sum=0;
            for(int i=0;i<10;i++)
            {
                sum+= turnstime[i];
            }
            move(20,15);
            printw("  Average Turn is : %6.3f" , sum/10);
        }
        
}
void CBattleShipApp::Play()
{
    SelectGamemode();
    Init();
    Render();
    Update();
    Destroy();
}
void CBattleShipApp::Render()
{
    mvprintw(1,1,"<< Battle Ship Game >>");

    Attackmap->Draw();
    Defendmap->Draw();
    pStatPane->Draw();
    if(gamemode == PLAY_INPUT)
    pInputPane->Draw();
    refresh();
}
void CBattleShipApp::Destroy()
{
    getch();
    endwin();
    delete Attackmap;
    delete Defendmap;
    delete modepane;
    delete pStatPane;
    if(gamemode == PLAY_INPUT)
    delete pInputPane;
    delete Manager;
}
void CBattleShipApp::SelectGamemode()
{
    initscr();
    start_color();
    refresh();
    modepane =  new ModePane(5,5,30,12);
    modepane->Draw();
    gamemode  = modepane->GetInput();
    modepane->clear();
    delete modepane;
}