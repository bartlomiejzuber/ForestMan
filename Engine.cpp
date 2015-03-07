#include "Engine.h"
#include "Character.h"
#include "Player.h"
#include "Wolf.h"
#include <string>


using namespace std;
using namespace sf;

Engine::Engine()
{
	CurrentLevel = 1;
	QuitTheGame = false;
	HitSound_1.openFromFile("Assets/Levels/1/hit14.mp3");
	MenuMusic.openFromFile("Assets/Levels/1/howl.wav");
	MainMusic.openFromFile("Assets/Music/Bohuslav_Martinu_Allegro.wav");
	MainMusic.setLoop(true);
	MainMusic.play();
}

void Engine::LevelManager(RenderWindow &MainWindow)
{
	while (PlayerAction != QUIT)
	{
		switch (CurrentLevel)
		{
		case 1:
			StartLevel_1(MainWindow);
			break;
		case 2:

		case 0:
			MainMusic.stop();
			TempMenu(MainWindow);
			break;
		}
	}
}

void Engine::TempMenu(RenderWindow &MainWindow)
{
	string str[] = { "RETRY", "BACK TO MAIN MENU", "QUIT" };
	Text *options = new Text[3];
	Font *czcionka = new Font;
	czcionka->Font_Main;

	Sprite Bg;
	Texture Tx;
	Tx.loadFromFile("Assets/Levels/1/Winner_is_you.jpg");
	Bg.setTexture(Tx);
	Bg.setOrigin(Bg.getScale().x / 2, 0);
	Bg.setPosition(Window_Width / 2, 20);
	

	MenuMusic.play();

	for (int i = 0; i < 3; i++)
	{
		(options + i)->setFont(*czcionka);
		(options + i)->setString(str[i]);
		(options + i)->setColor(Color::White);
		(options + i)->setOrigin((options + i)->getScale().x / 2, 0);
		(options + i)->setPosition((Window_Width / 2), (100 * i) + 255);
	}

	View defCamera;
	defCamera = MainWindow.getDefaultView();
	MainWindow.setView(defCamera);
	
	while (PlayerAction != QUIT && CurrentLevel == 0)
	{
		MainWindow.clear();
		Vector2f Mouse_pos(Mouse::getPosition(MainWindow));

		while (MainWindow.pollEvent(CurrentEvent)) // Pobieranie ostatniego wydarzenia ze stosu.
		{
			IsClickedX();

			if ((options+0)->getGlobalBounds().contains(Mouse_pos) && CurrentEvent.type == Event::MouseButtonReleased && CurrentEvent.key.code == Mouse::Left) // Wybranie opcji ABOUT
			{
				CurrentLevel = 1;
				MenuMusic.stop();
				MainMusic.play();
			}
			if ((options + 1)->getGlobalBounds().contains(Mouse_pos) && CurrentEvent.type == Event::MouseButtonReleased && CurrentEvent.key.code == Mouse::Left) // Wybranie opcji ABOUT
			{
				MenuMusic.stop();
				PlayerAction = QUIT;
			}
			if ((options + 2)->getGlobalBounds().contains(Mouse_pos) && CurrentEvent.type == Event::MouseButtonReleased && CurrentEvent.key.code == Mouse::Left) // Wybranie opcji ABOUT
			{
				MenuMusic.stop();
				PlayerAction = QUIT;
				QuitTheGame = true;
			}

		}

		for (int i = 0; i < Text_TMenuAmout; i++)
		{
			if ((options +i)->getGlobalBounds().contains(Mouse_pos))
				(options + i)->setColor(sf::Color(50, 255, 255, 255));
			else
				(options+i)->setColor(sf::Color(0, 204, 153, 255));
			for (int i = 0; i < Text_TMenuAmout; i++)
				MainWindow.draw(*(options+i));
		}
		if (HesAWinner == true)
			MainWindow.draw(Bg);
		MainWindow.display();
	}
	delete[] options;
	delete czcionka;
}

void Engine::StartLevel_1(RenderWindow &MainWindow)
{
	#pragma region wczytanie tla pozionu
		Texture *BGTexture_lvl1 = new Texture;
		BGTexture_lvl1->Texture_Lvl1Background;
		Sprite *BGSprite_lvl1 = new Sprite[BackgroundNumber];

		(BGSprite_lvl1 + 0)->setTexture(*BGTexture_lvl1);
		(BGSprite_lvl1 + 0)->setPosition(-995, 0);

		for (int i = 1; i < BackgroundNumber; i++)
		{
			(BGSprite_lvl1 + i)->setTexture(*BGTexture_lvl1);
			(BGSprite_lvl1 +i)->setPosition(995 * (i-1), 0);
		}
	#pragma endregion
		
	#pragma region wczytanie podlogi
		Texture *FloorTexture_lvl1 = new Texture;
		FloorTexture_lvl1->Texture_Lvl1Floor;
		Sprite *FloorSP_lvl1 = new Sprite[60];
		unsigned int Map[TilesNumber] = Level1_FloorMap;
		for (int i = 0; i < 60; i++)
		{
			if (Map[i]!=9)
				(FloorSP_lvl1 + i)->setTexture(*FloorTexture_lvl1);
			if (Map[i]==0)
				(FloorSP_lvl1 + i)->setPosition(85 * i, Ground);
			if (Map[i]==1)
				(FloorSP_lvl1 + i)->setPosition(85 * i, Air);
			if (Map[i]==2)
				(FloorSP_lvl1 + i)->setPosition(85 * i, Underground);
			if (Map[i]==3)
				(FloorSP_lvl1 + i)->setPosition(85 * i, HighUnderground);
		}
	#pragma endregion

	Color BgColor;
	BgColor.r = 221;
	BgColor.b = 255;
	BgColor.g = 248;

	HesAWinner = false;

	for (short int i = 0; i < 5; i++)
		Wave[i] = false;

	View MainCamera(Vector2f((Window_Width / 2), (Window_Height / 2)), Vector2f(Window_Height, Window_Width));
	MainWindow.setView(MainCamera);

	Character *MainChar, *char2;
	Player Gracz;
	Clock BossClock;
	bool BossClockRes = false;

	Text PlayerHp;
	Font HpFont;
	HpFont.Font_Default;
	PlayerHp.setFont(HpFont);
	PlayerHp.setCharacterSize(15);
	PlayerHp.setColor(Color::Black);
	string str;

	Text PlayerCong;
	PlayerCong.setFont(HpFont);
	PlayerCong.setCharacterSize(15);
	PlayerCong.setColor(Color::Black);

/*	// -------------------
	Text PlayerPos;
	PlayerPos.setFont(HpFont);
	PlayerPos.setCharacterSize(15);
	PlayerPos.setColor(Color::Black);
	//-------------------- */

	Wolf wolf[WolfsNumber];
	char2 = &wolf[0];

	for (int i = 0; i < Wave_I; i++)
	{
		if (i == Wave_I-1)
		{
			wolf[i].WolfSprite.setPosition(1150, 650);
			wolf[i].JumpApproved = false;
			wolf[i].HesNoob();
			break;
		}
		wolf[i].HesNoob();
		wolf[i].WolfSprite.setPosition((100 * i) + 800, 650);
		wolf[i].JumpApproved = false;
	}
	for (int i = Wave_I; i < Wave_II; i++)
	{
		wolf[i].HesNoob();
		wolf[i].WolfSprite.setPosition(2576, 445);
		wolf[i].JumpApproved = false;
	}
	for (short int i = Wave_II; i < Wave_III; i++)
	{
		wolf[i].HesNoob();
		wolf[i].WolfSprite.setPosition(3172+(i*100), 288);
		wolf[i].JumpApproved = false;
	}
	for (short int i = Wave_III; i < Wave_IV; i++)
	{
		wolf[i].WolfSprite.setPosition(5052, 435);
		wolf[i].JumpApproved = false;
		wolf[i].HesBoss();
	}


	Clock WaveClock;

	while (PlayerAction != QUIT && CurrentLevel != 0)
	{
		MainWindow.clear(BgColor);
		while (MainWindow.pollEvent(CurrentEvent)) // Pobieranie ostatniego wydarzenia ze stosu.
		{
			IsClickedX();
		}

		for (int i = 0; i < BackgroundNumber; i++)
			MainWindow.draw(BGSprite_lvl1[i]);
		for (int i = 0; i < TilesNumber; i++)
			MainWindow.draw(FloorSP_lvl1[i]);

		MainChar = &Gracz;
		if (MainChar->GetHealth() <= 0)
			CurrentLevel = 0;
		MainChar->Walk();
		MainChar->Update();
		for (int i = 0; i < TilesNumber; i++)
			CollisionCheck(MainChar, FloorSP_lvl1[i]); // kolizja gracza z otoczeniem

		StartWave(Gracz.GetPlayerPosition().x);

		// FALA 1
		if (Wave[0] == true)
		{
			for (int j = 0; j < Wave_I; j++)
			{
				char2 = &wolf[j];
				if (wolf[j].GetHealth() > 0)
					CollisionWithEnemyCheck(MainChar, wolf[j].WolfSprite, char2); // kolizja wilka z graczem
			}
			for (int i = 0; i < Wave_I; i++)
			{
				MainChar = &wolf[i];
				MainChar->Walk();
				MainChar->Update();
				for (int j = 0; j < TilesNumber; j++)
					CollisionCheck(MainChar, FloorSP_lvl1[j]); // kolizja wilka z otoczeniem
			}
		}
		// FALA 2
		if (Wave[1] == true)
		{
			Wave[0] = false;

			for (int j = Wave_I; j < Wave_II; j++)
			{
				MainChar = &Gracz;
				char2 = &wolf[j];
				if (wolf[j].GetHealth() > 0)
					CollisionWithEnemyCheck(MainChar, wolf[j].WolfSprite, char2); // kolizja wilka z graczem
			}
			for (int i = Wave_I; i < Wave_II; i++)
			{
				MainChar = &wolf[i];
				MainChar->Walk();
				MainChar->Update();
				for (int j = 0; j < TilesNumber; j++)
					CollisionCheck(MainChar, FloorSP_lvl1[j]); // kolizja wilka z otoczeniem
			}
		}
		if (Wave[2] == true)
		{
			Wave[1] = false;

			for (int j = Wave_II; j < Wave_III; j++)
			{
				MainChar = &Gracz;
				char2 = &wolf[j];
				if (wolf[j].GetHealth() > 0)
					CollisionWithEnemyCheck(MainChar, wolf[j].WolfSprite, char2); // kolizja wilka z graczem
			}
			for (int i = Wave_II; i < Wave_III; i++)
			{
				MainChar = &wolf[i];
				MainChar->Walk();
				MainChar->Update();
				for (int j = 0; j < TilesNumber; j++)
					CollisionCheck(MainChar, FloorSP_lvl1[j]); // kolizja wilka z otoczeniem
			}
		}
		if (Wave[3] == true)
		{
			Wave[2] = false;

			MainChar = &Gracz;
			char2 = &wolf[Wave_III];
			if (wolf[Wave_III].GetHealth() > 0)
				CollisionWithEnemyCheck(MainChar, wolf[Wave_III].WolfSprite, char2); // kolizja wilka z graczem
			MainChar = &wolf[Wave_III];
			MainChar->Walk();
			MainChar->Update();
			for (int j = 0; j < TilesNumber; j++)
				CollisionCheck(MainChar, FloorSP_lvl1[j]); // kolizja wilka z otoczeniem
		}
		str = "Player HP: ";
		str += to_string(Gracz.GetHealth());
		PlayerHp.setString(str);
		PlayerHp.setPosition(Gracz.GetPlayerPosition().x-400, Gracz.GetPlayerPosition().y-300);

	/*	str = "x = ";
		str += to_string((int)Gracz.GetPlayerPosition().x);
		str += " ; y = ";
		str += to_string((int)Gracz.GetPlayerPosition().y);
		PlayerPos.setString(str);
		PlayerPos.setPosition(Gracz.GetPlayerPosition().x - 300, Gracz.GetPlayerPosition().y - 300);*/

		if (wolf[Wave_IV-1].GetHealth() <= 0 && BossClockRes == false)
		{
			BossClock.restart();
			BossClockRes = true;

			str = "You are Winner!";
			PlayerCong.setString(str);
		}
		if (BossClock.getElapsedTime() > seconds(2) && BossClockRes == true)
		{
			CurrentLevel = 0;
			HesAWinner = true;
		}
		MainCamera.setCenter(Gracz.GetPlayerPosition());
		MainWindow.setView(MainCamera);
		if (Wave[0]==true)
			for (short int i = 0; i < Wave_I; i++)
				MainWindow.draw(wolf[i]);
		if (Wave[1]==true)
			for (short int i = Wave_I; i < Wave_II; i++)
				MainWindow.draw(wolf[i]);
		if (Wave[2] == true)
			for (short int i = Wave_II; i < Wave_III; i++)
				MainWindow.draw(wolf[i]);
		if (Wave[3] == true)
			for (short int i = Wave_III; i < Wave_IV; i++)
				MainWindow.draw(wolf[i]);
		MainWindow.draw(Gracz);
		MainWindow.draw(PlayerHp);
//		MainWindow.draw(PlayerPos);
		if (wolf[Wave_IV - 1].GetHealth() <= 0)
		{
			PlayerCong.setPosition(Gracz.GetPlayerPosition().x + 50, Gracz.GetPlayerPosition().y - 100);
			MainWindow.draw(PlayerCong);
		}
		MainWindow.display();
	}
	delete[] BGSprite_lvl1;
	delete[] FloorSP_lvl1;
}

void Engine::IsClickedX()
// Nacisniecie przycisku 'X' 
{
	if (CurrentEvent.type == Event::Closed)
	{
		PlayerAction = QUIT;
		QuitTheGame = true;
	}
}

void Engine::CollisionCheck(Character *postac, Sprite &Collider)
{
	FloatRect Box1(postac->GetBox());
	Box1.width = Box1.width / 2;
	Box1.left = Box1.left + 17;
	Box1.top = Box1.top - 9;
	if (Box1.intersects(Collider.getGlobalBounds()))
	{
		postac->StopRight();
	}
	
	Box1 = (postac->GetBox());
	Box1.top = Box1.top - 7;
	Box1.width = Box1.width / 2;
	if (Box1.intersects(Collider.getGlobalBounds()))
	{
		postac->StopLeft();
	}

	Box1 = (postac->GetBox());
	Box1.width = Box1.width / 2;
	Box1.left = Box1.left + 2.5;
	if (Box1.intersects(Collider.getGlobalBounds()))
	{
		postac->StopPadding();
	}
	FloatRect Box4(Vector2f(-870, 850), Vector2f(995 * BackgroundNumber, 2));
	if (Box1.intersects(Box4))
	{
		if ( (postac->Type()) == 0) // gracz
			CurrentLevel = 0;
		if (postac->Type() == 1) // wilk
			postac->Kill(200);
	}

	// WALKA Z BOSSEM
	if (postac->Type() == 2)
	{
		FloatRect Box5(Vector2f(4320, 440), Vector2f(1, 700));
		if (Box1.intersects(Box5))
		{
			postac->StopLeft();
		}
		FloatRect Box6(Vector2f(5080, 440), Vector2f(1, 700));
		if (Box1.intersects(Box6))
		{
			postac->StopRight();
		}
	}


}

void Engine::CollisionWithEnemyCheck(Character *postac, Sprite &Collider, Character *postac2)
{
	FloatRect Box1(postac->GetBox());
	Box1.width = Box1.width / 2;
	Box1.left = Box1.left + 17;
	Box1.top = Box1.top - 8;
	if (Box1.intersects(Collider.getGlobalBounds()))
	{
		postac->StopRight();
		if (postac->Type() == 0 && ( (postac2->Type() == 1 || postac2->Type() == 2) && postac2->GetHealth() > 0))
		{
			if (Keyboard::isKeyPressed(Keyboard::Key::LControl) && postac2->GetHealth() > 0 && postac2->Type() != 2) // zabicie wilka
			{
				HitSound_1.play();
				postac->Attack(postac2);
			}
			else if (postac2->GetHealth() > 0)
			{
				postac2->Attack(postac);
			}
		}

	}

	Box1 = (postac->GetBox());
	Box1.top = Box1.top - 7;
	Box1.width = Box1.width / 2;
	if (Box1.intersects(Collider.getGlobalBounds()))
	{
		postac->StopLeft();
	}

	Box1 = (postac->GetBox());
	Box1.width = Box1.width - 5;
	Box1.left = Box1.left + 2.5;
	
	FloatRect *WolfBox = new FloatRect;
	*WolfBox = (postac2->GetBox());
	WolfBox->width = WolfBox->width - 3;
	WolfBox->left = WolfBox->left + 3;

	if (Box1.intersects(*WolfBox))
	{
		postac->StopPadding();
		if (postac2->GetHealth() > 0)
		{
			HitSound_1.play();
			postac->Attack(postac2);
		}
	}

	FloatRect Box4(Vector2f(-870, 850), Vector2f(995 * BackgroundNumber, 1));
	if (Box1.intersects(Box4))
	{
		if ((postac->Type()) == 0) // gracz
			CurrentLevel = 0;
		if (postac2->Type() == 1) // wilk
			postac2->Kill(200);
	}
	delete WolfBox;
}

void Engine::StartWave(float PlayerPos)
{
	if (PlayerPos >= 400)
		Wave[0] = true;
	if (PlayerPos >= 2070)
		Wave[1] = true;
	if (PlayerPos >= 3072)
		Wave[2] = true;
	if (PlayerPos >= 4325)
		Wave[3] = true;
}

void Engine::Ini_world(RenderWindow &MainWindow)
{
	while (PlayerAction != QUIT)
	{
		LevelManager(MainWindow);
	}
}
