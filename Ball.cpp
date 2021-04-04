#include "Ball.h"

extern unsigned int texture[25];

void Ball::GetBallDirX()
{
	if (dx == 0.02f)
	{
		dx = 0.02f;
	}

	if (dx == -0.02f)
	{
		dx = -0.02f;
	}
}

void Ball::GetBallDirY()
{
	if (dy == 0.02f)
	{
		dy = 0.02f;
	}

	if (dy == -0.02f)
	{
		dy = -0.02f;
	}
}

void Ball::DrawSelf(float newX, float newY)
{
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, texture[11]);
	SetCoords(newX, newY);
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f);
	glVertex2d(coords[0].GetX(), coords[0].GetY());

	glTexCoord2f(1.0f, 0.0f);
	glVertex2d(coords[1].GetX(), coords[1].GetY());

	glTexCoord2f(1.0f, 1.0f);
	glVertex2d(coords[2].GetX(), coords[2].GetY());

	glTexCoord2f(0.0f, 1.0f);
	glVertex2d(coords[3].GetX(), coords[3].GetY());
	glEnd();
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}

void Ball::SetCoords(float newX, float newY)
{
	coords[0].SetXY(xLeft + newX, yTop + newY);
	coords[1].SetXY(xRight + newX, yTop + newY);
	coords[2].SetXY(xRight + newX, yBottom + newY);
	coords[3].SetXY(xLeft + newX, yBottom + newY);
}