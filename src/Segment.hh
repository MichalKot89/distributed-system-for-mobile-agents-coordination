/*!
 *\file Segment.hh
 *\author Michal Wcislo
 *\date 15.12.2011
 *\version 1.0
 *\brief Zawiera opis klasy Segment
 *
 *Zawiera opis klasy Segment
 *
 *
 */

#ifndef SEGMENT_HH_
#define SEGMENT_HH_
#include "Coordinates.hh"
/*!
 *
 * \class Segment
 * \brief Klasa opisujaca odcienek(prosta) w przestrzeni dwuwymiarowej
 *
 * Klasa opisujaca odcienek(prosta) w przestrzeni dwuwymiarowej. Zostala
 * wykorzystana jako element skladowy trasy mobilnego agenta.
 */
class Segment {
public:
	Coordinates _Start;///< poczatek odcinka
	Coordinates _End;///< koniec odcinka
	double _XParamA,_XParamB;///< wspolczynniki rownania opisujacego ruch dla osi X=at+b
	double _YParamA,_YParamB;///< wspolczynniki rownania opisujacego ruch dla osi Y=at+b

	Segment(){};
	/*!
	 *\brief Konstruktor parametryczny klasy Segment
	 *
	 * Konstruktor tworzacy obiekt odcinka(prostej)
	 * \param start - poczatek odcinka
	 * \param end - koniec odcinka
	 * \post Tworzona trasa (odcinek trasy) jest opisana ruchem jednostajnym
	 * z wypadkowa predkoscia 1.
	 */
	Segment(Coordinates start,Coordinates end);
	~Segment();
	/*!
	 *\brief Funkcja pozwalajaca na zmiane predkosci ruchu w segmencie
	 *
	 * Funkcja pozwalajaca na zmiane predkosci ruchu w segmencie.
	 */
	void SetVelocity(double v);
};

#endif /* SEGMENT_HH_ */
