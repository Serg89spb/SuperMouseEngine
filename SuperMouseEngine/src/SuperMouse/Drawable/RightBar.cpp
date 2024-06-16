#include "RightBar.h"

#include "DrawableText.h"
#include "NumberBox.h"

namespace super_mouse
{
    RightBar::RightBar()
    {
        _scoreNumBox = new NumberBox(6, { 342 ,16 }, 4);
        _scoreNumBox->setNumber(0);

        _speedNumBox = new NumberBox(2, { 350 ,unit * 10 }, 5);
        _speedNumBox->setNumber(1);

        _levelNumBox = new NumberBox(2, { 430 ,unit * 10 }, 5);
        _levelNumBox->setNumber(1);

        _tHi = new DrawableText("HI-", 22, { 342, 80 });
        _tScore = new DrawableText("SCORE", 22, { 380, 80 });

        _tSpeed = new DrawableText("SPEED", 18, { 350, 400 });
        _tLevel = new DrawableText("LEVEL", 18, { 430, 400 });

        _tPause = new DrawableText("PAUSE", 22, { 380, 600 });
        _tGameOver = new DrawableText("GAME OVER", 26, { 340, 660 });

        _textMap = {
            {Hi,_tHi},//
            {Score,_tScore},//
            {Speed,_tSpeed},//
            {Level,_tLevel},//
            {Pause,_tPause},//
            {GameOver,_tGameOver},//
        };
    }

    void RightBar::render(SDL_Renderer* renderer)
    {
        _scoreNumBox->render(renderer);
        _speedNumBox->render(renderer);
        _levelNumBox->render(renderer);

        _tHi->render(renderer);
        _tScore->render(renderer);
        _tSpeed->render(renderer);
        _tLevel->render(renderer);
        _tPause->render(renderer);
        _tGameOver->render(renderer);
    }

    void RightBar::setNumberScore(const int num) const
    {
        _scoreNumBox->setNumber(num);
    }

    void RightBar::setNumberSpeed(const int num) const
    {
        _speedNumBox->setNumber(num);
    }

    void RightBar::setNumberLevel(const int num) const
    {
        _levelNumBox->setNumber(num);
    }

    int RightBar::getScore() const
    {
        return _scoreNumBox->number();
    }

    int RightBar::getSpeed() const
    {
        return _speedNumBox->number();
    }

    int RightBar::getLevel() const
    {
        return _levelNumBox->number();
    }

    void RightBar::setTextVisibility(const ERightBarText text, const bool visible) const
    {
        _textMap.find(text)->second->setVisibility(visible);
    }

    void RightBar::setTextBlinkingPeriod(ERightBarText text, float period) const
    {
        _textMap.find(text)->second->setBlinkingPeriod(period);
    }

    void RightBar::setTextBlinking(ERightBarText text, bool isBlinking) const
    {
        _textMap.find(text)->second->setIsBlinking(isBlinking);
    }

    void RightBar::SwitchScoreAndHiScore(bool Score)
    {
        _tHi->setVisibility(!Score);
    }
}
