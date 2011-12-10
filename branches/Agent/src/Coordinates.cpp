/*
 * Coordinates.cpp
 *
 *  Created on: 27-10-2011
 *      Author: michal
 */

#include "Coordinates.hh"

Coordinates::Coordinates(double x, double y) {
	_x=x;
	_y=y;

}

Coordinates::~Coordinates() {
	// TODO Auto-generated destructor stub
}

Coordinates  Coordinates::operator -()const
{
	return Coordinates(-_x,-_y);
}

Coordinates & Coordinates::operator +=(const Coordinates& C)
		{
	_x+=C._x;
	_y+=C._y;
	return(*this);
		}

bool Coordinates::operator !=(const Coordinates& C){
	if((*this)==C)
		return false;
	else
		return true;

}

bool Coordinates::operator ==(const Coordinates& C){
	if((_x==C._x)&&(_y==C._y))
		return true;
	else
		return false;
}

