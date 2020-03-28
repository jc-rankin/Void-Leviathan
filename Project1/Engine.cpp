#include "Engine.h"
#include "libtcod.hpp"
#include "player.h"
#include "map.h"
#include "Engine.h"

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
	TCODConsole::initRoot(80, 50, "Void Leviathan");
	generateColorMap(palette);
}

engine::~engine()
{
	delete mapa;
	pionki.clearAndDelete();
}

void engine::rozpocznijRozgrywkê()
{
	gracz = new actor(40, 20, '@', 19, 0);
	mapa = new map(60, 50); 
	pionki.push(gracz);
	// tutaj bêdzie samo generowanie zgodnie z tym co przekazane zostanie funkcji jak tylko skoñczê pisaæ
}

void engine::update()
{
	TCOD_key_t key;
	TCOD_mouse_t mouse;
	TCOD_event_t ev = TCODSystem::waitForEvent(TCOD_EVENT_KEY, &key, &mouse, false);

	if (ev == TCOD_EVENT_KEY_PRESS) {
		switch (key.vk)
		{
		case TCODK_KP8:
			if (mapa->isPassable(gracz->getX(), gracz->getY() - 1)) {
				gracz->Ymm();
			}
			break;
		case TCODK_KP2:
			if (mapa->isPassable(gracz->getX(), gracz->getY() + 1)) {
				gracz->Ypp();
			}
			break;
		case TCODK_KP4:
			if (mapa->isPassable(gracz->getX() - 1, gracz->getY())) {
				gracz->Xmm();
			}
			break;
		case TCODK_KP6:
			if (mapa->isPassable(gracz->getX() + 1, gracz->getY())) {
				gracz->Xpp();
			}
			break;
		default: break;
		}
	}
	
	// reaguj na kliki gracza
}

void engine::render()
{
	mapa->drawMap();
	
	for (actor **iterator = pionki.begin(); iterator != pionki.end(); iterator++)
	{
		(*iterator)->render();
	}
}
