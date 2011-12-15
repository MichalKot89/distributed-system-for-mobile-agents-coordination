/*!
 *\file Coordinates.hh
 *\author Michal Wcislo
 *\date 15.12.2011
 *\version 1.0
 *\brief Zawiera opis klasy Coordinates
 *
 *Zawiera opis klasy Coordinates
 *
 *
 */

#ifndef COORDINATES_HH_
#define COORDINATES_HH_

/*!
 *
 * \class Coordinates
 * \brief Klasa opisujaca wspolrzedne w dwuwymiarowym ukladzie
 *
 * Klasa opisujaca wspolrzedne w dwuwymiarowym ukladzie.
 *
 */
class Coordinates {
public:
	double _x,_y;///< wspolrzedne obiektu w przestrzeni dwuwymiarowej
	Coordinates(){};
	Coordinates(double x, double y);
	~Coordinates();
	Coordinates operator -()const;
	Coordinates & operator +=(const Coordinates & C);
	bool operator !=(const Coordinates & C);
	bool operator ==(const Coordinates & C);

};

#endif /* COORDINATES_HH_ */
