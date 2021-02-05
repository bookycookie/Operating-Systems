#include <stdio.h>

#include <signal.h>

#include <unistd.h>

#include <sys/time.h>

#include <math.h>

#include <stdlib.h>



int pauza = 0;

unsigned long broj = 1000000001;

unsigned long zadnji = 1000000001;



int prost ( unsigned long n ) {

	unsigned long i, max;



	if ( ( n % 2 ) == 0 ) /* je li paran? */

		return 0;



	max = sqrt(n);

	for ( i = 3; i <= max; i += 2 )

		if ( ( n % i ) == 0 )

			return 0;



	return 1; /* broj je prost! */

}



void periodicki_posao ( int sig )

{

	printf("Zadnji broj je %ld.\n", zadnji);

	sleep(2);

}



void postavi_pauzu(int sig)

{

	pauza = 1 - pauza;

}



void prekini( int sig )

{

	printf("Zadnji prosti broj: %d!\n", zadnji);

	exit(1);

}



int main ()

{	

	printf("Moj PID je %d!\n", getpid());

	printf("Mozes me ubiti s naredbom: 'kill -sigint %d'\n", getpid());

	sigset(SIGINT, prekini);

	sigset(SIGQUIT, postavi_pauzu);



	struct itimerval t;



	/* povezivanje obrade signala SIGALRM sa funkcijom "periodicki_posao" */

	sigset ( SIGALRM, periodicki_posao );



	/* definiranje periodičkog slanja signala */

	/* prvi puta nakon: */

	t.it_value.tv_sec = 0;

	t.it_value.tv_usec = 500000;

	/* nakon prvog puta, periodicki sa periodom: */

	t.it_interval.tv_sec = 0;

	t.it_interval.tv_usec = 500000;



	/* pokretanje sata s pridruženim slanjem signala prema "t" */

	setitimer ( ITIMER_REAL, &t, NULL );

	

	while(1)

	{

		if(prost(broj))

			zadnji = broj;

		

		broj++;



		while(pauza == 1)

		{

			pause();

		}

	}



	return 0;

}