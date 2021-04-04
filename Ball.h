#pragma once
#include "RectObject.h"
class Ball :
    public RectObject
{
private:
	const float xLeft = -0.015f;
	const float xRight = 0.015f;
	const float yTop = -0.7f;
	const float yBottom = -0.75f;

public:
	float dy;
	float dx;

	void SetCoords(float newX, float newY);
	void GetBallDirX();
	void GetBallDirY();
	void DrawSelf(float newX, float newY);
};

