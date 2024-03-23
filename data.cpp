#include <stdlib.h>
#include <stdio.h>

#include "data.h"
#include "string.h"
#include "bledy.h"


void d_wyczysc(void* ptr){
	MY_STUDENT* ptrd = (MY_STUDENT*)ptr;
	if (ptrd){

		free(ptrd->nazwisko);
		ptrd->nazwisko = NULL;

		free(ptrd);
		ptrd = NULL;
		}
	}

void* d_init(char* lim, int rok, enum KIERUNEK kr) {

	MY_STUDENT* ptrd = (MY_STUDENT*)malloc(sizeof(MY_STUDENT));
	if (!ptrd) {
		blad(ALLOC_ERR);
		return NULL;
	}
	if (ptrd){
		size_t pom = strlen(lim) + 1;
		ptrd->dl = pom;
		ptrd->nazwisko = (char*)malloc(pom * sizeof(char));

		if (!ptrd->nazwisko) {
			blad(ALLOC_ERR);
			return NULL;
		}
		strcpy(ptrd->nazwisko, lim);
		ptrd->rok = rok;
		ptrd->stopien = kr;
	}
	return (void*)(ptrd);
}

void* d_push(char* nazwisko, int rok, enum KIERUNEK kr) {

	return d_init(nazwisko, rok, kr);
}



int d_nazwisko(void* cur_d, void* szuk_d) {

	MY_STUDENT* ptrc = (MY_STUDENT*)cur_d;
	MY_STUDENT* ptrs = (MY_STUDENT*)szuk_d;

	if (strcmp(ptrc->nazwisko, ptrs->nazwisko) == 0) {
		return 1;
	}
	else {
		return 0;
	}
	}

int d_rok(void* cur_d, void* szuk_d) {
	MY_STUDENT* ptrc = (MY_STUDENT*)cur_d;
	MY_STUDENT* ptrs = (MY_STUDENT*)szuk_d;

	if (ptrc->rok == ptrs->rok) {
	return 1;
	}
	else {

		return 0;
	}
	}

int d_kierunek(void* cur_d, void* szuk_d){

	MY_STUDENT* ptrc = (MY_STUDENT*)cur_d;
	MY_STUDENT* ptrs = (MY_STUDENT*)szuk_d;


	if (ptrc->stopien == ptrs->stopien) {
		return 1;
	}
	else {
		return 0;
	}
}

void d_wypisz(void* ptr) {
	MY_STUDENT* pom = (MY_STUDENT*)ptr;
	if (pom) {
		
			printf("%-20s", pom->nazwisko); 

			printf("%-20d", pom->rok);

		switch (pom->stopien) {

		case INFORMATYKA:

			printf("%-20s\n", "INFORMATYKA");
			break;
		case MATEMATYKA:

			printf("%-20s\n", "MATEMATYKA");
			break;
		case MATEMATYKA_STOSOWANA:

			printf("%-20s\n", "MATEMATYKA_STOSOWANA");
			break;
		}
	}
}


void* d_zaladuj(FILE* PLIK) {
	MY_STUDENT* pom = (MY_STUDENT*)malloc(sizeof(MY_STUDENT));
	if (!pom)
	{
		blad(ALLOC_ERR);
	}

	memset(pom, 0, sizeof(MY_STUDENT));



	if (fread(pom, sizeof(pom->rok) + sizeof(pom->stopien) + sizeof(pom->dl), 1, PLIK) != 1) {
		return 0;
	}

	pom->nazwisko = (char*)malloc(pom->dl * sizeof(char));



	if (fread(pom->nazwisko, pom->dl * sizeof(char), 1, PLIK) != 1) {
		return 0;
	}

	void* dptr = d_push(pom->nazwisko, pom->rok, pom->stopien);

	return dptr;

}

int d_zapisz(void* ptr, FILE* PLIK){
	MY_STUDENT* ptrd = (MY_STUDENT*)ptr;

	if (fwrite(ptrd, sizeof(ptrd->rok) + sizeof(ptrd->stopien) + sizeof(ptrd->dl), 1, PLIK) != 1) {
		return 0;
	}
	if (fwrite(ptrd->nazwisko, ptrd->dl * sizeof(ptrd->nazwisko[0]), 1, PLIK) != 1) {
		return 0;
	}
	else {
		return 1;
	}
}

