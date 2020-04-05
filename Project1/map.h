#pragma once
#include <vector>

class mcoord; //z engine.h


// id kostek terenowych do szybkiej organizacji i przypisywania
enum terrainids {
	tFloor = 0, // niby 0 ju� jest domy�lnie startowe, ale zabezpieczam si� na poczet przysz�ych zmian
	tWallSoft, //mo�na kopa� �atwo
	tWallHard, //ee, nie mo�na kopa� �atwo
	tBarrierclosed,
	tBarrieropened,
	tPorterin,
	tPorterout
};


struct roomData { //dane pokoju do iteracji drzewka bsp, rysowania drzwi i mo�e czego jeszcze jak wpadn� na pomys�
	int x;
	int y;
	int w;
	int h;
};

//struct bariery aka drzwi
struct barriertype {
	bool locked; 
	bool damaged; //je�li nie mo�na otworzy� hackowaniem - mo�na zniszczy� panel, wtedy bariera b�dzie losowo w��czana/wy��czona co tur�
	int difficulty; //trudno�� hackowania bariery
};

struct tile
{
	terrainids terrid;
	bool seen;
	barriertype barinfo;
	// int sndvol //poziom d�wi�ku do kalkulacji soundmap je�li si� na to zdecyduj� (a pewnie si� zdecyduj�)
	int hitpoints; //kopanie przez �ciany hurra
	int resistance;
};

class map
{
private:
	tile *_tiles;
	TCODMap * tcmap;
	int _GetTerrainHP(terrainids terr);
	int _GetTerrainRes(terrainids terr);
	char _GetMapTileChar(terrainids terr); //znak kafla
	int _GetMapTileForeId(terrainids terr); //id koloru w palecie
	int _GetMapTileBackId(terrainids terr); //id koloru w palecie
	void _AddDoorsToAllRooms(std::vector<roomData>& allroomdata);

public:
	friend class BspListener;
	int width, height;
	map(int width, int height);
	~map();
	
	int drawMap(bool recalcLos);

	void setTile(int x, int y, terrainids terr);
	terrainids getTile(int x, int y) const { return _tiles[x + y * width].terrid; }
	bool isBlocking(int x, int y) const { return !(tcmap->isWalkable(x, y)); }
	bool OpenDoor(int x, int y);

	void dig(int x1, int y1, int x2, int y2);
	void createRoom(bool first, int x1, int y1, int x2, int y2);

};

