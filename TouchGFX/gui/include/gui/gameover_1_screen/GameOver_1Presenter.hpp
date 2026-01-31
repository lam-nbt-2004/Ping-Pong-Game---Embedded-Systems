#ifndef GAMEOVER_1PRESENTER_HPP
#define GAMEOVER_1PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class GameOver_1View;

class GameOver_1Presenter : public touchgfx::Presenter, public ModelListener
{
public:
    GameOver_1Presenter(GameOver_1View& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~GameOver_1Presenter() {}

    int getWinner() const;
private:
    GameOver_1Presenter();

    GameOver_1View& view;

    Unicode::UnicodeChar winnerBuffer[3];
};

#endif // GAMEOVER_1PRESENTER_HPP
