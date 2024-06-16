#pragma once
#include "Drawable.h"
#include "NumberBox.h"

namespace super_mouse
{
    class DrawableText;
}

class NumberBox;

namespace super_mouse
{
    class RightBar : public Drawable
    {
    public:
        RightBar();
        void render(SDL_Renderer* renderer) override;

        void setNumberScore(int num) const;
        void setNumberSpeed(int num) const;
        void setNumberLevel(int num) const;

        int getScore() const;
        int getSpeed() const;
        int getLevel() const;

        void setTextVisibility(ERightBarText text, bool visible) const;

        void setTextBlinkingPeriod(ERightBarText text, float period) const;
        void setTextBlinking(ERightBarText text, bool isBlinking) const;

        void SwitchScoreAndHiScore(bool Score);

    private:
        NumberBox* _scoreNumBox;
        NumberBox* _speedNumBox;
        NumberBox* _levelNumBox;

        DrawableText* _tHi;
        DrawableText* _tScore;
        DrawableText* _tSpeed;
        DrawableText* _tLevel;
        DrawableText* _tPause;
        DrawableText* _tGameOver;

        std::map<ERightBarText, DrawableText*> _textMap{};
    };
}
