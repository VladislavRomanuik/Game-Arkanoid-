#include "Player.h"

extern unsigned int texture[25];

void Player::DrawSelf(float newX, float newY, float sizeX)
{
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor3f(1.0f, 1.0f, 1.0f);
    if (sizeX > 0)
    {
        glBindTexture(GL_TEXTURE_2D, texture[13]);
    }
    else
        glBindTexture(GL_TEXTURE_2D, texture[12]);
    SetCoords(newX, newY, sizeX);
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

void Player::SetCoords(float newX, float newY, float sizeX)
{
    coords[0].SetXY(xLeft - sizeX + newX, yTop + newY);
    coords[1].SetXY(xRight + sizeX + newX, yTop + newY);
    coords[2].SetXY(xRight + sizeX + newX, yBottom + newY);
    coords[3].SetXY(xLeft - sizeX + newX, yBottom + newY);

}