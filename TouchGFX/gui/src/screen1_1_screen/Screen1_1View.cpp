#include <gui/screen1_1_screen/Screen1_1View.hpp>

Screen1_1View::Screen1_1View()
{

}

void Screen1_1View::setupScreen()
{
    Screen1_1ViewBase::setupScreen();
}

void Screen1_1View::tearDownScreen()
{
    Screen1_1ViewBase::tearDownScreen();
}

void Screen1_1View::threePoints()
{
    presenter->setTargetScore(3);
    application().gotoScreen2ScreenSlideTransitionNorth();
}

void Screen1_1View::sevenPoints()
{
    presenter->setTargetScore(7);
    application().gotoScreen2ScreenSlideTransitionNorth();
}

void Screen1_1View::fifteenPoints()
{
    presenter->setTargetScore(15);
    application().gotoScreen2ScreenSlideTransitionNorth();
}
