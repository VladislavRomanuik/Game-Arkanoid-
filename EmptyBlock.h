#pragma once
#include "Block.h"
class EmptyBlock :
    public Block
{
public:
    EmptyBlock(){}
    EmptyBlock(bool IsBonus) : Block(IsBonus){}
  
    EmptyBlock(bool IsBonus, int typeBonus1) : Block(IsBonus, typeBonus1){}
    void DrawSelf(float newX, float newY, float newBonusY)
    {   
        bonus->DrawSelf(newX, newY, newBonusY);
    }
};

