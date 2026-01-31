#include <gui/gameover_screen/GameOverView.hpp>
#include <touchgfx/Unicode.hpp>

GameOverView::GameOverView()
{
}

void GameOverView::setupScreen()
{
    GameOverViewBase::setupScreen();

    int finalScore = presenter->getFinalScore();
    int highScore  = presenter->getHighScore();

    Unicode::snprintf(finalScoreBuffer, 6, "%d", finalScore);
    Unicode::snprintf(highScoreBuffer,  6, "%d", highScore);

    textArea2.setWildcard(finalScoreBuffer);
    textArea2_1.setWildcard(highScoreBuffer);

    textArea2.invalidate();
    textArea2_1.invalidate();
}

void GameOverView::tearDownScreen()
{
    GameOverViewBase::tearDownScreen();
}
