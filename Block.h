#pragma once
#include "RectObject.h"
#include "Bonus.h"
#include "EmptyBonus.h"
class Block :
    public RectObject
{
protected:
    const float xLeft = -0.3f;
    const float xRight = -0.2f;
    const float yTop = 0.8f;
    const float yBottom = 0.7;
public:
    bool BonusFall = false;
    string typeBlock;
    int countColision = 0;
    bool IsBonus = false;
    Bonus* bonus;
    float newBonusY = 0.0f;
    Block() {}
    Block(string typeBlock)
    {
        bonus = new EmptyBonus(0);
        this->typeBlock = typeBlock;
    }
    Block(bool IsBonus);
    Block(bool IsBonus, int typeBonus1);
    bool IsActivBonus = false;

    virtual void DrawSelf(float newX, float newY, float newBonusY);
    void SetCoords(float newX, float newY);
};

