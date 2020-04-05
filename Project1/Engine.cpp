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

void engine::RozpocznijRozgrywkê()
{
	gracz = new actor(40, 20, '@', 19, 0, 6); //los bêdzie podawany póŸniej gdzie indziej zale¿nie od bota
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

