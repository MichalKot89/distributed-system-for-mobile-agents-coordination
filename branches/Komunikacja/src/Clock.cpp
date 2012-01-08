/*
 * Clock.cpp
 *
 *  Created on: 10-12-2011
 *      Author: michal
 */

#include "Clock.hh"
#include <unistd.h>

Clock::Clock() {
        // TODO Auto-generated constructor stub

}
Clock::Clock(double TimeStep)
{
        _TimeStep=TimeStep;
        _TimeStepInUSecs=(unsigned int)(_TimeStep*1000000.0);
        _Time=0.0;

}
Clock::~Clock() {
        // TODO Auto-generated destructor stub
}

void Clock::TickTack()
{

    usleep(_TimeStepInUSecs);
    _Time+=_TimeStep;

}

double Clock::GiveActualTime()
{
        return _Time;
}
double Clock::GiveTimeStep()
{
        return _TimeStep;

}

