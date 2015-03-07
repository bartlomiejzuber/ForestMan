#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\Audio.hpp>
#include <SFML\System.hpp>

#include "cfg\Directives.h"
#include "Character.h"
#include <iostream>
#include <fstream>

using namespace sf;
class Engine
{
public:
	Engine();
	void Ini_world(RenderWindow &MainWindow);
	bool QuitTheGame;
private:
	Event CurrentEvent;
	unsigned int CurrentLevel;
	bool Wave[5];
	bool HesAWinner = false;
	Music HitSound_1, MenuMusic, MainMusic;



	//Engine
	void CollisionCheck(Character *postac, Sprite &Collider);
	void CollisionWithEnemyCheck(Character *postac, Sprite &Collider, Character *postac2);

	void LevelManager(RenderWindow &MainWindow);
		void StartLevel_1(RenderWindow &MainWindow);
			void LoadBgLvl1(Sprite *BgSprite, Texture *BgTexture, short int &i);
			//void LoodFloorLvl1(Sprite *FlSprite, Texture *FlTexture, unsigned int &i);
			void IsClickedX();
			void StartWave(float PlayerPos);
		void TempMenu(RenderWindow &MainWindow);


protected:
	enum PlayerSelection { RETRY, BACK_TO_MENU, QUIT };
	PlayerSelection PlayerAction;
};

