/*
 * Segment.cpp
 *
 *  Created on: 27-10-2011
 *      Author: michal
 */
#include <cmath>
#include "Segment.hh"

Segment::Segment(Coordinates start,Coordinates end) {
	double v;
	//Parametryzacja prostej na ktorej lezy odcinek
	_Start=start;
	_End=end;
	//obliczanie predkosci wypadkowej
	v=sqrt(pow(_End._x-_Start._x,2)+pow(_End._y-_Start._y,2));
	_XParamA=(_End._x-_Start._x)/v;
	_XParamB=_Start._x;
	_YParamA=(_End._y-_Start._y)/v;
	_YParamB=_Start._y;

}

Segment::~Segment() {
	// TODO Auto-generated destructor stub
}

void Segment::SetVelocity(double v)
{
	_XParamA*=sqrt(v);
	_YParamA*=sqrt(v);
}

