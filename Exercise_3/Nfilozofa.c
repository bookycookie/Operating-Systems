#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <pthread.h>
#include <semaphore.h>

pthread_mutex_t M;
pthread_cond_t uv;

int N_stick = 10;
int brojPonavljanja; 

void Filozof(int i);
void m_spusti_stapice(int i, int ruke);
void m_spusti_stapice(int i, int ruke);


int main(void) {
	pthread_mutex_init(&M, NULL);
	pthread_cond_init(&uv, NULL);
	pthread_t *f;
	
	
	
	FILE *file = fopen("filozof.txt", "r"); // u fajlu treba biti broj broj broj broj $, trebas stavit broj ruku, broj onavljanja i broj stapica i broj filozofa
	//Nfilozofa = // isparsiraj iz filea ovdje broj koliko filozofa imas
	
 	if (file == NULL)
   	       	 fprintf(stderr, "Error opening input file: %s\n", "filozof.txt");
        	
   	 
	int numberArray[10];
	int i;
	for(i = 0; i < 4; i++) {
	fscanf(file, "%d,", &numberArray[i]);
	}
	int Nfilozofa = numberArray[0];
	int ruke[3] = {numberArray[1],numberArray[2], numberArray[3]};
	pthread_t filozofi[Nfilozofa];
	
	f = (pthread_t*) malloc(Nfilozofa*sizeof(pthread_t));
	if(f == 0) {
		printf("Greska pri alociranju memorije\n");
		exit(0);
	}
	//printf("Hej\n");
	int i = 0;
	for(i = 0; i < Nfilozofa; i++) {
		//k = i;
		if(pthread_create(f+i, NULL, Filozof, (void*) i)){
			printf("Error: dretva %d\n", i);
			exit(1);
	}
}

	for(i = 0; i < Nfilozofa; i++) pthread_join(&filozofi[i], NULL);
	pthread_mutex_destroy(&M);
	pthread_mutex_destroy(&uv);
	return 0;
}

 void Filozof(int i) {//, //int brojPonavljanja) {
	 int brojPonavljanja = 1;
	 int j = 0;
	for(j = 0; j < brojPonavljanja; j++) {

//printf("Debug %d\n", j);
		//misliti(i); // N.K.O.
		printf("Mislim, dakle jesam %d. filozof\n", i);
		sleep(3);
		m_uzmi_stapice(i, 3); // prije K.O. //trebas stavit koliko ruke ima 
		sleep(3);
		//jedi(i); // K.O.
		printf("%d. filozof jede!\n", i);
		sleep(3);
		m_spusti_stapice(i, 3); // poslije K.O.
		
		//brojPonavljanja--;
	}
}

/*void primjer_monitorske_funkcije_koja_ispituje_uvjet(cond_t *uvjet){ 
   pthread_mutex_lock(&monitor);
   while(p==0 || q==0) 
      pthread_cond_wait(uvjet,&monitor); 
   p=q=0; 
   pthread_mutex_unlock(&monitor); 
} 
void primjer_monitorske_funkcije_koja_oslobadja_iz_reda_uvjeta(cond_t *uvjet){ 
   pthread_mutex_lock(&monitor); 
   p=q=1; 
   pthread_cond_broadcast(uvjet); 
   pthread_mutex_unlock(&monitor); 
} 
*/

void zauzmi_stapice(int i, int ruke){
	printf("Ja sam %d. filozof i ja sam uzeo %d stapica!\n", i, ruke);
}

void oslobodi_stapice(int i, int ruke) {
	printf("Ja, %d. filozof, oslobodio sam %d stapica!\n", i, ruke);
}

void m_uzmi_stapice(int i, int ruke) {
	pthread_mutex_lock(&M);
	
	while(ruke > N_stick) { 
		printf("Zapeo sam u redu uvjeta! Filozof sam broj %d. Na stolu je %d stapica, meni treba %d!\n", i, N_stick, ruke);		
		pthread_cond_wait(&uv,&M);
	}
	N_stick -= ruke;
	
	//zauzmi_stapice(i, ruke);
	printf("Ja sam %d. filozof i ja sam uzeo %d stapica!\n", i, ruke);
	
	pthread_mutex_unlock(&M);
}

void m_spusti_stapice(int i, int ruke) {
	pthread_mutex_lock(&M);
	
	//oslobodi_stapice(i, ruke);
	printf("Ja, %d. filozof, oslobodio sam %d stapica!\n", i, ruke);

	N_stick += ruke;
	pthread_cond_broadcast(&uv);
	
	pthread_mutex_unlock(&M);
}

void jedi(int i) {
	printf("%d. filozof jede!\n", i);
}

void misliti(int i) {
	printf("Mislim, dakle jesam %d. filozof\n", i);
}