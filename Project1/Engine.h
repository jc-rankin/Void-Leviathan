#pragma once

//drobne makro porównania - zwraca wiêksz¹/mniejsz¹ z wartoœci
#define imax(a, b) (a > b ? a : b)
#define imin(a, b) (a < b ? a : b)

//rozmiar ca³ego okna w kolumnach i rzêdach oraz rozmiar okna mapy
#define wincols 80
#define winrows 60 
#define vw 50
#define vh 50

#define mapw 100
#define maph 100

//domyœlne kolory porêczne na ró¿ne okazje wed³ug palety
#define normtext 15
#define normback 0
#define accenttext 22

//.bi ma centerx / centery obliczaj¹ce centralny punkt ekranu (?) - zobaczyæ jak to trzeba bêdzie wprowadziæ gdy przyjdzie pora

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

	void RozpocznijRozgrywkê(); // kiedy wszystko zosta³o ustalone generuje mapê i stawia gracza gdzie trzeba - tutaj bêd¹ podawane parametry konkretnie jaka mapa itd.
	bool Update();
	void Render(bool recalclos);
	void DrawUI();
	bool MoveChar(compass comp);
};

int CalcDist(int x1, int y1, int x2, int y2);

void DrawBox(int x, int y, int tx, int ty, int fillColor, bool halfbrite = false);
void DrawString(const char* string, int posx, int posy, int fore, int back, bool roll = false);
void DrawCenterString(const char* string, int posy, int fore, int back);
char GetKey(void);  
char GetChar(void);
void PutChar(char c, int posx, int posy, int fore, int back);
void InputString(char* string, short size, int posx, int posy); // bardzo wa¿ne: size musi byæ 1 punkt mniejszy od rozmiaru array gdy¿ inaczej korupcja stacku