#include "libtcod.hpp"
#include "player.h"
#include "map.h"
#include "Engine.h"

extern TCODColor palette[32];

int actor::Xpp()
{
	x++;
	return 0;
}

int actor::Xmm()
{
	x--;
	return 0;
}

int actor::Ypp()
{
	y++;
	return 0;
}

int actor::Ymm()
{
	y--;
	return 0;
}

void actor::render()
{
	TCODConsole::root->putCharEx(x, y, ch, palette[fore], palette[back]);
}

void actor::render(int rx, int ry)
{
	TCODConsole::root->putCharEx(rx, ry, ch, palette[fore], palette[back]);
}

actor::actor()
{
	ch = '@';
	fore = 17;
	back = 0;
}



actor::~actor()
{

}