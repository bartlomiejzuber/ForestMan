#pragma once

#include "SFML\Graphics.hpp"
class Character 
{
public:
	virtual void Attack(Character *postac2) = 0;
	virtual void Walk() = 0;
	virtual void StopPadding() = 0;
	virtual void StartPadding() = 0;
	virtual void StopRight() = 0;
	virtual void StopLeft() = 0;
	virtual void StartJump() = 0;
	virtual sf::FloatRect GetBox() = 0;
	virtual void Update() = 0;
	virtual short int Type() = 0;
	virtual void Kill(unsigned int Hit) = 0;
	virtual short int GetHealth() = 0;
};

