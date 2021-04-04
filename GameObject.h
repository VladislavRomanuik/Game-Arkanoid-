#pragma once
#include "GL/freeglut.h"
#include <string>
using namespace std;

class GameObject
{
private:
    float x = 0.0f;
    float y = 0.0f;
    string path;
public:
    char text[256];
    string GetPath(string nameFile);
    float GetX();
    float GetY();
    void SetX(float x);
    void SetY(float y);
    void SetXY(float x, float y);
    void InitTexture();
    virtual void DrawSelf(float newX, float newY){}
    virtual void SetCoords(float newX, float newY){}
    void DrawString(void* font, const char* text, float x, float y);
};

