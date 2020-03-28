#pragma once

/*notatki odno�nie konstrukcji mapy
	>rysowanie pod��g i mapy: 
		nie baw si� w czarowe bloczki-niebloczki dla �cian tylko �mia�o daj unikatowy background, znaczki mog� co najwy�ej pos�u�y� do dalszej dekoracji na sta�e alboco
		pod�oga to co� w stylu np. . albo buletki
	>generacja:
		d�efko BSP do ogarni�cia


*/

struct tile
{
	char ch;
	short fore, back, seenfore, seenback; //kolor kafla + t�a, oraz kiedy� widzianego kafla+t�a
	bool isPassable;
	bool isTransparent;
	bool wasSeen;
	tile() : wasSeen(false), isPassable(false), isTransparent(false), ch((char)TCOD_CHAR_BLOCK2), fore(0), back(10), seenfore(0), seenback(5) {}
};

class map
{
private:

protected:
	tile *tiles;
	friend class BspListener;

public:
	int width, height;

	map(int width, int height);
	~map();

	int drawMap();

	int setFloor(int x, int y);
	bool isPassable(int x, int y) const { return tiles[x + y * width].isPassable; }
	bool isTransparent(int x, int y) const { return tiles[x + y * width].isTransparent; }

	void dig(int x1, int y1, int x2, int y2);
	void createRoom(bool first, int x1, int y1, int x2, int y2);

	

};

