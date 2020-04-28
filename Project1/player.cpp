#include "libtcod.hpp"
#include "player.h"
#include "map.h"
#include "Engine.h"
#include <string.h>

extern TCODColor palette[32];

int actor::Xpp()
{
	_x++;
	return 0;
}

int actor::Xmm()
{
	_x--;
	return 0;
}

int actor::Ypp()
{
	_y++;
	return 0;
}

int actor::Ymm()
{
	_y--;
	return 0;
}

void actor::render(int rx, int ry)
{
	TCODConsole::root->putCharEx(rx, ry, _ch, palette[fore], palette[back]);
}

actor::actor()
{
	_ch = '@';
	fore = 17;
	back = 0;
}

actor::~actor()
{
	
}

void playerActor::_populateMechaData(void)
{
	// NONE potencjalnie te¿ na piechotê jeœli bêdê widzia³ w tym sens
	strcpy_s(_mecha_lookup[none].name, "None");
	_mecha_lookup[none].symbol = 2;
	_mecha_lookup[none].fore = 16;
	_mecha_lookup[none].back = 0;
	_mecha_lookup[none].maxHP = 0;
	_mecha_lookup[none].maxEN = 0;
	_mecha_lookup[none].melee = 2;
	_mecha_lookup[none].ranged = 2;
	_mecha_lookup[none].evasion = 5;
	_mecha_lookup[none].defense = 0;
	_mecha_lookup[none].speed = 100;
	_mecha_lookup[none].armor = 0;
	_mecha_lookup[none].los = 6;
	_mecha_lookup[none].pocketdepth = 2;
	_mecha_lookup[none].weaponmaxsize = 1;
	_mecha_lookup[none].optionpocketdepth = 2;
	_mecha_lookup[none].optionmaxsize = 0;
	_mecha_lookup[none]._weapontypes[impact] = true;
	_mecha_lookup[none]._weapontypes[sonic] = false;
	_mecha_lookup[none]._weapontypes[explosive] = true;
	_mecha_lookup[none]._weapontypes[laser] = false;
	_mecha_lookup[none]._weapontypes[plasma] = false;
	_mecha_lookup[none]._weapontypes[flame] = true;
	_mecha_lookup[none]._weapontypes[shock] = false;
	_mecha_lookup[none]._weapontypes[special] = false;


	strcpy_s(_mecha_lookup[king].name, "XC-99 King");
	_mecha_lookup[king].symbol = '@';
	_mecha_lookup[king].fore = 31;
	_mecha_lookup[king].back = 1;
	_mecha_lookup[king].maxHP = 150;
	_mecha_lookup[king].maxEN = 100;
	_mecha_lookup[king].melee = 3;
	_mecha_lookup[king].ranged = 3;
	_mecha_lookup[king].evasion = 3;
	_mecha_lookup[king].defense = 2;
	_mecha_lookup[king].speed = 110;
	_mecha_lookup[king].armor = 3;
	_mecha_lookup[king].los = 6;
	_mecha_lookup[king].pocketdepth = 4;
	_mecha_lookup[king].weaponmaxsize = 2;
	_mecha_lookup[king].optionpocketdepth = 4;
	_mecha_lookup[king].optionmaxsize = 2;
	_mecha_lookup[king]._weapontypes[impact] = true;
	_mecha_lookup[king]._weapontypes[sonic] = true;
	_mecha_lookup[king]._weapontypes[explosive] = false;
	_mecha_lookup[king]._weapontypes[laser] = true;
	_mecha_lookup[king]._weapontypes[plasma] = false;
	_mecha_lookup[king]._weapontypes[flame] = false;
	_mecha_lookup[king]._weapontypes[shock] = true;
	_mecha_lookup[king]._weapontypes[special] = false;


	strcpy_s(_mecha_lookup[giant].name, "Dynasphere Giant");
	_mecha_lookup[giant].symbol = '@';
	_mecha_lookup[giant].fore = 17;
	_mecha_lookup[giant].back = 3;
	_mecha_lookup[giant].maxHP = 200;
	_mecha_lookup[giant].maxEN = 150;
	_mecha_lookup[giant].melee = 1;
	_mecha_lookup[giant].ranged = 4;
	_mecha_lookup[giant].evasion = 1;
	_mecha_lookup[giant].defense = 3;
	_mecha_lookup[giant].speed = 80;
	_mecha_lookup[giant].armor = 3;
	_mecha_lookup[giant].los = 5;
	_mecha_lookup[giant].pocketdepth = 6;
	_mecha_lookup[giant].weaponmaxsize = 3;
	_mecha_lookup[giant].optionpocketdepth = 6;
	_mecha_lookup[giant].optionmaxsize = 3;
	_mecha_lookup[giant]._weapontypes[impact] = true;
	_mecha_lookup[giant]._weapontypes[sonic] = false;
	_mecha_lookup[giant]._weapontypes[explosive] = true;
	_mecha_lookup[giant]._weapontypes[laser] = true;
	_mecha_lookup[giant]._weapontypes[plasma] = true;
	_mecha_lookup[giant]._weapontypes[flame] = false;
	_mecha_lookup[giant]._weapontypes[shock] = true;
	_mecha_lookup[giant]._weapontypes[special] = false;


	strcpy_s(_mecha_lookup[gunslinger].name, "Gunslinger Mk II");
	_mecha_lookup[gunslinger].symbol = '@';
	_mecha_lookup[gunslinger].fore = 14;
	_mecha_lookup[gunslinger].back = 4;
	_mecha_lookup[gunslinger].maxHP = 100;
	_mecha_lookup[gunslinger].maxEN = 200;
	_mecha_lookup[gunslinger].melee = 2;
	_mecha_lookup[gunslinger].ranged = 5;
	_mecha_lookup[gunslinger].evasion = 5;
	_mecha_lookup[gunslinger].defense = 2;
	_mecha_lookup[gunslinger].speed = 120;
	_mecha_lookup[gunslinger].armor = 2;
	_mecha_lookup[gunslinger].los = 7;
	_mecha_lookup[gunslinger].pocketdepth = 4;
	_mecha_lookup[gunslinger].weaponmaxsize = 2;
	_mecha_lookup[gunslinger].optionpocketdepth = 2;
	_mecha_lookup[gunslinger].optionmaxsize = 1;
	_mecha_lookup[gunslinger]._weapontypes[impact] = true;
	_mecha_lookup[gunslinger]._weapontypes[sonic] = true;
	_mecha_lookup[gunslinger]._weapontypes[explosive] = true;
	_mecha_lookup[gunslinger]._weapontypes[laser] = false;
	_mecha_lookup[gunslinger]._weapontypes[plasma] = false;
	_mecha_lookup[gunslinger]._weapontypes[flame] = false;
	_mecha_lookup[gunslinger]._weapontypes[shock] = false;
	_mecha_lookup[gunslinger]._weapontypes[special] = false;


	strcpy_s(_mecha_lookup[reptile].name, "Dynasphere Reptile");
	_mecha_lookup[reptile].symbol = '@';
	_mecha_lookup[reptile].fore = 16;
	_mecha_lookup[reptile].back = 6;
	_mecha_lookup[reptile].maxHP = 300;
	_mecha_lookup[reptile].maxEN = 100;
	_mecha_lookup[reptile].melee = 5;
	_mecha_lookup[reptile].ranged = 1;
	_mecha_lookup[reptile].evasion = 2;
	_mecha_lookup[reptile].defense = 5;
	_mecha_lookup[reptile].speed = 90;
	_mecha_lookup[reptile].armor = 5;
	_mecha_lookup[reptile].los = 4;
	_mecha_lookup[reptile].pocketdepth = 4;
	_mecha_lookup[reptile].weaponmaxsize = 4;
	_mecha_lookup[reptile].optionpocketdepth = 2;
	_mecha_lookup[reptile].optionmaxsize = 4;
	_mecha_lookup[reptile]._weapontypes[impact] = true;
	_mecha_lookup[reptile]._weapontypes[sonic] = true;
	_mecha_lookup[reptile]._weapontypes[explosive] = true;
	_mecha_lookup[reptile]._weapontypes[laser] = false;
	_mecha_lookup[reptile]._weapontypes[plasma] = false;
	_mecha_lookup[reptile]._weapontypes[flame] = false;
	_mecha_lookup[reptile]._weapontypes[shock] = false;
	_mecha_lookup[reptile]._weapontypes[special] = true;


	strcpy_s(_mecha_lookup[victor].name, "AAF-44 Victor");
	_mecha_lookup[victor].symbol = '@';
	_mecha_lookup[victor].fore = 15;
	_mecha_lookup[victor].back = 24;
	_mecha_lookup[victor].maxHP = 80;
	_mecha_lookup[victor].maxEN = 400;
	_mecha_lookup[victor].melee = 2;
	_mecha_lookup[victor].ranged = 3;
	_mecha_lookup[victor].evasion = 4;
	_mecha_lookup[victor].defense = 2;
	_mecha_lookup[victor].speed = 120;
	_mecha_lookup[victor].armor = 2;
	_mecha_lookup[victor].los = 6;
	_mecha_lookup[victor].pocketdepth = 4;
	_mecha_lookup[victor].weaponmaxsize = 2;
	_mecha_lookup[victor].optionpocketdepth = 4;
	_mecha_lookup[victor].optionmaxsize = 2;
	_mecha_lookup[victor]._weapontypes[impact] = true;
	_mecha_lookup[victor]._weapontypes[sonic] = false;
	_mecha_lookup[victor]._weapontypes[explosive] = false;
	_mecha_lookup[victor]._weapontypes[laser] = false;
	_mecha_lookup[victor]._weapontypes[plasma] = true;
	_mecha_lookup[victor]._weapontypes[flame] = true;
	_mecha_lookup[victor]._weapontypes[shock] = false;
	_mecha_lookup[victor]._weapontypes[special] = false;

	strcpy_s(_mecha_lookup[dagger].name, "Aretech Dagger");
	_mecha_lookup[dagger].symbol = '@';
	_mecha_lookup[dagger].fore = 0;
	_mecha_lookup[dagger].back = 5;
	_mecha_lookup[dagger].maxHP = 50;
	_mecha_lookup[dagger].maxEN = 200;
	_mecha_lookup[dagger].melee = 3;
	_mecha_lookup[dagger].ranged = 3;
	_mecha_lookup[dagger].evasion = 5;
	_mecha_lookup[dagger].defense = 1;
	_mecha_lookup[dagger].speed = 150;
	_mecha_lookup[dagger].armor = 1;
	_mecha_lookup[dagger].los = 9;
	_mecha_lookup[dagger].pocketdepth = 4;
	_mecha_lookup[dagger].weaponmaxsize = 2;
	_mecha_lookup[dagger].optionpocketdepth = 2;
	_mecha_lookup[dagger].optionmaxsize = 1;
	_mecha_lookup[dagger]._weapontypes[impact] = true;
	_mecha_lookup[dagger]._weapontypes[sonic] = true;
	_mecha_lookup[dagger]._weapontypes[explosive] = false;
	_mecha_lookup[dagger]._weapontypes[laser] = false;
	_mecha_lookup[dagger]._weapontypes[plasma] = false;
	_mecha_lookup[dagger]._weapontypes[flame] = false;
	_mecha_lookup[dagger]._weapontypes[shock] = true;
	_mecha_lookup[dagger]._weapontypes[special] = true;
}

playerActor::playerActor() : actor()
{
	_inventory = new itemWeapon[1];
	_options = new itemOption[1];
	_populateMechaData();
}

playerActor::~playerActor() 
{
	delete _inventory;
	delete _options;
}

bool playerActor::createNewCharacter(void)
{
	bool chosen = false;
	while (!chosen) {
		DrawBox(0, 0, 79, 59, 0, true);
		DrawCenterString("Create new pilot credentials:", 2, 15, 0);
		DrawString("Name:", 2, 4, 13, 0);
		_pilot_name[0] = '\0';
		while (_pilot_name[0] == '\0') {
			InputString(_pilot_name, 15, 8, 4);
		}
	}
	return false;
}

void playerActor::modXP(long amt)
{
	_xp += amt;
	//_levelCheck();
}

void playerActor::setXP(long amt)
{
	_xp = amt;
	//_levelCheck();
}

bool playerActor::modCurrentHP(double amt)
{
	_currHP += amt;
	if (_currHP > _HP) _currHP = _HP;
	if (_currHP <= 0) return false; else return true; // false = zgon
}

bool playerActor::modCurrentEN(double amt)
{
	_currEN += amt;
	if (_currEN > _EN) _currEN = _EN;
	if (_currEN <= 0) {
		_currEN = 0;
		return false;
	}
	else return true; // false = koniec energii
}
