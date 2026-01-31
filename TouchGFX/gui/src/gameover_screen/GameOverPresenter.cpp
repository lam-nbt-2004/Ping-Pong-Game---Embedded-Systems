#include <gui/gameover_screen/GameOverPresenter.hpp>

GameOverPresenter::GameOverPresenter(GameOverView& v)
    : view(v)
{
}

void GameOverPresenter::activate()
{
}

void GameOverPresenter::deactivate()
{
}

int GameOverPresenter::getFinalScore() const
{
    return model->getFinalScore();
}

int GameOverPresenter::getHighScore() const
{
    return model->getHighScore();
}
