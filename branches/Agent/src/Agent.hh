/*!
 *\file Agent.hh
 *\author Michal Wcislo
 *\date 15.12.2011
 *\version 1.0
 *\brief Zawiera opis klasy Agent
 *
 *Zawiera opis klasy Agent
 *
 *
 */

#ifndef AGENT_HH_
#define AGENT_HH_

///komunikacji z Gnuplotem
#define PLOTDIR "../plots/" ///<sciezka do danych z wykresow
#define INFINITY 1000000000 ///< nieskonczonosc
#define MWDEBUG 1

#include "Segment.hh"
#include "Clock.hh"
#include <iostream>
#include <list>

/*!
 *
 * \class Agent
 * \brief Klasa opisujaca mobilnego agenta dzialajacego w srodowisku
 * systemu zdarzeniowego.
 *
 * Klasa opisuje podstawowe cechy agenta takie jak rozmiar, predkosc, status...
 * Dodatkowo klasa zawiera sciezke agenta i algorytmy interakcji pomiedzy innymi
 * agentami.
 */
class Agent {
public:
	/*!
	 * \enum Status
	 *
	 * \brief Typ wyliczeniowy opisujacy status agenta
	 */
	enum Status{Moving,LeavingSqare,WaitingToEnterSquare,WaitingToBypass};


static int _NumOfAgentsCreated; ///<Liczba stworzonych agentow
int _MyID;///< Numer ID agenta bedacy rowniez priorytetem agenta

double _MyRadius;///< promien agenta (agent jest kolem)
Status _MyStatus;///< status agenta
Coordinates _MySquare;///< kwadrat w ktorym obecnie znajduje sie agent
Coordinates _MyNextSquare;///< kwadrat na ktory agent ma zamiar wjechac
double _MyVel;///< predkosc wypadkowa agenta
Clock _MyClock;///< zegar agenta pozwalajacy na odniesienie do rzeczywistego czasu symulacji

std::list<Segment> _ListOfSegments;///< lista odcinkow w trasie agenta
int _SegmentNo;///< aktualnie realizowany odcinek trasy
double _SquareLength;///< dlugosc boku kwadratu bedacy sektorem w srodowisku symulatora
Coordinates _ActualPosition;///< globalna pozycja agenta




//Flagi
bool _PathDone;///< flaga trasy TRUE - trasa ukonczona, FALSE - odwrotnie

/*!
 *\brief Konstruktor parametryczny klasy agent
 *
 * Konstruktor tworzacy agenta w srodowisku systemu zdarzeniowego
 * \param ListOfSegments - wejsciowa lista odcinkow trasy
 * \param vel - predkosc agenta na calej trasie
 * \param radius - promien agenta
 * \param SquareLength - dlugosc boku kwadratu
 * \param TimeStep - dlugosc kroku symulacji
 */
	Agent(std::list<Segment> ListOfSegments,double vel,double radius,double SquareLength,double TimeStep);

	/*!
	 * \brief destruktor klasy Agent
	 *
	 */
	~Agent();

	/*!
	 * \brief Glowna procedura klasy agent bedaca realizacja istnienia agenta na scenie
	 *
	 * Glowna procedura klasy agent bedaca realizacja istnienia agenta na scenie
	 */
	void Run();
	/*!
	 * \brief Funkcja wykonująca ruch agenta zgodnie z zaplanowana sciezka
	 *
	 * Funkcja wykonująca ruch agenta zgodnie z zaplanowana sciezka. Zwraca status agenta
	 * po wykonaniu ruchu. Ruch jest wykonywany w czasie jednego kroku symulacji z zadana
	 * predkoscia. Ruch moze polegac także na poruszeniu sie do konca danego segmentu, do
	 * punktu wjazdu i wyjazdu z kwadratu, lub  moze sie nie wykonac w przypadku jezeli
	 * agent czeka na cos.
	 *
	 * \pre Funkcja może być wywolywana niezaleznie od warunkow, gdyz sama sprawdza warunki
	 * wykonywania ruchu
	 * \post Oprocz zmiany pozycji agenta _ActualPosition, funkcja moze zmienic status agenta
	 * _MyStatus, aktualnie realizowany odcinek trasy _SegmentNo, flage zakonczenia sciezki
	 * _PathDone,aktualny i nastepny kwadrat zajmowany przez agenta _MySquare,_MyNextSquare.
	 * Na koniec funkcja zapisuje aktualna pozycje agenta do pliku Agent(ID).dat .
	 *
	 */

	Status Move();

	/*!
	 * \brief Funkcja zwraca czas do momentu wkroczenia na sasiedni kwadrat
	 *
	 * Funkcja zwraca czas do momentu wkroczenia na sasiedni kwadrat. Wykorzystywana jest w
	 * procesie interakcji z innymi agentami do znalezienia momentu w ktorym agent powinien
	 * sie zatrzymac i wymienic informacje z innymi agentami
	 *
	 * \param ListIter - iterator wskazujacy na aktualnie realizowany odcinek trasy
	 * \param ModX - modyfikator wspolrzednych kwadratu w osi X, wykorzystywany w do obliczania
	 * wspolrzednych kwadratu na ktory agent ma zamiar wjechac.
	 * \param ModY - modyfikator wspolrzednych kwadratu w osi X, wykorzystywany w do obliczania
	 * wspolrzednych kwadratu na ktory agent ma zamiar wjechac.
	 *
	 */
	double GiveTimeToCrossSquare(std::list<Segment>::iterator ListIter,int& ModX,int& ModY);
	/*!
	 * \brief Funkcja zwraca czas do momentu calkowitego opuszczenia kwadratu
	 *
	 * Funkcja zwraca czas do momentu calkowitego opuszczenia kwadratu. Wykorzystywana jest w
	 * procesie interakcji z innymi agentami do znalezienia momentu w ktorym agent powinien
	 * zwolnic poprzednio zajmowany kwadrat
	 *
	 * \param ListIter - iterator wskazujacy na aktualnie realizowany odcinek trasy
	 *
	 *
	 */
	double GiveTimeToLeaveSquare(std::list<Segment>::iterator ListIter);
	/*!
	 * \brief Funkcja modyfikuje wejsciowa trase agenta tak aby omijala wierzcholki
	 * kwadratowych sektorów
	 *
	 * Funkcja modyfikuje wejsciowa trase agenta tak aby omijala wierzcholki
	 * kwadratowych sektorów. Zmodyfikowana trasa takze skalda sie z odcinkow.
	 *
	 * \param ListOfSegments - lista odcinkow tworzacych trase
	 * \pre ListOfSegments musi zawierac ciagla trase dla agenta
	 * \post Funkcja zwraca zmodyfikowana trase agenta
	 *
	 */
	std::list<Segment> ResolveForbiddenSectors(std::list<Segment> ListOfSegments);
	/*!
	 * \brief Procedura ustawia predkosc ruchu agenta poprzez zmiane funkcji ruchu
	 * w poszczegolnych segmentach trasy
	 *
	 * Procedura ustawia predkosc ruchu agenta poprzez zmiane funkcji ruchu
	 * w poszczegolnych segmentach trasy
	 *
	 *
	 */
	void SetVelocityToSegments();
	/*!
	 * \brief Procedura zapisuje aktualną pozycje agenta di pliku Agent(ID).dat
	 *
	 * Procedura zapisuje aktualną pozycje agenta di pliku Agent(ID).dat
	 *
	 *
	 */
	int DropActualPosition();
	/*!
	 * \brief Funkcja obliczajaca czas do wjazdu i wyjazdu z okregu o srodku w
	 * wierzcholku kwadratu
	 *
	 * Funkcja obliczajaca czas do wjazdu i wyjazdu z okregu o srodku w
	 * wierzcholku kwadratu. Zwraca ilosc punktow przecieca (0,1,2).
	 *
	 * \param S - odcinek trasy
	 * \param r - promien okregu
	 * \param Start - miejse startowe (poczatek ruchu)
	 * \param O - wspolrzedne srodka okregu (wierzcholka kwadratu)
	 * \param InTime - czas wjazdu(wyjazdu)
	 * \param OutTime - czas wyjazdu(wjazdu)
	 */
	static int CalculateCollisionPoints(Segment S,double r,Coordinates Start,Coordinates O, double & InTime, double & OutTime);
	/*!
	 * \brief Funkcja oblicza pierwiastki rownania kwadratowego
	 *
	 * Funkcja oblicza pierwiastki rownania kwadratowego.
	 *
	 * \param a,b,c - wspolczynniki rownania kwadratowego
	 * \param t1,t2 - pierwiastki rownania kwadratowego (wpisywane po
	 * wykonaniu obliczen)
	 */
	static int SquareEqRoots(double a,double b,double c,double &t1,double &t2);
	/*!
	 * \brief Funkcja zwraca trase omijajaca zakazany obszar (kolo) w
	 * wierzcholku kwadratu
	 *
	 * Funkcja zwraca trase omijajaca zakazany obszar (kolo) w
	 * wierzcholku kwadratu. Wygenerowana trasa omija zakazany obszar
	 * generujac lamana laczaca punkt wejscia i wyjscia na obszar
	 * niedozwolony.
	 *
	 * \param In - wspolrzedne wejscia na zakazane kolo
	 * \param Out - wspolrzedne wyjscia z zakazanego kola
	 * \param O - wspolrzedne srodka zakazanego kola
	 */
	static std::list<Segment> FindPathResolvingForbiddenSector
	(Coordinates In,Coordinates Out,Coordinates O);
	/*!
	 * \brief Procedura zmienia uklad wspolrzednych segmentu
	 *
	 * Procedura zmienia uklad wspolrzednych segmentu.
	 *
	 * \param OneSegment - zmieniany odcinek segment
	 * \param Into - wspolrzedne srodka ukladu do ktorego transformujemy
	 * segment (wzgledem obecnego ukladu)
	 */
	static void ChangeStartOfCordSysForSegment
	(Segment & OneSegment, Coordinates Into);
	/*!
	 * \brief Procedura zmienia uklad wspolrzednych listy segmentow
	 *
	 * Procedura zmienia uklad wspolrzednych listy segmentow.
	 *
	 * \param ListOfSegments - zmieniana lista segmentow
	 * \param Into - wspolrzedne srodka ukladu do ktorego transformujemy
	 * segment (wzgledem obecnego ukladu)
	 */
	static void ChangeStartOfCordSysForSegment
	(std::list<Segment> & ListOfSegments, Coordinates Into);
	/*!
	 * \brief Funkcja szuka odcinka (prostej) prostopadlej do zadanej
	 * prostej w punkcie
	 *
	 * Funkcja szuka odcinka (prostej) prostopadlej do zadanej
	 * prostej w punkcie.
	 *
	 * \param OneSegment - zadana prosta
	 * \param Point - punkt przeciecia
	 *
	 * \pre Point musi lezec na prostej OneSegment
	 * \post Zwracany segment NIE MA USTAWIONYCH PUNKTOW POCZATKOWEGO
	 * I KONCOWEGO!!!
	 */
	static Segment FindLinePerpendicularToPoint(Segment OneSegment, Coordinates Point);
	/*!
	 * \brief Funkcja szuka punktu przeciecia dwoch odcinkow (prostych)
	 *
	 * Funkcja szuka punktu przeciecia dwoch odcinkow (prostych). Zwraca
	 * wspolrzedne punktu przeciecia prostych.
	 *
	 * \param Seg1,Seg2 - badane segmenty
	 *
	 * \pre Segmenty nie moga byc rownolegle, jezeli sa, nastepuje przerwanie
	 * programu
	 *
	 */
	static Coordinates FindCrossPointBetweenSegments(Segment Seg1,Segment Seg2);
	/*!
	 * \brief Funkcja zamienia wspolrzedne globalne na wspolrzedne kwadratu
	 * w ktorym znajduje sie agent
	 *
	 * Funkcja zamienia wspolrzedne globalne na wspolrzedne kwadratu
	 * w ktorym znajduje sie agent.
	 *
	 * \param C - wspolrzedne na plaszczyznie globalnej
	 * \param SquareLength - dlugosc boku kwadratu
	 * \pre Nalezy pamietac,ze do danego kwadratu nalezy jego pole,
	 * lewy i dolny bok i wierzcholek laczacy dany kwadrat, pozostale trzy
	 * wierzcholki i dwa boki beda zaliczone do kolejnego kwadratu.
	 *
	 */
	static Coordinates CoordinatesToSquare(Coordinates C, double SquareLength);
};

#endif /* AGENT_HH_ */
