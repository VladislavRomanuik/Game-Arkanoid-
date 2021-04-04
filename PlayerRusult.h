#ifndef ADD_H
#define ADD_H
#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <vector>
#include "GameObject.h"

using namespace std;

const int lengthName = 20;
const long int N = 1000;

struct PlayerInfo
{
    string name;
    int score;
    char level[2];
    char day[3];
    char month[2];
    char time[8];
};

class ResultPlayer : public GameObject
{
private:
    int countTop = 7;
    int countRow = 0;
    ifstream fin;
public:
    PlayerInfo player[N];

    void ReadData()
    {
        countRow = 0;
        fin.open(GetPath("Test.txt"));
        if (!fin.fail())
        {
            do
            {
                fin >> player[countRow].name >> player[countRow].score >> player[countRow].level >> player[countRow].day >> player[countRow].month >> player[countRow].time;
                countRow++;
            } while (fin.good());
            fin.close();
        }
    }

    void DrawTopPlayer()
    {
        float coord_x = -0.55f, coord_y = 0.15f;
        for (int i = 0; i < countTop; i++)
        {
            sprintf_s(text, player[i].name.c_str());
            DrawString(GLUT_BITMAP_TIMES_ROMAN_24, text, coord_x, coord_y);
            coord_x+=0.4f;
            sprintf_s(text, "%d", player[i].score);
            DrawString(GLUT_BITMAP_TIMES_ROMAN_24, text, coord_x, coord_y);
            coord_x += 0.3f;
            sprintf_s(text, player[i].level);
            DrawString(GLUT_BITMAP_TIMES_ROMAN_24, text, coord_x, coord_y);
            coord_x += 0.2f;
            sprintf_s(text, player[i].day);
            DrawString(GLUT_BITMAP_TIMES_ROMAN_24, text, coord_x, coord_y);
            coord_x += 0.05f;
            sprintf_s(text, player[i].month);
            DrawString(GLUT_BITMAP_TIMES_ROMAN_24, text, coord_x, coord_y);
            coord_x += 0.05f;
            sprintf_s(text, player[i].time);
            DrawString(GLUT_BITMAP_TIMES_ROMAN_24, text, coord_x, coord_y);
            coord_x = -0.55f;
            coord_y -= 0.125f;
        }
        //glFlush();
    }

    void SortFile()
    {
        ReadData();
        PlayerInfo tempSwap;
        for (int i = 0; i < countRow; i++)
        {
            for (int j = 0; j < countRow; j++)
            {
                if (player[i].score > player[j].score)
                {
                    tempSwap = player[i];
                    player[i] = player[j];
                    player[j] = tempSwap;
                }
            }
        }   
        DrawTopPlayer();
    }
};
#endif
