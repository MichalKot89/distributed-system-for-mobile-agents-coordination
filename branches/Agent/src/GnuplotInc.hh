/*!
 *\file GnuplotInc.hh
 *\author Michal Wcislo
 *\date 24.03.2011
 *\version 1.0
 *\brief Zawiera funkcje uzywane do rysowania wykresow uzywajac Gnuplot'a
 *
 *Zawiera funkcje uzywane do rysowania wykresow uzywajac Gnuplot'a
 *
 *
 */
#ifndef GNUPLOINC_HH_
#define GNUPLOINC_HH_
#include <fstream>

#define FIFO_FILE       "GNUPLOT" ///<Nazwa potoku FIFO wykorzystywanego do
///komunikacji z Gnuplotem
#define PLOTDIR "../plots/" ///<sciezka do danych z wykresow



/*!
 * \enum FileType
 *
 * \brief Typ wyliczeniowy grupujacy typy plikow wynikowych wykresow.
 *
 * Typ wyliczeniowy grupujacy typy plikow wynikowych wykresow.
 */
enum FileType
{
	none,///<brak pliku wyjsciowego
	eps,///< plik .eps
	png///< plik .png

};

/*!
 * \brief Procedura zapisuje wyrysowany wykres do pliku o podanym rozszerzeniu.
 *
 * Procedura zapisuje wyrysowany wykres do pliku o podanym rozszerzeniu.
 *
 * \param Strm - referencja na obiekt strumienia plikow (Potok FIFO)
 * \param PlotName - nazwa zapisywanego pliku
 * \param ext - rozszerzenie pliku, do ktorego wykres zostanie zapisany wartosc
 * 'none' powoduje opuszczenie procedury.
 * \param winid - identyfikator okna na ktorym ma byc rysowany wykres
 *
 */

void SavePlot(std::ofstream &Strm,char* PlotName,FileType ext,int winid);

/*!
 * \fn GnuplotInit
 *
 * \brief Procedura uruchamiajaca serwer, ktory dane z potoku przekazuje do
 * Gnuplota
 *
 * Procedura uruchamiajaca serwer, ktory dane z potoku przekazuje do
 * Gnuplota. W jej ciele uruchamiany jest program FIFOserv
 */
void GnuplotInit();

/*!
 * \fn GnuplotShutDown
 *
 * \brief Procedura konczaca dzialanie serwera FIFO
 *
 * Procedura konczaca dzialanie serwera FIFO. Zamkniecie programu powoduje
 * zamkniecie wszystkich stworzonych wykresow.
 *
 */
int GnuplotShutDown();

void GnuplotSceneClean();

int PlotScene(double SquareLength,int SceneSize,int AgentID);

/*!
 * \fn int BarPlot(double **T,int n, int m,int winid, FileType ext)
 *
 * \brief Funkcja wyswietla dane zawarte w tablicy T w formie wykresu slupkowego
 *
 * Funkcja wyswietla dane zawarte w tablicy T w formie wykresu slupkowego. Aby
 * pozwolic na poprawne wyswietlanie danych nalezy pamietac o zapewnienie
 * okreslonego czasu na odrysowanie wykresu.
 *
 * \param T - tablica z danymi
 * \param n - ilosc wierszy tablicy
 * \param m - ilosc kolumn tablicy
 * \param winid - identyfikator okna na ktorym ma byc rysowany wykres
 * \param ext - rozszerzenie pliku, do ktorego wykres zostanie zapisany wartosc
 * 'none' nie zapisuje pliku.
 */
int BarPlot(double **T,int n, int m,int winid, FileType ext);

/*!
 * \fn int ColMapPlot(double **T,int n, int m,double pa,double pb,double ka,
 *		double kb, int winid, FileType ext);
 *
 * \brief Funkcja wyswietla dane zawarte w tablicy T w formie trojwymiarowej.
 *
 * Funkcja wyswietla dane zawarte w tablicy T w formie trojwymiarowej. Aby
 * pozwolic na poprawne wyswietlanie danych nalezy pamietac o zapewnienie
 * okreslonego czasu na odrysowanie wykresu.
 *
 * \param T - tablica z danymi
 * \param n - ilosc wierszy tablicy
 * \param m - ilosc kolumn tablicy
 * \param pa - poczatek zakresu pierwszej zmiennej
 * \param pb - poczatek zakresu drugiej zmiennej
 * \param ka - koniec zakresu pierwszej zmiennej
 * \param kb - koniec zakresu drugiej zmiennej
 * \param winid - identyfikator okna na ktorym ma byc rysowany wykres
 * \param ext - rozszerzenie pliku, do ktorego wykres zostanie zapisany wartosc
 * 'none' nie zapisuje pliku.
 *
 */
int ColMapPlot(double **T,int n, int m,double pa,double pb,double ka,
		double kb, int winid, FileType ext);

/*!
 *
 *
 * \brief Funkcja wyswietla dane zawarte w tablicach a i b w odniesieniu do
 * wartosci ref w formie wykresu 2d.
 *
 * Funkcja wyswietla dane zawarte w tablicach a i b w odniesieniu do
 * wartosci ref w formie wykresu 2d. Aby pozwolic na poprawne wyswietlanie
 * danych nalezy pamietac o zapewnienie okreslonego czasu na odrysowanie wykresu.
 *
 * \param a - tablica z danymi
 * \param b - tablica z danymi
 * \param ra - rozmiar tablicy a
 * \param rb - rozmiar tablicy b
 * \param ref - wartosc odniesienia (np. wynik algorytmu Neh)
 * \param ref2 - druga wartosc odniesienia (np. benchmark)
 * \param winid - identyfikator okna na ktorym ma byc rysowany wykres
 * \param ext - rozszerzenie pliku, do ktorego wykres zostanie zapisany wartosc
 * 'none' nie zapisuje pliku.
 *
 */
int PerformPlot(int *a,int *b, int ra,int rb,int ref,int ref2,int winid, FileType ext);


#endif /* GNUPLOINC_HH_ */
