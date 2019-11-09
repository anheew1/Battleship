/* 소프트웨어 학부 20171646 안희운*/
#include "Ship.h"
Ship::Ship(int size,Shiptype type){
    this->size = size;
    this->type = type;
    pos.resize(6);
}
Ship::~Ship(){

}
string Ship::Getname()
{
    return name;
}

vector<position> Ship::GetPosition() 
{
    return pos;
}
vector<position> Ship::GetnPosition()
{
    return npos;
}
void Ship::ClearPosition()
{
    pos.clear();
    pos.resize(6);
}
int Ship::Getsize()
{
    return size;
}
Hittype Ship::HitCheck(const position& ppos)
{
   for(int i=0;i<size;i++)
        {
            if(ppos == pos[i])
            {
                npos.push_back(ppos);
                pos.erase(pos.begin()+i);
                size-=1;
                if(size == 0) return DESTROY;
                return HIT;
            }
        }
        return MISS;
}

void Ship::SetPosition(int index, position &ppos)
{
    pos[index] = ppos;
}
Shiptype Ship::Gettype()
{
    return type;
}
bool Ship::ContainPosition(position &ppos)
{
    for(int i=0;i<npos.size();i++)
    {
        if(ppos == npos[i]) return true;
    }
    return false;
}
