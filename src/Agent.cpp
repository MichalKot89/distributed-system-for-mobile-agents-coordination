/*
 * Agent.cpp
 *
 *  Created on: 27-10-2011
 *      Author: michal
 */

#include "Agent.hh"
//#include "GnuplotInc.hh"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <cmath>
#include <ctime>

//#define PanicProgramming 1


using namespace std;




Agent::Agent() : AgentBase() {
    _TimeStep = 0;
    _AgentsInSector = 0;
    _MyStatus = Moving;
    _ActualCommand = "NONE";
    _BoardWidth = 10;
    _BoardHeight = 10;
    _SquareLength = 2;
    _MySquare._x = rand()%_BoardWidth;   _MySquare._y = rand()%_BoardHeight;
    _ActualPosition._x = _MySquare._x * _SquareLength + 0.5*_SquareLength;
    _ActualPosition._y = _MySquare._y * _SquareLength + 0.5*_SquareLength;
    _MyNextSquare._x = -1;   _MyNextSquare._y = -1;
}

// Parametric constructor
Agent::Agent(list<Segment> ListOfSegments,double vel,double radius,double SquareLength,double TimeStep)
: AgentBase()
{
    //Agent();
    SetParameters(ListOfSegments, vel, radius, SquareLength, TimeStep);
}

// Set parameters
bool Agent::SetParameters(list<Segment> ListOfSegments,double vel,double radius,double SquareLength,double TimeStep)
{
        _ActualPosition=ListOfSegments.front()._Start;
        _MySquare=_MyNextSquare=CoordinatesToSquare(_ActualPosition,SquareLength);
        _SegmentNo=0;

        _MyVel=vel;
        _PathDone=false;
        _SquareLength=SquareLength;
        _MyRadius=radius;
        _MyStatus=Moving;
        cout<<"Jest1"<<endl;
        list<Segment>::iterator ListIter2=ListOfSegments.begin();
                for(;ListIter2!=ListOfSegments.end();ListIter2++){
                	_ListOfSegments.push_back(*ListIter2);
                }
                list<Segment>::iterator ListIter=_ListOfSegments.begin();
                for(;ListIter!=_ListOfSegments.end();ListIter++){
        cout<<ListIter->_Start._x<<" "<<ListIter->_Start._y<<" "
                        <<ListIter->_End._x<<" "<<ListIter->_End._y<<endl;
                }
                        cout<<"Jest5"<<endl;
        _ListOfSegments=ResolveForbiddenSectors(_ListOfSegments);
        SetVelocityToSegments();
        cout<<"Jest2"<<endl;

        ListIter=_ListOfSegments.begin();
        for(;ListIter!=_ListOfSegments.end();ListIter++){
cout<<ListIter->_Start._x<<" "<<ListIter->_Start._y<<" "
                <<ListIter->_End._x<<" "<<ListIter->_End._y<<endl;
        }
        cout<<"Jest3"<<endl;
        //DropActualPosition();
    std::cout << "Agent" << _MyID << ": ustawiono parametry" << std::endl;
    return true;
}

Agent::~Agent() {
        // TODO Auto-generated destructor stub
}


void Agent::Run()
{
	cout<<"Poza runem"<<endl;
	if(_MyStatus!=Finished){
		cout<<"W runie"<<endl;
    if (_ActualCommand != "NONE") {
        cerr << "Agent didn't managed to finish communication operation: Agent" << _MyID << endl
             << "   Actual command: " << _ActualCommand << endl;
        SetStatus(ERROR);
        return;
    }

        while(!_PathDone){
                //_MyClock.TickTack();
                if(Move()>Moving){
                        //czekanie
                        //PlotScene(5,3,_MyID);
                        //cout<<_MySquare._x<<" "<<_MySquare._y<<" Next: "<<_MyNextSquare._x<<" "<<_MyNextSquare._y<<endl;
                        //sleep(3);
                        _MyStatus=Moving;

                }

                        if(_SegmentNo>=(_ListOfSegments.size())){
                        _PathDone=true;
                    	_MyStatus=Finished;
                    	cout<<"ID:"<<_MyID<<" "<<"Trasa skonczona"<<endl;
                        }

                //cout<<"Actual TIme:"<<_MyClock.GiveActualTime()<<endl;
                //PlotScene(5,3,_MyID);
        }
       // PlotScene(5,3,_MyID);
    _MyTime += _TimeStep;
    /************* Przyklad sposobu dzialania *******************/
    switch (_MyStatus) {
    case Moving:
        SetStatus( Move() );
        break;
    case InterestChecking:
        if (--_AvailableNumOfCycles <= 0)
            SetStatus( WaitingToEnterSquare );
        else Move();
        break;
    case PlaceInSectorChecking:
        if (--_AvailableNumOfCycles <= 0)
            SetStatus( WaitingToEnterSquare );
        else Move();
        break;
    case Finished:

        break;
    default:
        break;
    }
    if(_SegmentNo>=(_ListOfSegments.size())){
    _PathDone=true;
	_MyStatus=Finished;
	cout<<"ID:"<<_MyID<<" "<<"Trasa3 skonczona"<<endl;
#ifdef MWDEBUG
	exit(1);
#endif
    }
    //std::cout << "Agent: " << _MyID << " Time: " << _MyTime << " Status: " << _MyStatus << std::endl;
	}
}

Agent::Status Agent::Move()
{
        double FinalX,FinalY,timeToCrossSqare,timeToLeaveSqare;
        double EstimatedTimeToEndX,EstimatedTimeToEndY,EstimatedTimeToEnd;
        Status ActualStatus=_MyStatus;
        int ModX,ModY;

if((_MyStatus!=WaitingToEnterSquare)&&(_MyStatus!=WaitingToBypass)){


        _MySquare=CoordinatesToSquare(_ActualPosition, _SquareLength);

        if(_MyStatus==LeavingSqare){
//Jakas funkcja interakcji
        _MyStatus=Moving;
#ifdef PanicProgramming
                        if(_SegmentNo>=(_ListOfSegments.size())){
                        _PathDone=true;
                    	_MyStatus=Finished;
                    	cout<<"ID:"<<_MyID<<" "<<"Trasa skonczona"<<endl;
                        }
#endif
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
if((timeToCrossSqare<_TimeStep) &&(timeToCrossSqare>0.0)){
        FinalX=ListIter->_XParamA*timeToCrossSqare+ListIter->_XParamB;
        FinalY=ListIter->_YParamA*timeToCrossSqare+ListIter->_YParamB;
        _ActualPosition=Coordinates(FinalX,FinalY);


        //ustalanie wspolrzednych kolejnego kwadratu
        _MyNextSquare+=Coordinates(ModX,ModY);
        //zmiana statusu
        _MyStatus=ActualStatus=WaitingToEnterSquare;
#ifdef PanicProgramming
                        if(_SegmentNo>=(_ListOfSegments.size())){
                        _PathDone=true;
                    	_MyStatus=Finished;
                    	cout<<"ID:"<<_MyID<<" "<<"Trasa skonczona"<<endl;
                        }
#endif
}else if((timeToLeaveSqare<_TimeStep) &&(timeToLeaveSqare>0.0)){
        FinalX=ListIter->_XParamA*timeToLeaveSqare+ListIter->_XParamB;
        FinalY=ListIter->_YParamA*timeToLeaveSqare+ListIter->_YParamB;
        _ActualPosition=Coordinates(FinalX,FinalY);
        //zwolnienie kwadratu
        //Jakas funkcja interakcji
if(_MySquare!=_MyNextSquare)//sytuacja w ktorej agent tylko na chwile, czescia
        //wjezdza na kwadrat
        _MyNextSquare=_MySquare;

        _MyStatus=ActualStatus=LeavingSqare;
#ifdef PanicProgramming
                        if(_SegmentNo>=(_ListOfSegments.size())){
                        _PathDone=true;
                    	_MyStatus=Finished;
                    	cout<<"ID:"<<_MyID<<" "<<"Trasa skonczona"<<endl;
                        }
#endif
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
        if(EstimatedTimeToEnd<_TimeStep){
                _ActualPosition=ListIter->_End;
                _SegmentNo++;
            	cout<<"Segment:"<<_SegmentNo<<"Lista:"<<_ListOfSegments.size()<<endl;
                //Jezeli cala sciezka
#ifdef PanicProgramming
                        if(_SegmentNo>=(_ListOfSegments.size())){
                        _PathDone=true;
                    	_MyStatus=Finished;
                    	cout<<"ID:"<<_MyID<<" "<<"Trasa skonczona"<<endl;
                        }
#endif
        }else{

        FinalX=ListIter->_XParamA*_TimeStep+ListIter->_XParamB;
        FinalY=ListIter->_YParamA*_TimeStep+ListIter->_YParamB;
        _ActualPosition=Coordinates(FinalX,FinalY);
        }
        _MyStatus=ActualStatus=Moving;
#ifdef PanicProgramming
                        if(_SegmentNo>=(_ListOfSegments.size())){
                        _PathDone=true;
                    	_MyStatus=Finished;
                    	cout<<"ID:"<<_MyID<<" "<<"Trasa skonczona"<<endl;
                        }
#endif
}
        ListIter->_XParamB=_ActualPosition._x;
        ListIter->_YParamB=_ActualPosition._y;

        //DropActualPosition();

}else{
        //waiting
//Jakas funkcja interakcji
}

/*
    Status ActualStatus = _MyStatus;    int LotterySize = 100;
    int Lottery = rand() % LotterySize + 1;

    if (Lottery == LotterySize) {
        _MyNextSquare._x = _MySquare._x + rand() % 3 - 1;
        _MyNextSquare._y = _MySquare._y + rand() % 3 - 1;
        if (_MyNextSquare._x >= _BoardWidth || _MyNextSquare._x < 0) _MyNextSquare._x = _MySquare._x;
        if (_MyNextSquare._y >= _BoardHeight || _MyNextSquare._y < 0) _MyNextSquare._y = _MySquare._y;

        // Checks if next square is different from actual
        if (_MyNextSquare._x != _MySquare._x || _MyNextSquare._y != _MySquare._y) ActualStatus = InterestChecking;
    }*/
cout<<"ID:"<<_MyID<<"Pozycja:"<<_ActualPosition._x<<" "<<_ActualPosition._y<<endl;
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

	if(sqrt(pow(xO-LocalStartX,2.0)+pow(yO-LocalStartY,2.0))<(r-0.001)){//MWci numeric problems here

                CalculateCollisionPoints(*ListIter,r, Coordinates(LocalStartX,LocalStartY),Coordinates(xO,yO),InTime,OutTime);
                if((OutTime<0))
                        OutTime=InTime;

                LocalStartX=ListIter->_XParamA*OutTime+LocalStartX;
                LocalStartY=ListIter->_YParamA*OutTime+LocalStartY;
                ActualPos._x=ListIter->_XParamB=ListIter->_Start._x=LocalStartX+SquareX*_SquareLength;
                ActualPos._y=ListIter->_YParamB=ListIter->_Start._y=LocalStartY+SquareY*_SquareLength;
                ColisionFound=true;
                SquareResolved=true;
        }
        CornerIter++;
        }
        //ColisionFound=false;
        CornerIter=0;
        //koniec w zakazanym kole
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

if(sqrt(pow(xO-LocalEndX,2.0)+pow(yO-LocalEndY,2.0))<(r-0.001)){//NE
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
/*
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
*/

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


/**
Returns actual position of the Agent
*/
const Coordinates & Agent::GetActualPosition() const {
    return _ActualPosition;
}


/**
Sets new Agent's status and make connected with that operations
*/
bool Agent::SetStatus(Status NewStatus) {
    switch (NewStatus) {
    case Moving:
        _ActualCommand = "NONE";
        _MyStatus = NewStatus;
        break;
    case InterestChecking:
        if (_MyStatus == InterestChecking)
            break;
        else if (_MyStatus == InterestCollision) {}
        else
            _AvailableNumOfCycles = AV_NUM_OF_CYCLES;

        _MyStatus = InterestChecking;
        break;
    default:
        _MyStatus = NewStatus;
        break;
    }
    if(_SegmentNo>=(_ListOfSegments.size())){
    _PathDone=true;
	_MyStatus=Finished;
	cout<<"ID:"<<_MyID<<" "<<"Trasa skonczona"<<endl;
    }
    return true;
}


/**
Gets Agent's status
*/
AgentBase::Status Agent::GetStatus() const {
    return _MyStatus;
}

/**
Loads Agent's params from file
*/
bool Agent::LoadParams() const {
    if (_MyID <= 0)
        return false;

    cout << "Wczytuje parametry: Agent" << _MyID << endl;
    return true;
}


/**
React to Timer timeout event
*/
bool Agent::TimerTimeout(int TimerID, list <string> & OutputBuffer) {

    switch (TimerID) {
    case 0:                 // INTEREST
        if (_ActualCommand == "INTEREST") {
            cout << "INTEREST_Timer_Done: Agent" << _MyID << endl;
            cout << "TimerTimeout: " << "I have right to ask for place in sector: " << _MyNextSquare._x
                 << " " << _MyNextSquare._y << ": Agent" << _MyID << endl;
            SetStatus( PlaceInSectorChecking );
            OutputBuffer.push_front(StateMessage());
        } else return ErrorMesg("Not adequate timer to the INTEREST command");
        break;
    case 1:                 // PLACE
        if (_ActualCommand == "PLACE") {
            cout << "PLACE_Timer_Done: Agent" << _MyID << endl;
            cout << "TimerTimeout: " << "I am assingning sector: " << _MyNextSquare._x
                 << " " << _MyNextSquare._y << ": Agent" << _MyID << endl;
            _MySquare._x = _MyNextSquare._x;        _MySquare._y = _MyNextSquare._y;
            _ActualPosition._x = _MySquare._x * _SquareLength + 0.5*_SquareLength;
            _ActualPosition._y = _MySquare._y * _SquareLength + 0.5*_SquareLength;
            _MyNextSquare._x = -1;   _MyNextSquare._y = -1;

            SetStatus( Moving );    _AssignedSectors.push_back(SQUARE_TYPE(_MyNextSquare._x,_MyNextSquare._y));
        } else return ErrorMesg("Not adequate timer to the PLACE command");
        break;
    default:
        return ErrorMesg("Bad timer ID");
        break;
    }
    return true;
}


/**
Loads Agent's params from file
*/
// TODO trzeba dodać LeavingSqare
bool Agent::ProcessMessage(const std::string & Command, std::list <std::string> & OutputBuffer) {
        string CommandName;
        int AgentID, ReceiverID;
        int RowNum;
        int ColumnNum;
        string EndString;

        istringstream MessageStreamInput(Command);
        ostringstream MessageStreamOutput();

        // Answer for the command
        string ReturnedStr = MessageFitsToAgent(Command, CommandName, AgentID, RowNum, ColumnNum);
        if (ReturnedStr == "true") {
            cout << "ProcessMessage: " << CommandName << " " << AgentID << " "
                 << RowNum << " " << ColumnNum << ": Agent" << _MyID << endl;
            ReturnedStr = AnswerCommand(CommandName, AgentID);
            if (ReturnedStr == "NONE") {}
            else if (ReturnedStr == "FAIL") {return ErrorMesg ("Invalid answer to the command: ", CommandName.c_str()); }
            else OutputBuffer.push_back(ReturnedStr);

        } else if (ReturnedStr == "false") {
        } else return ErrorMesg(ReturnedStr.c_str());

        //cout << "!!!!!!!!!!!!!!!!!" << _MyID << endl;
        // React for the answer
        ReturnedStr = MessageFitsToAgent(Command, CommandName, AgentID, ReceiverID);
        if (ReturnedStr == "true") {
            cout << "ProcessMessage: " << CommandName << " " << AgentID << " "
                 << ReceiverID  << ": Agent" << _MyID << endl;
            if (CommandName == "I_AM_INTERESTED") {
                if (_ActualCommand == "INTEREST") {
                    SetStatus( InterestCollision );   OutputBuffer.push_back(StateMessage());
                    SetStatus( InterestChecking );
                } else return ErrorMesg("Invalid answer to the command. The real command was: ", _ActualCommand.c_str());
            } else if (CommandName == "I_AM_IN_SECTOR") {
                if (_ActualCommand == "PLACE") {
                    ++_AgentsInSector;
                } else return ErrorMesg("Invalid answer to the command. The real command was: ", _ActualCommand.c_str());
                if (_AgentsInSector >= NUM_OF_AGENTS_AVAILABLE) {
                    SetStatus( WaitingToEnterSquare );      _AgentsInSector = 0;    _ActualCommand = "NONE";
                }
            } else {
                return ErrorMesg ("Invalid answer to the command: ", CommandName.c_str());
            }
        } else if (ReturnedStr == "false") {
        } else return ErrorMesg(ReturnedStr.c_str());
        //cout << "!!!!!!!!!!!!!!!!!" << _MyID << endl;
    return true;
}


/**
  Checks whether command fits to the Agent
  */
string Agent::AnswerCommand(string & CommandName, int & AgentID) const {

    ostringstream MessageStreamOutput;
    if (CommandName == "INTEREST") MessageStreamOutput << "I_AM_INTERESTED"
                                                       << std::endl;
    else if (CommandName == "PLACE") MessageStreamOutput << "I_AM_IN_SECTOR" << std::endl;
    else if (CommandName == "DIFFERENTIATE") return "NONE";
    else return "FAIL";
    MessageStreamOutput << _MyID << std::endl;        // Agents ID
    MessageStreamOutput << AgentID << std::endl;        // Sender ID
    MessageStreamOutput << "END" << std::endl;
    return MessageStreamOutput.str();
}


/**
  Checks whether command fits to the Agent

  true - message concerns to current agent
  false - message doesn't concerns to current agent
  other - error statement
  */
string Agent::MessageFitsToAgent(const string & Message, string & CommandName, int & AgentID, int & RowNum, int & ColumnNum) const {
    string EndString;

    istringstream MessageStreamInput(Message);
    ostringstream MessageStreamOutput;

    MessageStreamInput >> CommandName;
    if (CommandName != "INTEREST" && CommandName != "PLACE" && CommandName != "DIFFERENTIATE")        return "false";

    MessageStreamInput >> AgentID;
    if (AgentID <= 0 || AgentID==_MyID) {
        MessageStreamOutput << "Not allowed Agent's' ID: " << Message.c_str() << std::endl; return MessageStreamOutput.str();
    }
    MessageStreamInput >> RowNum;
    if (RowNum < 0) {
        MessageStreamOutput << "Invalid row number: " << Message.c_str() << std::endl; return MessageStreamOutput.str();
    }
    MessageStreamInput >> ColumnNum;
    if (ColumnNum < 0) {
        MessageStreamOutput << "Invalid column number: " << ColumnNum << std::endl; return MessageStreamOutput.str();
    }
    MessageStreamInput >> EndString;
    if (EndString != "END") {
        MessageStreamOutput << "1Invalid end of command: " << Message.c_str() << endl; return MessageStreamOutput.str();
    }

    if (CommandName == "INTEREST" && _MyNextSquare._x == RowNum && _MyNextSquare._y == ColumnNum)
        return "true";
    else if (CommandName == "PLACE") {
        for (list<SQUARE_TYPE>::const_iterator it=_AssignedSectors.begin() ; it != _AssignedSectors.end(); ++it ) {
            if (it->_x == RowNum && it->_y == ColumnNum)    return "true";
        }
        return "false";
    } else return "false";
    return "true";
}


/**
  Checks whether command fits to the Agent
  */
string Agent::MessageFitsToAgent(const string & Message, string & CommandName, int & AgentID, int & ReceiverID) const {
    string EndString;

    istringstream MessageStreamInput(Message);
    ostringstream MessageStreamOutput;

    MessageStreamInput >> CommandName;
    if (CommandName != "I_AM_INTERESTED" && CommandName != "I_AM_IN_SECTOR")       return "false";

    MessageStreamInput >> AgentID;
    if (AgentID <= 0 || AgentID == _MyID)  {
        MessageStreamOutput << "Invalid Agent's' ID: " << Message.c_str() << std::endl; return MessageStreamOutput.str();}
    MessageStreamInput >> ReceiverID;
    // This Agent is not a right receiver so we don't want to print errors
    if (ReceiverID!=_MyID) {MessageStreamOutput << "false"; return MessageStreamOutput.str();}
    MessageStreamInput >> EndString;
    if (EndString != "END") {MessageStreamOutput << "2Invalid end of command: " << endl; return MessageStreamOutput.str();}
    return "true";
}




/**
  Composes string message adequate to the actual state
  */
string Agent::StateMessage() {

    /************* Przyklad sposobu dzialania *******************/
    ostringstream MessageStream;

    switch (_MyStatus) {
    case Moving:
        MessageStream << "NONE";
    case InterestChecking:
    case WaitingToEnterSquare:
    case WaitingToBypass:
        // is there anybody who is interested in the sector?
        cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
        cout << "StageMessage: " << "I am interested in sector: " << _MyNextSquare._x
             << " " << _MyNextSquare._y << ": Agent" << _MyID << endl;
        MessageStream << "INTEREST" << endl;    // is there anybody who is interested in sector
        MessageStream << _MyID << endl;        // Agents ID
        MessageStream << _MyNextSquare._x << endl;        // Row number
        MessageStream << _MyNextSquare._y << endl;    // Colimn number
        MessageStream << "END";
        _ActualCommand = "INTEREST";
        break;
    case PlaceInSectorChecking:
        // is there anybody in the sector?
        cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
        cout << "StageMessage: " << "I am asking for the place in sector: " << _MyNextSquare._x
             << " " << _MyNextSquare._y << ": Agent" << _MyID << endl;
        MessageStream << "PLACE" << endl;
        MessageStream << _MyID << endl;        // Agents ID
        MessageStream << _MyNextSquare._x << endl;        // Row number
        MessageStream << _MyNextSquare._y << endl;    // Colimn number
        MessageStream << "END";
        _ActualCommand = "PLACE";
        break;
    case InterestCollision:
        // is there anybody in the sector?
        cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
        cout << "StageMessage: " << "Conflict of interest occured, sector: " << _MyNextSquare._x
             << " " << _MyNextSquare._y << ": Agent" << _MyID << endl;
        MessageStream << "DIFFERENTIATE" << endl;
        MessageStream << _MyID << endl;        // Agents ID
        MessageStream << _MyNextSquare._x << endl;        // Row number
        MessageStream << _MyNextSquare._y << endl;    // Colimn number
        MessageStream << "END" ;
        _ActualCommand = "DIFFERENTIATE";
        break;
    default:
        MessageStream << "FAIL";
        break;
    }

    return MessageStream.str();
}



#ifdef CREATE_LIBRARY
AgentBase * CreateAgent() {
    return new Agent();
}
#endif
