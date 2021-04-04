#include "Game.h"
#include <ctime>

void Game::SetIsBall(bool IsBallMove)
{
    this->IsBallMove = IsBallMove;
}

void Game::SetIsGameLose(bool IsGameLose)
{
    this->IsGameLose = IsGameLose;
}

void Game::SetIsGameWin(bool IsGameWin)
{
    this->IsGameWin = IsGameWin;
}

bool Game::GetIsGameWin()
{
    return IsGameWin;
}

bool Game::GetIsGameLose()
{
    return IsGameLose;
}

void Game::CreateLevel()
{
    SoundEngine->play2D(path.GetPath("breakout.mp3").c_str(), true);
    ifstream file(path.GetPath("Level" + to_string(numLevel) + ".txt"));

    srand(time(0));
    for (int i = 0; i < width; i++)
    {
        arrRandom[i] = rand() % countBonus;
        typeBonus[i] = rand() % countTypeBonus;
    }

    if (file.is_open())
    {
        char buf;
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                file >> buf;
                switch (buf)
                {
                case '0':                  
                    mapBlocks[i][j] = new Block((string)"Stone");
                    break;
                case '2':
                    mapBlocks[i][j] = new Block((string)"Simple");
                    countBlocks++;
                    break;
                case '1':                                              
                    mapBlocks[i][j] = new Block((string)"Hard");
                    countBlocks++;
                    break;
                case '3':
                    mapBlocks[i][j] = new EmptyBlock(false);
                    break;
                }
            }
        }
    }
}

void Game::GamePlay()
{
    player[0].DrawSelf(newPlayerX[0], 0.0f, newPlayerSize);
    if (IsDoublePlayer)
    {
        player[1].DrawSelf(newPlayerX[1], 1.65f, newPlayerSize);
    }
    ball.DrawSelf(newBallX, newBallY);

    if (!IsCreateLevel)
    {
        CreateLevel();
        IsCreateLevel = true;
    }

    if (countBrokenBlocks >= countBlocks)
    {
        SoundEngine->stopAllSounds();
        IsBallMove = false;
        SetIsGameWin(true);
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {           
            if (mapBlocks[i][j]->bonus->IsFall)
            {
                mapBlocks[i][j]->newBonusY += speedBall_Bonus;
                mapBlocks[i][j]->DrawSelf(xBlock, yBlock, mapBlocks[i][j]->newBonusY);
            }

            else
            {
                mapBlocks[i][j]->DrawSelf(xBlock, yBlock, 0.0f);
            }
            xBlock += crotchBlockX;
            if (mapBlocks[i][j]->IsActivBonus)
            {
                BonusActivity(mapBlocks[i][j]->bonus);
            }

            if (mapBlocks[i][j]->bonus->GetLeftBottomY() < -borderCoord)
            {
                mapBlocks[i][j]->bonus->IsFall = false;
                mapBlocks[i][j]->bonus = new EmptyBonus(typeBonus[i]);
            }
        }
        xBlock = 0;
        yBlock -= crotchBlockY;
    }
    yBlock = 0;
}

void Game::BonusActivity(Bonus* bonus)
{
    bonusTime[bonus->typeBonus]--;
    if (bonusTime[bonus->typeBonus] < 0)
    {
        bonus->IsActivBonus = false;
        bonusTime[bonus->typeBonus] = 0;
        if (bonus->typeBonus == 0)
        {
            doublePoint = 1;
        }

        if (bonus->typeBonus == 1)
        {
            newPlayerSize = 0.0f;
        }

        if (bonus->typeBonus == 2)
        {
            IsAddLife = false;
        }

    }
}

void Game::ActivateBonus(Bonus &bonus)
{
    if (bonus.typeBonus == 1)
    {
        newPlayerSize = 0.2f;
    } 
    
    if (bonus.typeBonus == 0)
    {
        doublePoint = 2;
    } 

    if (bonus.typeBonus == 2)
    {
        IsAddLife = true;
    } 

    if (bonus.typeBonus == 3)
    {
        IsGameLose = true;
        SoundEngine->stopAllSounds();
    } 
}

void Game::ColisionActivity(int j, int i)
{
    if (mapBlocks[i][j]->typeBlock == "Stone" || (mapBlocks[i][j]->typeBlock == "Hard" && mapBlocks[i][j]->countColision < 2))
    {
        SoundEngine->play2D(path.GetPath("solid.wav").c_str(), false);
    }

    if (mapBlocks[i][j]->typeBlock == "Simple")
    {
        SoundEngine->play2D(path.GetPath("bleep.mp3").c_str(), false);
        points += doublePoint;
        countBrokenBlocks++;
        if (j == arrRandom[i])
        {
            mapBlocks[i][j] = new EmptyBlock(true, typeBonus[i]);
        }
        else
        {
            mapBlocks[i][j] = new EmptyBlock(false);
        }
    }

    if (mapBlocks[i][j]->typeBlock == "Hard")
    {
        mapBlocks[i][j]->countColision += 1;
        if (mapBlocks[i][j]->countColision > 2)
        {
            SoundEngine->play2D(path.GetPath("bleep.mp3").c_str(), false);
            points += doublePoint;
            countBrokenBlocks++;
            if (j == arrRandom[i])
            {
                mapBlocks[i][j] = new EmptyBlock(true, typeBonus[i]);
            }
            else
            {
                mapBlocks[i][j] = new EmptyBlock(false);
            }
        }
    }

    if (j == arrRandom[i] && mapBlocks[i][j]->bonus != NULL)
    {
        mapBlocks[i][j]->bonus->IsFall = true;
    }

    newBallY += ball.dy;
    newBallX += ball.dx;
}

void Game::Colision()
{
    if (IsBallMove)
    {
        newBallX += ball.dx;
        newBallY += ball.dy;
    }
    //colision with window border
    if (ball.GetLeftBottomX() < -borderCoord)//Left
    {
        ball.dx = speedBall_Bonus;
        newBallX += ball.dx;
    }

    else if (ball.GetRightBottomX() > borderCoord)//Right
    {
        ball.dx = -speedBall_Bonus;
        newBallX += ball.dx;
    }

    if (ball.GetLeftBottomY() < -borderCoord)
    {
        //GAME OVER
        if (IsAddLife)
        {
            newBallX = 0.0f;
            newBallY = 0.0f;
            ball.dx = speedBall_Bonus;
            ball.dy = speedBall_Bonus;
            IsBallMove = false;
        }
        else
        {
            SoundEngine->stopAllSounds();
            IsBallMove = false;
            SetIsGameLose(true);  
        }
    }

    else if (ball.GetLeftTopY() > borderCoord)//Up
    {
        if (IsDoublePlayer)
        {
            SoundEngine->stopAllSounds();
            IsBallMove = false;
            SetIsGameLose(true);
        }
        else
        {
            ball.dy = -speedBall_Bonus;
            newBallY += ball.dy;
        }
    }
    //colision with player
    if (ball.GetLeftBottomX() > player[0].GetLeftTopX() - 0.015
        && ball.GetRightBottomX() < player[0].GetRightTopX() + 0.015
        && ball.GetRightBottomY() < player[0].GetLeftTopY() + 0.015
        && ball.GetRightBottomY() > player[0].GetLeftTopY() - 0.015)
    {
        SoundEngine->play2D(path.GetPath("bleep.wav").c_str(), false);
        ball.GetBallDirX();
        ball.dy = speedBall_Bonus;
        newBallX += ball.dx;
        newBallY += ball.dy;
    }

    if (IsDoublePlayer)
    {
        if (ball.GetLeftBottomX() > player[1].GetLeftTopX() - 0.015
            && ball.GetRightBottomX() < player[1].GetRightTopX() + 0.015
            && ball.GetRightTopY() > player[1].GetLeftBottomY() - 0.015
            && ball.GetRightTopY() < player[1].GetLeftBottomY() + 0.015)
        {
            SoundEngine->play2D(path.GetPath("bleep.wav").c_str(), false);
            ball.GetBallDirX();
            ball.dy = -speedBall_Bonus;
            newBallX += ball.dx;
            newBallY += ball.dy;
        }
    }
    //colision with block
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            if (mapBlocks[i][j]->bonus->IsFall)
            {
                if (mapBlocks[i][j]->bonus->GetLeftBottomX() > player[0].GetLeftTopX()
                    && mapBlocks[i][j]->bonus->GetRightBottomX() < player[0].GetRightTopX()
                    && mapBlocks[i][j]->bonus->GetRightBottomY() < player[0].GetLeftTopY() + 0.015
                    && mapBlocks[i][j]->bonus->GetRightBottomY() > player[0].GetLeftTopY() - 0.015)
                {
                    ActivateBonus(*mapBlocks[i][j]->bonus);
                    bonusTime[mapBlocks[i][j]->bonus->typeBonus] += mapBlocks[i][j]->bonus->bonusTime;
                    mapBlocks[i][j]->IsActivBonus = true;
                    mapBlocks[i][j]->bonus = new EmptyBonus(typeBonus[i]);
                    mapBlocks[i][j]->bonus->IsFall = false;
                    SoundEngine->play2D(path.GetPath("powerup.wav").c_str(), false);
                }
            }
            //Bottom border blocks colision
            if (ball.GetLeftBottomX() > mapBlocks[i][j]->GetLeftBottomX() - 0.025f &&
                ball.GetRightBottomX() < mapBlocks[i][j]->GetRightBottomX() + 0.025f &&
                ball.GetLeftTopY() > mapBlocks[i][j]->GetRightBottomY() - 0.02 &&
                ball.GetLeftTopY() < mapBlocks[i][j]->GetRightBottomY() + 0.02)
            {
                ball.GetBallDirX();
                ball.dy = -speedBall_Bonus;
                ColisionActivity(j, i);
                break;
            }
            //Top border blocks colision
            if (ball.GetLeftBottomX() > mapBlocks[i][j]->GetLeftBottomX() - 0.025f &&
                ball.GetRightBottomX() < mapBlocks[i][j]->GetRightBottomX() + 0.025f &&
                ball.GetLeftBottomY() < mapBlocks[i][j]->GetRightTopY() + 0.02f &&
                ball.GetLeftBottomY() > mapBlocks[i][j]->GetRightTopY() - 0.02f)
            {
                ball.GetBallDirX();
                ball.dy = speedBall_Bonus;
                ColisionActivity(j, i);
                break;
            }
            //Right border blocks colision
            if (ball.GetLeftTopX() - 0.015f < mapBlocks[i][j]->GetRightBottomX() &&
                ball.GetLeftTopX() + 0.015f > mapBlocks[i][j]->GetRightBottomX() &&
                ball.GetLeftTopY() < mapBlocks[i][j]->GetRightTopY() + 0.035f &&
                ball.GetLeftBottomY() > mapBlocks[i][j]->GetRightBottomY() - 0.035f)
            {
                ball.GetBallDirY();
                ball.dx = speedBall_Bonus;
                ColisionActivity(j, i);
                break;
            }
            //Left border blocks colision
            if (ball.GetRightTopX() + 0.015f > mapBlocks[i][j]->GetLeftBottomX() &&
                ball.GetRightTopX() - 0.015f < mapBlocks[i][j]->GetLeftBottomX() &&
                ball.GetLeftTopY() < mapBlocks[i][j]->GetRightTopY() + 0.035f &&
                ball.GetLeftBottomY() > mapBlocks[i][j]->GetRightBottomY() - 0.035f)
            {
                ball.GetBallDirY();
                ball.dx = -speedBall_Bonus;
                ColisionActivity(j, i);
                break;
            }

        }
    }
}

void Game::PrintText()
{
    glColor3f(1.0, 1.0, 1.0);
    sprintf_s(text, "%d", numLevel);
    path.DrawString(GLUT_BITMAP_TIMES_ROMAN_24, text, -0.59f, 0.475f);
    sprintf_s(text, "%d", points);
    path.DrawString(GLUT_BITMAP_TIMES_ROMAN_24, text, -0.65f, 0.35f);
    sprintf_s(text, "%d", bonusTime[2]);
    path.DrawString(GLUT_BITMAP_TIMES_ROMAN_24, text, -0.62f, -0.3f);
    sprintf_s(text, "%d", bonusTime[1]);
    path.DrawString(GLUT_BITMAP_TIMES_ROMAN_24, text, -0.62f, -0.4f);
    sprintf_s(text, "%d", bonusTime[0]);
    path.DrawString(GLUT_BITMAP_TIMES_ROMAN_24, text, -0.62f, -0.5f);
}

void Game::StartGame(int numLevel)
{
    this->numLevel = numLevel;
    IsGame = true;
    IsAddLife = false;
    IsCreateLevel = false;
    IsDoublePlayer = false;
    doublePoint = 1;
    countBlocks = 0;
    countBrokenBlocks = 0;
    points = 0;
    ball.dx = 0.02f;
    ball.dy = 0.02f;
    newBallX = 0.0f;
    newBallY = 0.0f;
    newPlayerX[0] = 0.0f;
    newPlayerSize = 0.0f;
    bonusTime[0] = 0; bonusTime[1] = 0; bonusTime[2] = 0;
    IsBallMove = false;
}

void Game::DisplayGame()
{
    GamePlay();
    Colision();
    PrintText();
    glFlush();
}
