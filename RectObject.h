#pragma once
#include "GameObject.h"
class RectObject :
    public GameObject
{
protected:
    GameObject coords[4];
public:
    float GetLeftTopX();
    float GetLeftTopY();
    float GetRightTopX();
    float GetRightTopY();
    float GetRightBottomX();
    float GetRightBottomY();
    float GetLeftBottomX();
    float GetLeftBottomY();
};

