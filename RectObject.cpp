#include "RectObject.h"

float RectObject::GetLeftTopX()
{
    return coords[0].GetX();
}

float RectObject::GetLeftTopY()
{
    return coords[0].GetY();
}

float RectObject::GetRightTopX()
{
    return coords[1].GetX();
}

float RectObject::GetRightTopY()
{
    return coords[1].GetY();
}

float RectObject::GetRightBottomX()
{
    return coords[2].GetX();
}

float RectObject::GetRightBottomY()
{
    return coords[2].GetY();
}

float RectObject::GetLeftBottomX()
{
    return coords[3].GetX();
}

float RectObject::GetLeftBottomY()
{
    return coords[3].GetY();
}
