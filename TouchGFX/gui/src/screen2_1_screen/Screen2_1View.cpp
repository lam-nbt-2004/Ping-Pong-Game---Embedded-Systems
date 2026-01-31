#include <gui/screen2_1_screen/Screen2_1View.hpp>
#include "touchgfx/widgets/canvas/Circle.hpp"

extern "C" {
    extern volatile uint8_t p1_up;
    extern volatile uint8_t p1_down;
}

#define SCREEN_WIDTH   240
#define SCREEN_HEIGHT  320

#define BALL_SIZE      10
#define BALL_SPEED_X   3
#define BALL_SPEED_Y   3
#define MAX_BALL_SPEED_Y  4

#define PADDLE_SPEED   3

#define START_DELAY_TICKS  60   // ~1s
#define MISS_DELAY_TICKS   90   // ~1.5s

// ==============================
// AABB collision helper
// ==============================
static bool intersects(int ax, int ay, int aw, int ah,
                       int bx, int by, int bw, int bh)
{
    return !(ax + aw <= bx ||
             ax >= bx + bw ||
             ay + ah <= by ||
             ay >= by + bh);
}

Screen2_1View::Screen2_1View()
{

}

void Screen2_1View::setupScreen()
{
    Screen2_1ViewBase::setupScreen();

    hitCount = 0;
    updateScoreText();

    resetBall();

    gameState  = GAME_WAIT_START;
    delayTicks = START_DELAY_TICKS;
}

void Screen2_1View::tearDownScreen()
{
    Screen2_1ViewBase::tearDownScreen();
}

void Screen2_1View::resetBall()
{
    ballX = (SCREEN_WIDTH  - BALL_SIZE) / 2;
    ballY = (SCREEN_HEIGHT - BALL_SIZE) / 2;

    ballVX = BALL_SPEED_X;
    ballVY = BALL_SPEED_Y;

    circle1.moveTo(ballX, ballY);
    circle1.invalidate();
}

void Screen2_1View::updateScoreText()
{
    Unicode::snprintf(scoreBuffer, 6, "%d", hitCount);
    textArea1.setWildcard1(scoreBuffer);
    textArea1.invalidate();
}

void Screen2_1View::pause()
{
    if (gameState == GAME_PLAYING)
        gameState = GAME_PAUSED;
    else if (gameState == GAME_PAUSED)
        gameState = GAME_PLAYING;
}

void Screen2_1View::tickEvent()
{
    if (gameState == GAME_WAIT_START)
    {
        if (delayTicks > 0)
        {
            delayTicks--;
            return;
        }
        else
        {
            gameState = GAME_PLAYING;
        }
    }

    if (gameState == GAME_PAUSED)
    {
        return;   // freeze
    }

    if (gameState == GAME_MISS_DELAY)
    {
        if (delayTicks > 0)
        {
            delayTicks--;
            return;
        }
        else
        {
        	presenter->setFinalScore(hitCount);
        	application().gotoGameOverScreenNoTransition();
            return;
        }
    }

    if (gameState != GAME_PLAYING)
    {
        circle1.moveTo(ballX, ballY);
        circle1.invalidate();
        return;
    }

    if (p1_up)
    {
        int newY = box2.getY() - PADDLE_SPEED;
        if (newY < 0) newY = 0;
        box2.moveTo(box2.getX(), newY);
        box2.invalidate();
    }
    else if (p1_down)
    {
        int newY = box2.getY() + PADDLE_SPEED;
        if (newY + box2.getHeight() > SCREEN_HEIGHT)
            newY = SCREEN_HEIGHT - box2.getHeight();
        box2.moveTo(box2.getX(), newY);
        box2.invalidate();
    }

    ballX += ballVX;
    ballY += ballVY;

    if (ballY <= 0)
    {
        ballY = 0;
        ballVY = -ballVY;
    }
    else if (ballY + BALL_SIZE >= SCREEN_HEIGHT)
    {
        ballY = SCREEN_HEIGHT - BALL_SIZE;
        ballVY = -ballVY;
    }

    if (ballX + BALL_SIZE >= SCREEN_WIDTH)
    {
        ballX = SCREEN_WIDTH - BALL_SIZE;
        ballVX = -ballVX;
    }

    if (ballX < 0)
    {
        presenter->submitScore(hitCount);
        gameState  = GAME_MISS_DELAY;
        delayTicks = MISS_DELAY_TICKS;
        return;
    }
    // collision
    if (ballVX < 0 &&
        intersects(ballX, ballY, BALL_SIZE, BALL_SIZE,
                   box2.getX(), box2.getY(),
                   box2.getWidth(), box2.getHeight()))
    {
        ballX = box2.getX() + box2.getWidth();
        ballVX = -ballVX;

        int paddleCenter = box2.getY() + box2.getHeight() / 2;
        int ballCenter   = ballY + BALL_SIZE / 2;
        int offset       = ballCenter - paddleCenter;

        ballVY = (offset * MAX_BALL_SPEED_Y) / (box2.getHeight() / 2);

        if (ballVX > 0 && ballVX < 5) ballVX++;

        hitCount++;
        updateScoreText();
    }

    if (ballVY >  MAX_BALL_SPEED_Y) ballVY =  MAX_BALL_SPEED_Y;
    if (ballVY < -MAX_BALL_SPEED_Y) ballVY = -MAX_BALL_SPEED_Y;

    circle1.moveTo(ballX, ballY);
    circle1.invalidate();
}
