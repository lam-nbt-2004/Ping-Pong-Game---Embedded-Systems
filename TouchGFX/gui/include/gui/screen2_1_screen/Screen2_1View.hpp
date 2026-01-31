#ifndef SCREEN2_1VIEW_HPP
#define SCREEN2_1VIEW_HPP

#include <gui_generated/screen2_1_screen/Screen2_1ViewBase.hpp>
#include <gui/screen2_1_screen/Screen2_1Presenter.hpp>
#include <touchgfx/Unicode.hpp>

class Screen2_1View : public Screen2_1ViewBase
{
public:
    Screen2_1View();
    virtual ~Screen2_1View() {}

    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void tickEvent();

    // FlexButton2 callback
    void pause();

private:
    // ==============================
    // GAME STATE
    // ==============================
    enum GameState
    {
        GAME_WAIT_START,
        GAME_PLAYING,
        GAME_PAUSED,
        GAME_MISS_DELAY
    };

    GameState gameState;
    int delayTicks;

    // ==============================
    // BALL
    // ==============================
    int ballX, ballY;
    int ballVX, ballVY;

    // ==============================
    // SCORE
    // ==============================
    int hitCount;
    Unicode::UnicodeChar scoreBuffer[6];

    // ==============================
    // HELPERS
    // ==============================
    void resetBall();
    void resetGame();
    void updateScoreText();
};

#endif // SCREEN2_1VIEW_HPP
