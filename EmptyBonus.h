#pragma once
#include "Bonus.h"
class EmptyBonus :
    public Bonus
{
public:
    EmptyBonus(int typeBonus)
    {
        this->typeBonus = typeBonus;
    }
    void DrawSelf(float blockX, float blockY, float newY){}
};

