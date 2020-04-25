#pragma once
#include <string> //z wielk� niech�ci� i tymczasowo a� znajd� jak to prawid�owo nale�y zrobi�
#include "libtcod.hpp"

//drobne makro por�wnania - zwraca wi�ksz�/mniejsz� z warto�ci
#define imax(a, b) (a > b ? a : b)
#define imin(a, b) (a < b ? a : b)

//rozmiar ca�ego okna w kolumnach i rz�dach oraz rozmiar okna mapy
#define wincols 80
#define winrows 60 
#define vw 50
#define vh 50

#define mapw 100
#define maph 100

//domy�lne kolory por�czne na r�ne okazje wed�ug palety
#define normtext 15
#define normback 0
#define accenttext 22

//.bi ma centerx / centery obliczaj�ce centralny punkt ekranu (?) - zobaczy� jak to trzeba b�dzie wprowadzi� gdy przyjdzie pora

enum compass;
enum terrainids;
class map;
class actor;
class TCODColor;




class engine
{
private:
	void generateColorMap(TCODColor colArray[]);

public:
	engine();
	~engine();
	actor *gracz;
	map *mapa;

	void RozpocznijRozgrywk�(); // kiedy wszystko zosta�o ustalone generuje map� i stawia gracza gdzie trzeba - tutaj b�d� podawane parametry konkretnie jaka mapa itd.
	bool Update();
	void Render(bool recalclos);
	void DrawUI();
	bool MoveChar(compass comp);
};

int CalcDist(int x1, int y1, int x2, int y2);


//sekcja procedur umiejkowych, w razie czego mo�ne je potem wyci�� i przeklei� gdzie indziej
void DrawBox(int x, int y, int tx, int ty, int fillColor, bool halfbrite = false);
void DrawString(std::string strig, int posx, int posy, int fore, int back, bool roll = false);
void DrawCenterString(std::string strig, int posy, int fore, int back);
TCOD_key_t GetKey(void);  
char GetChar(void);
void PutChar(char c, int posx, int posy, int fore, int back);
void InputString(char* string, short size, int posx, int posy); // bardzo wa�ne: size musi by� 1 punkt mniejszy od rozmiaru array gdy� inaczej korupcja stacku
int ListSelector(std::string * list, int listsize, int posx, int posy, int fore, int back, bool interline = false);