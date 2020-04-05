#pragma once
/****************************************************************************
*
* Synopsis : 2D Vector object for DOD.
*
* Description : This implements a 2D vector as an object along with useful operators.
*
* Copyright 2006, Richard D.Clark
*
*                          The Wide Open License(WOL)
*
* Permission to use, copy, modify, distribute and sell this software and its
* documentation for any purpose is hereby granted without fee, provided that
* the above copyright notice and this license appear in all source copies.
* THIS SOFTWARE IS PROVIDED "AS IS" WITHOUT EXPRESS OR IMPLIED WARRANTY OF
* ANY KIND.See http ://www.dspguru.com/wol.htm for more information.
*
*****************************************************************************/


class mcoord //koordynaty x-y do u¿ycia w kilku ró¿nych miejscach
{
public:	
	int x;
	int y;
	mcoord() : x(0), y(0) {}
	mcoord(int x, int y) : x(x), y(y) {}
	mcoord & operator= (const mcoord &coord);
	friend bool operator== (const mcoord &c1, const mcoord &c2);
	friend bool operator!= (const mcoord &c1, const mcoord &c2);
};

bool operator==(const mcoord & c1, const mcoord & c2)
{
	return ((c1.x == c2.x) && (c1.y == c2.y));
}

bool operator!=(const mcoord & c1, const mcoord & c2)
{
	return !(c1 == c2);
}

mcoord & mcoord::operator=(const mcoord & coord)
{
	x = coord.x;
	y = coord.y;

	return *this;
}

////////////////////////////////////////////////////////////////////////////////

enum compass {
	north = 0,
	neast,
	east,
	seast,
	south,
	swest,
	west,
	nwest
};

class vec {
private:
	int _x;
	int _y;
	mcoord _dirmatrix[8]{ {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1} };
public:
	vec() : _x(0), _y(0) {}
	vec(int x, int y) : _x(x), _y(y) {}

	void vx(int x) { _x = x; }
	int vx() const { return _x; }
	void vy(int y) { _y = y; }
	int vy() const { return _y; }

	void ClearVec() {
		_x = 0;
		_y = 0;
	}

	vec& operator+= (const compass& rhs) {
		if ((rhs >= north) && (rhs <= nwest)) {
			_x += _dirmatrix[rhs].x;
			_y += _dirmatrix[rhs].y;
		}
		return *this;
	}

};



