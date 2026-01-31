#ifndef SCREEN2VIEW_HPP
#define SCREEN2VIEW_HPP

#include <gui_generated/screen2_screen/Screen2ViewBase.hpp>
#include <gui/screen2_screen/Screen2Presenter.hpp>

class Screen2View : public Screen2ViewBase
{
public:
    Screen2View();
    virtual ~Screen2View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    void tickEvent();
    void pause();
    uint32_t tickCount;
protected:
    int scoreP1 = 0;
    int scoreP2 = 0;
    int targetScore;

    Unicode::UnicodeChar scoreP1Buffer[8];
    Unicode::UnicodeChar scoreP2Buffer[8];

    void updateScoreText();

    int ballX, ballY;
	int ballVX, ballVY;

	void resetBall(bool serveLeft);
private:
    int delayTicks;
	bool isPaused = false;

    enum GameState
    {
        GAME_WAIT_START,
        GAME_PLAYING,
        GAME_SCORE_PAUSE,
		GAME_PAUSED
    };

    GameState gameState;
};

#endif // SCREEN2VIEW_HPP
