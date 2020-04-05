#pragma once
#include <vector>

class mcoord; //z engine.h


// id kostek terenowych do szybkiej organizacji i przypisywania
enum terrainids {
	tFloor = 0, // niby 0 ju¿ jest domyœlnie startowe, ale zabezpieczam siê na poczet przysz³ych zmian
	tWallSoft, //mo¿na kopaæ ³atwo
	tWallHard, //ee, nie mo¿na kopaæ ³atwo
	tBarrierclosed,
	tBarrieropened,
	tPorterin,
	tPorterout
};


struct roomData { //dane pokoju do iteracji drzewka bsp, rysowania drzwi i mo¿e czego jeszcze jak wpadnê na pomys³
	int x;
	int y;
	int w;
	int h;
};

//struct bariery aka drzwi
struct barriertype {
	bool locked; 
	bool damaged; //jeœli nie mo¿na otworzyæ hackowaniem - mo¿na zniszczyæ panel, wtedy bariera bêdzie losowo w³¹czana/wy³¹czona co turê
	int difficulty; //trudnoœæ hackowania bariery
};

struct tile
{
	terrainids terrid;
	bool seen;
	barriertype barinfo;
	// int sndvol //poziom dŸwiêku do kalkulacji soundmap jeœli siê na to zdecydujê (a pewnie siê zdecydujê)
	int hitpoints; //kopanie przez œciany hurra
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

