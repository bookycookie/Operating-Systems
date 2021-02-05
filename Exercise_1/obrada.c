#include<stdio.h>
#include<signal.h>

#define N 6

static int OZNAKA_CEKANJA[N]={0};
static int PRIORITET[N]={0};
static int TEKUCI_PRIORITET=0;

static int sig[]={SIGTERM, SIGUSR2, SIGTRAP, SIGUSR1, SIGINT};

void zabrani_prekidanje(){
   int i;
   for(i=0; i<5; i++)
      sighold(sig[i]);
}

void dozvoli_prekidanje(){
   int i;
   for(i=0; i<5; i++)
      sigrelse(sig[i]);
}

void obrada_signala(int i) {
   switch (i) {
      case (1):
         printf("   +  P  +  +  +  +\n");
	 for(int j=1; j<=5;j++) {
	    printf("   +  %d  +  +  +  +\n", j);
            sleep(1);
	 }
         printf("   +  K  +  +  +  +\n");
	 break;
      case (2):
         printf("   +  +  P  +  +  +\n");
	 for(int j=1; j<=5;j++) {
	    printf("   +  +  %d  +  +  +\n", j);
            sleep(1);
	 }
         printf("   +  +  K  +  +  +\n");
	 break;
      case (3):
         printf("   +  +  +  P  +  +\n");
	 for(int j=1; j<=5;j++) {
	    printf("   +  +  +  %d  +  +\n", j);
            sleep(1);
	 }
         printf("   +  +  +  K  +  +\n");
	 break;
      case (4):
         printf("   +  +  +  +  P  +\n");
	 for(int j=1; j<=5;j++) {
	    printf("   +  +  +  +  %d  +\n", j);
            sleep(1);
	 }
         printf("   +  +  +  +  K  +\n");
	 break;
      case (5):
         printf("   +  +  +  +  +  P\n");
	 for(int j=1; j<=5;j++) {
	    printf("   +  +  +  +  +  %d\n", j);
            sleep(1);
	 }
         printf("   +  +  +  +  +  K\n");
	 break;
   }
}


void prekidna_rutina(int sig) {
   int n=-1;
   zabrani_prekidanje();
   switch (sig) {
      case SIGTERM:
         n=1;
	 printf("   +  X  +  +  +  +\n");
	 break;
      case SIGUSR2:
         n=2;
	 printf("   +  +  X  +  +  +\n");
	 break;
      case SIGTRAP:
         n=3;
	 printf("   +  +  +  X  +  +\n");
	 break;
      case SIGUSR1:
         n=4;
	 printf("   +  +  +  +  X  +\n");
	 break;
      case SIGINT:
         n=5;
	 printf("   +  +  +  +  +  X\n");
	 break;

   }
   OZNAKA_CEKANJA[n]++;
   if(TEKUCI_PRIORITET<n){
      int j;
      do {
         for(j=N;j>TEKUCI_PRIORITET;j--){
	    if(OZNAKA_CEKANJA[j]>0) break;
         }
	 
	 if(j>0){
	    OZNAKA_CEKANJA[j]--;
	    PRIORITET[j]=TEKUCI_PRIORITET;
	    TEKUCI_PRIORITET=j;
	    dozvoli_prekidanje();
	    obrada_signala(j);
	    zabrani_prekidanje();
	    TEKUCI_PRIORITET=PRIORITET[j];
	    if(OZNAKA_CEKANJA[j]==0 && PRIORITET[j]!=0) break;
	 }
      } while(j>0);
   }
   dozvoli_prekidanje();
}


int main (void) {
   sigset(SIGTERM, prekidna_rutina);   
   sigset(SIGUSR2, prekidna_rutina); 
   sigset(SIGTRAP, prekidna_rutina);  
   sigset(SIGUSR1, prekidna_rutina);
   sigset(SIGINT, prekidna_rutina);  

   printf("Legenda: X - pojava signala, P - početak, K - kraj, prioritet: 5 > 4 > 3 > 2 > 1\n");
   printf("Proces obrade prekida, PID=%d\n", getpid());
   printf("  GP S1 S2 S3 S4 S5\n");
   printf("  -----------------\n");
   
   for(int i=1;i<=50;i++) {
      printf("  %2d  +  +  +  +  +  \n", i);
      sleep(1);
   }
      
   return 0;
}

























