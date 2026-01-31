#include <gui/gameover_1_screen/GameOver_1View.hpp>
#include <touchgfx/Unicode.hpp>

GameOver_1View::GameOver_1View()
{

}

void GameOver_1View::setupScreen()
{
    GameOver_1ViewBase::setupScreen();

    int winner = presenter->getWinner();

    Unicode::snprintf(winnerBuffer, 3, "%d", winner);
    textArea2.setWildcard1(winnerBuffer);
    textArea2.invalidate();
}

void GameOver_1View::tearDownScreen()
{
    GameOver_1ViewBase::tearDownScreen();
}
