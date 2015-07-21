#include "Animation.h"

Animation::Animation(void)
{
	Frame = 0;
}

int Animation::Update(sf::Sprite &AnimationSprite, unsigned int FramesAmout,float TxtrShiftPerFrame, unsigned int TxtRectWidth, unsigned int TxtRectHeight, float FTime_perFrame, bool FrameLoop)
{
	if (Animation::Frame_timer.getElapsedTime() > sf::seconds(FTime_perFrame)) // Warunek sprawdzajacy czy uplynal zalozony czas.
	{
		if (Frame < FramesAmout) // Ilość klatek w animacji.
			Frame++;
		else if (FrameLoop) // Zapetlenie animacji 
		Frame = 0;

		AnimationSprite.setTextureRect(sf::IntRect(Frame * TxtrShiftPerFrame, 0 , TxtRectWidth, TxtRectHeight));
		Animation::Frame_timer.restart();
		return Frame;
	}
}


