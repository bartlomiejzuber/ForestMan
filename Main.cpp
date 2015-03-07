/*=======================================================================================================================
#	Projekt z przedmiotu "Programowanie w C++" - Politechnika Rzeszowska 2014											#
#	Autor: Bartlomiej Zuber																								#
#	Nr_albumu: * 137539 *																								#
#	Email: bajtas@gmail.com																								#																			#
#=======================================================================================================================#*/

#include "Game.h"
#include "Engine.h"
#include "cfg\Directives.h"

using namespace sf;

int main()
{
	//	Stworzenie głównego okna gry.
	RenderWindow Main_Window(VideoMode(Window_Height, Window_Width), Title_String, Style::Close);
	Main_Window.setFramerateLimit(Max_FPS);

	bool Escape_seq = false;

	while (!Escape_seq)
	{
		Game *game = new Game;
		game->InitializeGame(Main_Window);
		if (game->IniEngine == true)
		{
			delete game;
			Engine *MainEngine = new Engine;
			MainEngine->Ini_world(Main_Window);
			
			if (MainEngine->QuitTheGame == true)
				Escape_seq = true;

			delete MainEngine;
		}
		else
		{
			delete game;
			Escape_seq = true;
		}
		
	}
	
	return EXIT_SUCCESS;
}
