#pragma once
#include <GL/freeglut.h>
#include <string>
#include <fstream>
#include "Block.h"
#include "Ball.h"
#include "Bonus.h"
#include "EmptyBonus.h"
#include "Player.h"
#include "EmptyBlock.h"
#include "include/irrKlang.h"

using namespace std;
using namespace irrklang;
#pragma comment(lib, "irrKlang.lib")

class Game
{
private:
	static const int countBonus = 8;
	static const int height = 8;
	static const int width = 8;
	static const int countTypeBonus = 4;
	int typeBonus[countBonus];
	int arrRandom[countBonus];
	int countBlocks = 0;
	int countBrokenBlocks = 0;
	int numLevel = 1;
	int bonusTime[3] = {0, 0, 0};
	int timeLifeBonus = 150;
	int doublePoint = 1;
	const float crotchBlockY = 0.11f;
	const float crotchBlockX = 0.105f;
	float xBlock = 0.0f;
	float yBlock = 0.0f;
	float newBallX = 0.0f;
	float newBallY = 0.0f;
	float newBonusY = 0.0f;
	float newPlayerSize = 0.0f;
	float speedBall_Bonus = 0.02f;
	GameObject path;
	ISoundEngine* SoundEngine;
	ISound* sound;
	Block* mapBlocks[height][width];
	Player player[2];
	Ball ball;
	string typeBlock[3] = { "Simple", "Hard", "Stone" };
	bool IsCreateLevel = false;
	bool IsGameLose = false;
	bool IsGameWin = false;
	bool IsBallMove = false;
	bool IsBonus = false;
	bool IsAddLife = false;
	char text[128];

	void PrintText();
	void CreateLevel();
	void GamePlay();
	void Colision();
	void ActivateBonus(Bonus &bonus);
	void ColisionActivity(int j, int i);
	void BonusActivity(Bonus* bonus);
public:
	Game()
	{
		SoundEngine = createIrrKlangDevice();
	}
	int points = 0;
	float newPlayerX[2] = { 0.0f, 0.0f };
	const float borderCoord = 0.98f;
	bool IsGame = false;
	bool IsDoublePlayer = false;

	bool GetIsGameLose();
	bool GetIsGameWin();
	void SetIsGameLose(bool IsGameLose);
	void SetIsGameWin(bool IsGameWin);
	void SetIsBall(bool IsBall);
	void PlayerMove(unsigned char key);
	void StartGame(int numlevel);
	void DisplayGame();
};

