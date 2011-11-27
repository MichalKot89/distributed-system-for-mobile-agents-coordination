/*
 * Segment.hh
 *
 *  Created on: 27-10-2011
 *      Author: michal
 */

#ifndef SEGMENT_HH_
#define SEGMENT_HH_
#include "Coordinates.hh"

class Segment {
public:
	Coordinates _Start;
	Coordinates _End;
	double _XParamA,_XParamB;
	double _YParamA,_YParamB;
	Segment(){};
	Segment(Coordinates start,Coordinates end);
	~Segment();
};

#endif /* SEGMENT_HH_ */
