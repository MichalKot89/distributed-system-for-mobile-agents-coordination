#include "stdafx.h"
#include <iostream>
#include "conio.h"
#include <list>

using namespace std;

class Plansza {
public:
	int _ileKwadratow; // okresla rozmiar szachownicy
	list<int> **_lista; // dwuwymiarowa tablica list (zawiera nr ID agentow przebywajacych w danym kwadracie

	void dodaj(int x, int y, int ID);
	void usun(int x, int y, int ID);
	void wyswietl(int x, int y);
	void wyswietlSasiadow(int x, int y);
	bool czyPusta(int x, int y);
	void help();
	int wybierzZarzadce(int x, int y);

	Plansza(int ileKwadratow);
	~Plansza();
};

Plansza::Plansza(int ileKwadratow) {
	_ileKwadratow = ileKwadratow;
	_lista = new list<int>*[ileKwadratow];
	for(int i=0;i<ileKwadratow;i++)
		_lista[i] = new list<int>[ileKwadratow];
}

Plansza::~Plansza() {
}

void Plansza::dodaj(int x, int y, int ID){
	if(x >= _ileKwadratow && y >= _ileKwadratow)
		cout << "\nBledne wspolrzedne! Przekroczyles zakres.";
	else {
	if(_lista[x][y].size()<2) {
	_lista[x][y].push_back(ID);
	cout << "\n# Dodano element: " << ID << " do listy[" << x << "][" << y << "]\n";
	}
	else
		cout <<"\n# Lista [" << x << "][" << y << "] zawiera juz 2 agentow!\n";
	_lista[x][y].sort();  // sortuje liste by wybrac zarzadce
	}
	cout << "Twoj wybor: ";
}

void Plansza::usun(int x, int y, int ID) {
		if(_lista[x][y].empty()==false) {
			_lista[x][y].remove(ID);
			cout << "\nUsunieto agenta o nr ID " << ID << " z listy[" << x << "][" << y << "]\n";
		}
		else
			cout << "\nBlad! Lista[" << x << "][" << y << "] jest pusta!\n";
}

void Plansza::wyswietl(int x, int y) {
		if(_lista[x][y].empty() == false) {
			list<int>::iterator it;
			for(it=_lista[x][y].begin();it!=_lista[x][y].end();it++) {
				cout << "\n# Zawartosc listy[" << x << "][" << y << "] : " << *it << " ";
				cout << "\n";
			}
	}
	else
		cout << "\nLista [" << x << "][" << y << "] jest pusta!\n";
}

void Plansza::wyswietlSasiadow(int x, int y) {
	list<int>::iterator it;
	// gorny sasiad
	if(y+1 <= _ileKwadratow-1) {
	for(it=_lista[x][y+1].begin();it!=_lista[x][y+1].end();it++) {
				cout << "\n# Zawartosc listy[" << x << "][" << y+1 << "] : " << *it << " ";
				cout << "\n";
			}
	}
	// dolny sasiad
	if(y-1 >= 0) {
	for(it=_lista[x][y-1].begin();it!=_lista[x][y-1].end();it++) {
				cout << "\n# Zawartosc listy[" << x << "][" << y-1 << "] : " << *it << " ";
				cout << "\n";
			}
	}
	// lewy sasiad
	if(x-1 >= 0) {
	for(it=_lista[x-1][y].begin();it!=_lista[x-1][y].end();it++) {
				cout << "\n# Zawartosc listy[" << x-1 << "][" << y << "] : " << *it << " ";
				cout << "\n";
			}
	}
	// prawy sasiad
	if(x+1 <= _ileKwadratow-1) {
	for(it=_lista[x+1][y].begin();it!=_lista[x+1][y].end();it++) {
				cout << "\n# Zawartosc listy[" << x+1 << "][" << y << "] : " << *it << " ";
				cout << "\n";
			}
	}
	// lewy - gorny sasiad
	if(x-1 >=0 && y+1 <= _ileKwadratow-1) {
	for(it=_lista[x-1][y+1].begin();it!=_lista[x-1][y+1].end();it++) {
				cout << "\n# Zawartosc listy[" << x-1 << "][" << y+1 << "] : " << *it << " ";
				cout << "\n";
			}
	}
	// prawy - gorny sasiad
	if(x+1 <= _ileKwadratow-1 && y+1 <= _ileKwadratow-1) {
	for(it=_lista[x+1][y+1].begin();it!=_lista[x+1][y+1].end();it++) {
				cout << "\n# Zawartosc listy[" << x+1 << "][" << y+1 << "] : " << *it << " ";
				cout << "\n";
			}
	}
	// lewy - dolny sasiad
	if(x-1 >= 0 && y-1 >=0) {
	for(it=_lista[x-1][y-1].begin();it!=_lista[x-1][y-1].end();it++) {
				cout << "\n# Zawartosc listy[" << x-1 << "][" << y-1 << "] : " << *it << " ";
				cout << "\n";
			}
	}
	// prawy - dolny sasiad
	if(x+1 <= _ileKwadratow-1 && y-1 >=0) {
	for(it=_lista[x+1][y-1].begin();it!=_lista[x+1][y-1].end();it++) {
				cout << "\n# Zawartosc listy[" << x+1 << "][" << y-1 << "] : " << *it << " ";
				cout << "\n";
			}
	}
}

bool Plansza::czyPusta(int x, int y) {
	if(_lista[x][y].empty() == true)
		return true;
	else
		return false;
}

void Plansza::help() {
	cout << "\n#####   MENU   #####\n";
	cout << "# q - wyjscie\n";
	cout << "# h - help\n";
	cout << "# d - dodaj agenta do listy\n";
	cout << "# u - usun agenta z listy\n";
	cout << "# w - wyswietl liste agentow z 1 pola\n";
	cout << "# v - wyswietl agentow sasiadujacych z tym polem\n";
	cout << "# c - sprawdz czy dane pole jest zajete\n";
	cout << "# z - wybierz zarzadce\n";
	cout << "###################################################\n";
	cout << "Twoj wybor: ";
}

int Plansza::wybierzZarzadce(int x, int y) {
	return _lista[x][y].back();
}


int main()
{
	int rozmiar; // rozmiar szachownicy
	int x,y,ID;
	char opcja;
	cout << "#####   ZARZADZANIE PLANSA   #####\n";
	cout << "#       Podaj rozmiar szachownicy: ";
	cin >> rozmiar;
	Plansza p(rozmiar);
	cout << "\n#       Stworzono plansze o wymiarach: " << p._ileKwadratow << " x " << p._ileKwadratow << "\n";

	p.help();
	do {
		cin >> opcja;
		switch(opcja) {
			case 'd' :
				cout << "\nPodaj wspolrzedne listy oraz nr ID agenta formatu: x y ID\n";
				cin >> x >> y >> ID;
				p.dodaj(x,y,ID);
				break;
			case 'h' :
				p.help();
				break;
			case 'c' :
				cout << "\nPodaj wspolrzedne listy formatu: x y\n";
				cin >> x >> y ;
				if(x >= p._ileKwadratow || y >= p._ileKwadratow) {
					cout << "\nBledne wspolrzedne! Przekroczyles zakres.";
					break;
				}
				else {
				if(p.czyPusta(x,y)==true)
					cout << "\nLista[" << x << "][" << y << "] jest pusta!\n";
				else
					cout << "\nLista[" << x << "][" << y << "] nie jest pusta! (" << p._lista[x][y].size() << " agent(ow))\n";
				}
				cout << "Twoj wybor: ";
				break;
			case 'w' :
				cout << "\nPodaj wspolrzedne listy formatu: x y\n";
				cin >> x >> y;
				if(x >= p._ileKwadratow || y >= p._ileKwadratow) {
					cout << "\nBledne wspolrzedne! Przekroczyles zakres.";
					break;
				}
				else
					p.wyswietl(x,y);
				cout << "\nTwoj wybor: ";
				break;
			case 'u' :
				cout << "\nPodaj wspolrzedne listy oraz nr ID agenta formatu: x y ID\n";
				cin >> x >> y >> ID;
				if(x >= p._ileKwadratow || y >= p._ileKwadratow) {
					cout << "\nBledne wspolrzedne! Przekroczyles zakres.";
					break;
				}
				else
					p.usun(x,y,ID);
				cout << "Twoj wybor: ";
				break;
			case 'z' :
				cout << "\nPodaj wspolrzedne listy formatu: x y\n";
				cin >> x >> y;
				if(x >= p._ileKwadratow || y >= p._ileKwadratow) {
					cout << "\nBledne wspolrzedne! Przekroczyles zakres.";
					break;
				}
				else {
					if(p._lista[x][y].size() == 2)
						cout << "\nZarzadca zostal agent o nr ID: " << p.wybierzZarzadce(x,y);
					else
						cout << "\nBrak zarzadcy! (mniej niz 2 agentow)";
				}
				cout << "\nTwoj wybor: ";
				break;
			case 'v' :
				cout << "\nPodaj wspolrzedne listy formatu: x y\n";
				cin >> x >> y;
				if(x >= p._ileKwadratow || y >= p._ileKwadratow) {
					cout << "\nBledne wspolrzedne! Przekroczyles zakres.";
					break;
				}
				else
					p.wyswietlSasiadow(x,y);
				cout << "\nTwoj wybor: ";
				break;
		default: cout << "\nNierozpoznana opcja!\n";
			break;
		}
	}while(opcja!='q');

	return 0;
}

