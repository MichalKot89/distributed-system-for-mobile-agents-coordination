/*
 * Clock.h
 *
 *  Created on: 10-12-2011
 *      Author: michal
 */

#ifndef CLOCK_HH_
#define CLOCK_HH_

class Clock {
public:


	Clock();
	Clock(double TimeStep);
	void TickTack();
	double GiveActualTime();
	double GiveTimeStep();
	virtual ~Clock();

private:
	double _TimeStep;
	double _Time;
    unsigned int _TimeStepInUSecs;
};

#endif /* CLOCK_HH_ */
