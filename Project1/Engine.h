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
	TCODList<actor*> pionki; // lista aktor�w coby wszystkich hurtem rendern�� bez spinania si� o �ledzenie ka�dego z osobna
	//przerobi� na deque
	actor *gracz;
	map *mapa;
	

	void rozpocznijRozgrywk�(); // kiedy wszystko zosta�o ustalone generuje map� i stawia gracza gdzie trzeba - tutaj b�d� podawane parametry konkretnie jaka mapa itd.
	void update();
	void render();
};
