#include "Bonus.h"

extern unsigned int texture[25];

void Bonus::SetCoords(float blockX, float blockY, float newY)
{
	//0 - Left 1 - Right 2 - Top 3 - Bottom
    coords[0].SetXY(arrayCoord[typeBonus][0] + blockX, arrayCoord[typeBonus][2] - newY + blockY);
    coords[1].SetXY(arrayCoord[typeBonus][1] + blockX, arrayCoord[typeBonus][2] - newY + blockY);
    coords[2].SetXY(arrayCoord[typeBonus][1] + blockX, arrayCoord[typeBonus][3] - newY + blockY);
    coords[3].SetXY(arrayCoord[typeBonus][0] + blockX, arrayCoord[typeBonus][3] - newY + blockY);
}

void Bonus::DrawSelf(float blockX, float blockY, float newY)
{
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor3f(1.0f, 1.0f, 1.0f);

	if (typeBonus == 0)
	{
		glBindTexture(GL_TEXTURE_2D, texture[6]);//6
	}
	if (typeBonus == 1)
	{
		glBindTexture(GL_TEXTURE_2D, texture[7]);//7
	}
	if (typeBonus == 2)
	{
		glBindTexture(GL_TEXTURE_2D, texture[4]);//4
	}

	if (typeBonus == 3)
	{
		glBindTexture(GL_TEXTURE_2D, texture[5]);//5
	}

	SetCoords(blockX, blockY, newY);
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