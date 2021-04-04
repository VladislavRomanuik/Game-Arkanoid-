#pragma once
#include "GameObject.h"
class Display :
    public GameObject
{
private:

    void DrawWindow(unsigned int texture, float alpha);
public:
    void DisplayRegulations(unsigned int texture);
    void DisplayWin(float alpha);
    void DisplayGame();
    void DisplayLose(float alpha);
    void DisplayMainMenu(float alpha);
    void DisplayRecords();
    void DrawEnterNamePanel(bool Is);
};

