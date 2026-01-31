#include <gui/gameover_1_screen/GameOver_1View.hpp>
#include <gui/gameover_1_screen/GameOver_1Presenter.hpp>

GameOver_1Presenter::GameOver_1Presenter(GameOver_1View& v)
    : view(v)
{

}

void GameOver_1Presenter::activate()
{

}

void GameOver_1Presenter::deactivate()
{

}

int GameOver_1Presenter::getWinner() const
{
    return model->getWinner();
}

