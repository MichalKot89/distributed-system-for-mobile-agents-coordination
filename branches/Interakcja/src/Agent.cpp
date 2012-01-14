/*!
 *\file Agent.cpp
 *\author Michal Wcislo
 *\date 15.12.2011
 *\version 1.0
 *\brief Zawiera implementacje klasy Agent
 *
 *Zawiera implementacje klasy Agent
 *
 *
 */

#include "Agent.hh"
#include "GnuplotInc.hh"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <cmath>

using namespace std;

int Agent::_NumOfAgentsCreated=0;

Agent::Agent(list<Segment> ListOfSegments,double vel,double radius,double SquareLength,double TimeStep)
{
	_MyClock=Clock(TimeStep);
	_ActualPosition=ListOfSegments.front()._Start;
	_MySquare=_MyNextSquare=CoordinatesToSquare(_ActualPosition,SquareLength);
	_SegmentNo=0;

	_MyVel=vel;
	_PathDone=false;
	_SquareLength=SquareLength;
	_MyRadius=radius;
	_MyStatus=Moving;
	_MyID=_NumOfAgentsCreated++;
	_ListOfSegments=ResolveForbiddenSectors(ListOfSegments);
	SetVelocityToSegments();
	Order=1;


	list<Segment>::iterator ListIter=_ListOfSegments.begin();
	for(;ListIter!=_ListOfSegments.end();ListIter++){
cout<<ListIter->_Start._x<<" "<<ListIter->_Start._y<<" "
		<<ListIter->_End._x<<" "<<ListIter->_End._y<<endl;
	}

	DropActualPosition();

}

Agent::~Agent() {
	// TODO Auto-generated destructor stub
}

void Agent::Run()
{
	while(!_PathDone){
		_MyClock.TickTack();
		if(Move()>Moving){
			//czekanie
			//PlotScene(5,3,_MyID);
			cout<<_MySquare._x<<" "<<_MySquare._y<<" Next: "<<_MyNextSquare._x<<" "<<_MyNextSquare._y<<endl;
			//sleep(3);
			_MyStatus=Moving;

		}
		cout<<"Actual TIme:"<<_MyClock.GiveActualTime()<<endl;
		PlotScene(5,3,_MyID);
	}
	PlotScene(5,3,_MyID);

}

Agent::Status Agent::Move()
{
	double FinalX,FinalY,timeToCrossSqare,timeToLeaveSqare;
	double EstimatedTimeToEndX,EstimatedTimeToEndY,EstimatedTimeToEnd;
	Status ActualStatus=_MyStatus;
	int ModX,ModY;
if((_MyStatus!=WaitingToEnterSquare)&&(_MyStatus!=WaitingToBypass)){

	_MySquare=CoordinatesToSquare(_ActualPosition, _SquareLength);

	if(_MyStatus==LeavingSquare){

	_MyStatus=Moving;
	}
	//poruszanie sie
	list<Segment>::iterator ListIter=_ListOfSegments.begin();
	for(int i=0;i<_SegmentNo;i++)
		if(ListIter!=_ListOfSegments.end())
			ListIter++;
		else{
			cerr<<"Blad liczba segmentow wieksza niz rzeczywisty rozmiar listy!"<<endl;
		exit(1);
		}
	timeToCrossSqare=GiveTimeToCrossSquare(ListIter,ModX,ModY);
	timeToLeaveSqare=GiveTimeToLeaveSquare(ListIter);
if((timeToCrossSqare<_MyClock.GiveTimeStep()) &&(timeToCrossSqare>0.0)){
	FinalX=ListIter->_XParamA*timeToCrossSqare+ListIter->_XParamB;
	FinalY=ListIter->_YParamA*timeToCrossSqare+ListIter->_YParamB;
	_ActualPosition=Coordinates(FinalX,FinalY);


	//ustalanie wspolrzednych kolejnego kwadratu
	_MyNextSquare+=Coordinates(ModX,ModY);
	//zmiana statusu
	_MyStatus=ActualStatus=WaitingToEnterSquare;
}else if((timeToLeaveSqare<_MyClock.GiveTimeStep()) &&(timeToLeaveSqare>0.0)){
	FinalX=ListIter->_XParamA*timeToLeaveSqare+ListIter->_XParamB;
	FinalY=ListIter->_YParamA*timeToLeaveSqare+ListIter->_YParamB;
	_ActualPosition=Coordinates(FinalX,FinalY);
	//zwolnienie kwadratu
	//Jakas funkcja interakcji
	DoSthWhenIAmLeavingSquare();
if(_MySquare!=_MyNextSquare)//sytuacja w ktorej agent tylko na chwile, czescia
	//wjezdza na kwadrat
	_MyNextSquare=_MySquare;

	_MyStatus=ActualStatus=LeavingSquare;
}else{
if(ListIter->_XParamA!=0.0)
	EstimatedTimeToEndX=
		(ListIter->_End._x-ListIter->_XParamB)/ListIter->_XParamA;
else
	EstimatedTimeToEndX=0;

if(ListIter->_YParamA!=0.0)
	EstimatedTimeToEndY=
		(ListIter->_End._y-ListIter->_YParamB)/ListIter->_YParamA;
else
	EstimatedTimeToEndY=0;

	EstimatedTimeToEnd=EstimatedTimeToEndX > EstimatedTimeToEndY ? EstimatedTimeToEndX : EstimatedTimeToEndY;

	//sprawdzanie czy dotarl do punktu koncowego
	if(EstimatedTimeToEnd<_MyClock.GiveTimeStep()){
		_ActualPosition=ListIter->_End;
		_SegmentNo++;
		//Jezeli cala sciezka
		if(_SegmentNo>=_ListOfSegments.size())
		_PathDone=true;
	}else{

	FinalX=ListIter->_XParamA*_MyClock.GiveTimeStep()+ListIter->_XParamB;
	FinalY=ListIter->_YParamA*_MyClock.GiveTimeStep()+ListIter->_YParamB;
	_ActualPosition=Coordinates(FinalX,FinalY);
	}
	_MyStatus=ActualStatus=Moving;
}
	ListIter->_XParamB=_ActualPosition._x;
	ListIter->_YParamB=_ActualPosition._y;

	DropActualPosition();

}else{
	//waiting
//Jakas funkcja interakcji
	DoSthWhenIAmWaitingToEnterSquare();
}
return ActualStatus;
}

double Agent::GiveTimeToCrossSquare(std::list<Segment>::iterator ListIter,int & ModX,int& ModY)
{
	double SquareX,SquareY,LocalStartX,LocalStartY,time1,time2,time3,time4;
	//przeliczanie wspolrzednych do ukladu zwiazanego z kwadratem
	SquareX=floor(_ActualPosition._x / _SquareLength);
	SquareY=floor(_ActualPosition._y / _SquareLength);
	LocalStartX=_ActualPosition._x - SquareX*_SquareLength;
	LocalStartY=_ActualPosition._y - SquareY*_SquareLength;
	ModX=ModY=0;
	if(ListIter->_XParamA!=0.0){
		time1=(_SquareLength-_MyRadius-LocalStartX)/ListIter->_XParamA;
		time2=(_MyRadius-LocalStartX)/ListIter->_XParamA;
		ModX=time1>time2? 1: -1;
		time1=time1>time2? time1 : time2;
	}else
		time1=-1.0;

	if(ListIter->_YParamA!=0.0){
		time3=(_SquareLength-_MyRadius-LocalStartY)/ListIter->_YParamA;
		time4=(_MyRadius-LocalStartY)/ListIter->_YParamA;
		ModY=time3>time4? 1: -1;
		time3=time3>time4? time3 : time4;

	}else
		time3=-1.0;
if((time1>0.0)&&(time3>0.0)){
	if(time1 < time3)
		ModY=0;
	else
		ModX=0;
	return time1 < time3 ? time1 : time3;
}else if(time1>0.0){
	ModY=0;
	return time1;
}else if(time3>0.0){
	ModX=0;
	return time3;
}else return 0.0;



}

double Agent::GiveTimeToLeaveSquare(std::list<Segment>::iterator ListIter)
{
	double SquareX,SquareY,LocalStartX,LocalStartY,time1,time2,time3,time4;
	//przeliczanie wspolrzednych do ukladu zwiazanego z kwadratem
	SquareX=floor(_ActualPosition._x / _SquareLength);
	SquareY=floor(_ActualPosition._y / _SquareLength);
	LocalStartX=_ActualPosition._x - SquareX*_SquareLength;
	LocalStartY=_ActualPosition._y - SquareY*_SquareLength;
	if(ListIter->_XParamA!=0.0){
		time1=(_SquareLength-_MyRadius-LocalStartX)/ListIter->_XParamA;
		time2=(_MyRadius-LocalStartX)/ListIter->_XParamA;

		time1=time1<time2? time1 : time2;
	}else
		time1=-1.0;

	if(ListIter->_YParamA!=0.0){
		time3=(_SquareLength-_MyRadius-LocalStartY)/ListIter->_YParamA;
		time4=(_MyRadius-LocalStartY)/ListIter->_YParamA;

		time3=time3<time4? time3 : time4;

	}else
		time3=-1.0;
if((time1>0.0)&&(time3>0.0))
	return time1 < time3 ? time1 : time3;
else if(time1>0.0)
	return time1;
else if(time3>0.0)
	return time3;
else return 0.0;



}
list<Segment> Agent::ResolveForbiddenSectors(list<Segment> ListOfSegments)
{
	double InTime=0,OutTime=0,TempTime=0,SquareX,SquareY;
	double LocalStartX=0,LocalStartY=0,LocalEndX=0,LocalEndY=0;
	double InX,InY,OutX,OutY;
	double a,b,c,xO,yO;
	double r=_MyRadius*sqrt(2);
	bool ColisionFound=false,SquareResolved=false,EndOfSegInCircle=false;
	bool OnlyInPoint=false;
	int NumOfRoots=0,CornerIter=0;
	Coordinates ActualPos,ActualPosNext;
	list<Segment> ResultListOfSegments;
	list<Segment> TempListOfSegments;
	list<Segment>::iterator IteratorForLastElement;
//dla kazdego segmentu sprawdzamy czy przechodzi przez "zakazane" KOLA
	list<Segment>::iterator ListIter=ListOfSegments.begin();
	for(;ListIter!=ListOfSegments.end();ListIter++){
		ActualPos=ListIter->_Start;

while(ActualPos!=ListIter->_End){
//w kazdym kwadracie przechodzimy do lokalnego ukladu wspolrzednych kwadratu
	SquareResolved=false;
	ColisionFound=false;
	EndOfSegInCircle=false;
	OnlyInPoint=false;
	CornerIter=0;
	TempListOfSegments.clear();
	SquareX=floor(ActualPos._x / _SquareLength);
	if((ActualPos._x / _SquareLength)==SquareX)//jezeli na granicy kwadratow
		if(ListIter->_XParamA<0)//jezeli pochodna ujemna
			SquareX--;

	SquareY=floor(ActualPos._y / _SquareLength);
	if((ActualPos._y / _SquareLength)==SquareY)//jezeli na granicy kwadratow
		if(ListIter->_YParamA<0)//jezeli pochodna ujemna
			SquareY--;

	LocalStartX=ActualPos._x - SquareX*_SquareLength;
	LocalStartY=ActualPos._y - SquareY*_SquareLength;
	LocalEndX=ListIter->_End._x - SquareX*_SquareLength;
	LocalEndY=ListIter->_End._y - SquareY*_SquareLength;


	//TODO uwzglednic przypadki rozne
	//poczatek w zakazanym kole
	while((!ColisionFound)&&(CornerIter<4)){
		switch(CornerIter){
		case 0:
			xO=_SquareLength;
			yO=_SquareLength;
			break;
		case 1:
			xO=0;
			yO=_SquareLength;
			break;
		case 2:
			xO=_SquareLength;
			yO=0;
			break;
		case 3:
			xO=0;
			yO=0;
			break;
		}

	if(sqrt(pow(xO-LocalStartX,2.0)+pow(yO-LocalStartY,2.0))<r){//NE

		CalculateCollisionPoints(*ListIter,r, Coordinates(LocalStartX,LocalStartY),Coordinates(xO,yO),InTime,OutTime);
		if((OutTime<0))
			OutTime=InTime;

		LocalStartX=ListIter->_XParamA*OutTime+LocalStartX;
		LocalStartY=ListIter->_YParamA*OutTime+LocalStartY;
		ActualPos._x=ListIter->_XParamB=ListIter->_Start._x=LocalStartX+SquareX*_SquareLength;
		ActualPos._y=ListIter->_YParamB=ListIter->_Start._y=LocalStartY+SquareY*_SquareLength;
		ColisionFound=true;
	}
	CornerIter++;
	}
	ColisionFound=false;
	CornerIter=0;
	while((!ColisionFound)&&(CornerIter<4)){
		switch(CornerIter){
		case 0:
			xO=_SquareLength;
			yO=_SquareLength;
			break;
		case 1:
			xO=0;
			yO=_SquareLength;
			break;
		case 2:
			xO=_SquareLength;
			yO=0;
			break;
		case 3:
			xO=0;
			yO=0;
			break;
		}
	//koniec w zakazanym kole
if(sqrt(pow(xO-LocalEndX,2.0)+pow(yO-LocalEndY,2.0))<r){//NE
	ColisionFound=true;
//szukanie punktu wejscia na zakazany okrag
CalculateCollisionPoints((*ListIter),r, Coordinates(LocalStartX,LocalStartY),Coordinates(xO,yO),InTime,OutTime);
if(OutTime<InTime)
	InTime=OutTime;
InX=ListIter->_XParamA*InTime+LocalStartX;
InY=ListIter->_YParamA*InTime+LocalStartY;
//szukanie punktu wyjscia z okregu
if ((++ListIter)!=ListOfSegments.end()){

	ActualPosNext=ListIter->_Start;
	LocalStartX=ActualPosNext._x - SquareX*_SquareLength;
	LocalStartY=ActualPosNext._y - SquareY*_SquareLength;
	LocalEndX=ListIter->_End._x - SquareX*_SquareLength;
	LocalEndY=ListIter->_End._y - SquareY*_SquareLength;


CalculateCollisionPoints(*ListIter,r, Coordinates(LocalStartX,LocalStartY),Coordinates(xO,yO),InTime,OutTime);
if((InTime<0))
	InTime=OutTime;

OutX=ListIter->_XParamA*InTime+LocalStartX;
OutY=ListIter->_YParamA*InTime+LocalStartY;

TempListOfSegments=FindPathResolvingForbiddenSector(Coordinates(InX,InY),Coordinates(OutX,OutY),Coordinates(xO,yO));

EndOfSegInCircle=true;
}else{
	ListIter--;
	OnlyInPoint=true;
	TempListOfSegments.push_back(Segment(Coordinates(InX,InY),Coordinates(InX,InY)));
	EndOfSegInCircle=true;
//koniec przesuwany do miejsca wjazdu na zakazany obszar
	ListIter->_End=Coordinates(InX+ SquareX*_SquareLength,InY+ SquareY*_SquareLength);
}

//}else if (sqrt(pow(-LocalEndX,2.0)+pow(_SquareLength-LocalEndY,2.0))<=r){//NW

//}else if (sqrt(pow(_SquareLength-LocalEndX,2.0)+pow(-LocalEndY,2.0))<=r){//SE

//}else if (sqrt(pow(-LocalEndX,2.0)+pow(-LocalEndY,2.0))<=r){//SW

//}
if(EndOfSegInCircle){
	SquareResolved=true;
	if (!OnlyInPoint){
	//ListIter--;
	//ActualPos=ListIter->_Start;
	LocalStartX=ActualPos._x - SquareX*_SquareLength;
	LocalStartY=ActualPos._y - SquareY*_SquareLength;
	//LocalEndX=ListIter->_End._x - SquareX*_SquareLength;
	//LocalEndY=ListIter->_End._y - SquareY*_SquareLength;
	//ListIter++;
	}
//dodanie pozycji segmentu od startu do miejsca wjechania na zakazane kolo
TempListOfSegments.push_front(Segment(Coordinates(LocalStartX,LocalStartY),TempListOfSegments.begin()->_Start));
//Jezeli nie byl tylko segment wejsciowy trzeba go usunac, bo byl potrzebny
//jedynie do oznaczenia punktu wejscia
if (OnlyInPoint)
	TempListOfSegments.pop_back();

//przejscie do globalnego ukladu wspolrzednych
ChangeStartOfCordSysForSegment(TempListOfSegments,Coordinates(-SquareX*_SquareLength,-SquareX*_SquareLength));
//przepisanie scizeki do wynikowej trasy
list<Segment>::iterator TempListIter=TempListOfSegments.begin();
for(;TempListIter!=TempListOfSegments.end();TempListIter++){
	ResultListOfSegments.push_back(*TempListIter);
}
IteratorForLastElement=ResultListOfSegments.end();
IteratorForLastElement--;
ActualPos=IteratorForLastElement->_End;
}
}
CornerIter++;
	}
	if(!SquareResolved){
	ColisionFound=false;
	CornerIter=0;
	//koniec segmentu w badanym kwadracie
	if((LocalEndX<=_SquareLength)&&(LocalEndX>=0)&&(LocalEndY<=_SquareLength)&&(LocalEndY>=0)){
		//koniec segmentu w kwadracie wiec dodajemy segment i koniec
		Segment S(Coordinates(LocalStartX,LocalStartY),Coordinates(LocalEndX,LocalEndY));
		ChangeStartOfCordSysForSegment(S,Coordinates(- SquareX*_SquareLength,- SquareY*_SquareLength));
		ResultListOfSegments.push_back(S);
	ActualPos=ListIter->_End;
	}else{
//sprawdzamy czy wchodza na te male kola w rogach
//Kolo NE

		while((!ColisionFound)&&(CornerIter<4)){
			switch(CornerIter){
			case 0:
				xO=_SquareLength;
				yO=_SquareLength;
				break;
			case 1:
				xO=0;
				yO=_SquareLength;
				break;
			case 2:
				xO=_SquareLength;
				yO=0;
				break;
			case 3:
				xO=0;
				yO=0;
				break;
			}
		//rownanie kwadratowe opisujace kolizje
		a=pow(ListIter->_XParamA,2)+pow(ListIter->_YParamA,2);
		b=2.0*(ListIter->_XParamA*(LocalStartX-xO)+
				ListIter->_YParamA*(LocalStartY-yO));
		c=pow(LocalStartX-xO,2)+pow(LocalStartY-yO,2)-pow(r,2);
		if(((NumOfRoots=SquareEqRoots(a,b,c,InTime,OutTime))>1)){//jezeli dwa rozwiazania
			if((InTime>0)&&(OutTime>0)){//TODO Sprawdzic kiedy mozliwe jest ze jeden z czasow jest dodatni
			ColisionFound=true;//to kolizja
			if(OutTime<InTime){//czas wyjscia nie moze byc mniejszy od czasu wejscia
				TempTime=InTime;
				InTime=OutTime;
				OutTime=TempTime;
			}
			//Obliczanie wspolrzednych poczatkowych i koncowych
			InX=ListIter->_XParamA*InTime+LocalStartX;
			InY=ListIter->_YParamA*InTime+LocalStartY;
			OutX=ListIter->_XParamA*OutTime+LocalStartX;
			OutY=ListIter->_YParamA*OutTime+LocalStartY;
			}
		}else if (NumOfRoots==1){
			ColisionFound=true;//"otarcie" sie o niedozwolony obszar
			SquareResolved=true;//Kolizji nie trzeba rozwiazywac
		}
		CornerIter++;
	}

	if((SquareResolved)||(!ColisionFound)){//jezeli nie ma kolizji
//szukanie miejsca opuszczenia kwadratu
		TempTime=-1.0;
		if(ListIter->_XParamA!=0.0){
			TempTime=(_SquareLength-LocalStartX)/ListIter->_XParamA;//prawy bok kwadratu
			if((TempTime>0)) {//prawy bok kwadratu
				LocalEndX=_SquareLength;
				LocalEndY=ListIter->_YParamA*TempTime+LocalStartY;
				if((LocalEndY<=_SquareLength)&&(LocalEndY>=0.0))
					SquareResolved=true;
			}
		}
		if((!SquareResolved)&&(ListIter->_XParamA!=0.0)){
			TempTime=(-LocalStartX)/ListIter->_XParamA;//lewy bok kwadratu
			if((TempTime>0)){//lewy bok kwadratu
				LocalEndX=0;
				LocalEndY=ListIter->_YParamA*TempTime+LocalStartY;
				if((LocalEndY<=_SquareLength)&&(LocalEndY>=0.0))
					SquareResolved=true;
			}
		}

		if((!SquareResolved)&&(ListIter->_YParamA!=0.0)){
			TempTime=(_SquareLength-LocalStartY)/ListIter->_YParamA;//gorny kwadrat
			if((TempTime>0)){//gorny kwadrat
				LocalEndY=_SquareLength;
				LocalEndX=ListIter->_XParamA*TempTime+LocalStartX;
				if((LocalEndY<=_SquareLength)&&(LocalEndY>=0.0))
					SquareResolved=true;
			}
		}
		if((!SquareResolved)&&(ListIter->_YParamA!=0.0)){
			TempTime=(-LocalStartY)/ListIter->_YParamA;//dolny kwadrat
			if(TempTime>0)
			{//dolny kwadrat
				LocalEndY=0;
				LocalEndX=ListIter->_XParamA*TempTime+LocalStartX;
				if((LocalEndY<=_SquareLength)&&(LocalEndY>=0.0))
					SquareResolved=true;
			}
		}


//przejscie do globalnego ukladu wspolrzednych
		LocalStartX+=SquareX*_SquareLength;
		LocalStartY+=SquareY*_SquareLength;
		LocalEndX+=SquareX*_SquareLength;
		LocalEndY+=SquareY*_SquareLength;




//tworzenie sciezki przechodzacej przez kwadrat bez kolizji
		ResultListOfSegments.push_back(Segment(Coordinates(LocalStartX,LocalStartY),Coordinates(LocalEndX,LocalEndY)));
	}else{//generujemy sciezke od poczatku do momentu dojazdu do miejsca kontynuacji sciezki
		TempListOfSegments.clear();
		TempListOfSegments=FindPathResolvingForbiddenSector(Coordinates(InX,InY),Coordinates(OutX,OutY),Coordinates(xO,yO));
		//dodanie pozycji segmentu od startu do miejsca wjechania na zakazane kolo
		TempListOfSegments.push_front(Segment(Coordinates(LocalStartX,LocalStartY),TempListOfSegments.begin()->_Start));
		//przejscie do globalnego ukladu wspolrzednych
		ChangeStartOfCordSysForSegment(TempListOfSegments,Coordinates(-SquareX*_SquareLength,-SquareY*_SquareLength));
		//przepisanie scizeki do wynikowej trasy
		list<Segment>::iterator TempListIter=TempListOfSegments.begin();
		for(;TempListIter!=TempListOfSegments.end();TempListIter++){
			ResultListOfSegments.push_back(*TempListIter);
		}

	}
	IteratorForLastElement=ResultListOfSegments.end();
	IteratorForLastElement--;
	ActualPos=IteratorForLastElement->_End;
	}
	}
}//koniec while
}
return ResultListOfSegments;
}



void Agent::SetVelocityToSegments()
{
	list<Segment>::iterator ListIter=_ListOfSegments.begin();
	for(;ListIter!=_ListOfSegments.end();ListIter++){
		ListIter->SetVelocity(_MyVel);
	}


}

int Agent::DropActualPosition()
{
	ofstream Strm;
	char dir[50]=PLOTDIR;
	char agentID[20];
	strcat(dir,"Agent");
	snprintf(agentID, 20,"%d",_MyID);
	strcat(dir, agentID);
	strcat(dir,".dat");

	Strm.open(dir,ios::out|ios::app);//dopisywanie
	if(!Strm.is_open())
	{
		cerr<<"Nie mozna otworzyc pliku"<<endl;
		return 1;
	}
	Strm<<_ActualPosition._x<<" "<<_ActualPosition._y<<" "<<_MyClock.GiveActualTime()<<endl;
	Strm.close();
	return 1;
}


int Agent::CalculateCollisionPoints(Segment S,double r,Coordinates Start,Coordinates O, double & InTime, double & OutTime)
{
	double a,b,c;

	a=pow(S._XParamA,2)+pow(S._YParamA,2);
	b=2*(S._XParamA*(Start._x-O._x)+
			S._YParamA*(Start._y-O._y));
	c=pow(Start._x-O._x,2)+pow(Start._y-O._y,2)-pow(r,2);
	return SquareEqRoots(a,b,c,InTime,OutTime);

}
int Agent::SquareEqRoots(double a,double b,double c,double &t1,double &t2)
{
double delta=pow(b,2.0)-4*a*c;
if(delta>0){
	t1=(-b+sqrt(delta))/(2*a);
	t2=(-b-sqrt(delta))/(2*a);
	return 2;
}else if(delta==0){
	t1=(-b)/(2*a);
	return 1;
}
return 0;

}
list<Segment> Agent::FindPathResolvingForbiddenSector
(Coordinates In,Coordinates Out,Coordinates O)
{
	list<Segment> ResultListOfSegments;
	Segment ToInSeg,ToOutSeg,ToMiddleSeg,MiddleSeg;
	double fi1,fi2,fi3;//fi - kat pomiedzy poszczegolnymi prostymi
	//do ktorych szuka sie stycznych
	double R=sqrt(pow(O._x-In._x,2)+pow(O._y-In._y,2));//promien
//Tworzenie stycznych

//Proste zawierajace promienie okregu z punktami wejscia i wyjscia z kolizji
	Segment InSeg(In,O);
	Segment OutSeg(O,Out);
//przejscie do ukladu wspolrzednych zwiazanego ze srodkiem omijanego okregu
	ChangeStartOfCordSysForSegment(InSeg,O);
	ChangeStartOfCordSysForSegment(OutSeg,O);
//znajdywanie stycznych
	ToInSeg=FindLinePerpendicularToPoint(InSeg,InSeg._Start);
	ToOutSeg=FindLinePerpendicularToPoint(OutSeg,OutSeg._End);
//Ustalanie trzeciej stycznej
	//ustalanie punktu stycznosci
	fi1=acos(InSeg._Start._x/R);
	if(InSeg._Start._y<0)
		fi1+=2*(M_PI-fi1);
	fi2=acos(OutSeg._End._x/R);
	if(OutSeg._End._y<0)
		fi2+=2*(M_PI-fi2);
	if(fabs(fi1-fi2)>=M_PI){
		if(fi1>fi2)
			fi3=fi2-fabs(2*M_PI-fi1+fi2)/2.0;
		else
			fi3=fi1-fabs(2*M_PI-fi2+fi1)/2.0;

	}else{
		if(fi1>fi2)
			fi3=fi2+fabs(fi1-fi2)/2.0;
		else
			fi3=fi1+fabs(fi1-fi2)/2.0;
	}
	if(fabs(fi1-fi2)<=M_PI/2.0){
		InSeg=Segment(InSeg._Start,FindCrossPointBetweenSegments(ToInSeg,ToOutSeg));
		OutSeg=Segment(InSeg._End,OutSeg._End);
		//wracamy do wyjsciowego ukladu
		ChangeStartOfCordSysForSegment(InSeg,-O);
		ChangeStartOfCordSysForSegment(OutSeg,-O);
		//tworzymy sciezke wynikowa
		ResultListOfSegments.push_back(InSeg);
		ResultListOfSegments.push_back(OutSeg);
	}else{
	MiddleSeg=Segment(Coordinates(0.0,0.0),Coordinates(R*cos(fi3),R*sin(fi3)));
	//tworzenie stycznej do srodkowego promienia
	ToMiddleSeg=FindLinePerpendicularToPoint(MiddleSeg,MiddleSeg._End);

	//Szukamy lamanej zawierajacej cala trase
		//najpierw trzeba znalezc punkty przeciecia stworzonych prostych
	InSeg=Segment(InSeg._Start,FindCrossPointBetweenSegments(ToInSeg,ToMiddleSeg));
	MiddleSeg=Segment(InSeg._End,FindCrossPointBetweenSegments(ToMiddleSeg,ToOutSeg));
	OutSeg=Segment(MiddleSeg._End,OutSeg._End);
	//wracamy do wyjsciowego ukladu
	ChangeStartOfCordSysForSegment(InSeg,-O);
	ChangeStartOfCordSysForSegment(MiddleSeg,-O);
	ChangeStartOfCordSysForSegment(OutSeg,-O);

	//Mamy juz trzy segmenty wiec tworzymy sciezke



	ResultListOfSegments.push_back(InSeg);
	ResultListOfSegments.push_back(MiddleSeg);
	ResultListOfSegments.push_back(OutSeg);
	}

return ResultListOfSegments;


}

void Agent::ChangeStartOfCordSysForSegment
	(Segment & OneSegment, Coordinates Into)
{
OneSegment._Start=Coordinates(OneSegment._Start._x-Into._x,OneSegment._Start._y-Into._y);
OneSegment._End=Coordinates(OneSegment._End._x-Into._x,OneSegment._End._y-Into._y);
OneSegment._XParamB=OneSegment._Start._x;
OneSegment._YParamB=OneSegment._Start._y;
}

void Agent::ChangeStartOfCordSysForSegment
(list<Segment> & ListOfSegments, Coordinates Into)
{
	list<Segment>::iterator ListIter=ListOfSegments.begin();
	for(;ListIter!=ListOfSegments.end();ListIter++){
		ChangeStartOfCordSysForSegment
			((*ListIter), Into);
	}

}

Segment Agent::FindLinePerpendicularToPoint(Segment OneSegment, Coordinates Point)
{
Segment ResultSegment;
double t;
ResultSegment._XParamA=-1.0*OneSegment._YParamA;
ResultSegment._YParamA=OneSegment._XParamA;
//t=(Point._x-OneSegment._XParamB)/OneSegment._XParamA;
//ResultSegment._XParamB=Point._x-ResultSegment._XParamA*t;
//t=(Point._y-OneSegment._YParamB)/OneSegment._YParamA;
//ResultSegment._YParamB=Point._y-ResultSegment._YParamA*t;
ResultSegment._XParamB=Point._x;
ResultSegment._YParamB=Point._y;
ResultSegment._Start=Coordinates(Point._x,Point._y);
ResultSegment._End=Coordinates(Point._x,Point._y);
//pamietaj ze _Start i _End nie jest ustawione
return ResultSegment;

}

Coordinates Agent::FindCrossPointBetweenSegments(Segment Seg1,Segment Seg2)
{

	double y=0;
	double x=0;
if(Seg1._XParamA*Seg2._XParamA==0.0){
	if((Seg2._XParamA==0.0)&&(Seg1._XParamA==0.0)){
		cerr<<"Proste rownolegle lub proste nie przecinaja sie"<<endl;
		exit(1);
	}else if(Seg2._XParamA==0.0){
		x=Seg2._XParamB;
		y=(x-Seg1._XParamB)/Seg1._XParamA*Seg1._YParamA+Seg1._YParamB;
	}else{
		x=Seg1._XParamB;
		y=(x-Seg2._XParamB)/Seg2._XParamA*Seg2._YParamA+Seg2._YParamB;
	}

}else if(Seg1._YParamA*Seg2._YParamA==0.0){
	if((Seg2._YParamA==0.0)&&(Seg1._YParamA==0.0)){
		cerr<<"Proste rownolegle lub proste nie przecinaja sie"<<endl;
		exit(1);
	}else if(Seg2._YParamA==0.0){
		y=Seg2._YParamB;
		x=(y-Seg1._YParamB)/Seg1._YParamA*Seg1._XParamA+Seg1._XParamB;
	}else{
		y=Seg1._YParamB;
		x=(y-Seg2._YParamB)/Seg2._YParamA*Seg2._XParamA+Seg2._XParamB;
	}

}else{
	y=((Seg2._YParamA*Seg1._XParamA)/(Seg1._YParamA*Seg2._XParamA)*-Seg1._YParamB+
				(Seg2._YParamA)/(Seg2._XParamA)*(Seg1._XParamB-Seg2._XParamB)+Seg2._YParamB)
				/(1.0-(Seg2._YParamA*Seg1._XParamA)/(Seg1._YParamA*Seg2._XParamA));
	x=(Seg1._XParamA)/(Seg1._YParamA)*(y-Seg1._YParamB)+Seg1._XParamB;
}
	Coordinates ResultCoordinates(x,y);
return ResultCoordinates;

}


Coordinates Agent::CoordinatesToSquare(Coordinates C, double SquareLength)
{
	Coordinates SquareCoordinates;
	double SquareX,SquareY;
	SquareX=floor(C._x / SquareLength);
		//if((C._x / SquareLength)==SquareX)//jezeli na granicy kwadratow
			//if(ListIter->_XParamA<0)//jezeli pochodna ujemna
				//SquareX--;
	SquareY=floor(C._y / SquareLength);
		//if((C._y / SquareLength)==SquareY)//jezeli na granicy kwadratow
			//if(ListIter->_YParamA<0)//jezeli pochodna ujemna
				//SquareY--;

	SquareCoordinates=Coordinates(SquareX,SquareY);

	return SquareCoordinates;
}
void Agent::DoSthWhenIAmWaitingToEnterSquare(){};
void Agent::DoSthWhenIAmLeavingSquare(){};

void Agent::DoSthWhenIAmWaitingForAnotherAgent(){};

//funkcja zmienia cie¿kê agenta, który jako pierwszy bêdzie w kwadracie
void Agent::Coordinate_Admin()
{
	double SquareX, SquareY;

	SquareX=floor(_ActualPosition._x/_SquareLength);
	SquareY=floor(_ActualPosition._y/_SquareLength);

	//ustawienie siê agenta w œrodku kwadratu
	//wskaŸnik do listy segmentów
	list<Segment>::iterator ListIter=_ListOfSegments.begin();

	//ustawienie wskaŸnika na aktualnie realizowany odcinek trasy
	std::advance(ListIter,_SegmentNo);

	//zmiana parametrów aktualnie realizowanego odcinka trasy
	ListIter->_Start._x=SquareX;
	ListIter->_Start._y=SquareY;
	ListIter->_End._x=_SquareLength/2;
	ListIter->_End._y=_SquareLength/2;

	//zmiana parametrów nastêpnego odcinka trasy
	std::advance(ListIter,_SegmentNo+1);
	ListIter->_Start._x=_SquareLength/2;
	ListIter->_Start._y=_SquareLength/2;
}

//funkcja zmieniaj¹ca trasê agenta, który jako drugi wjedzie do kwadratu
void Agent::Coordinate_User()
{
	double InTime=0,OutTime=0,TempTime=0,SquareX,SquareY;
	double LocalStartX=0,LocalStartY=0,LocalEndX=0,LocalEndY=0;
	double InX,InY,OutX,OutY;
	double a,b,c,xO,yO;
	double r=(_MyRadius+anotherRadius)*sqrt(2);
	bool ColisionFound=false,SquareResolved=false,EndOfSegInCircle=false;
	bool OnlyInPoint=false;
	int NumOfRoots=0,CornerIter=0;
	Coordinates ActualPos,ActualPosNext;
	list<Segment> ResultListOfSegments;
	list<Segment> TempListOfSegments;

	list<Segment>::iterator ListIter=_ListOfSegments.begin();
	for(;ListIter!=_ListOfSegments.end();ListIter++){

	}
}
