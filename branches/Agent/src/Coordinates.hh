/*
 * Coordinates.hh
 *
 *  Created on: 27-10-2011
 *      Author: michal
 */

#ifndef COORDINATES_HH_
#define COORDINATES_HH_

class Coordinates {
public:
	double _x,_y;
	Coordinates(){};
	Coordinates(double x, double y);
	~Coordinates();
	Coordinates operator -()const;
	bool operator !=(Coordinates C);
	bool operator ==(Coordinates C);
};

#endif /* COORDINATES_HH_ */
