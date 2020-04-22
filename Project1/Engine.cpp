#include "Engine.h"
#include "libtcod.hpp"
#include "player.h"
#include "map.h"
#include "wektor.h"
#include <cmath>
#include <cstdio>

extern TCODColor palette[32];

void engine::generateColorMap(TCODColor colArray[])
{
	TCODColor col[3] = { TCODColor(0, 0, 0), TCODColor(138, 120,103), TCODColor(255,250,235) };
	int indx[3] = { 0,7,15 };
	TCODColor::genMap(colArray, 3, col, indx);
	TCODColor colb[3] = { TCODColor(67, 13, 1), TCODColor(185, 110,	64), TCODColor(250,205,144) };
	int indy[3] = { 16,23,31 };
	TCODColor::genMap(colArray, 3, colb, indy);
}

engine::engine()
{
	TCODConsole::initRoot(wincols, winrows, "Void Leviathan");
	generateColorMap(palette);
}

engine::~engine()
{
	delete mapa;
}

void engine::RozpocznijRozgrywk�()
{
	gracz = new actor(40, 20, '@', 19, 0, 6); //los b�dzie podawany p�niej gdzie indziej zale�nie od bota
	mapa = new map(mapw, maph); 
	// tutaj b�dzie samo generowanie zgodnie z tym co przekazane zostanie funkcji jak tylko sko�cz� pisa�
}

bool engine::Update()
{
	TCOD_key_t key;
	TCOD_event_t ev = TCODSystem::waitForEvent(TCOD_EVENT_KEY, &key, NULL, false);
	bool mret = false;
	if (ev == TCOD_EVENT_KEY_PRESS) {
		switch (key.vk)
		{
		case TCODK_KP8:
			mret = MoveChar(north);
			break;
		case TCODK_KP9:
			mret = MoveChar(neast);
			break;
		case TCODK_KP6:
			mret = MoveChar(east);
			break;
		case TCODK_KP3:
			mret = MoveChar(seast);
			break;
		case TCODK_KP2:
			mret = MoveChar(south);
			break;
		case TCODK_KP1:
			mret = MoveChar(swest);
			break;
		case TCODK_KP4:
			mret = MoveChar(west);
			break;
		case TCODK_KP7:
			mret = MoveChar(nwest);
			break;
		default: break;
		}
	}
	
	return mret;
	// reaguj na kliki gracza
}

void engine::Render(bool recalclos)
{
	mapa->drawMap(recalclos);
	
}

void engine::DrawUI()
{
	//rysowanie bajer�w UI
	//pewnie wszystko pozostanie r�cznie �eby nie by� przypi�tym na sztywno do kolorystyki
	//p�niej jaki� algorytm zale�ny od rozmiaru okna w kaflach
	int posx = 0;
	for (int indeks = 14; indeks > 9; indeks--) {
		for (int powt�rzenie = 0; powt�rzenie < (wincols / 5); powt�rzenie++) {
			TCODConsole::root->putCharEx(posx, 0, ' ', palette[0], palette[indeks]);
			TCODConsole::root->putCharEx(posx, vh + 1, ' ', palette[0], palette[indeks - (vh / (winrows / 5) + 1)]);
			TCODConsole::root->putCharEx(posx, winrows - 1, ' ', palette[0], palette[indeks - 5]);

			posx++;
		}
		TCODConsole::root->putCharEx(posx - 2, 0, ' ', palette[0], palette[indeks - 1]);
		TCODConsole::root->putCharEx(posx - 2, winrows - 1, ' ', palette[0], palette[indeks - 6]);
		TCODConsole::root->putCharEx(posx - 2, vh + 1, ' ', palette[0], palette[indeks - (vh / (winrows / 5) + 2)]);
		TCODConsole::root->putCharEx(posx - 14, 0, ' ', palette[0], palette[indeks + 1]);
		TCODConsole::root->putCharEx(posx - 14, winrows - 1, ' ', palette[0], palette[indeks - 4]);
		TCODConsole::root->putCharEx(posx - 14, vh + 1, ' ', palette[0], palette[indeks - (vh / (winrows / 5))]);
	}

	int posy = 0;
	for (int indeks = 14; indeks > 9; indeks--) {
		for (int powt�rzenie = 0; powt�rzenie < (winrows / 5); powt�rzenie++) {
			TCODConsole::root->putCharEx(0, posy, ' ', palette[0], palette[indeks]);
			TCODConsole::root->putCharEx(wincols - 1, posy, ' ', palette[0], palette[indeks - 5]);
			if ((posy > 0) && (posy < (vh + 1))) TCODConsole::root->putCharEx(vw + 1, posy, ' ', palette[0], palette[indeks - (vw / (wincols / 5) + 1)]);
			posy++;
		}
		TCODConsole::root->putCharEx(0, posy - 2, ' ', palette[0], palette[indeks - 1]);
		TCODConsole::root->putCharEx(0, posy - 10, ' ', palette[0], palette[indeks + 1]);
		TCODConsole::root->putCharEx(wincols - 1, posy - 2, ' ', palette[0], palette[indeks - 6]);
		TCODConsole::root->putCharEx(wincols - 1, posy - 10, ' ', palette[0], palette[indeks - 4]);
		if (posy < (vh + 1)) TCODConsole::root->putCharEx(vw + 1, posy - 2, ' ', palette[0], palette[indeks - (vw / (wincols / 5) + 2)]);
		if (posy < (vh + 1)) TCODConsole::root->putCharEx(vw + 1, posy - 10, ' ', palette[0], palette[indeks - (vw / (wincols / 5))]);
	}
}

bool engine::MoveChar(compass comp)
{
	bool ret = false;
	vec vc{ gracz->getX(), gracz->getY() };
	terrainids tileid;
	//tutaj te� pewnie walka wr�cz, a potem p�jdziemy w destination �eby da� rzeczy typu szar�e i doskoki; no chyba �e b�d� traktowane specjalnie :thonk:

	// ustalamy kafel docelowy
	vc += comp;

	//sprawdzamy czy jeste�my w granicach mapy
	if ((vc.vx() >= 0) && (vc.vx() <= mapa->width))
		if ((vc.vy() >= 0) && (vc.vy() <= mapa->height)) {
			//czy kafel jest wolny?
			bool block = mapa->isBlocking(vc.vx(), vc.vy());
			if (!block) {
				gracz->setX(vc.vx());
				gracz->setY(vc.vy());
				ret = true;
			}
			else {
				//je�li kafel ma stwora to tutaj b�dzie resolw meleji
				tileid = mapa->getTile(vc.vx(), vc.vy());
				if (tileid == tBarrierclosed) {
					ret = mapa->OpenDoor(vc.vx(), vc.vy());
					if (!ret) {
						//wiadomo�� o nieudanym hacku tutaj
					}
					else
					{
						gracz->setX(vc.vx());
						gracz->setY(vc.vy());
					}
				}
			}
		}
	return ret;

}


int CalcDist(int x1, int y1, int x2, int y2)
{
	int xdiff = std::abs(x1 - x2);
	int ydiff = std::abs(y1 - y2);
	int dist = (xdiff + ydiff + imax(xdiff, ydiff)) >> 1;
	return dist;
}

void DrawBox(int x, int y, int tx, int ty, int fillColor, bool halfbrite)
{
	//bardzo wa�ne: ze wzgl�du na nieco prymitywne jeszcze kalkulacje pude�ka rysowane t� metod� nie mog� by� mniejsze ni� 5 punkt�w
	int firstColor = (halfbrite) ? 30 : 14;
	int posx = x;
	int posy = y;
	int distancex = (tx - x + 1); //+1 gdy� pocz�tkowy kafel te� jest rysowany
	int distancey = (ty - y + 1);
	int sectionx = (distancex / 5);
	int extrax = (distancex % 5);
	int sectiony = (distancey / 5);
	int extray = (distancey % 5);
	bool glitterx = (distancex > 6) ? true : false;
	bool glittery = (distancey > 6) ? true : false;

	std::cout << "dx " << distancex << "sectx " << sectionx << "exx" << extrax;

	int petla = 0;
	for (int indeks = firstColor; indeks > (firstColor - 5); indeks--) {
		for (int rpt = 0; rpt < sectionx; rpt++) {
			TCODConsole::root->putCharEx(posx, y, ' ', palette[0], palette[indeks]);
			TCODConsole::root->putCharEx(posx, ty, ' ', palette[0], palette[indeks - 5]);
			posx++;
		}

		//odcinek narysowany - teraz dodatkowy punkt d�ugo�ci w zale�no�ci od tego jaka jest reszta z dzielenia i kt�ry to by� odcinek (�eby by�o w miar� r�wno a nie wszystko na koniec)
		if ((extrax == 1) && (petla == 4)) {
			TCODConsole::root->putCharEx(posx, y, ' ', palette[0], palette[indeks]);
			TCODConsole::root->putCharEx(posx, ty, ' ', palette[0], palette[indeks - 5]);
			posx++;
		}
		if ((extrax == 2) && ((petla == 2) || (petla == 4))) {
			TCODConsole::root->putCharEx(posx, y, ' ', palette[0], palette[indeks]);
			TCODConsole::root->putCharEx(posx, ty, ' ', palette[0], palette[indeks - 5]);
			posx++;
		}
		if ((extrax == 3) && ((petla == 4) || (petla == 3) || (petla == 1))) {
			TCODConsole::root->putCharEx(posx, y, ' ', palette[0], palette[indeks]);
			TCODConsole::root->putCharEx(posx, ty, ' ', palette[0], palette[indeks - 5]);
			posx++;
		}
		if ((extrax == 4) && ((petla == 4) || (petla == 3) || (petla == 2) || (petla == 1))) {
			TCODConsole::root->putCharEx(posx, y, ' ', palette[0], palette[indeks]);
			TCODConsole::root->putCharEx(posx, ty, ' ', palette[0], palette[indeks - 5]);
			posx++;
		}
		petla++;
		// a teraz "glitter" na kraw�dziach odcinka, ale tylko je�li odcinek jest dostatecznie d�ugi

		if (glitterx) {
			TCODConsole::root->putCharEx(posx - 2, y, ' ', palette[0], palette[indeks - 1]);
			TCODConsole::root->putCharEx(posx - (sectionx - 2), y, ' ', palette[0], palette[indeks + 1]);
			TCODConsole::root->putCharEx(posx - 2, ty, ' ', palette[0], palette[indeks - 6]);
			TCODConsole::root->putCharEx(posx - (sectionx - 2), ty, ' ', palette[0], palette[indeks - 4]);
		}
	}
	// a teraz wszystko to samo ale w pionie hoho
	petla = 0;
	for (int indeks = firstColor; indeks > (firstColor - 5); indeks--) {
		for (int rpt = 0; rpt < sectiony; rpt++) {
			TCODConsole::root->putCharEx(x, posy, ' ', palette[0], palette[indeks]);
			TCODConsole::root->putCharEx(tx, posy, ' ', palette[0], palette[indeks - 5]);
			posy++;
		}

		//odcinek narysowany - teraz dodatkowy punkt d�ugo�ci w zale�no�ci od tego jaka jest reszta z dzielenia i kt�ry to by� odcinek (�eby by�o w miar� r�wno a nie wszystko na koniec)
		if ((extray == 1) && (petla == 4)) {
			TCODConsole::root->putCharEx(x, posy, ' ', palette[0], palette[indeks]);
			TCODConsole::root->putCharEx(tx, posy, ' ', palette[0], palette[indeks - 5]);
			posy++;
		}
		if ((extray == 2) && ((petla == 2) || (petla == 4))) {
			TCODConsole::root->putCharEx(x, posy, ' ', palette[0], palette[indeks]);
			TCODConsole::root->putCharEx(tx, posy, ' ', palette[0], palette[indeks - 5]);
			posy++;
		}
		if ((extray == 3) && ((petla == 4) || (petla == 3) || (petla == 1))) {
			TCODConsole::root->putCharEx(x, posy, ' ', palette[0], palette[indeks]);
			TCODConsole::root->putCharEx(tx, posy, ' ', palette[0], palette[indeks - 5]);
			posy++;
		}
		if ((extray == 4) && ((petla == 4) || (petla == 3) || (petla == 2) || (petla == 1))) {
			TCODConsole::root->putCharEx(x, posy, ' ', palette[0], palette[indeks]);
			TCODConsole::root->putCharEx(tx, posy, ' ', palette[0], palette[indeks - 5]);
			posy++;
		}
		petla++;
		// a teraz "glitter" na kraw�dziach odcinka, ale tylko je�li odcinek jest dostatecznie d�ugi

		if (glittery) {
			TCODConsole::root->putCharEx(x, posy - 2, ' ', palette[0], palette[indeks - 1]);
			TCODConsole::root->putCharEx(x, posy - (sectiony - 2), ' ', palette[0], palette[indeks + 1]);
			TCODConsole::root->putCharEx(tx, posy - 2, ' ', palette[0], palette[indeks - 6]);
			TCODConsole::root->putCharEx(tx, posy - (sectiony - 2), ' ', palette[0], palette[indeks - 4]);
		}
	}
	// na koniec - wyczyszczenie wn�trza boxa
	for (int rx = x + 1; rx < tx; rx++) 
		for (int ry = y + 1; ry < ty; ry++) 
			TCODConsole::root->putCharEx(rx, ry, ' ', palette[0], palette[fillColor]);
	TCODConsole::flush();
}

void DrawString(const char * string, int posx, int posy, int fore, int back, bool roll)
{
	//funkcja rysuje string tam gdzie trzeba, w kolorach takich jak trzeba
	//parametr roll b�dzie s�u�y� specjalnemu tekstowi pojawiaj�cemu si� stopniowo aczkolwiek niewykluczone �e w takich okazjach turlanie si� tekstu b�dzie zrobione r�cznie w ramach funkcji wywo�uj�cej
	//tak, istniej� funkcje print, printex, printf oferowana w ramach tcod, ale przy nich ryzykuj� nadpisanie fancy ramek interfejsu
	//co nie znaczy �e nie b�d� z nich korzysta� jak b�dzie okazja
	if (!roll) {
		int strpos = 0;
		while ((string[strpos] != '\0') && ((posx + strpos) < (wincols - 1)) && (posy < (winrows - 1))) {
			TCODConsole::root->putCharEx(posx + strpos, posy, string[strpos], palette[fore], palette[back]);
			strpos++;
		}
	}
	TCODConsole::flush();
}

void DrawCenterString(const char * string, int posy, int fore, int back)
{
	int len = 0;
	while (string[len] != '\0') len++;	
	int startX = (wincols - len) / 2;
	if (startX < 1) startX = 1; //zaczynamy od 1 poniewa� planuj� wsz�dzie mie� ramki
	int strpos = 0;
	while ((string[strpos] != '\0') && (strpos + startX < (wincols - 1))) {
		TCODConsole::root->putCharEx(startX + strpos, posy, string[strpos], palette[fore], palette[back]);
		strpos++;
	}
	TCODConsole::flush();
}

char GetKey(void) //przerobi� na tcod_key? zrobi� inny wariant na branie vk?
{
	char ret;
	TCOD_key_t key;
	TCOD_event_t ev;
	ev = TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL, false);
	ret = key.c;
	ev = TCODSystem::waitForEvent(TCOD_EVENT_KEY_RELEASE, &key, NULL, false);
	return ret;
}

char GetChar(void)
{
	char ret;
	TCOD_key_t key;
	TCOD_event_t ev = TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL, false);
	while ((key.c < '!' && key.c > '}') && (key.c != '\n') && (key.c != '\b'))
		ev = TCODSystem::waitForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL, false);
	ret = key.c;
	ev = TCODSystem::waitForEvent(TCOD_EVENT_KEY_RELEASE, &key, NULL, false);
	return ret;
}

void PutChar(char c, int posx, int posy, int fore, int back)
{
	TCODConsole::root->putCharEx(posx, posy, c, palette[fore], palette[back]);
	TCODConsole::flush();
}

void InputString(char * string, short size, int posx, int posy)
{
	short currsize = 0;
	short currx = posx;
	PutChar('_', currx, posy, accenttext, normback);
	char c = GetChar();
	while ((int)c != 13)
	{
		if (c == '\b') {
			if (currsize > 0) {
				PutChar(' ', currx, posy, normback, normback);
				currx--;
				currsize--;
				PutChar('_', currx, posy, accenttext, normback);
			}
		}
		else
		{
			if (currsize < size) {
				PutChar(c, currx, posy, normtext, normback);
				string[currsize] = c;
				currsize++;
				currx++;
				PutChar('_', currx, posy, accenttext, normback);
			}
		}
		c = GetChar();
	}
	PutChar(' ', currx, posy, normback, normback);
	string[currsize] = '\0';
}