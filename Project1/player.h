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
	int _los;
	
public:
	actor();
	actor(short x, short y, char ch, short fore, short back, int los) : x(x), y(y), ch(ch), fore(fore), back(back), _los(los) {}
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
	int getLOS() const { return _los; }
	void setLOS(int los) { _los = los; }

	void render(); // deprecjonowane - rysowanie postaci bêdzie zale¿ne od subprogramów mapy gdy¿ ruchome okienko
	void render(int rx, int ry); //lepiej - wskauzjê gdzie a gra rysuje... gdzie.
};

