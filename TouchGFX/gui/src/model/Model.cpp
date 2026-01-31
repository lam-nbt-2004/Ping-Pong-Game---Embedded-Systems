#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

Model::Model() : modelListener(0)
{

}

void Model::tick()
{

}

void Model::setFinalScore(int score)
{
    finalScore = score;
}

int Model::getFinalScore() const
{
    return finalScore;
}

void Model::updateHighScore(int score)
{
    if (score > highScore)
    {
        highScore = score;
    }
}

int Model::getHighScore() const
{
    return highScore;
}

void Model::setTargetScore(int score)
{
    targetScore = score;
}

int Model::getTargetScore() const
{
    return targetScore;
}

void Model::setWinner(int player)
{
    winner = player;
}

int Model::getWinner() const
{
    return winner;
}

