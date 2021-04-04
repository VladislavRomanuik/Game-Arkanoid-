#pragma once
#include "RectObject.h"
class Bonus :
    public RectObject
{
private:
    const float xLeft = -0.2666f;
    const float xRight = -0.2356f;
    const float yTop = 0.77f;
    const float yBottom = 0.72f;
    //0 - Left 1 - Right 2 - Top 3 - Bottom ||| 0 - Point 1 - Size 2 - Life 3 - Die 
    float arrayCoord[4][4] = 
    { 
        { -0.27f, -0.23f, 0.77f, 0.72f },
        { -0.29f, -0.21f, 0.76f, 0.73f },
        { -0.2666f, -0.2356f, 0.77f, 0.72f },
        { -0.26f, -0.23f, 0.77f, 0.72f }
    };
public:
    bool IsFall = false;
    int bonusTime = 300;
    int typeBonus;
    bool IsActivBonus = false;    
    virtual void DrawSelf(float blockX, float blockY, float newY);
    void SetCoords(float blockX, float blockY, float newY);
};

