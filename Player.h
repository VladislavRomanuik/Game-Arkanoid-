#pragma once
#include "RectObject.h"
class Player :
    public RectObject
{
private:
    const float xLeft = -0.1f;
    const float xRight = 0.1f;
    const float yTop = -0.75f;
    const float yBottom = -0.85f;

public:
    void DrawSelf(float newX, float Y, float sizeX);
    void SetCoords(float newX, float newY, float sizeX);
};

