#ifndef GAMEOVER_1VIEW_HPP
#define GAMEOVER_1VIEW_HPP

#include <gui_generated/gameover_1_screen/GameOver_1ViewBase.hpp>
#include <gui/gameover_1_screen/GameOver_1Presenter.hpp>

class GameOver_1View : public GameOver_1ViewBase
{
public:
    GameOver_1View();
    virtual ~GameOver_1View() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
    Unicode::UnicodeChar winnerBuffer[3];
};

#endif // GAMEOVER_1VIEW_HPP
