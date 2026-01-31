#include <gui/screen2_1_screen/Screen2_1View.hpp>
#include <gui/screen2_1_screen/Screen2_1Presenter.hpp>

Screen2_1Presenter::Screen2_1Presenter(Screen2_1View& v)
    : view(v)
{

}

void Screen2_1Presenter::activate()
{

}

void Screen2_1Presenter::deactivate()
{

}

int Screen2_1Presenter::getFinalScore() const
{
    return model->getFinalScore();
}

void Screen2_1Presenter::setFinalScore(int score)
{
    model->setFinalScore(score);
}

void Screen2_1Presenter::submitScore(int score)
{
    model->setFinalScore(score);
    model->updateHighScore(score);
}
