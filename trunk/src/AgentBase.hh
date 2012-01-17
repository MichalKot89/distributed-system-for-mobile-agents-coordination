/*
 * AgentBase.hh
 *
 */

#ifndef AGENT_BASE_HH
#define AGENT_BASE_HH

#include "Coordinates.hh"
#include "Segment.hh"
#include <iostream>
#include <string>
#include <list>


class AgentBase {
public:
enum Status{Moving, InterestChecking, InterestCollision, PlaceInSectorChecking,LeavingSqare,WaitingToEnterSquare,WaitingToBypass, Finished, ERROR};
int _MyID;
Status _MyStatus;
double _TimeStep;

	AgentBase() {
		_MyID = 0;
		_MyStatus = Moving;
	}
        virtual ~AgentBase() {}
        virtual const Coordinates &  GetActualPosition() const = 0;
        virtual bool LoadParams() const = 0;
        virtual void Run() = 0;
        virtual bool ProcessMessage(const std::string &, std::list <std::string> &) = 0;
        virtual bool TimerTimeout(int, std::list <std::string> &) = 0;
        virtual std::string MessageFitsToAgent(const std::string &, std::string &, int &, int &, int &) const = 0;
        virtual std::string MessageFitsToAgent(const std::string &, std::string &, int &, int &) const = 0;
        virtual bool SetStatus(Status) = 0;
        virtual Status GetStatus() const = 0;
        virtual std::string StateMessage() = 0;
        virtual bool SetParameters(std::list<Segment> ,double ,double ,double ,double ) =0;

};

#endif /* AGENT_BASE_HH */
