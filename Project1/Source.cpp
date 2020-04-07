#include <cstdio>
#include "libtcod.hpp"
#include "player.h"
#include "map.h"
#include "Engine.h"

// Hide the console window
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")


int newgame(void);
int mainloop();
TCODColor palette[32]; // na razie tutaj, póŸniej mo o o ¿e gdzie indziej, ale na razie starczy

engine silnik; // wzium wzium

// TODO: ZRÓB PÊTELKÊ PO INTOWYM CHARZE ¯EBY ZOBACZYÆ CO SIÊ RENDERUJE A CO WYPIEPRZY KOD


int main()
{
	TCODConsole::credits();
	TCODConsole::root->clear();
	TCODConsole::root->printf(30, 25, "z = exit s = start");
	TCOD_key_t key;
	TCOD_mouse_t mouse;
	

	for (int i = 0; i < 32; i++) {
		TCODConsole::root->putCharEx((16+i),26, ' ', palette[0], palette[i]);
	}
	while (!TCODConsole::isWindowClosed())
	{
		TCODConsole::flush();
	
		TCOD_event_t ev = TCODSystem::waitForEvent(TCOD_EVENT_KEY, &key, &mouse, false);
		if (ev==TCOD_EVENT_KEY_PRESS && (key.c == 'z' || key.c == 's')) break;
	}
	switch (key.c)
	{
	case 's':
	{
		TCODConsole::root->clear();
		newgame();
	}
	default:
		break;
	}

	return 0;
}

int newgame(void)
{
	//init player properly

	silnik.RozpocznijRozgrywkê();
	mainloop();
	return 0;
}



int mainloop()
{
	bool recalclos;
	TCODConsole::root->clear();
	silnik.DrawUI();
	silnik.Render(true);
	TCODConsole::root->flush(); //flush po ka¿dym ruchu jest rozwi¹zaniem tymczasowym, póŸniej bêdzie flush tylko gdy bêde musia³ rysowaæ UI od zera
	while (!TCODConsole::isWindowClosed())
	{
		TCODConsole::root->clear();
		recalclos = silnik.Update();
		silnik.Render(recalclos);
		silnik.DrawUI();
		TCODConsole::root->flush();
		std::cout << "X: " << silnik.gracz->getX() << " Y: " << silnik.gracz->getY() << std::endl;
	}
	return 0;
}
