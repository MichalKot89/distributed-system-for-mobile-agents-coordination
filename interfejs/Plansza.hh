#ifndef PLANSZA_H
#define PLANSZA_H

#include <iostream>
#include <list>
#include <vector>
#include "Segment.hh"
#include "Coordinates.hh"

using namespace std;

class Plansza {
public:
    int _ileKwadratow; // okresla rozmiar szachownicy
    list<int> **_lista; // dwuwymiarowa tablica list (zawiera nr ID agentow przebywajacych w danym kwadracie
    vector<Coordinates> _Agenci; // tab zawieraja nr wszystkich agentow na planszy oraz ich polozenie x,y w globalnym ukladzie
    vector<list<Segment> > _TrasyAgentow;//int k; // pom - aktualna liczba agentow
    double _size;
    int _segments;

        void ustalRozmiar(int segments);
        void add(int ID, double x, double y);
        bool check(int ID);
	int index(double x);
	void zajmij(int ID, int x, int y);
	void odblokuj(int ID, int x, int y);
	int admin(int x, int y);
	bool czyPusta(int x, int y);
        void aktualizuj(std::vector<Coordinates> coords);
	

	Plansza(){}
	Plansza(double size, int segments);
	~Plansza();
};
#endif // PLANSZA_HH
