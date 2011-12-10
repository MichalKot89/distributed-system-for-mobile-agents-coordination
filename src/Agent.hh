/*
 * Agent.hh
 *
 *  Created on: 27-10-2011
 *      Author: michal
 */

#ifndef AGENT_HH_
#define AGENT_HH_

///komunikacji z Gnuplotem
#define PLOTDIR "../plots/" ///<sciezka do danych z wykresow
#define INFINITY 1000000000
#define MWDEBUG 1

#include "Segment.hh"
#include <iostream>
#include <list>


class Agent {
public:
	enum Status{Moving,LeavingSqare,WaitingToEnterSquare,WaitingToBypass};


static int _NumOfAgentsCreated;

int _MyID;
std::list<Segment> _ListOfSegments;
int _SegmentNo;
double _SquareLength;
double _MyRadius;
Status _MyStatus;
Coordinates _ActualPosition;
Coordinates _MySquare;
Coordinates _MyNextSquare;
double _MyVel;
double _TimeStep;
double _Time;

//Flagi
bool _PathDone;

	Agent(std::list<Segment> ListOfSegments,double vel,double radius,double SquareLength);
	~Agent();
	Status Move();
	double GiveTimeToCrossSquare(std::list<Segment>::iterator ListIter,int& ModX,int& ModY);
	double GiveTimeToLeaveSquare(std::list<Segment>::iterator ListIter);
	std::list<Segment> ResolveForbiddenSectors(std::list<Segment> ListOfSegments);
	void SetVelocityToSegments();
	int DropActualPosition();
	static int CalculateCollisionPoints(Segment S,double r,Coordinates Start,Coordinates O, double & InTime, double & OutTime);
	static int SquareEqRoots(double a,double b,double c,double &t1,double &t2);
	static std::list<Segment> FindPathResolvingForbiddenSector
	(Coordinates In,Coordinates Out,Coordinates O);
	static void ChangeStartOfCordSysForSegment
	(Segment & OneSegment, Coordinates Into);
	static void ChangeStartOfCordSysForSegment
	(std::list<Segment> & ListOfSegments, Coordinates Into);
	static Segment FindLinePerpendicularToPoint(Segment OneSegment, Coordinates Point);
	static Coordinates FindCrossPointBetweenSegments(Segment Seg1,Segment Seg2);
	static Coordinates CoordinatesToSquare(Coordinates C, double SquareLength);
};

#endif /* AGENT_HH_ */
