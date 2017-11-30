//Zdefiniowane dyrektywy preprocesora.
#define Window_Height 800 // Wysokoœæ okna
#define Window_Width 600 // Szerokoœæ okna
#define Title_String "ForestMan 1.0a" // Tytul okna
#define Max_FPS 30 // Maksymalna iloœæ klatek na sekunde

#define Font_Main loadFromFile("Assets/Fonts/chinese_rocks.ttf") // Wczytanie czcionki z dysku.
#define Font_Default loadFromFile("Assets/Fonts/times.ttf") // Wczytanie standardowej czcionki.
#define TA_StartString "Assets/Bg_Images/title_anim/title_anim ()" // Sciezka do wczytania animacji tytulu gry.
#define TA_FilesAmout 252 // Iloœæ plików do wczytania w animacji.
#define ConfigDir_Path "Config/menu.ini" // Sciezka do pliku konfiguracyjnego
#define ConfigFile_MAXLines 1 // Ilosc opcji w pliku konfiguracyjnym
#define SavesDir_Path "Saves/1.dat"
#define SavesFile_MAXLines 1

#define Text_Load "LOADING..." // Napis wyswietlajacy sie podczas wczytywania...
#define Text_MMenu1 "START" // Napisy wyœwietlane w MENU g³ównym.
#define Text_MMenu2 "ABOUT" // Opcja ABOUT MENU GLOWNE
#define Text_MMenu_About "COFNIJ"
#define Text_MMenu3 "EXIT" 
#define Text_MMenuAmout 3 // Ilosc opcji do wyboru w MENU G³ównym gry.
#define Text_TMenuAmout 3 // Ilosc opcji do wyboru w MENU przejsciowym gry.
//OPCJA ABOUT//
#define Text_A1 "Projekt zaliczeniowy z przedmiotu \"Programowanie w C++\" "
#define Text_A2 "Informacje o autorze:"
#define Text_A3 "Imie i nazwisko: Bartlomiej Zuber"
#define Text_A4 "Symbol kierunku: 2 EF-DI "
#define Text_A5 "Nr albumu: 137539"
#define Text_A6 "Adres email: bajtas@gmail.com"
#define Text_A7 "Data wykonania: 05.01.2015 r."
//-------------------GRAFIKA W GRZE-------------------------//
#define Image_Icon loadFromFile("Assets/Images/icon.png") // sciezka do ikony gry
// # Grafika w MENU G£ÓWNYM # //
#define Texture_MMBackground loadFromFile("Assets/Bg_Images/main_menu_tlo.jpg") // T³o w MENU g³ównym.
#define Texture_ABBackground loadFromFile("Assets/Bg_Images/about_tlo.png") // Tlo w ABOUT
#define Texture_MuteBtn loadFromFile("Assets/Bg_Images/Mute_button.png") // Przycisk MUTE
#define Texture_UnMuteBtn loadFromFile("Assets/Bg_Images/unMute_button.png") // Przycisk UNMUTE
#define Texture_MMFogAnim loadFromFile("Assets/Bg_Images/logo_anim/logo2.png") // Mg³a
#define Texture_MMChoose loadFromFile("Assets/Bg_Images/choose_menu.png") // Mg³a
// # Grafika w LEVEL 1 # //
#define Texture_Lvl1Background loadFromFile("Assets/Levels/1/background.png")
#define Texture_Lvl1Floor loadFromFile("Assets/Levels/1/grass.png")

//-----------------------MUZYKA----------------------------------//
#define Music_MainMenu openFromFile("Assets/Music/Jean_Baptiste_Lully_-_Gavotte_-_Burmester_.wav")

//------------------------MAPY POZIOMOW----------------------------//
// # GRACZ # // 
#define OneFramePlayerSize Vector2i(34, 64)
#define PlayerStartPos setPosition(Vector2f(0, 442)) //4320
// # WILK # //
#define OneFrameWolfSize Vector2i(64,32)
// # Poziom 1 # //
#define Ground 350
#define Air 255
#define Underground 500
#define HighUnderground 635
#define TilesNumber 60
#define BackgroundNumber 7
//#define EnemyNumber 1
#define WolfsNumber 11
#define Wave_I 4
#define Wave_II 5
#define Wave_III 10
#define Wave_IV 11

#define TypeTile -1
#define TypeWolf 1

// 0 - poziom ziemi, 1 - poziom wysoki, 2 - poziom niski, 3 - poziom bardzo niski 9 - przerwa
#define Level1_FloorMap {3,3,3,3,3,3,3,3,3,3,3,3,3,9,3,2,2,9,3,2,0,9,0,9,0,2,2,2,2,2,2,3,9,3,2,2,0,0,0,0,0,0,0,0,0,0,1,1,9,9,9,2,2,2,2,2,2,2,2,2}