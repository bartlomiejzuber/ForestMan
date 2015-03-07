#pragma once
/*
#-----------------------------------------------------------------------------------#
#																					#
#	Klasa odpowiadająca za wyświetlanie animacji.									#
#																					#
#	sf::Sprite &AnimationSprite - Sprite który ma być animacją.						#
#	unsigned int FramesAmout - Ilość klatek w animacji.								#
#	unsigned int TxtrShiftPerFrame - Wartosc przesuniecia SpriteSheet'a co kaltke.	#
#	unsigned int TxtRectWidth - Szerokosc wyswietlanego box'a.						#
#	unsigned int TxtRectHeight - Wysokosc wyswietlanego box'a.						#
#	float FTime_perFrame - Czas do kolejnej zmiany klatki							#
#	bool FrameLoop - Wartosc odpowiadajaca za zapetlenie animacji					#
#																					#
#-----------------------------------------------------------------------------------#
*/
#include <SFML\Graphics.hpp>

class Animation
{
public:
	Animation(void);
	unsigned int Frame;
	sf::Clock Frame_timer;
	int Update(sf::Sprite &AnimationSprite, unsigned int FramesAmout, float TxtrShiftPerFrame, unsigned int TxtRectWidth, unsigned int TxtRectHeight, float FTime_perFrame, bool FrameLoop);
};



