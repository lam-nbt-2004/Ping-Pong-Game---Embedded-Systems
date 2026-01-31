#ifndef MODEL_HPP
#define MODEL_HPP

class ModelListener;

class Model
{
public:
    Model();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    void tick();

    void setTargetScore(int score);
    int  getTargetScore() const;

    void setFinalScore(int score);
    int  getFinalScore() const;

    void updateHighScore(int score);
    int  getHighScore() const;

    void setWinner(int player);
	int getWinner() const;
protected:
    ModelListener* modelListener;
    int targetScore = 0;
    int finalScore = 0;
    int highScore  = 0;
    int winner = 0;
};

#endif // MODEL_HPP
