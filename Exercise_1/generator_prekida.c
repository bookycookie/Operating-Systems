#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>

int pid=0;

void prekidna_rutina(int sig){
   /* pošalji SIGKILL procesu 'pid'*/
   kill(pid, SIGKILL);	
   exit(0);
}

int main(int argc, char *argv[]){

   srand((unsigned) time (NULL));
   pid=atoi(argv[1]);
   sigset(SIGINT, prekidna_rutina);

   while(1){
      /* odspavaj 3-5 sekundi */
      /* slučajno odaberi jedan signal (od 4) */
      /* pošalji odabrani signal procesu 'pid' funkcijom kill*/
      int randZzz=rand()%(5-3+1)+3;
      sleep(randZzz);
      int randSig = rand()%4;
      switch (randSig){
	case (0):
           kill(pid, SIGTERM);
	   break;
	case (1):
	   kill(pid, SIGUSR2);
	   break;
	case (2):
	   kill(pid, SIGTRAP);	
	   break;	
	default:
	   kill(pid, SIGUSR1);
	   break;
	}
   }
   return 0;
}
