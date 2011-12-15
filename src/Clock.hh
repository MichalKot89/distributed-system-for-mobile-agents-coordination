/*!
 *\file Clock.hh
 *\author Michal Wcislo
 *\date 15.12.2011
 *\version 1.0
 *\brief Zawiera opis klasy Clock
 *
 *Zawiera opis klasy Clock
 *
 *
 */

#ifndef CLOCK_HH_
#define CLOCK_HH_
/*!
 *
 * \class Clock
 * \brief Klasa opsiujaca obiekt zegarka
 *
 * Klasa opsiujaca obiekt zegarka. Moze zostac wykorzystna do
 * powiazania ruchu agenta z czasem rzeczywistym
 */
class Clock {
public:

	/*!
	 *\brief Konstruktor bezparametryczny klasy Clock
	 *
	 * Konstruktor bezparametryczny klasy Clock.
	 *
	 */
	Clock();
	/*!
	 *\brief Konstruktor parametryczny klasy Clock
	 *
	 * Konstruktor klasy Clock. Ustawia pola klasy zgodnie z podanym
	 * parametrem kroku zegara.
	 *
	 */
	Clock(double TimeStep);
	/*!
	 *\brief Procedura odmierzajaca krok zegara
	 *
	 * Procedura odmierzajaca krok zegara. Czas odmierzany jest poprzez
	 * uspienie programu na zadany czas (usleep()).
	 *
	 */
	void TickTack();
	/*!
	 *\brief Funkcja zwracajaca aktualny czas od poczatku istnienia zegara
	 *
	 * Funkcja zwracajaca aktualny czas od poczatku istnienia zegara.
	 *
	 */
	double GiveActualTime();
	/*!
	 *\brief Funkcja zwracajaca krok zegara
	 *
	 * Funkcja zwracajaca krok zegara.
	 *
	 */
	double GiveTimeStep();
	virtual ~Clock();

private:
	double _TimeStep;///< krok zegara
	double _Time;///< Czas globalny
    unsigned int _TimeStepInUSecs; ///< czas kroku w mikrosekundach
};

#endif /* CLOCK_HH_ */
