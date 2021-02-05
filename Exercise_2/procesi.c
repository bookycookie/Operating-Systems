#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
int SharedMemory; /* identifikacijski broj segmenta */
int *A;
int M;
int N;
void brisi(int sig)
{
   /* oslobađanje zajedničke memorije */
   (void) shmdt((int *) A);
   (void) shmctl(SharedMemory, IPC_RMID, NULL);
   exit(0);
}

void Add(int M) {
	int j = 0;
	for(j = 0; j < M; j++) {
	*A+=1;
	}
}

int main(int argc, char *argv[]) {
	int j = 0;
	 N = atoi(argv[1]);
   	 M = atoi(argv[2]);	
	
   /* zauzimanje zajedničke memorije */
   SharedMemory = shmget(IPC_PRIVATE, 2*sizeof(int)*(N+1)+(M+1)*sizeof(int), 0600);
 
   if (SharedMemory == -1)
      exit(1);  /* greška - nema zajedničke memorije */
 
   A = (int *) shmat(SharedMemory, NULL, 0);
   *A = 0;
   sigset(SIGINT, brisi);//u slučaju prekida briši memoriju
   
   /* pokretanje paralelnih procesa */
   //printf("Jel se ovo uopce izvrsava?\n");
	//printf("N = %d\n", N);
   for(j = 0; j < N; j++){
		switch(fork()) {
			case 0:
				//printf("Ja sam ovdje!\n");
				Add(M);
				exit(1);
			
			case -1:
				printf("Došlo je do greške! Nemogu stvoriti proces!\n");
				
			default:	
			//printf("Sada sam O V D J E ! \n");		
			Add(M);
   }
}

printf("A = %d\n", *A);
   while (j--) wait (NULL);
   
   brisi(0);
 
	
   return 0;
}