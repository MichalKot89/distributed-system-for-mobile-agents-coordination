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
#define MWDEBUG 1
#define AV_NUM_OF_CYCLES    10
#define SQUARE_TYPE         Sector
#define NUM_OF_AGENTS_AVAILABLE     2

#include "Common.hh"
#include "Segment.hh"
#include "AgentBase.hh"
#include <iostream>
#include <string>
#include <list>
#include <cstdlib>
#include <sstream>


// Sector struct
struct Sector {
    int _x;
    int _y;

    Sector () {
        _x = 0;     _y = 0;
    }
    Sector (int x,int y) {
        _x = x;     _y = y;
    }
};

class Agent
        :public AgentBase
{
public:

std::list<Segment> _ListOfSegments;
int _SegmentNo;
double _SquareLength;
double _MyRadius;
Coordinates _ActualPosition;
Coordinates _MySquare;
Coordinates _MyNextSquare;
double _MyVel;
double _MyTime;
std::list<SQUARE_TYPE> _AssignedSectors;  // Sectors that are assigned to the agent
int _AvailableNumOfCycles;       // Available number of cycles to make decide whether move or wait
std::string _ActualCommand;
int _AgentsInSector;
int _BoardWidth;
int _BoardHeight;

//Flagi
bool _PathDone;

        Agent();
        Agent(std::list<Segment> ListOfSegments,double vel,double radius,double SquareLength,double TimeStep);
        ~Agent();
        bool SetParameters(std::list<Segment> ListOfSegments,double vel,double radius,double SquareLength,double TimeStep);
        void Run();
        Status Move();
        double GiveTimeToCrossSquare(std::list<Segment>::iterator ListIter,int& ModX,int& ModY);
        double GiveTimeToLeaveSquare(std::list<Segment>::iterator ListIter);
        std::list<Segment> ResolveForbiddenSectors(std::list<Segment> ListOfSegments);
        void SetVelocityToSegments();
        //int DropActualPosition();
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

        const Coordinates &  GetActualPosition() const;
        bool LoadParams() const;
        bool ProcessMessage(const std::string &, std::list <std::string> &);
        bool TimerTimeout(int, std::list <std::string> &);
        std::string AnswerCommand(std::string &, int &) const;
        std::string MessageFitsToAgent(const std::string &, std::string &, int &, int &, int &) const;
        std::string MessageFitsToAgent(const std::string &, std::string &, int &, int &) const;
        bool SetStatus(Status);
        Status GetStatus() const;
        std::string StateMessage();
};

#ifdef CREATE_LIBRARY
/// Funkcja tworząca obiekt Agent
extern "C" AgentBase * CreateAgent();
#endif

#endif /* AGENT_HH_ */

