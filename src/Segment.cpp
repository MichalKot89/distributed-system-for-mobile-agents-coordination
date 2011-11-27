/*
 * Segment.cpp
 *
 *  Created on: 27-10-2011
 *      Author: michal
 */

#include "Segment.hh"

Segment::Segment(Coordinates start,Coordinates end) {
	//Parametryzacja prostej na ktorej lezy odcinek
	_Start=start;
	_End=end;
	_XParamA=_End._x-_Start._x;
	_XParamB=_Start._x;
	_YParamA=_End._y-_Start._y;
	_YParamB=_Start._y;

}

Segment::~Segment() {
	// TODO Auto-generated destructor stub
}

