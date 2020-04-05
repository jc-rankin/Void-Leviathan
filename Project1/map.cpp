#include "libtcod.hpp"
#include "player.h"
#include "map.h"
#include "Engine.h"
#include <cmath>
#include <vector>
#include <cstdio>

extern TCODColor palette[32];
extern engine silnik;

static const int ROOM_MAX_SIZE = 12;
static const int ROOM_MIN_SIZE = 5;

//trza kiedy rozgryŸæ co i gdzie i dlaczego s³uchad³o dzia³ad³o
class BspListener : public ITCODBspCallback {
private:
	map &mapa;
	int roomNum;
	int lastX, lastY;

public:
	std::vector<roomData> rdata;
	BspListener(map &mapa) : mapa(mapa), roomNum(0) {}
	bool visitNode(TCODBsp *node, void *userData) {
		if (node->isLeaf()) {
			int x, y, w, h;
			TCODRandom *rng = TCODRandom::getInstance();
			w = rng->getInt(ROOM_MIN_SIZE, node->w - 2);
			h = rng->getInt(ROOM_MIN_SIZE, node->h - 2);
			x = rng->getInt(node->x + 1, node->x + node->w - w - 1);
			y = rng->getInt(node->y + 1, node->y + node->h - h - 1);
			mapa.createRoom(roomNum == 0, x, y, x + w - 1, y + h - 1);
			if (roomNum != 0) {
				//kopiemy korytarz od ostatniego pomieszczenia
				mapa.dig(lastX, lastY, x + w / 2, lastY);
				mapa.dig(x + w / 2, lastY, x + w / 2, y + h / 2);
				// tutaj postawi siê drzwi, w tym miejscu oto w³aœnie
				
			}
			roomData thisRoomData = {x, y, w ,h};
			rdata.push_back(thisRoomData);
			lastX = x + w / 2;
			lastY = y + h / 2;
			roomNum++;
		}
		return true;
	}
};

int map::_GetTerrainHP(terrainids terr)
{
	//wartoœci placeholderowe na razie
	switch (terr) {
	case tFloor: return -1;
	case tWallSoft: return 30;
	case tWallHard: return 50;
	case tBarrierclosed: return 10;
	case tBarrieropened: return -1;
	case tPorterin: return -1;
	case tPorterout: return -1;
	default: return -1;
	}
}

int map::_GetTerrainRes(terrainids terr)
{
	//równie¿ placeholder
	switch (terr) {
	case tFloor: return -1;
	case tWallSoft: return 5;
	case tWallHard: return 10;
	case tBarrierclosed: return 2;
	case tBarrieropened: return -1;
	case tPorterin: return -1;
	case tPorterout: return -1;
	default: return -1;
	}
}

char map::_GetMapTileChar(terrainids terr)
{
	switch (terr) {
	case tFloor: return '.';
	case tWallSoft: return ' ';
	case tWallHard: return '#'; //do pomyœlenia
	case tBarrierclosed: return '=';
	case tBarrieropened: return '.';
	case tPorterin: return '_';
	case tPorterout: return '^';
	default: return '?';
	}
}

int map::_GetMapTileForeId(terrainids terr)
{
	switch (terr) {
	case tFloor: return 8;
	case tWallSoft: return 0;
	case tWallHard: return 8;
	case tBarrierclosed: return 28;
	case tBarrieropened: return 16;
	case tPorterin: return 16;
	case tPorterout: return 15;
	default: return 0;
	}
}

int map::_GetMapTileBackId(terrainids terr)
{
	switch (terr) {
	case tFloor: return 0;
	case tWallSoft: return 16;
	case tWallHard: return 14;
	case tBarrierclosed: return 0;
	case tBarrieropened: return 0;
	case tPorterin: return 0;
	case tPorterout: return 0;
	default: return 18;
	}
}

void map::_AddDoorsToAllRooms(std::vector<roomData>& allroomdata)
{
	
	for (auto iteroom = allroomdata.begin(); iteroom != allroomdata.end(); iteroom++) {
		int tx = iteroom->x - 1;
		if (tx < 0) tx = 0;
		int ty = iteroom->y - 1;
		if (ty < 0) ty = 0;
		int tw = iteroom->w + 2;
		if ((tw + tx) > width) tw = width - tx;
		int th = iteroom->h + 2;
		if ((th + ty) > height) th = height - ty;
		for (int cx = 0; cx < tw; cx++) {
			if (getTile(tx + cx, ty) == tFloor) setTile(tx + cx, ty, tBarrierclosed); //póŸniej tutaj bêdzie zamykanko poprzez setBarrier
			if (getTile(tx + cx, ty + th) == tFloor) setTile(tx + cx, ty + th, tBarrierclosed);
		}
		for (int cy = 0; cy < th; cy++) {
			if (getTile(tx, ty + cy) == tFloor) setTile(tx, ty + cy, tBarrierclosed); //póŸniej tutaj bêdzie zamykanko poprzez setBarrier
			if (getTile(tx + tw, ty + cy) == tFloor) setTile(tx + tw, ty + cy, tBarrierclosed);
		}
			
	}
}

map::map(int width, int height) : width(width), height(height){

	_tiles = new tile[width*height];
	tcmap = new TCODMap(width, height);
	tcmap->clear();

	//inicjowanie mapy jako œcian które s¹ niewidziane i niewidoczne
	for (int cly = 0; cly < height; cly++)
		for (int clx = 0; clx < width; clx++)
		{
			setTile(clx, cly, tWallSoft);
			_tiles[clx + cly * width].barinfo = { false, false, 0 };
			_tiles[clx + cly * width].seen = false;
		}
	TCODBsp bsp(0, 0, width, height);

	// tutaj pewnie wejdzie parametr i switch odnoœnie konkretnego typu generowanego uk³adu mapy
	bsp.splitRecursive(NULL, 8, ROOM_MAX_SIZE, ROOM_MAX_SIZE, 1.6f, 1.6f);
	BspListener listener(*this);
	bsp.traverseInvertedLevelOrder(&listener, NULL);

}

map::~map()
{
	delete [] _tiles;
	delete tcmap;
}


void map::setTile(int x, int y, terrainids terr)
{
	_tiles[x + y * width].terrid = terr;
	_tiles[x + y * width].hitpoints = _GetTerrainHP(terr);
	_tiles[x + y * width].resistance = _GetTerrainRes(terr);
}

int map::drawMap(bool recalcLos)
{

	if (recalcLos) {
		tcmap->computeFov(silnik.gracz->getX(), silnik.gracz->getY());
	}

	//koordynaty okienka do wyrysowania
	int i = silnik.gracz->getX() - (vw / 2);
	int j = silnik.gracz->getY() - (vh / 2);
	if (i < 1) i = 1;
	if (j < 1) j = 1;
	if ((i + vw) > mapw) i = mapw - vw;
	if ((j + vh) > maph) j = maph - vh;

	for (int x = 0; x < vw; x++)
		for (int y = 0; y < vh; y++) {
			terrainids tiddy = _tiles[(i + x) + (j + y) * width].terrid; 
			//system rysowania kafel widoczny/niewidoczny jest u³omny lekko w tej chwili; pewnie bêdê musia³ robiæ jak¹œ gimnastykê aby wyrysiowaæ aktorów i to pewnie bêdzie dok³adnie tutaj
			//wstêpny pomys³ - kazaæ silnikowi poiterowaæ po aktorach
			//alternatywnie - waliæ iteracjê, daæ array stworów i ka¿dy kafel bêdzie mia³ indeks w tym array
			//also czy przypi¹æ osobn¹ paletê na kafle które by³y widziane czy nie s¹ czy pozostaæ przy ciemnoszarym? decyzje, decyzje...
			if (tcmap->isInFov(i + x, j + y)) {
				TCODConsole::root->putCharEx(x + 1, y + 1, _GetMapTileChar(tiddy), palette[_GetMapTileForeId(tiddy)], palette[_GetMapTileBackId(tiddy)]);
				_tiles[(i + x) + (j + y) * width].seen = true; //tymczasowo?
			}
			else
			if (_tiles[(i + x) + (j + y) * width].seen)
					TCODConsole::root->putCharEx(x + 1, y + 1, _GetMapTileChar(tiddy), palette[3], palette[1]);
		}

	//gracz na œrodku albo niekoniecznie
	int px = silnik.gracz->getX() - i + 1;
	int py = silnik.gracz->getY() - j + 1;
	silnik.gracz->render(px, py);
	return 0;
}

bool map::OpenDoor(int x, int y)
{
	bool ret = false;
	if (getTile(x, y) == tBarrierclosed) {
		setTile(x, y, tBarrieropened);
		ret = true;
	}
	return ret;
}

void map::dig(int x1, int y1, int x2, int y2)
{
	if (x2 < x1) {
		int tmp = x2;
		x2 = x1;
		x1 = tmp;
	}
	if (y2 < y1) {
		int tmp = y2;
		y2 = y1;
		y1 = tmp;
	}
	for (int tiley = y1; tiley <= y2; tiley++)
		for (int tilex = x1; tilex <= x2; tilex++) {
			setTile(tilex, tiley, tFloor);
			tcmap->setProperties(tilex, tiley, true, true);
		}
}

void map::createRoom(bool first, int x1, int y1, int x2, int y2)
{
	dig(x1, y1, x2, y2);
	if (first) {
		int centrex = (x1 + x2) / 2;
		int centrey = (y1 + y2) / 2;

		silnik.gracz->setX(centrex);
		silnik.gracz->setY(centrey);
		_tiles[centrex + centrey * width].terrid = tPorterin;	
	}
	else {
		//tutaj wejd¹ generowane interaktywne rzeczy wewn¹trz danego pomieszczenia
		// na razie tylko bezmyœlny pionek s³u¿¹cy do testu renderererererowania i fov
	}
}


