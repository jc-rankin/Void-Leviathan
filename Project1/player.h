/*PIERWOTNIE KLASA MIA£A BYÆ POŒWIÊCONA GRACZOWI JAKO BYTOWI.
OSTATECZNIE (???) GENERYCZNIE OBS£UGUJE WSZYSTKIE PIONKI MAPOWE, A ŒCIŒLEJ MÓWI¥C ICH LOKALIZACJÊ, WYGL¥D I NARYSOWANIE
CZÊŒCI STATYSTYCZNO-BOJOWO-INTELIGENTNE BÊD¥ GDZIE INDZIEJ ---- CHYBA. NA RAZIE PLAN: GRACZ W ENGINE, AI (hehehe) W MAP.CPP
*/

#pragma once


class actor
{
private:
	short x, y;
	char ch; //znak postaci
	short fore, back; //kolor postaci + t³a wed³ug indeksu 0-31 tabeli palety
	
public:
	actor();
	actor(short x, short y, char ch, short fore, short back) : x(x), y(y), ch(ch), fore(fore), back(back) {}
	~actor();
	int getX() const { return x; }
	int getY() const { return y; }
	int setX(int sx) { x = sx; return true; }
	int setY(int sy) { y = sy; return true; }
	int Xpp(); //X++
	int Xmm(); //X--
	int Ypp(); //Y++
	int Ymm(); //Y--
	char geticon() const { return ch; }
	int getfore() const { return fore; }
	int getback() const { return back; }

	void render();
};

