#pragma once
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"
#include "Character.h"
#include "cfg\Directives.h"

using namespace sf;

class Wolf : public Character, public sf::Drawable
{
public:
	Wolf();

	virtual void Attack(Character *postac);
	virtual void Walk();
	virtual void StopPadding();
	virtual void StartPadding();
	virtual void StopRight();
	virtual void StopLeft();
	virtual sf::FloatRect GetBox()
	{
		return WolfSprite.getGlobalBounds();
	}
	virtual void StartJump();
	virtual void Update();
	virtual short int Type();
	virtual void Kill(unsigned int Hit);
	virtual short int GetHealth();

	void HesBoss();
	void HesNoob();
	Sprite WolfSprite;
	
	bool JumpApproved = true;
	

private:

	Texture WolfTx;
	Texture WolfDeadTx;

	Music WolfDeadSound;

	short int Lives = 2;
	short int Padding_Speed = 6;
	short int Walk_speed = 2;

	unsigned int frame = 0;
	unsigned int WolfType = 2;
	
	bool runleft = true;
	bool runright = false;
	bool LeftCollision = false;
	bool RightCollision = false;
	bool FeetCollision = false;
	bool StartJumping = false;
	bool CanJump = true;
	bool iamBoss = false;

	Clock Jump_clock;
	Clock animclock;

	void Jump();
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		target.draw(WolfSprite);
	}
};

