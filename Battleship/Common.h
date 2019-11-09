/* 소프트웨어 학부 20171646 안희운*/
#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <stdlib.h>
struct position{
    position() : x(0),y(0){};
    position(int x_, int y_) : x(x_),y(y_){};
    int x;
    int y;
    friend std::ostream& operator << (std::ostream& os,position pos)
    {
        os << "x" << pos.x << " ";
        os << "y" << pos.y;
        return os;
    }
    position operator-(const position &pos) const
    {
        position retpos;
        retpos.x=x-pos.x;
        retpos.y=y-pos.y;
        return retpos;
    }
    position operator+(position &pos) const
    {
        position retpos;
        retpos.x=x+pos.x;
        retpos.y=y+pos.y;
        return retpos;
    }
    bool operator==(position &pos) const
    {
        if(x == pos.x && y == pos.y) return true;
        return false;
    }

};
enum Shiptype{
    DATA_ERROR =-1,
    SHIP_NONE,
    AIRCRAFT,
    BATTLESHIP,
    CRUSIER,
    DESTROYER,
    HITPOINT,
    MISSPOINT,
    DESTROYPOINT,
    SHIP_CANT_PLACE
};
enum Hittype{
    HIT,MISS,DESTROY,GAME_CLEAR
};
enum GameMode{
    PLAY_INPUT,PLAY_RANDOM,PLAY_FOLLOW_AI
};
static const int MAP_SIZE = 8;