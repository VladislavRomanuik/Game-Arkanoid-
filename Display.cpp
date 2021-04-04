#include "Display.h"

extern int SCREN_HEIGHT, SCREN_WIDTH, HALF_SCEEN_HEIGHT, HALF_SCREEN_WIDTH;
extern unsigned int texture[25];

void Display::DisplayGame()
{
    DrawWindow(texture[1], 1.0);
}

void Display::DisplayRegulations(unsigned int texture)
{
    DrawWindow(texture, 1.0);
    glFlush();
}

void Display::DisplayMainMenu(float alpha)
{
    DrawWindow(texture[0], alpha);
    glFlush();
}

void Display::DisplayLose(float alpha)
{
    DrawWindow(texture[2], alpha);
}

void Display::DisplayWin(float alpha)
{
    DrawWindow(texture[3], alpha);
}

void Display::DisplayRecords()
{
    DrawWindow(texture[16], 1.0f);
}

void Display::DrawEnterNamePanel(bool IsEnterName)
{
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    if (IsEnterName)
    {
        glBindTexture(GL_TEXTURE_2D, texture[17]);
    }
    else
    {
        glBindTexture(GL_TEXTURE_2D, texture[18]);
    }
    glBegin(GL_QUADS);

    glTexCoord2f(0.0f, 0.0f);
    glVertex2d((float)625 / HALF_SCREEN_WIDTH - 1.0f, -((float)280 / HALF_SCEEN_HEIGHT - 1.0f));

    glTexCoord2f(1.0f, 0.0f);
    glVertex2d((float)1325 / HALF_SCREEN_WIDTH - 1.0f, -((float)280 / HALF_SCEEN_HEIGHT - 1.0f));

    glTexCoord2f(1.0f, 1.0f);
    glVertex2d((float)1325 / HALF_SCREEN_WIDTH - 1.0f, -((float)760 / HALF_SCEEN_HEIGHT - 1.0f));

    glTexCoord2f(0.0f, 1.0f);
    glVertex2d((float)625 / HALF_SCREEN_WIDTH - 1.0f, -((float)760 / HALF_SCEEN_HEIGHT - 1.0f));
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
}

void Display::DrawWindow(unsigned int texture, float alpha)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(1.0f, 1.0f, 1.0f, alpha);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBegin(GL_QUADS);
    
    glTexCoord2f(0.0f, 0.0f);
    glVertex2d(-1.0f, 1.0f);

    glTexCoord2f(1.0f, 0.0f);
    glVertex2d(1.0f, 1.0f);

    glTexCoord2f(1.0f, 1.0f);
    glVertex2d(1.0f, -1.0f);

    glTexCoord2f(0.0f, 1.0f);
    glVertex2d(-1.0f, -1.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
}


  
