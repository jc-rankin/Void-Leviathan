#include "libtcod.hpp"
#include "player.h"
#include "map.h"
#include "Engine.h"

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
			}
			lastX = x + w / 2;
			lastY = y + h / 2;
			roomNum++;
		}
		return true;
	}
};

map::map(int width, int height) : width(width), height(height)
{
	tiles = new tile[width*height];
	TCODBsp bsp(0, 0, width, height);
	// tutaj pewnie wejdzie parametr i switch odnoœnie konkretnego typu generowanego uk³adu mapy
	bsp.splitRecursive(NULL, 8, ROOM_MAX_SIZE, ROOM_MAX_SIZE, 1.6f, 1.6f);
	BspListener listener(*this);
	bsp.traverseInvertedLevelOrder(&listener, NULL);
}

map::~map()
{
	delete tiles;
}

int map::setFloor(int x, int y)
{
	tiles[x + y * width].back = 0;
	tiles[x + y * width].fore = 10;
	tiles[x + y * width].seenback = 0;
	tiles[x + y * width].seenfore = 4;
	tiles[x + y * width].ch = '.';
	tiles[x + y * width].isPassable = true;
	tiles[x + y * width].isTransparent = true;

	return 0;
}

int map::drawMap()
{
	for (int iy = 0; iy<height; iy++)
		for (int ix = 0; ix < width; ix++)
		{
			TCODConsole::root->putCharEx(ix, iy, tiles[ix + iy * width].ch, palette[tiles[ix + iy * width].fore], palette[tiles[ix + iy * width].back]);
		}
	return 0;
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
			setFloor(tilex, tiley);
		}
}

void map::createRoom(bool first, int x1, int y1, int x2, int y2)
{
	dig(x1, y1, x2, y2);
	if (first) {
		silnik.gracz->setX((x1 + x2) / 2);
		silnik.gracz->setY((y1 + y2) / 2);
	}
	else {
		//tutaj wejd¹ generowane interaktywne rzeczy
		// na razie tylko bezmyœlny pionek s³u¿¹cy do testu renderererererowania i fov
		TCODRandom *rng = TCODRandom::getInstance();
		if (rng->getInt(0, 3) == 0) {
			silnik.pionki.push(new actor((x1 + x2) / 2, (y1 + y2) / 2, 'E', 22, 0));
		}
	}
}
