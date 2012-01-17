#include <iostream>
#include <list>
#include "Plansza.hh"
#include <cmath>


using namespace std;

Plansza::Plansza(double size, int segments) {
	_size = size;
	_segments = segments;

	_lista = new list<int>*[_segments];
	for(int i=0;i<_segments;i++) 
		_lista[i] = new list<int>[_segments];
}

void Plansza::ustalRozmiar(int segments){
	_segments = segments;
	_lista = new list<int>*[_segments];
	for(int i=0;i<_segments;i++) 
		_lista[i] = new list<int>[_segments];
}

Plansza::~Plansza() {
        _Agenci.clear();
}

void Plansza::add(int ID, double x, double y) {
                _Agenci.at(ID)._x=x;
                _Agenci.at(ID)._y=y;
}

bool Plansza::check(int ID) {
                if(_Agenci.at(ID)._x==0 && _Agenci.at(ID)._y==0)
                        return false;
                else
                    return true;
}

int Plansza::index(double x) {
	return int(floor(x/(_size/_segments)));
}

// x,y - polozenia danego kwadratu w szachownicy
void Plansza::zajmij(int ID, int x, int y) {
	if(_lista[x][y].size() == 1) {
	_lista[x][y].push_back(ID);
	_lista[x][y].sort();
	////////////////////
	// UNIKNIJ KOLIZJI!
	////////////////////
	}
	if(_lista[x][y].size() > 1) {
	////////////////////
	// ZACZEKAJ NA WOLNE MIEJSCE
	////////////////////
	}
	else {
		_lista[x][y].push_back(ID);
		_lista[x][y].sort();
	}
}

void Plansza::odblokuj(int ID, int x, int y) {
	_lista[x][y].remove(ID);
}

// wybiera zarzadce
int Plansza::admin(int x, int y) {
        return _lista[x][y].back();
}


bool Plansza::czyPusta(int x, int y) {
	if(_lista[x][y].empty() == true)
		return true;
	else
		return false;
}

void Plansza::aktualizuj(std::vector<Coordinates> coords) {

    for(int i = 0; i < _Agenci.size(); ++i)
        add(i,coords.at(i)._x,coords.at(i)._y);
    //for(vector<Coordinates>::iterator iter = _Agenci.begin(); iter != _Agenci.end(); ++iter)
        //iter->
}








