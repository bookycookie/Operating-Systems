#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define TAS(ZASTAVICA) __atomic_test_and_set (&ZASTAVICA, __ATOMIC_SEQ_CST)

int N, M;
long int A;

volatile char zastavica = 0; //globalna varijabla

void *Add () {
	while ( TAS(zastavica) == 1)    ; // radno čekanje 
	for (int j=0; j<M; ++j) {
		A++;
	}
	zastavica = 0;
}

int main (int argc, char *argv[]) {
	int i;
	pthread_t *t;
	
	A=0;
	N=atoi(argv[1]);
	M=atoi(argv[2]);
	t=(pthread_t*) malloc (N*sizeof(pthread_t));
	
	if(argc != 3) printf("Krivi broj unesenih podataka!\n");
	if(t == 0) {
		printf("Greska pri alociranju memorije\n");
		exit(0);
	}
	
	for (i=0;i<N;++i) {
		if (pthread_create(t+i, NULL, Add, NULL)) {
			printf("Greska pri stvaranju dretve\n");
			printf("Gasim program\n");
			exit(0);
		}
	}
	
	for (i=0; i<N; i++) {
		//printf("Brisem dretvu %d\n", i);
		pthread_join(t[i],NULL);
	}
	
	printf ("A = %ld\n", A);
	return 0;
}
