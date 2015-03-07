#include "Game.h"

Game::Game(void)
{
	CurrentState = MENU;
}

Game::~Game(void)
{
	MainMenu_Music.stop();
}

void Game::LoadFont()
//	Wczytanie czcionki stanu: MENU oraz ABOUT.
{
	if (!Main_Font.Font_Main || !About_me_font.Font_Default)
	{
		MessageBox(NULL, "Nie znaleziono czcionki!", "Błąd!", MB_OK);
		CurrentState = QUIT;
	}
}

void Game::LoadMusic(string *Config)
//	Wczytanie muzyki w MENU gry.
{
	if (!Game::MainMenu_Music.Music_MainMenu)
	{
		MessageBox(NULL, "Nie znaleziono sciezki audio!", "Błąd!", MB_OK);
		CurrentState = QUIT;
	}
	//Zapetlenie muzyki MENU
	MainMenu_Music.setLoop(true);


	// Wczytanie buttonów Mute & unMute
	if (Config[0].at(13) == '1')
	{
		Game::MainMenu_Music.play();
		Game::Mute_button_sp.setTexture(Game::Mute_button_tx);
	}
	else if (Config[0].at(13) == '0')
	{
		Game::MainMenu_Music.pause();
		Game::Mute_button_sp.setTexture(Game::unMute_button_tx);
	}
	Game::Mute_button_sp.setPosition(730, 540);
}

void Game::LoadTextures()
{
	//------------WCZYTYWANIE TEKSTUR MENU------------//
	if (!Tx_MainMenu_Background.Texture_MMBackground || !Tx_MainMenu_FogAnim.Texture_MMFogAnim
		|| !About_bg.Texture_ABBackground || !Game::Mute_button_tx.Texture_MuteBtn || !Game::unMute_button_tx.Texture_UnMuteBtn )
	{
		MessageBox(NULL, "Nie znaleziono tekstur!", "Błąd!", MB_OK);
		Game::CurrentState = QUIT;
	}
	Game::Sp_MainMenu_Background.setTexture(Game::Tx_MainMenu_Background);	//Wczytanie tla w MENU
	Game::Sp_MainMenu_FogAnim.setTexture(Game::Tx_MainMenu_FogAnim);		//Wczytanie animacji mgły MENU
	Game::About_sp.setTexture(About_bg); // Opcja ABOUT
	
}

string* Game::LoadCFG_File() const
//WCZYTANIE PLIKU KONFIGURACYJNEGO
{
	fstream *plik = new fstream;
	string *dane = new string[ConfigFile_MAXLines];
	plik->open(ConfigDir_Path, std::ios::in);
	if (plik->good() == true)
	{
		int i = 0;
		while (!plik->eof())
		{
			getline(*plik, dane[i]); //wczytanie CAŁEGO jednego wiersza danych
			i++;
		}
	}
	plik->close();
	delete plik;
	return dane;
}

void Game::LoadText(Text *MainMenu_Text)
// Tworzenie napisów w MENU głównym.
{
	string *str = new string[Text_MMenuAmout];
	str[0] = Text_MMenu1; // Napisy które będą w MENU głównym.
	str[1] = Text_MMenu2;
	str[2] = Text_MMenu3;
	for (int i = 0; i<Text_MMenuAmout; i++) // Wypełnienie zmiennych TEXT , łańcuchami.
	{
		MainMenu_Text[i].setFont(Main_Font); // Ustawienie czcionki.
		MainMenu_Text[i].setCharacterSize(35); // Ustawienie wielkości czcionki
		MainMenu_Text[i].setString(str[i]); // Ustawienie STRINGÓW w zmiennych TEXT
		MainMenu_Text[i].setPosition((Window_Height / 2) - (MainMenu_Text[i].getGlobalBounds().width / 2), 320 + (i * 75)); // Ustawienie pozycji napisów w oknie.
	}
	delete[] str;
}

void Game::Loading(RenderWindow &Main_Window) const
{
	Image *icon = new Image;
	if (!icon->Image_Icon)
	{
		MessageBox(NULL, "Nie wczytano ikony gry!", "Błąd!", MB_OK);
	}
	else
		Main_Window.setIcon(32, 32, icon->getPixelsPtr());
	Font *times = new Font;
	times->Font_Default;
	Text *load = new Text;
	load->setFont(*times);
	load->setCharacterSize(25);
	load->setString(Text_Load);
	load->setStyle(sf::Text::Italic);
	load->setColor(Color::White);
	load->setPosition((Window_Width/ 1.8), (Window_Height/ 3));
	Main_Window.clear(Color::Black);
	Main_Window.draw(*load);
	Main_Window.display();
	delete times;
	delete load;
	delete icon;
}

void Game::LoadTitleAnimation()
//ANIMACJA MENU
{
	string *file_name = new string;
	*file_name = TA_StartString;
	string *number = new string;
	for (int i = 1; i <= TA_FilesAmout; i++)
	{
		*number = std::to_string(i);
		*number += ").png";

		file_name->replace(40, 8, *number);
		if (i >= 10)
			file_name->replace(40, 8, *number);
		if (i == 250)
			cout << "s";
		if (!Game::Tx_MainMenu_Animation[i-1].loadFromFile(*file_name))
		{
			MessageBox(NULL, "Nie znaleziono tekstur!", "Błąd!", MB_OK);
			CurrentState = QUIT;
		}

		Game::Sp_MainMenu_Animation[i-1].setTexture(Game::Tx_MainMenu_Animation[i-1]);
		Game::Sp_MainMenu_Animation[i-1].setPosition(265, 150);
	}
	delete file_name;
	delete number;
}

void Game::LoadGame() // METODA WCZYTUJACA STAN GRY
{
	 
}

void Game::InitializeGame(RenderWindow &Main_Window)
{
	string *ActualConfig = new string;

	Loading(Main_Window);
	ActualConfig = LoadCFG_File();
	LoadTextures();
	LoadFont();
	LoadMusic(ActualConfig);
	LoadTitleAnimation();

	RunGame(Main_Window);
}

void Game::RunGame(RenderWindow &Main_window)
// Funkcja zarządzająca stanami gry.
{
	while (CurrentState != QUIT)
	{
		switch (CurrentState)
		{
		case GameStates::MENU:
			MainMenu(Main_window);
			break;
		case GameStates::GAME_START:
			Player_ContinueOrStart(Main_window);
			break;
		case GameStates::ABOUT:
			AboutMe(Main_window);
			break;
		case GameStates::LOAD:
			IniEngine = true;
			LoadGame();
			CurrentState = QUIT;
			break;
		case GameStates::START_FROM_THE_BEGINING:
			IniEngine = true;
			CurrentState = QUIT;
			break;
		}
	}
}

//--------- CLICK EVENTS -----------------------//
void Game::IsClickedX()
// Nacisniecie przycisku 'X' 
{
	if (MainMenu_event.type == Event::Closed) 
	{
		CurrentState = QUIT;
	}
}

void Game::IsClickedStart(Vector2f &Mouse_pos, Text *MainMenu_Text)
{
	if (MainMenu_Text[0].getGlobalBounds().contains(Mouse_pos) && MainMenu_event.type == Event::MouseButtonReleased && MainMenu_event.key.code == Mouse::Left) // Wybranie opcji ABOUT
	{
		CurrentState = GAME_START;
	}
}

void Game::IsClickedAbout(Vector2f &Mouse_pos, Text *MainMenu_Text)
{
	if (MainMenu_Text[1].getGlobalBounds().contains(Mouse_pos) && MainMenu_event.type == Event::MouseButtonReleased && MainMenu_event.key.code == Mouse::Left) // Wybranie opcji ABOUT
	{
		Game::CurrentState = ABOUT;
	}
}

void Game::IsClickedExit(Vector2f &Mouse_pos, Text *MainMenu_Text)
{
	if (MainMenu_Text[2].getGlobalBounds().contains(Mouse_pos) && MainMenu_event.type == Event::MouseButtonReleased && MainMenu_event.key.code == Mouse::Left) // Wybranie opcji EXIT
	{
		Game::MainMenu_Music.stop();
		Game::CurrentState = QUIT;
	}
}

void Game::IsClickedMusicBtn(Vector2f &Mouse_pos)
{
	Music::Status *MusicCurrentState = new Music::Status;
	if (Mute_button_sp.getGlobalBounds().contains(Mouse_pos) && MainMenu_event.type == Event::MouseButtonReleased && MainMenu_event.key.code == Mouse::Left) // Wybranie opcji EXIT
	{
		*MusicCurrentState = Game::MainMenu_Music.getStatus();

		if (*MusicCurrentState == SoundSource::Status::Paused || *MusicCurrentState == SoundSource::Status::Stopped)
		{
			fstream *plik = new fstream;
			plik->open("Config/menu.ini", std::ios::out);
			if (plik->good() == true)
			{
				*plik << "Menu_Music = 1;";
			}
			else
			{
				MessageBox(NULL, "Wystapil blad z tworzeniem pliku konfiguracyjnego, ustawienia zmieniane w grze nie zostana zapisane!", "Uwaga!", MB_OK);
			}
			plik->close();
			delete plik;


			Game::Mute_button_sp.setTexture(Game::Mute_button_tx);
			Game::MainMenu_Music.play();
		}
		else if (*MusicCurrentState == SoundSource::Status::Playing)
		{
			fstream *plik = new fstream;
			plik->open("Config/menu.ini", std::ios::out);
			if (plik->good() == true)
			{
				cout << "\nPlik konfiguracyjny otworzono pomyslnie!";
				*plik << "Menu_Music = 0;";
			}
			else
			{
				MessageBox(NULL, "Wystapil blad z tworzeniem pliku konfiguracyjnego, ustawienia zmieniane w grze nie zostana zapisane!", "Uwaga!", MB_OK);
			}

			delete plik;
			delete MusicCurrentState;

			Game::Mute_button_sp.setTexture(Game::unMute_button_tx);
			Game::MainMenu_Music.pause();
		}
	}
}
//----------------------------------------------//

void Game::MainMenu_Actions(Vector2f &Mouse_pos, Text *MainMenu_Text) 
{
	IsClickedX();
	IsClickedStart(Mouse_pos, MainMenu_Text);
	IsClickedAbout(Mouse_pos, MainMenu_Text);
	IsClickedExit(Mouse_pos, MainMenu_Text);
	IsClickedMusicBtn(Mouse_pos);
}

void Game::MainMenu(RenderWindow &MainMenu_window)										// Funkcja wyświetlająca MENU główne gry.
{
	Text *MainMenu_Text = new Text[3];
	LoadText(MainMenu_Text);

	unsigned int i = 0;
	sf::Clock Frame_timer;

	while (MainMenu_window.isOpen() && CurrentState != GAME_START && CurrentState != QUIT && CurrentState!=ABOUT) // Główna pętla MENU.
	{
		Vector2f Mouse_pos(Mouse::getPosition(MainMenu_window));						// Pobieranie pozycji myszki przy każdej klatce.
		MainMenu_window.clear();													// czyszczenie okna

		while (MainMenu_window.pollEvent(MainMenu_event)) // Pobieranie ostatniego wydarzenia ze stosu.
		{
			MainMenu_Actions(Mouse_pos, MainMenu_Text);
		}

		Animation_MMenu.Update(Sp_MainMenu_FogAnim, 1120, 4, 800, 600, 0.03f, true);

		MainMenu_window.draw(Game::Sp_MainMenu_Background); // Tlo
		MainMenu_window.draw(Sp_MainMenu_FogAnim); // Animacja mgly
		MainMenu_window.draw(Game::Mute_button_sp); // Przycisk Mute&UnMute
		MainMenu_window.draw(Sp_MainMenu_Animation[i]);

		for (int i = 0; i < Text_MMenuAmout; i++)
		{
			if (MainMenu_Text[i].getGlobalBounds().contains(Mouse_pos))
				MainMenu_Text[i].setColor(sf::Color(50, 255, 255, 255));
			else
				MainMenu_Text[i].setColor(sf::Color(0, 204, 153, 255));
			for (int i = 0; i < Text_MMenuAmout; i++)
				MainMenu_window.draw(MainMenu_Text[i]);
		}

		MainMenu_window.display();
		if (Frame_timer.getElapsedTime() > sf::seconds(0.008) && i < 251)
		{
			i++;
			Frame_timer.restart();
		}
	}
	delete[] MainMenu_Text;
}

void Game::FillStr(string *str) const
{
	str[0] = Text_A1;
	str[1] = Text_A2;
	str[2] = Text_A3;
	str[3] = Text_A4;
	str[4] = Text_A5;
	str[5] = Text_A6;
	str[6] = Text_A7;
	str[7] = Text_MMenu_About;
}

void Game::AboutMe(RenderWindow &About_window)
{
	Text *About_me = new Text[8];
	string *str = new string[8];

	FillStr(str);

	About_me[0].setPosition(100, 50);
	About_me[0].setCharacterSize(25);
	About_me[0].setColor(Color::Cyan);

	About_me[1].setCharacterSize(20);
	About_me[1].setPosition(100, 110);

	About_me[7].setPosition(350, 500);

	for (int i = 0; i < 8; i++)
	{
		About_me[i].setString(str[i]);
		About_me[i].setFont(About_me_font);
		if (i > 1 && i<7)
		{
			About_me[i].setCharacterSize(18);
			About_me[i].setPosition(150, 80 + (i * 30));
		}
	}
	
	About_me[7].setCharacterSize(34);
	About_me[7].setFont(Main_Font);

	About_window.clear();

	while (About_window.isOpen() && Game::CurrentState != MENU && Game::CurrentState != QUIT)
	{
		Vector2f mouse(Mouse::getPosition(About_window));
		while (About_window.pollEvent(MainMenu_event))
		{
			IsClickedX();
			if (About_me[7].getGlobalBounds().contains(mouse) && MainMenu_event.type == Event::MouseButtonReleased && MainMenu_event.key.code == Mouse::Left)
			{
				Game::CurrentState = MENU;
			}
		}
		About_window.clear();
		About_window.draw(Game::Sp_MainMenu_Background);
		Animation_MMenu.Update(Sp_MainMenu_FogAnim, 1120, 4, 800, 600, 0.03f, true);
		About_window.draw(Sp_MainMenu_FogAnim);
		About_window.draw(About_sp);
		if (About_me[7].getGlobalBounds().contains(mouse))
			About_me[7].setColor(Color::Cyan);
		else
			About_me[7].setColor(Color::White);
		for (int i = 0; i < 8; i++)
			About_window.draw(About_me[i]);
		About_window.display();
	}
	delete[] About_me;
	delete[] str;
}

void Game::Player_ContinueOrStart(RenderWindow &MainWindow)
{

	Font *Option_ft = new Font;
	Text *Option_tx = new Text[3];
	string *str = new string[3];
	str[0] = "CHOOSE ACTION";
	str[1] = "START FROM THE BEGINING";
	str[2] = "BACK TO MENU";

	Texture *ChooseBG = new Texture;
	ChooseBG->Texture_MMChoose;
	Sprite *ChooseSP = new Sprite;
	ChooseSP->setTexture(*ChooseBG);

	Option_ft->Font_Default;

	for (unsigned int i = 0; i < 3; i++)
	{
		(Option_tx + i)->setFont(*Option_ft);
		(Option_tx + i)->setString(str[i]);
		(Option_tx + i)->setCharacterSize(25);
		if (i == 0)
		{
			(Option_tx + i)->setPosition(150 + (Window_Height / 2) - ((Option_tx + i)->getGlobalBounds().width / 2) +15, 180);
			(Option_tx + i)->setColor(Color(63,65,94,255));
			(Option_tx + i)->setStyle(Text::Style::Italic);
			continue;
		}
		if (i == 2)
		{
			(Option_tx + i)->setPosition(150 + (Window_Height / 2) - ((Option_tx + i)->getGlobalBounds().width / 2) +15, 210 + (i * 45));
			break;
		}
		(Option_tx + i)->setPosition(150 + (Window_Height / 2) - ((Option_tx + i)->getGlobalBounds().width / 2)+15, 180 + (i * 35));

	}

	while (CurrentState != QUIT && CurrentState != MENU && CurrentState!=LOAD && CurrentState!=START_FROM_THE_BEGINING)
	{
		Vector2f Mouse_pos(Mouse::getPosition(MainWindow));						// Pobieranie pozycji myszki przy każdej klatce.
		MainWindow.clear();													// czyszczenie okna

		while (MainWindow.pollEvent(MainMenu_event)) // Pobieranie ostatniego wydarzenia ze stosu.
		{
			IsClickedX();
			if ((Option_tx + 1)->getGlobalBounds().contains(Mouse_pos) && MainMenu_event.type == Event::MouseButtonReleased && MainMenu_event.key.code == Mouse::Left)
			{
				CurrentState = LOAD;
				break;
			}
			if ((Option_tx + 2)->getGlobalBounds().contains(Mouse_pos) && MainMenu_event.type == Event::MouseButtonReleased && MainMenu_event.key.code == Mouse::Left)
			{
				CurrentState = START_FROM_THE_BEGINING;
				break;
			}
			if ((Option_tx + 3)->getGlobalBounds().contains(Mouse_pos) && MainMenu_event.type == Event::MouseButtonReleased && MainMenu_event.key.code == Mouse::Left)
			{
				CurrentState = MENU;
				break;
			}
		}

		MainWindow.draw(*ChooseSP); // Tlo
		
		for (int i = 1; i < 3; i++)
		{
			if ((Option_tx + i)->getGlobalBounds().contains(Mouse_pos))
				(Option_tx + i)->setColor(Color(92, 95, 84, 255));
			else
				(Option_tx + i)->setColor(Color(30, 31, 26, 255));
			for (int i = 0; i <3; i++)
				MainWindow.draw(*(Option_tx + i));
		}
		
		MainWindow.display();
	}
	delete[] str;
	delete[] Option_tx;
	delete ChooseBG;
	delete ChooseSP;
	delete Option_ft;
}
