/*!
 *\file FIFOserv.cpp
 *\author Michal Wcislo
 *\date 24.03.2011
 *\version 1.0
 *\brief Zawiera program serwera odczytujacego dane z potoku i przekazujacego
 * je na wejscie Gnuplot'a
 *
 *Zawiera program serwera odczytujacego dane z potoku i przekazujacego
 * je na wejscie Gnuplot'a
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/stat.h>
#include "../src/GnuplotInc.hh"
//#define FIFO_FILE       "GNUPLOT" ///<Nazwa potoku FIFO wykorzystywanego do
									///komunikacji z Gnuplotem


int main(void)
{
	FILE *fp;
	char readbuf[80];


	umask(0);
	mknod(FIFO_FILE, S_IFIFO|0666, 0);
	fp = fopen(FIFO_FILE, "r");
	while(1)
	{

		fgets(readbuf, 80, fp);
		if(readbuf[0]=='q')
			return 0;
		printf("%s", readbuf);


	}
	fclose(fp);
	return(0);
}
