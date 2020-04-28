#include "Engine.h"
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

void engine::RozpocznijRozgrywkê()
{
	gracz = new playerActor();
	bool ret = gracz->createNewCharacter();
	YesNoSelector(10, 10, 10, 0);
	mapa = new map(mapw, maph); 
	// tutaj bêdzie samo generowanie zgodnie z tym co przekazane zostanie funkcji jak tylko skoñczê pisaæ
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
	//rysowanie bajerów UI
	//pewnie wszystko pozostanie rêcznie ¿eby nie byæ przypiêtym na sztywno do kolorystyki
	//póŸniej jakiœ algorytm zale¿ny od rozmiaru okna w kaflach
	int posx = 0;
	for (int indeks = 14; indeks > 9; indeks--) {
		for (int powtórzenie = 0; powtórzenie < (wincols / 5); powtórzenie++) {
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
		for (int powtórzenie = 0; powtórzenie < (winrows / 5); powtórzenie++) {
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
	//tutaj te¿ pewnie walka wrêcz, a potem pójdziemy w destination ¿eby daæ rzeczy typu szar¿e i doskoki; no chyba ¿e bêd¹ traktowane specjalnie :thonk:

	// ustalamy kafel docelowy
	vc += comp;

	//sprawdzamy czy jesteœmy w granicach mapy
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
				//jeœli kafel ma stwora to tutaj bêdzie resolw meleji
				tileid = mapa->getTile(vc.vx(), vc.vy());
				if (tileid == tBarrierclosed) {
					ret = mapa->OpenDoor(vc.vx(), vc.vy());
					if (!ret) {
						//wiadomoœæ o nieudanym hacku tutaj
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
	//bardzo wa¿ne: ze wzglêdu na nieco prymitywne jeszcze kalkulacje pude³ka rysowane t¹ metod¹ nie mog¹ byæ mniejsze ni¿ 5 punktów
	int firstColor = (halfbrite) ? 30 : 14;
	int posx = x;
	int posy = y;
	int distancex = (tx - x + 1); //+1 gdy¿ pocz¹tkowy kafel te¿ jest rysowany
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

		//odcinek narysowany - teraz dodatkowy punkt d³ugoœci w zale¿noœci od tego jaka jest reszta z dzielenia i który to by³ odcinek (¿eby by³o w miarê równo a nie wszystko na koniec)
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
		// a teraz "glitter" na krawêdziach odcinka, ale tylko jeœli odcinek jest dostatecznie d³ugi

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

		//odcinek narysowany - teraz dodatkowy punkt d³ugoœci w zale¿noœci od tego jaka jest reszta z dzielenia i który to by³ odcinek (¿eby by³o w miarê równo a nie wszystko na koniec)
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
		// a teraz "glitter" na krawêdziach odcinka, ale tylko jeœli odcinek jest dostatecznie d³ugi

		if (glittery) {
			TCODConsole::root->putCharEx(x, posy - 2, ' ', palette[0], palette[indeks - 1]);
			TCODConsole::root->putCharEx(x, posy - (sectiony - 2), ' ', palette[0], palette[indeks + 1]);
			TCODConsole::root->putCharEx(tx, posy - 2, ' ', palette[0], palette[indeks - 6]);
			TCODConsole::root->putCharEx(tx, posy - (sectiony - 2), ' ', palette[0], palette[indeks - 4]);
		}
	}
	// na koniec - wyczyszczenie wnêtrza boxa
	for (int rx = x + 1; rx < tx; rx++) 
		for (int ry = y + 1; ry < ty; ry++) 
			TCODConsole::root->putCharEx(rx, ry, ' ', palette[0], palette[fillColor]);
	TCODConsole::flush();
}

void DrawString(std::string strig, int posx, int posy, int fore, int back, bool roll)
{
	//funkcja rysuje string tam gdzie trzeba, w kolorach takich jak trzeba
	//parametr roll bêdzie s³u¿y³ specjalnemu tekstowi pojawiaj¹cemu siê stopniowo aczkolwiek niewykluczone ¿e w takich okazjach turlanie siê tekstu bêdzie zrobione rêcznie w ramach funkcji wywo³uj¹cej
	//tak, istniej¹ funkcje print, printex, printf oferowana w ramach tcod, ale przy nich ryzykujê nadpisanie fancy ramek interfejsu
	//co nie znaczy ¿e nie bêdê z nich korzysta³ jak bêdzie okazja
	if (!roll) {
		int strpos = 0;
		while ((strpos < strig.length()) && ((posx + strpos) < (wincols - 1)) && (posy < (winrows - 1))) {
			TCODConsole::root->putCharEx(posx + strpos, posy, strig[strpos], palette[fore], palette[back]);
			strpos++;
		}
	}
	TCODConsole::flush();
}

void DrawCenterString(std::string strig, int posy, int fore, int back)
{
	int startX = (wincols - strig.length()) / 2;
	if (startX < 1) startX = 1; //zaczynamy od 1 poniewa¿ planujê wszêdzie mieæ ramki
	int strpos = 0;
	while ((strpos < strig.length()) && (strpos + startX < (wincols - 1))) {
		TCODConsole::root->putCharEx(startX + strpos, posy, strig[strpos], palette[fore], palette[back]);
		strpos++;
	}
	TCODConsole::flush();
}

TCOD_key_t GetKey(void) 
{
	//przerobiæ na checkforevent
	TCOD_key_t key;
	TCOD_mouse_t mouse;
	TCOD_event_t ev;
	bool got = false;
	while (!got) {
		ev = TCODSystem::checkForEvent(TCOD_EVENT_ANY, &key, &mouse);
		if (ev == TCOD_EVENT_KEY_PRESS && key.vk != TCODK_SHIFT) {
			got = true;
		}
	}
	return key;
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
	TCOD_key_t c = GetKey();
	while (c.vk != TCODK_ENTER)
	{
		if (c.vk == TCODK_BACKSPACE) {
			if (currsize > 0) {
				PutChar(' ', currx, posy, normback, normback);
				currx--;
				currsize--;
				PutChar('_', currx, posy, accenttext, normback);
			}
		}
		else
		{
			if ((currsize < size) && (c.vk == TCODK_CHAR)) {
				string[currsize] = c.c;
				if (c.shift) string[currsize] -= 32;
				PutChar(string[currsize], currx, posy, normtext, normback);
				currsize++;
				currx++;
				PutChar('_', currx, posy, accenttext, normback);
			}
		}
		c = GetKey();
	}
	PutChar(' ', currx, posy, normback, normback);
	string[currsize] = '\0';
}

int ListSelector(std::string * list,  int listsize,  int posx,  int posy,  int fore,  int back, bool interline)
{
	int choice = 0;
	int mno¿nik = interline ? 2 : 1;
	for (int rozpiska = 0; rozpiska < listsize; rozpiska++) {
		DrawString(list[rozpiska], posx + 2, posy + (rozpiska*mno¿nik), fore, back);
	}
	TCODConsole::root->putCharEx(posx, posy+(choice*mno¿nik), 16, palette[fore], palette[back]);
	TCODConsole::flush();
	TCOD_key_t sel;
	bool chosen = false;
	while (!chosen) {
		sel = GetKey();
		switch (sel.vk) {
		case TCODK_KP8:
		case TCODK_UP: {
			if (choice > 0) {
				TCODConsole::root->putCharEx(posx, posy + (choice*mno¿nik), ' ', palette[fore], palette[back]);
				choice--;
				TCODConsole::root->putCharEx(posx, posy + (choice*mno¿nik), 16, palette[fore], palette[back]);
				TCODConsole::flush();
			}
			break;
		}
		case TCODK_KP2:
		case TCODK_DOWN: {
			if (choice < (listsize-1)) {
				TCODConsole::root->putCharEx(posx, posy + (choice*mno¿nik), ' ', palette[fore], palette[back]);
				choice++;
				TCODConsole::root->putCharEx(posx, posy + (choice*mno¿nik), 16, palette[fore], palette[back]);
				TCODConsole::flush();
			}
			break;
		}
		case TCODK_ENTER: {
			chosen = true;
			break;
		}
		default:
			break;
		}
	}

	return choice;
}

bool YesNoSelector(int posx, int posy, int fore, int back)
{
	DrawString("  No   Yes", posx, posy, fore, back, false);
	int choice = 0;
	TCODConsole::root->putCharEx(posx, posy, 16, palette[fore], palette[back]);
	TCODConsole::flush();
	TCOD_key_t sel;
	bool chosen = false;
	while (!chosen) {
		sel = GetKey();
		switch (sel.vk) {
		case TCODK_KP6:
		case TCODK_RIGHT: {
			if (choice == 0) {
				TCODConsole::root->putCharEx(posx, posy, ' ', palette[fore], palette[back]);
				choice = 1;
				TCODConsole::root->putCharEx(posx + 5, posy, 16, palette[fore], palette[back]);
				TCODConsole::flush();
			}
			break;
		}
		case TCODK_KP4:
		case TCODK_LEFT: {
			if (choice == 1) {
				TCODConsole::root->putCharEx(posx + 5, posy, ' ', palette[fore], palette[back]);
				choice = 0;
				TCODConsole::root->putCharEx(posx, posy, 16, palette[fore], palette[back]);
				TCODConsole::flush();
			}
			break;
		}
		case TCODK_ENTER: {
			chosen = true;
			break;
		}
		default:
			break;
		}
	}
	return (choice = 1 ? true : false);
}
