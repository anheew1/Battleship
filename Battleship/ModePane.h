#pragma once
#include "Pane.h"
class ModePane: public Pane
{
public:
    ModePane(int x, int y,int width, int height);
    ~ModePane();
    GameMode GetInput();
    void Draw();
    void clear();
};