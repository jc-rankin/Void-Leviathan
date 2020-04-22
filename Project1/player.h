/*PIERWOTNIE KLASA MIA£A BYÆ POŒWIÊCONA GRACZOWI JAKO BYTOWI.
OSTATECZNIE (???) GENERYCZNIE OBS£UGUJE WSZYSTKIE PIONKI MAPOWE
*/

#pragma once

enum dmgType {
	impact = 0, //najzwyklejsze kule i broñ bia³a - albo wiêcej dakka, albo raz a dobrze
	sonic, //ultradŸwiêki - atak obszarowy w sto¿ku, potê¿ny vs bio
	explosive, //atak obszarowy wokó³ celu
	laser, //promieñ a¿ do œciany
	plasma, //pomiêdzy impact a explosive
	flame, //damage over time + aoe
	shock, //sto¿ek vs elektro
	special //???
};

struct itemWeapon {
	char name[16];
	short tohit;
	int damage;
	dmgType damagetype;
	short size; //1-3 1 = smol 3 = big
	short burst; //ile pocisków/ataków w serii
	bool multihit; //true = atakuje wszystkich widocznych wrogów
	double encostperbullet;
	short speed;
	bool shield; //jeœli true, damage to bonus do uników i nie mo¿na atakowaæ
	bool ranged;
	bool twohanded;
	int forecolor; //jak zwykle ID palety
	int backcolor;
};

struct itemOption {
	char name[16];
	short tohit;
	int damage;
	dmgType damagetype;
	short size; //1-3
	short ammo;
	short burst; //ile pocisków/ataków w serii
	bool multihit;
	short speed;
	int forecolor; //jak zwykle ID palety
	int backcolor;
};

enum mechaID {
	none,
	king, //laserowy zbalansowany
	giant, //plazma-laser-impact zasiêgowe
	gunslinger, //trudny do trafienia ale wy³¹cznie impact/explosive
	reptile, //behemot broni bia³ej
	victor, //flame-plazma
	dagger, //gotta go fast - shock
	/*
	emperor,
	behemoth,
	vulcan,
	raptor,
	excelsior,
	saber
	*/
};

struct mechaData {
	char name[20];
	char symbol;
	short fore;
	short back;
	int maxHP;
	int maxEN;
	short melee;
	short ranged;
	short evasion;
	short defense;
	short speed;
	short armor;
	short los;
	short pocketdepth;
	short weaponmaxsize;
	short optionpocketdepth;
	short optionmaxsize;
	bool _weapontypes[8]; //typy broni jakie mo¿na ubraæ wed³ug enum
};


class actor
{
private:
	short _x, _y;
	char _ch; //znak postaci
	short fore, back; //kolor postaci + t³a wed³ug indeksu 0-31 tabeli palety
	int _los; 
	
public:
	actor();
	actor(short x, short y, char ch, short fore, short back, int los) : _x(x), _y(y), _ch(ch), fore(fore), back(back), _los(los) {}
	~actor();
	int getX() const { return _x; }
	int getY() const { return _y; }
	int setX(int sx) { _x = sx; return true; }
	int setY(int sy) { _y = sy; return true; }
	int Xpp(); //X++
	int Xmm(); //X--
	int Ypp(); //Y++
	int Ymm(); //Y--
	char geticon() const { return _ch; }
	int getfore() const { return fore; }
	int getback() const { return back; }
	virtual int getLOS() const { return _los; }
	void setLOS(int los) { _los = los; }
	virtual void render(int rx, int ry); //lepiej - wskauzjê gdzie a gra rysuje... gdzie.
};

class playerActor : public actor {
private:
	char _pilot_name[16];
	short _stam, _refl, _intl, _perc;
	long _xp;
	short _lvl;
	short _pilotHP, _pilotcurrHP;
	double _HP, _EN, _currHP, _currEN;
	short _HP_lv, _EN_lv; //poziom upgrade
	short _melee_lv, _ranged_lv, _evasion_lv, _defense_lv, _speed_lv; //poziom upgrade
	itemWeapon _mainhand, _offhand;
	itemWeapon * _inventory;
	itemOption * _options;
	mechaID _current_machine_ID;
	mechaData _current_machine_data;

	mechaData _mecha_lookup[13];
	itemWeapon _weapon_lookup[16];
	itemOption _option_lookup[6];
	void _populateMechaData(void);
	void _populateWeaponData(void);
	void _populateOptionData(void);

public:
	playerActor();
	~playerActor();
	
	bool createNewCharacter(void);
	void setMecha(mechaID ID);
	short getStam() const { return _stam; }
	short getRefl() const { return _refl; }
	short getIntl() const { return _intl; }
	short getPerc() const { return _perc; }
	void setStam(short amt) { _stam = amt; }
	void setRefl(short amt) { _refl = amt; }
	void setIntl(short amt) { _intl = amt; }
	void setPerc(short amt) { _perc = amt; }
	long getXP() const { return _xp; }
	void modXP(long amt);
	void setXP(long amt);
	//_levelCheck();
	double getHP() const { return _HP; }
	double getEN() const {	return _EN;	}
	double getCurrentHP() const { return _currHP; }
	double getCurrentEN() const { return _currEN; }
	bool modCurrentHP(double amt);
	bool modCurrentEN(double amt);

};