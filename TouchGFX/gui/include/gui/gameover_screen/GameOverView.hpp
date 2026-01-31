#ifndef GAMEOVERVIEW_HPP
#define GAMEOVERVIEW_HPP

#include <gui_generated/gameover_screen/GameOverViewBase.hpp>
#include <gui/gameover_screen/GameOverPresenter.hpp>
#include <touchgfx/Unicode.hpp>

class GameOverView : public GameOverViewBase
{
public:
    GameOverView();
    virtual ~GameOverView() {}

    virtual void setupScreen();
    virtual void tearDownScreen();

private:
    Unicode::UnicodeChar finalScoreBuffer[6];
    Unicode::UnicodeChar highScoreBuffer[6];
};

#endif // GAMEOVERVIEW_HPP
