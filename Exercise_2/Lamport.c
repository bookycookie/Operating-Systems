#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdatomic.h>


int N, M;
long int A;
atomic_int *TRAZIM;
atomic_int *BROJ;
//copy paste
void udi_u_kriticni_odsjecak(int i) {
		//printf("Hello Ida3!\n");
		TRAZIM[i] = 1;
		//printf("Hello Ida2!\n");
			int MAX = BROJ[0];
			for(int i = 0;i < N ;i++) {
				if(BROJ[i] > MAX) {
				MAX = BROJ[i];
				}
			}
			BROJ[i]=MAX+1;
			TRAZIM[i] = 0;
			for(int j = 0; j < N ; j++) {
				while(TRAZIM[j]!=0) {

				}

				while(BROJ[j] != 0 && (BROJ[j] < BROJ[i] || (BROJ[j] == BROJ[i] && j < i))) {

				}
			}
}

void izadi_iz_kriticnog_odsjecka(int i) {
	BROJ[i] = 0;
}
//kraj copy paste
void *Add () {
	for (int j=0; j<M; ++j) {
		//printf("Hello Ida!\n");
		udi_u_kriticni_odsjecak(j);
		//printf("Hello Ida1!\n");
		A+=1;
		izadi_iz_kriticnog_odsjecka(j);
	}
}

int main (int argc, char *argv[]) {
	int i;
	pthread_t *t;
	TRAZIM = malloc(sizeof(pthread_t));
	BROJ = malloc(sizeof(pthread_t));
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
