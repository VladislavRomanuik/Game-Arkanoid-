#include <GL/freeglut.h>
#include<iostream>
#include "Game.h"
#include "Display.h"
#include "PlayerRusult.h"
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

unsigned int texture[25];
vector <string> names(1);
Game game;
Display display;
ResultPlayer result;
ofstream rec;
bool IsPause = false;
bool IsEnterName = false;
bool IsPanelNotMenu = false;
bool IsSelectLan = false;
bool Is = false;
int SCREN_HEIGHT, SCREN_WIDTH, HALF_SCEEN_HEIGHT, HALF_SCREEN_WIDTH;
int typeLan = 15;//14 - rus, 15 - eng
int level_one_player = 2;
int level_two_player = 5;
int countCreateNewLevel = 0;
float coord_x, coord_y;
int stateKeyEvent[4] = { 0, 0, 0, 0 }; // 1 - Left1| 2 - Right1| 3 - Left2| 4 - Right2|
void DisplayAll();

enum State
{
    State_MainMenu = 0,
    State_Game = 1,
    State_WinPanel = 2,
    State_LosePanel = 3,
    State_Regulations = 4,
    State_Record = 5
};

class State_
{
public:
    State_(int state_prg)
    {
        gState = state_prg;
    }
    int gState;
};

State_* gState = new State_(State_MainMenu);
State_* lastState = new State_(State_MainMenu);

void Timer(int = 0)
{
    DisplayAll();
    glutTimerFunc(50, Timer, 0);
}

void DisplayAll()
{
    if (stateKeyEvent[0] == 1)
    {
        if (game.newPlayerX[0] < game.borderCoord - 0.09f)
        {
            game.newPlayerX[0] += 0.02f;
        }
    }
    if (stateKeyEvent[1] == 1)
    {
       if (game.newPlayerX[0] > -game.borderCoord + 0.09f)
       {
           game.newPlayerX[0] -= 0.02f;
       }
    }
    if (stateKeyEvent[2] == 1)
    {
        if (game.newPlayerX[1] < game.borderCoord - 0.09f)
        {
            game.newPlayerX[1] += 0.02f;
        }
    }
    if (stateKeyEvent[3] == 1)
    {
        if (game.newPlayerX[1] > -game.borderCoord + 0.09f)
        {
            game.newPlayerX[1] -= 0.02f;
        }
    }

    if (game.GetIsGameLose())
    {
        game.IsGame = false;
        if (!IsPanelNotMenu)
        {
            gState->gState = State_LosePanel;
        }
        if (countCreateNewLevel < 1)
        {
            if (!game.IsDoublePlayer)
            {
                rec.open(display.GetPath("Test.txt"), std::ios::app);
                time_t now = time(0);
                tm* ltm = localtime(&now);
                rec << endl << names[0] << " " << game.points << " " << level_one_player << " " << ltm->tm_mday << " " << 1 + ltm->tm_mon << " " << ltm->tm_hour << ":" << ltm->tm_min;
            }

            countCreateNewLevel++;
            rec.close();
        }
    }

    if (game.GetIsGameWin())
    {
        game.IsGame = false;
        if (!IsPanelNotMenu)
        {
            gState->gState = State_WinPanel;
        }
        if (countCreateNewLevel < 1)
        {
            
            if (!game.IsDoublePlayer)
            {
                rec.open(display.GetPath("Test.txt"), std::ios::app);
                time_t now = time(0);
                tm* ltm = localtime(&now);
                rec << endl << names[0] << " " << game.points << " " << level_one_player << " " << ltm->tm_mday << " " << 1 + ltm->tm_mon << " " << ltm->tm_hour << ":" << ltm->tm_min;
                level_one_player++;
                countCreateNewLevel++;
                rec.close();
            }
            else
            {
                level_two_player++;
            }
        }
    }

    switch (gState->gState)
    {
        case State_MainMenu:
        {
            if (IsEnterName)
            {
                display.DisplayMainMenu(0.3f);
                display.DrawEnterNamePanel(true);
                ostringstream oss;
                oss << names[0];
                sprintf_s(display.text, (const char*)oss.str().c_str());
                display.DrawString(GLUT_BITMAP_TIMES_ROMAN_24, display.text, -0.05f, 0.0f);
                glFlush();
            }
            else if (Is)
            {
                display.DisplayMainMenu(0.3f);
                display.DrawEnterNamePanel(false);
                glFlush();
            }
            else
            {
                display.DisplayMainMenu(1.0f);
                glFlush();
            }
            break;
        }

        case State_Game:
        {
            display.DisplayGame();
            game.DisplayGame();
            break;
        }

        case State_LosePanel:
        {
            if (Is)
            {
                display.DisplayLose(0.3f);
                display.DrawEnterNamePanel(false);
                glFlush();
            }
            else
            {
                display.DisplayLose(1.0f);
                glFlush();
            }
            break;
        }

        case State_WinPanel:
        {
            if (Is)
            {
                display.DisplayWin(0.3f);
                display.DrawEnterNamePanel(false);
                glFlush();
            }
            else
            {
                display.DisplayWin(1.0f);
                glFlush();
            }
            break;
        }

        case State_Regulations:
        {
            display.DisplayRegulations(texture[typeLan]);
            break;
        }

        case State_Record:
        {
            display.DisplayRecords();
            result.SortFile();
            glFlush();
            break;
        }
    }
}

void processNormalKeys(unsigned char key, int x, int y)
{
    switch (key)
    {
        case VK_RETURN:
            if (!IsEnterName)
            {
                game.SetIsBall(true);
                IsPause = false;
                break;
            }
    }
    if (IsEnterName)
    {
        if (key == 13)// enter key
        {
            names.push_back("");
            IsEnterName = false;
        }
        else if (key == 8)// backspace
        {
            if (!names.back().empty())
            {
                names.back().pop_back();
            }
        }
        else
        {
            names.back().push_back(key);
        }
    }
}

void processSpecialKeys(int key, int x, int y)
{
    switch (key)
    {
        case GLUT_KEY_F1:
            stateKeyEvent[3] = 1;
            break;
        case GLUT_KEY_F2:
            stateKeyEvent[2] = 1;
            break;
        case GLUT_KEY_RIGHT:
            stateKeyEvent[0] = 1;
            break;
        case GLUT_KEY_LEFT:
            stateKeyEvent[1] = 1;
            break;
    }
}

void processSpecialUpKeys(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_F1:
        stateKeyEvent[3] = 0;
        break;
    case GLUT_KEY_F2:
        stateKeyEvent[2] = 0;
        break;
    case GLUT_KEY_RIGHT:
        stateKeyEvent[0] = 0;
        break;
    case GLUT_KEY_LEFT:
        stateKeyEvent[1] = 0;
        break;
    }
}

void mouse(int button, int state, int x, int y)
{    
    float mx = x;
    float my = y;
    coord_x = (mx / HALF_SCREEN_WIDTH - 1.0);
    coord_y = -(my / HALF_SCEEN_HEIGHT - 1.0);

    if (state == GLUT_DOWN)
    {

        if (gState->gState == State_MainMenu || gState->gState == State_LosePanel || gState->gState == State_WinPanel)
        {
            //colision with button Play

            if (coord_x < 0.54375 && coord_x > -0.55415 && coord_y < 0.263 && coord_y > 0.0814)
            {
                if (!names[0].empty())
                {
                    Is = true;
                }
                else
                {
                    IsEnterName = true;
                }

            }
        }
        //colision with button Help    
        if (coord_x < 0.54375 && coord_x > -0.55417 && coord_y < -0.222222 && coord_y > -0.3888888 && !Is && !IsEnterName && gState->gState != State_Game)
        {
            if ((gState->gState == State_LosePanel || gState->gState == State_WinPanel))
            {
                IsPanelNotMenu = true;
                lastState->gState = gState->gState;
            }
            gState->gState = State_Regulations;
        }
        //colision with button Quit
        if (coord_x < 0.54375 && coord_x > -0.55417 && coord_y < -0.46296 && coord_y > -0.62962963
            && !Is && !IsEnterName && gState->gState != State_Game)
        {
            if ((gState->gState == State_LosePanel || gState->gState == State_WinPanel))
            {
                IsPanelNotMenu = true;
            }
            exit(0);
        }

        if (coord_x < 0.54375 && coord_x > -0.55417 && coord_y < 0.022222 && coord_y > -0.16296
            && !Is && !IsEnterName && gState->gState != State_Game)
        {
            if ((gState->gState == State_LosePanel || gState->gState == State_WinPanel))
            {
                IsPanelNotMenu = true;
                lastState->gState = gState->gState;
            }
            gState->gState = State_Record;
        }

        if (Is)
        {
            if (coord_x < -0.0458 && coord_x > -0.26 && coord_y < -0.05185 && coord_y > -0.2185)
            {
                Is = false;
                game.SetIsGameLose(false);
                game.SetIsGameWin(false);
                game.StartGame(level_one_player);
                gState->gState = State_Game;
                countCreateNewLevel = 0;
            }

            if (coord_x < 0.28646 && coord_x > 0.078125 && coord_y < -0.05185 && coord_y > -0.2185)
            {
                Is = false;
                game.SetIsGameLose(false);
                game.SetIsGameWin(false);
                game.StartGame(level_two_player);
                gState->gState = State_Game;
                game.IsDoublePlayer = true;
                countCreateNewLevel = 0;
            }
        }
        //colision with button pause
        if (gState->gState == State_Game)
        {
            if (coord_x < 0.983333 && coord_x > 0.73475 && coord_y < 0.9537 && coord_y > 0.75)
            {
                game.SetIsBall(false);
                IsPause = true;
            }
        }
        //colision with button back to menu
        if (gState->gState == State_Regulations || gState->gState == State_Record)
        {
            if (coord_x < 0.2375 && coord_x > -0.275 && coord_y < -0.72222 && coord_y > -0.94444)
            {
                gState->gState = lastState->gState;
            }
        }
        //colision with button eng/rus
        if (gState->gState == State_Regulations)
        {
            if (coord_x < 0.8927 && coord_x > 0.751 && coord_y < -0.65555 && coord_y > -0.76111)
            {
                IsSelectLan = true;
                if (state == GLUT_DOWN)
                {
                    if (typeLan == 14 && IsSelectLan)
                    {
                        typeLan = 15;
                        IsSelectLan = false;
                    }

                    if (typeLan == 15 && IsSelectLan)
                    {
                        typeLan = 14;
                        IsSelectLan = false;
                    }
                }
            }
        }
        if (IsEnterName)
        {
            //colision with button Create
            if (coord_x < 0.121875 && coord_x > -0.09166 && coord_y < -0.09629 && coord_y > -0.177778)
            {
                names.push_back("");
                IsEnterName = false;
            }

            if (coord_x < 0.09791 && coord_x > -0.06979 && coord_y < -0.207 && coord_y > -0.29259)
            {
                IsEnterName = false;
                names[0] = "";
            }
        }
    }
}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "rus");
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
    SCREN_HEIGHT = glutGet(GLUT_SCREEN_HEIGHT);
    SCREN_WIDTH = glutGet(GLUT_SCREEN_WIDTH);
    glutInitWindowSize(SCREN_WIDTH, SCREN_HEIGHT);
    HALF_SCEEN_HEIGHT = SCREN_HEIGHT / 2;
    HALF_SCREEN_WIDTH = SCREN_WIDTH / 2;
    glutCreateWindow("Game");
    glutFullScreen();
    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(processSpecialKeys);
    glutSpecialUpFunc(processSpecialUpKeys);
    glutMouseFunc(mouse);
    glutTimerFunc(50, Timer, 0);
    display.InitTexture();
    glutDisplayFunc(DisplayAll);
    glutMainLoop();
    return 0;
}