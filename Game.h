#pragma once
//Wczytanie bibliotek SFML 2.1
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Audio.hpp>

//Biblioteki podstawowe C++
#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>

//Biblioteki zdefiniowane
#include "Animation.h"
#include "cfg\Directives.h"

using namespace std;
using namespace sf;  // Dodanie przestrzeni nazw z biblioteki SFML 2.1

// Podstawowa klasa, zarzadzająca całą grą.
class Game
{
public:
	Game(void);
	~Game(void);

	void InitializeGame(RenderWindow &Main_Window);
	bool IniEngine = false;
private:
	Font Main_Font, About_me_font;
	Event MainMenu_event;											// Zmienna przechwytująca wydarzenia.
	Texture Tx_MainMenu_Background, Tx_MainMenu_FogAnim, About_bg, Mute_button_tx, unMute_button_tx, Tx_MainMenu_Animation[TA_FilesAmout];
	Sprite Sp_MainMenu_Background, Sp_MainMenu_FogAnim, About_sp, Mute_button, Mute_button_sp, Sp_MainMenu_Animation[TA_FilesAmout];
	Animation Animation_MMenu;
	Music MainMenu_Music;

	// Funkcje inicjalizacji.
	void Loading(RenderWindow &Main_Window) const;
	void LoadMusic(string *Config);
	void LoadFont();
	void LoadTextures();
	void LoadText(Text *MainMenu_Text);
	void LoadTitleAnimation();
	void LoadGame();
	string* LoadCFG_File() const;

	void MainMenu_Actions(Vector2f &Mouse_pos, Text *MainMenu_Text);
	void IsClickedX();
	void IsClickedStart(Vector2f &Mouse_pos, Text *MainMenu_Text);
	void IsClickedAbout(Vector2f &Mouse_pos, Text *MainMenu_Text);
	void IsClickedExit(Vector2f &Mouse_pos, Text *MainMenu_Text);
	void IsClickedMusicBtn(Vector2f &Mouse_pos);
	void FillStr(string *str) const;

	void RunGame(RenderWindow &Main_window);
	void MainMenu(RenderWindow &MainMenu_window);
	void AboutMe(RenderWindow &About_window);

	void Player_ContinueOrStart(RenderWindow &MainWindow);

	//Komentarz dotyczący znaczenia stanów gry.
	/*
	#-----------------------------------------------------------------------------------------------------------------------------------#
	#Lista wyliczeniowa przedstawiająca obsługe różnych stanów gry.																		#
	#	Stan:																															#
	#			- MENU - Gracz jest w MENU głównym gry.																					#
	#			- GAME_START - Gracz rozpoczął gre, tzn. nacisnął przycistk START w MENU głównym gry.									#
	#			- ABOUT - Tabelka z informacjami o autorze.																				#
	#			- QUIT - Gracz nacisnął klawisz EXIT lub wystąpił bład w grze, związany z wyczytwaniem zawartości gry, lub INNY.		#
	#																																	#
	#-----------------------------------------------------------------------------------------------------------------------------------#*/
	enum GameStates { MENU, ABOUT,GAME_START, QUIT, LOAD, START_FROM_THE_BEGINING };
	GameStates CurrentState;
};
