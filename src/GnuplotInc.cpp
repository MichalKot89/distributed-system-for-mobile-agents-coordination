/*!
 *\file GnuplotInc.cpp
 *\author Michal Wcislo
 *\date 24.03.2011
 *\version 1.0
 *\brief Zawiera funkcje uzywane do rysowania wykresow uzywajac Gnuplot'a
 *
 *Zawiera funkcje uzywane do rysowania wykresow uzywajac Gnuplot'a
 *
 *
 */
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include "GnuplotInc.hh"

using namespace std;

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

void SavePlot(ofstream &Strm,char* PlotName,FileType ext,int winid)
{
        switch(ext){
        case none:
                break;
        case eps:
                Strm<<"set terminal postscript eps enhanced color"<<endl;
                Strm<<"set output '"<<PLOTDIR<<PlotName<<winid<<".eps'"<<endl;
                Strm<<"replot"<<endl;
                break;
        case png:
                Strm<<"set terminal png"<<endl;
                Strm<<"set output '"<<PLOTDIR<<PlotName<<winid<<".png'"<<endl;
                Strm<<"replot"<<endl;
                break;




        }

        Strm<<"set term x11 "<<winid<<endl;
        Strm<<"unset output "<<endl<<endl;


}

/*!
 * \fn GnuplotInit
 *
 * \brief Procedura uruchamiajaca serwer, ktory dane z potoku przekazuje do
 * Gnuplota
 *
 * Procedura uruchamiajaca serwer, ktory dane z potoku przekazuje do
 * Gnuplota. W jej ciele uruchamiany jest program FIFOserv
 */
void GnuplotInit()
{
        system("rm GNUPLOT");
        system("./FIFOserv | gnuplot &");

}

void GnuplotSceneClean()
{
        ofstream Strm;
        Strm.open("../plots/todel.dat");
        Strm.close();
        system("rm ../plots/*.dat");
}

/*!
 * \fn GnuplotShutDown
 *
 * \brief Procedura konczaca dzialanie serwera FIFO
 *
 * Procedura konczaca dzialanie serwera FIFO. Zamkniecie programu powoduje
 * zamkniecie wszystkich stworzonych wykresow.
 *
 */
int GnuplotShutDown()
{
        ofstream Strm;
        Strm.open(FIFO_FILE);
        if(!Strm.is_open())
        {
                cerr<<"Nie mozna otworzyc potoku"<<endl;
                return 1;
        }
        Strm<<"q"<<endl<<endl;//zamkniecie Gnuplot
        Strm.close();
        return 0;
}


int PlotScene(double SquareLength,int SceneSize,int AgentID)
{
        ofstream Strm;

        Strm.open(FIFO_FILE);
        if(!Strm.is_open())
        {
                cerr<<"Nie mozna otworzyc potoku"<<endl;
                return 1;
        }

        Strm<<"set trange [0:"<<SceneSize*SquareLength<<"]"<<endl;
        Strm<<"set xrange [0:"<<SceneSize*SquareLength<<"]"<<endl;
        Strm<<"set yrange [0:"<<SceneSize*SquareLength<<"]"<<endl;
        Strm<<"set nokey"<<endl;
        Strm<<"set multiplot"<<endl;
        //Strm<<"set term x11"<<endl;
        Strm<<"plot \""<<PLOTDIR<<"Agent"<<AgentID<<".dat\" using 1:2 with points"<<endl<<endl;
        //SavePlot(Strm,"Scene",eps,1);
        //Rysowanie kwadratow (siatki)
        Strm<<"set parametric"<<endl;

        for(int i=1;i<=SceneSize;i++){
        Strm<<"const="<<SquareLength*i<<endl;
        Strm<<"plot const,t"<<endl;
        }
        Strm<<"unset parametric"<<endl;
        for(int i=1;i<=SceneSize;i++){
        Strm<<"const="<<SquareLength*i<<endl;
        Strm<<"plot const"<<endl;
        }
        Strm<<"set nomultiplot"<<endl;
        Strm.close();

        return 0;

}


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
int BarPlot(double **T,int n, int m,int winid, FileType ext)
{
        ofstream Strm;
        char dir[50]=PLOTDIR;
        char wid[4];
        strcat(dir,"barplot");
        sprintf(wid,"%d",winid);
        strcat(dir,wid);
        strcat(dir,".dat");
        Strm.open(dir);
        if(!Strm.is_open())
        {
                cerr<<"Nie mozna otworzyc pliku"<<endl;
                return 1;
        }
        Strm<<"0"<<" "<<"0"<<" "<<"0"<<endl;
        for(int j=0;j<m;j++)
        {

                Strm<<"0"<<" "<<j<<" "<<"0"<<endl;
                Strm<<"0"<<" "<<j+1.0<<" "<<"0"<<endl;

        }
        Strm<<"0"<<" "<<m<<" "<<"0"<<endl;
        for(int i=0;i<n;i++)
        {

                Strm<<endl;
                Strm<<i<<" "<<"0"<<" "<<"0"<<endl;
                for(int j=0;j<m;j++)
                {

                        Strm<<i<<" "<<j<<" "<<T[i][j]<<endl;
                        Strm<<i<<" "<<j+1.0<<" "<<T[i][j]<<endl;

                }
                Strm<<i<<" "<<m<<" "<<"0"<<endl;
                Strm<<endl;
                Strm<<i+1<<" "<<"0"<<" "<<"0"<<endl;
                for(int j=0;j<m;j++)
                {

                        Strm<<i+1.0<<" "<<j<<" "<<T[i][j]<<endl;
                        Strm<<i+1.0<<" "<<j+1.0<<" "<<T[i][j]<<endl;

                }
                Strm<<i+1<<" "<<m<<" "<<"0"<<endl;

        }
        Strm<<endl;
        Strm<<n<<" "<<"0"<<" "<<"0"<<endl;
        for(int j=0;j<m;j++)
        {

                Strm<<n<<" "<<j<<" "<<"0"<<endl;
                Strm<<n<<" "<<j+1.0<<" "<<"0"<<endl;

        }
        Strm<<n<<" "<<m<<" "<<"0"<<endl;


        Strm.close();

        Strm.open(FIFO_FILE);
        if(!Strm.is_open())
        {
                cerr<<"Nie mozna otworzyc potoku"<<endl;
                return 1;
        }
        Strm<<"set term x11 "<<winid<<endl;
        Strm<<"set hidden3d"<<endl;
        Strm<<"set pm3d"<<endl;
        Strm<<"splot \""<<PLOTDIR<<"barplot"<<winid<<".dat\" with pm3d"<<endl<<endl;
        SavePlot(Strm,"BarPlot",ext,winid);
        Strm.close();

        return 0;
}

/*!
 * \fn int ColMapPlot(double **T,int n, int m,double pa,double pb,double ka,
 *              double kb, int winid, FileType ext);
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
 * \param pa - poczatek zakresu drugiej zmiennej
 * \param ka - koniec zakresu pierwszej zmiennej
 * \param kb - koniec zakresu drugiej zmiennej
 * \param winid - identyfikator okna na ktorym ma byc rysowany wykres
 * \param ext - rozszerzenie pliku, do ktorego wykres zostanie zapisany wartosc
 * 'none' nie zapisuje pliku.
 *
 */
int ColMapPlot(double **T,int n, int m,double pa,double pb,double ka,
                double kb, int winid, FileType ext)
{
        ofstream Strm;
        char dir[50]=PLOTDIR;
        char wid[4];
        strcat(dir,"colmapplot");
        sprintf(wid,"%d",winid);
        strcat(dir,wid);
        strcat(dir,".dat");

        double a=pa,b;
        Strm.open(dir);
        if(!Strm.is_open())
        {
                cerr<<"Nie mozna otworzyc pliku"<<endl;
                return 1;
        }

        for(int i=0;i<n;i++)
        {

                b=pb;
                for(int j=0;j<m;j++)
                {

                        Strm<<a<<" "<<b<<" "<<T[i][j]<<endl;
                        b+=(kb-pb)/(double)m;
                }
                Strm<<endl;
                a+=(ka-pa)/(double)n;
        }

        Strm.close();

        Strm.open(FIFO_FILE);
        if(!Strm.is_open())
        {
                cerr<<"Nie mozna otworzyc potoku"<<endl;
                return 1;
        }
        Strm<<"set term x11 "<<winid<<endl;
        Strm<<"set ticslevel 0"<<endl;
        Strm<<"set hidden3d"<<endl;
        Strm<<"set pm3d"<<endl;



        Strm<<"splot \""<<PLOTDIR<<"colmapplot"<<winid<<".dat\" using 1:2:3 with pm3d"<<endl<<endl;
        SavePlot(Strm,"ColMap",ext,winid);
        Strm.close();

        return 0;
}

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
int PerformPlot(int *a,int *b, int ra,int rb,int ref,int ref2,int winid, FileType ext)
{
        ofstream Strm;
        int r;
        char dir[50]=PLOTDIR;
        char wid[4];
        strcat(dir,"performplot");
        sprintf(wid,"%d",winid);
        strcat(dir,wid);
        strcat(dir,".dat");
        Strm.open(dir);
        if(!Strm.is_open())
        {
                cerr<<"PerformPlot:Nie mozna otworzyc pliku"<<endl;
                return 1;
        }
        if(ra>=rb)
                r=ra;
        else
                r=rb;
        for(int i=0;i<r;i++)
        {
                if((r<=ra)&&(r<=rb))
                        Strm<<i<<" "<<a[i]<<" "<<b[i]<<" "<<ref<<" "<<ref2<<endl;
                else if(r<=ra)
                        Strm<<i<<" "<<a[i]<<" "<<b[rb-1]<<" "<<ref<<" "<<ref2<<endl;
                else
                        Strm<<i<<" "<<a[ra-1]<<" "<<b[i]<<" "<<ref<<" "<<ref2<<endl;

        }
        Strm.close();

        Strm.open(FIFO_FILE);
        if(!Strm.is_open())
        {
                cerr<<"Nie mozna otworzyc potoku"<<endl;
                return 1;
        }



        Strm<<"set term x11 "<<winid<<endl;
        //Strm<<"unset ticslevel 0"<<endl;
        Strm<<"unset hidden3d"<<endl;
        Strm<<"unset pm3d"<<endl;

        Strm<<"set grid"<<endl;
        Strm<<"plot \""<<PLOTDIR<<"performplot"<<winid<<".dat\" using 1:2 with lines,  ";
        Strm<<"\""<<PLOTDIR<<"performplot"<<winid<<".dat\" using 1:3 with lines,  ";
        Strm<<"\""<<PLOTDIR<<"performplot"<<winid<<".dat\" using 1:4 with lines,  ";
        Strm<<"\""<<PLOTDIR<<"performplot"<<winid<<".dat\" using 1:5 with lines  "<<endl<<endl;
        SavePlot(Strm,"sym",ext,winid);
        Strm.close();
        return 0;
}

