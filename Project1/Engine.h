#pragma once

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

void DrawString(const char* string, int posx, int posy, int fore, int back, bool roll = false);