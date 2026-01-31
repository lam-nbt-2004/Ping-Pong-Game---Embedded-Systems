#include <gui/screen2_screen/Screen2View.hpp>
#include "touchgfx/widgets/canvas/Circle.hpp"
#include <touchgfx/Unicode.hpp>

extern "C" {
    extern volatile uint8_t p1_up;
    extern volatile uint8_t p1_down;
    extern volatile uint8_t p2_up;
    extern volatile uint8_t p2_down;
}

#define SCREEN_WIDTH   240
#define SCREEN_HEIGHT  320

#define START_DELAY_TICKS   60   // ~1 second
#define SCORE_DELAY_TICKS   90   // ~1.5 seconds

#define PADDLE_WIDTH   10
#define PADDLE_HEIGHT  80
#define PADDLE_SPEED  3

#define BALL_SIZE      10   // diameter
#define MAX_BALL_SPEED_Y  4   // controls steepness

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

Screen2View::Screen2View()
{

}

void Screen2View::setupScreen()
{
	Screen2ViewBase::setupScreen();

	scoreP1 = 0;
	scoreP2 = 0;

	targetScore = presenter->getTargetScore();

	updateScoreText();

    resetBall(false);

    gameState = GAME_WAIT_START;
    delayTicks = START_DELAY_TICKS;
}

void Screen2View::tearDownScreen()
{
    Screen2ViewBase::tearDownScreen();
}

void Screen2View::tickEvent()
{
	if (isPaused)
	{
		return;   // ⛔ freeze everything
	}

    if (gameState != GAME_PLAYING)
    {
        if (delayTicks > 0)
        {
            delayTicks--;
            circle1.moveTo(ballX, ballY);
            circle1.invalidate();
            return;
        }
        else
        {
            gameState = GAME_PLAYING;
        }
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

    if (p2_up)
    {
        int newY = box2_1.getY() - PADDLE_SPEED;
        if (newY < 0) newY = 0;
        box2_1.moveTo(box2_1.getX(), newY);
        box2_1.invalidate();
    }
    else if (p2_down)
    {
        int newY = box2_1.getY() + PADDLE_SPEED;
        if (newY + box2_1.getHeight() > SCREEN_HEIGHT)
            newY = SCREEN_HEIGHT - box2_1.getHeight();
        box2_1.moveTo(box2_1.getX(), newY);
        box2_1.invalidate();
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

    if (ballX < 0)
    {
        scoreP2++;
        updateScoreText();
        if (scoreP2 >= targetScore)
	   {
        	presenter->setWinner(2);
			application().gotoGameOver_1ScreenNoTransition();
			return;
	   }
        resetBall(false);
        return;
    }
    else if (ballX + BALL_SIZE > SCREEN_WIDTH)
    {
        scoreP1++;
        updateScoreText();
        if (scoreP1 >= targetScore)
		{
        	presenter->setWinner(1);
			application().gotoGameOver_1ScreenNoTransition();
			return;
		}
	resetBall(true);
        return;
    }

    if (ballVX < 0 &&
        intersects(ballX, ballY, BALL_SIZE, BALL_SIZE,
                   box2.getX(), box2.getY(),
                   box2.getWidth(), box2.getHeight()))
    {
        ballX = box2.getX() + box2.getWidth();

        int offset =
            (ballY + BALL_SIZE / 2) -
            (box2.getY() + box2.getHeight() / 2);

        ballVY = (offset * MAX_BALL_SPEED_Y) / (box2.getHeight() / 2);
        ballVX = -ballVX;
    }
    // RIGHT paddle
    else if (ballVX > 0 &&
             intersects(ballX, ballY, BALL_SIZE, BALL_SIZE,
                        box2_1.getX(), box2_1.getY(),
                        box2_1.getWidth(), box2_1.getHeight()))
    {
        ballX = box2_1.getX() - BALL_SIZE;

        int offset =
            (ballY + BALL_SIZE / 2) -
            (box2_1.getY() + box2_1.getHeight() / 2);

        ballVY = (offset * MAX_BALL_SPEED_Y) / (box2_1.getHeight() / 2);
        ballVX = -ballVX;
    }

    // ==============================
    // CLAMP Y SPEED
    // ==============================
    if (ballVY >  MAX_BALL_SPEED_Y) ballVY =  MAX_BALL_SPEED_Y;
    if (ballVY < -MAX_BALL_SPEED_Y) ballVY = -MAX_BALL_SPEED_Y;

    circle1.moveTo(ballX, ballY);
    circle1.invalidate();
}

void Screen2View::updateScoreText()
{
    Unicode::snprintf(scoreP1Buffer, 8, "%d", scoreP1);
    Unicode::snprintf(scoreP2Buffer, 8, "%d", scoreP2);
    textArea1.setWildcard1(scoreP1Buffer);
    textArea1.setWildcard2(scoreP2Buffer);
    textArea1.resizeToCurrentTextWithAlignment();
    textArea1.invalidate();
}

void Screen2View::resetBall(bool serveLeft)
{
    ballX = (SCREEN_WIDTH  - BALL_SIZE) / 2;
    ballY = (SCREEN_HEIGHT - BALL_SIZE) / 2;

    ballVX = serveLeft ? -2 : 2;
    ballVY = 0;

    gameState  = GAME_SCORE_PAUSE;
    delayTicks = SCORE_DELAY_TICKS;

    circle1.moveTo(ballX, ballY);
    circle1.invalidate();
}

void Screen2View::pause()
{
    isPaused = !isPaused;

    if (isPaused)
    {
        gameState = GAME_WAIT_START;
    }
    else
    {
        gameState = GAME_PLAYING;
    }
}
