#ifndef GAMEOVERPRESENTER_HPP
#define GAMEOVERPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class GameOverView;

class GameOverPresenter : public Presenter, public ModelListener
{
public:
    GameOverPresenter(GameOverView& v);
    virtual ~GameOverPresenter() {}

    virtual void activate();
    virtual void deactivate();

    int getFinalScore() const;
    int getHighScore() const;
private:
    GameOverPresenter();   // not implemented
    GameOverView& view;
};

#endif // GAMEOVERPRESENTER_HPP
