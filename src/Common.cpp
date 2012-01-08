#include <iostream>
#include "Common.hh"

using namespace std;

/*!
 * \brief Wyświetla komunika błędu
 *
 * Funkcja wyświetla komunikat błędu na wyjściu \e stderr.
 * \param Msg - (\b we.) wskaźnik na wyświetlany komunikat.
 * \pre Parameter \e Msg musi zawierać adres poprawnego ciągu
 *      tekstowego w sensie języka C. Nie może zawierać adresu \p NULL.
 * \return Zawsze zwracana jest wartość false.
 */
bool ErrorMesg(const char* Msg)
{
    cerr << Msg << endl;
    return false;
}

/*!
 * \brief Wyświetla komunika błędu
 *
 * Funkcja wyświetla komunikat błędu na wyjściu \e stderr.
 * \param Msg - (\b we.) wskaźnik na wyświetlany komunikat.
 * \param Obj - (\b we.) wskaźnik na ciąg znaków do których odnosi się
 *              komunikat.
 * \pre Parameter \e Msg musi zawierać adres poprawnego ciągu
 *      tekstowego w sensie języka C. Nie może zawierać adresu \p NULL.
 * \return Zawsze zwracana jest wartość false.
 */
bool ErrorMesg(const char* Msg, const char* Obj)
{
    cerr << Msg << Obj <<  endl;
    return false;
}
