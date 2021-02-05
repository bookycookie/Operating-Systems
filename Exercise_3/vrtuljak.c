#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#define vrtuljak 1
#define sjeo 2
#define kraj_voznje 3
#define sisao 4
/*void posjetitelj() {
	Cekaj_OSEM(vrtuljak);
	sjedni;
	Postavi_OSEM(sjeo);
	Cekaj_OSEM(kraj_voznje);
	ustani;
	siđi;
	Postavi_OSEM(sisao);	
}

void vrtuljak() {
	while(1) {
		for(i = 1 do N) Postavi_OSEM(vrtuljak);
		for(i = 1 do N) Cekaj_OSEM(sjeo);
		pokreni_vrtuljak;
		zaustavi_vrtuljak;
		for(i = 1 do N) Postavi_OSEM(kraj_voznje);
		for(i = 1 do N) Cekaj_OSEM(sisao);
	}
}
*/
//P.V. svi semafori.v = 0;
int SemId;

void SemGet(int n){
  /* dobavi skup semafora sa ukupno n semafora */
   SemId = semget(IPC_PRIVATE, n, 0600);
   if (SemId == -1) {
      printf("Nema semafora!\n");
      exit(1);
   }
}

int Cekaj_OSEM(int SemNum) {
	return SemOp(SemNum, -1);
}

int Postavi_OSEM(int SemNum) {
	return SemOp(SemNum, 1);
}

int SemSetVal(int SemNum, int SemVal){
  /* postavi vrijednost semafora SemNum na SemVal */
   return semctl(SemId, SemNum, SETVAL, SemVal);
}

int SemOp(int SemNum, int SemOp){
  /* obavi operaciju SemOp sa semaforom SemNum */
   struct sembuf SemBuf;
   SemBuf.sem_num = SemNum;
   SemBuf.sem_op  = SemOp;
   SemBuf.sem_flg = 0;
   return semop(SemId, & SemBuf, 1);
}

void SemRemove(void){
  /* uništi skup semafora */
   (void) semctl(SemId, 0, IPC_RMID, 0);
}



int main(int argc, char *argv[]) {
	int N = atoi(argv[1]);
	//provjera za error
	int i = 0;
	//for(i = 1; i < 4; i++) {
	//	SemGet(i);
	//}
	
	SemGet(4);
	
	for(i = 0; i < 4; i++) {
		SemSetVal(i, 0);
	}
	
	if(fork() == 0) Vrtuljak(N);
	
	for(i = 0; i < N; i++) {
		if(fork() == 0) {
			Posjetitelj(i);
		}
	}
	
	for(i = 0; i < N + 1; i++) wait(NULL);
			
	//SemRemove(void)
			
	return 0;
}

void Vrtuljak(int N) {
	int i = 0;
	int b = 0;
	printf("Vrtuljak se pokrece 3 puta!\n");
	while(b < 3) {
	//printf("Pokrecem vrtuljak po %d. put!\n", b+1);
	sleep(3);
	for(i = 0; i < N; i++) Postavi_OSEM(vrtuljak);
	
	for(i = 0; i < N; i++) Cekaj_OSEM(sjeo);
	Pokreni_Vrtuljak();
	sleep(3);
	Zaustavi_Vrtuljak();
	
	for(i = 0; i < N; i++) Postavi_OSEM(kraj_voznje);
	
	for(i = 0; i < N; i++) Cekaj_OSEM(sisao);	
	b++;
	}
}

void Posjetitelj(int i) {
	
	Cekaj_OSEM(vrtuljak);
	
	Sjedni(i);
	sleep(3);
	Postavi_OSEM(sjeo);
	
	Cekaj_OSEM(kraj_voznje);
	Ustani_i_Sidji(i);
	
	
	Postavi_OSEM(sisao);
	sleep(3);
	printf("----------------------%d-----------------------------\n", i);
	
}

void Pokreni_Vrtuljak() {
	printf("Vrtuljak je pokrenut!\n");
}

void Zaustavi_Vrtuljak() {
	printf("Vrtuljak se zaustavio!\n");
}

void Sjedni(int i) {
	printf("%d. osoba je sjela!\n", i);
}

void Ustani_i_Sidji(int i) {
	printf("%d. osoba je ustala i sisla s vrtuljka!\n", i);
}


		