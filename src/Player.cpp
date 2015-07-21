#include "Player.h"


Player::Player()
{
	PlayerTexture.loadFromFile("Assets/Levels/1/player.png");
	PlayerSprite.setTexture(PlayerTexture);
	PlayerSprite.setTextureRect(IntRect(Vector2i(53, 127), OneFramePlayerSize));
	PlayerSprite.PlayerStartPos; // POZYCJA STARTOWA
}

Vector2f Player::GetPlayerPosition()
{
	return PlayerSprite.getPosition();
}

void Player::StopPadding()
{
	FeetCollision = true;
}

void Player::StartPadding()
{
	FeetCollision = false;
}

sf::FloatRect Player::GetBox()
{
	return PlayerSprite.getGlobalBounds();
}

void Player::StopRight()
{
	RightCollision = true;
}

void Player::Jump()
{

	PlayerSprite.move(0, -17.5);
	if (Jump_clock.getElapsedTime() > seconds(0.45))
	{
		StartJumping = false;
		Jump_clock.restart();
	}
}

void Player::StartJump()
{
	StartJumping = true;
}

void Player::StopLeft()
{
	LeftCollision = true;
}

void Player::Walk()
{
	if (StartJumping == false && FeetCollision == true && CanJump == false)
	{
		CanJump = true;
	}
	else
		CanJump = false;

	if (FeetCollision != true)
		PlayerSprite.move(0, (Padding_Speed));
	else
		FeetCollision = false;

	if (Keyboard::isKeyPressed(Keyboard::Key::D) && RightCollision == false)
		PlayerSprite.move(Walk_speed * 2, 0);
	else
		RightCollision = false;

	if (Keyboard::isKeyPressed(Keyboard::Key::A) && LeftCollision == false)
	{
		PlayerSprite.move(-(Walk_speed * 2), 0);
	}
	else
		LeftCollision = false;

	if (Keyboard::isKeyPressed(Keyboard::Key::Space) && CanJump == true && StartJumping == false)
	{
		StartJump();
		CanJump = false;
		Jump_clock.restart();
	}

	if (StartJumping == true && CanJump == false)
	{
		Jump();
	}
}

void Player::Update()
{


	if (StartJumping == false)
	{
		if (Keyboard::isKeyPressed(Keyboard::Key::D))
		{
			if (Keyboard::isKeyPressed(Keyboard::Key::LControl))
			{
				if (animclock.getElapsedTime() > sf::seconds(0.05))
				{
					animclock.restart();
					if (frame < 3)
						frame++;
					if (frame == 3)
						frame = 0;
					PlayerSprite.setTextureRect(IntRect(Vector2i(52 * frame, 0), Vector2i(44,64)));
				}
			}
			else
			{
				if (animclock.getElapsedTime() > sf::seconds(0.05))
				{
					animclock.restart();
					if (frame < 3)
						frame++;
					if (frame == 3)
						frame = 0;
					PlayerSprite.setTextureRect(IntRect(Vector2i(52 * frame, 64), OneFramePlayerSize));
				}
			}
		}
		else if (Keyboard::isKeyPressed(Keyboard::Key::A))
		{
			if (animclock.getElapsedTime() > sf::seconds(0.05))
			{
				animclock.restart();
				if (frame < 3)
					frame++;
				if (frame == 3)
					frame = 0;
				PlayerSprite.setTextureRect(IntRect(Vector2i(52 * frame, 192), OneFramePlayerSize));
			}
		}
	}
	else
		PlayerSprite.setTextureRect(IntRect(Vector2i(104, 64), OneFramePlayerSize));

}

short int Player::Type()
{
	return 0;
}

void Player::Attack(Character *postac)
{
	postac->Kill(2);
}

void Player::Kill(unsigned int Hit)
{
	Lives = Lives - Hit;
	PlayerSprite.move(-38, -10);
}

short int Player::GetHealth()
{
	return Lives;
}
