/*
 * main.cpp
 *
 *  Created on: 14-10-2011
 *      Author: michal
 */
#include <iostream>
#include "main.hh"
#include "GnuplotInc.hh"
#include "Segment.hh"
#include "Agent.hh"
#include "Coordinates.hh"
#include <cmath>

using namespace std;

int main()
{
	int i;

	GnuplotInit();
	GnuplotSceneClean();
	std::list<Segment> Trasa;

	Trasa.push_back(Segment(Coordinates(2,2),Coordinates(8,2)));
	Trasa.push_back(Segment(Coordinates(8,2),Coordinates(5,10)));
	Trasa.push_back(Segment(Coordinates(5,10),Coordinates(8,12)));
	//Trasa.push_back(Segment(Coordinates(6,6),Coordinates(8,6)));
	//Trasa.push_back(Segment(Coordinates(8,6),Coordinates(10.5,10.5)));
	//Trasa.push_back(Segment(Coordinates(10.5,10.5),Coordinates(15,15)));
	//Trasa.push_back(Segment(Coordinates(15,15),Coordinates(7,12)));





	Agent A1(Trasa,50,1,5);
	while(!A1._PathDone){
		if(A1.Move()>0){
			//czekanie
			PlotScene(5,3,A1._MyID);
			sleep(3);

		}

	}
	PlotScene(5,3,A1._MyID);

	cin>>i;
	GnuplotShutDown();

}

