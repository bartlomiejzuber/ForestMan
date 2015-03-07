#pragma once
#include "Character.h"
#include "SFML\Graphics.hpp"
#include "cfg\Directives.h"

using namespace sf;

class Player : public Character, public sf::Drawable
{
public:
	Player();

	virtual void Attack(Character *postac2);
	virtual void Walk();
	virtual void StopPadding();
	virtual void StartPadding();
	virtual void StopRight();
	virtual void StopLeft();
	virtual sf::FloatRect GetBox();
	virtual void StartJump();
	virtual void Update();
	virtual short int Type();
	virtual void Kill(unsigned int Hit);
	virtual short int GetHealth();
	
	Vector2f GetPlayerPosition();
private:
	bool FeetCollision = false;
	bool RightCollision = false;
	bool LeftCollision = false;
	bool StartJumping = false;

	bool CanJump = true;
	bool walking = false;
	

	Clock Jump_clock;

	short int Padding_Speed = 6;
	short int Walk_speed = 2;
	short int Jump_str = 2;
	short int frame = 0;
	short int Lives = 100;

	Clock animclock;

	Sprite PlayerSprite;
	Texture PlayerTexture;

	Sprite PlayerWeaponSprite;
	Texture PlayerWeapon;

	void Jump();
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		target.draw(PlayerSprite);
	}
};

