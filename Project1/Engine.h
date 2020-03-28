#pragma once

#include "libtcod.hpp"
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
	TCODList<actor*> pionki; // lista aktorów coby wszystkich hurtem rendern¹æ bez spinania siê o œledzenie ka¿dego z osobna
	//przerobiæ na deque
	actor *gracz;
	map *mapa;
	

	void rozpocznijRozgrywkê(); // kiedy wszystko zosta³o ustalone generuje mapê i stawia gracza gdzie trzeba - tutaj bêd¹ podawane parametry konkretnie jaka mapa itd.
	void update();
	void render();
};
