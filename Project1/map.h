#pragma once

/*notatki odnoœnie konstrukcji mapy
	>rysowanie pod³óg i mapy: 
		nie baw siê w czarowe bloczki-niebloczki dla œcian tylko œmia³o daj unikatowy background, znaczki mog¹ co najwy¿ej pos³u¿yæ do dalszej dekoracji na sta³e alboco
		pod³oga to coœ w stylu np. . albo buletki
	>generacja:
		d¿efko BSP do ogarniêcia


*/

struct tile
{
	char ch;
	short fore, back, seenfore, seenback; //kolor kafla + t³a, oraz kiedyœ widzianego kafla+t³a
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

