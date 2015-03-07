#include "Wolf.h"

using namespace sf;
Wolf::Wolf()
{
	WolfTx.loadFromFile("Assets/Levels/1/wolfsrunning.png");
	WolfSprite.setTexture(WolfTx);
	WolfSprite.setTextureRect(IntRect(Vector2i(0, 0), OneFrameWolfSize));
	WolfDeadTx.loadFromFile("Assets/Levels/1/wolfdead.png");
	WolfDeadSound.openFromFile("Assets/Levels/1/wolf_hityelp.wav");
}
void Wolf::Kill(unsigned int Hit)
{
	Lives = Lives - Hit;
	WolfSprite.move(28, -10);
	if (Lives <= 0 && Lives>=-100)
	{
		WolfDeadSound.play();
		WolfSprite.setTexture(WolfDeadTx);
		WolfSprite.setTextureRect(IntRect(Vector2i(0, 0), Vector2i(60, 21)));
	}
	if (Lives < -150)
		WolfSprite.setTextureRect(IntRect(Vector2i(0, 0), Vector2i(1, 1)));
}
short int Wolf::GetHealth()
{
	return Lives;
}
void Wolf::StopPadding()
{
	FeetCollision = true;
}
void Wolf::StartPadding()
{
	FeetCollision = false;
}

void Wolf::StopLeft()
{
	LeftCollision = true;
}
void Wolf::StopRight()
{
	RightCollision = true;
}
void Wolf::StartJump()
{
	StartJumping = true;
}
void Wolf::HesNoob()
{
	WolfType = 1;
}
short int Wolf::Type()
{
	return WolfType; // 0 - gracz, 1 - wilk, 2 - niedźwiedz
}

void Wolf::Attack(Character *postac)
{
	postac->Kill(1);
}

void Wolf::Jump()
{
	WolfSprite.move(-2, -9);
	if (Jump_clock.getElapsedTime() > seconds(0.35))
	{
		StartJumping = false;
		Jump_clock.restart();
	}
}

void Wolf::HesBoss()
{
	WolfSprite.setScale(Vector2f(WolfSprite.getScale().x * 2, WolfSprite.getScale().y * 2));
	Lives = 10;
	WolfType = 2;
}

void Wolf::Walk()
{
	if (WolfType == 1)
	{
		if (GetHealth() > 0)
		{
			if (StartJumping == false && FeetCollision == true && CanJump == false && JumpApproved == true)
				CanJump = true;
		}

		if (GetHealth() > -100)
		{
			if (FeetCollision != true)
				WolfSprite.move(0, (Padding_Speed));
			else
				FeetCollision = false;
		}
		else
			StopPadding();

		if (GetHealth() > 0)
		{
			if (CanJump == true && StartJumping == false)
			{
				StartJump();
				CanJump = false;
				Jump_clock.restart();
			}
			if (StartJumping == true && CanJump == false)
				Jump();

			if (LeftCollision == false)
				WolfSprite.move(-(Walk_speed * 2), 0);
			else
				LeftCollision = false;
		}
	}
	if (WolfType == 2)
	{
		if (GetHealth() > -100)
		{
			if (FeetCollision != true)
				WolfSprite.move(0, (Padding_Speed));
			else
				FeetCollision = false;
		}
		else
			StopPadding();

		if (GetHealth() > 0)
		{
			if (LeftCollision == false)
				WolfSprite.move(-(Walk_speed * 2), 0);

			if (LeftCollision == true)
				WolfSprite.move((Walk_speed * 2), 0);

			if (RightCollision == true)
			{
				LeftCollision = false;
				RightCollision = false;
			}
		}
	}
}

void Wolf::Update()
{
	if (StartJumping == false && Lives > 0)
	{
		if (LeftCollision == false)
		{
			if (animclock.getElapsedTime() > sf::seconds(0.05))
			{
				animclock.restart();
				if (frame < 5)
					frame++;
				if (frame == 5)
					frame = 0;
				WolfSprite.setTextureRect(IntRect(Vector2i(64 * frame, 0), OneFrameWolfSize));
			}
		}
		else
		{
			if (animclock.getElapsedTime() > sf::seconds(0.05) && WolfType == 2 && LeftCollision == true)
			{
				animclock.restart();
				if (frame < 5)
					frame++;
				if (frame == 5)
					frame = 0;
				WolfSprite.setTextureRect(IntRect(Vector2i(64 * frame, 32), OneFrameWolfSize));
			}
		}
	}
	else if (FeetCollision == true && Lives > 0)
	{
		if (animclock.getElapsedTime() > sf::seconds(0.05))
		{
			animclock.restart();
			if (frame < 5)
				frame++;
			if (frame == 5)
				frame = 0;
			WolfSprite.setTextureRect(IntRect(Vector2i(64 * frame, 0), OneFrameWolfSize));
		}
	}
}
