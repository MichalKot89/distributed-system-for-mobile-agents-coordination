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
	Coordinates & operator +=(const Coordinates & C);
	bool operator !=(const Coordinates & C);
	bool operator ==(const Coordinates & C);

};

#endif /* COORDINATES_HH_ */
