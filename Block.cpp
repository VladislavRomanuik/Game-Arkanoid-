#include "Block.h"

extern unsigned int texture[25];

Block::Block(bool IsBonus)
{
    bonus = new EmptyBonus(0);
}

Block::Block(bool IsBonus, int typeBonus)
{
    if (IsBonus)
    {
        bonus = new Bonus;         
        bonus->typeBonus = typeBonus;
    }
    else
    {
        bonus = new EmptyBonus(0);
    }        
}
void Block::SetCoords(float newX, float newY)
{
    coords[0].SetXY((xLeft + newX), (yTop + newY));
    coords[1].SetXY((xRight + newX), (yTop + newY));
    coords[2].SetXY((xRight + newX), (yBottom + newY));
    coords[3].SetXY((xLeft + newX), (yBottom + newY));
}

void Block::DrawSelf(float newX, float newY, float newBonusY)
{
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0);

    if (typeBlock == "Stone" && countColision < 1)
    {
        glBindTexture(GL_TEXTURE_2D, texture[10]);
    }
    if (typeBlock == "Hard")
    {
        glBindTexture(GL_TEXTURE_2D, texture[9]);
    }
    if (typeBlock == "Simple" || countColision > 0)
    {
        glBindTexture(GL_TEXTURE_2D, texture[8]);
    }

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