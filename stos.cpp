#include <stdlib.h>
#include <stdio.h>

#include "stos.h"
#include "bledy.h"

static STOS* top = NULL;
char tab[] = "PLIK.bin";

Brakdanych_O brak_p;

Wypisz_O wypiszp;

Plik_O zapiszp;
Load wczytajp;

void stworz_stos(Brakdanych_O ptrbrak, Wypisz_O wypisz_pom, Plik_O zapisz_pom, Load wczytaj_pom) {
	top = NULL;

	brak_p = ptrbrak;
	wypiszp = wypisz_pom;
	zapiszp = zapisz_pom;
	wczytajp = wczytaj_pom;
}

void wypisz_stos() {
	STOS* pom = top;
	if (pom != NULL) {

		printf("%-29s", " ");
		printf("%s", "STOS");

		printf("\n \n");
		while (pom != NULL) {

			wypiszp(pom->PTR);
			pom = pom->nastep;
		}
		printf("\n \n");
	}
	else {
		printf("Stos jest pusty. Dodaj do stosu dane lub wczytaj z pliku!\n \n");
	}
}

STOS* push_stos(void* ptrD){

	STOS* nastepny = (STOS*)malloc(sizeof(STOS));

	if (!nastepny) {
		blad(ALLOC_ERR);
		return NULL;
	}

	nastepny->PTR = ptrD;
	nastepny->nastep = top;

	top = nastepny;

	return nastepny;
}


void* pop_stos() {
	STOS pom;
	if (!top) {

		blad(STACK_UNDERFLOW);

		return NULL;
	}
	else {
		STOS* nastepny = top->nastep;
		pom.PTR = top->PTR;

		free(top);

		top = nastepny;
		return pom.PTR;
	}

}

void zwolnij_stos() {

	STOS* ptr = top;

	STOS * ptrpom = NULL;

	while (ptr) {


		(*brak_p)(ptr->PTR);

		ptrpom = ptr;

		ptr = ptr->nastep;

		free(ptrpom);
	}

	top = NULL;
}


void* przeszukaj_stos(void* szuk, Znajdz_O szukptr, int pierwsz) {
	static STOS* ptr;

	STOS* ptrpom = NULL;


	if (top == NULL) {
		blad(STACK_UNDERFLOW);
		return NULL;
	}
	if (pierwsz)

		ptr = top;

	while (ptr)
	{
		if (!(*szukptr)(ptr->PTR, szuk)){
			ptr = ptr->nastep;
		}
		else{
			ptrpom = ptr;
			ptr = ptr->nastep;

			return ptrpom->PTR;
		}
	}
	return NULL;
}

void zapisz_stos() {
	STOS* pom = top;

	if (pom == NULL) {

		blad(STACK_UNDERFLOW);
		return;
	}

	size_t ile = 0;

	while (pom != NULL) {
		ile++;
		pom = pom->nastep;
	}


	pom = top;

	unsigned int dane = (unsigned int)ile;

	__int64* dplik = (__int64*)malloc((dane + 1) * sizeof(__int64));

	if (!dplik){
		blad_plik(NULL, dplik);
	}

	FILE* fp = fopen(tab, "wb");
	if (!fp){
		blad_plik(fp, dplik);
	}


	if (fwrite(&dane, sizeof(unsigned int), 1, fp) != 1){
		blad_plik(fp, dplik);
	}


	_fseeki64(fp, (ile + 1) * sizeof(__int64),   SEEK_CUR);
	size_t rdane = 0;

	while (pom != NULL) {
		dplik[rdane] = ftell(fp);
		rdane++;
		if (zapiszp(pom->PTR, fp) != 1){
			blad_plik(fp, dplik);
		}

		pom = pom->nastep;

	}

	dplik[rdane] = ftell(fp);

	_fseeki64(fp, sizeof(unsigned int), SEEK_SET);
	if (fwrite(dplik, sizeof(__int64), ile + 1, fp) != ile + 1)
		blad_plik(fp, dplik);

	if (fp) {
		fclose(fp);
		fp = NULL;
	}

	if (dplik) {
		free(dplik);
		dplik = NULL;
	}
}

void wczytaj_stos() {

	zwolnij_stos();

	__int64* file_desc = NULL;
	unsigned int items = 0, item_s, record;


	FILE* pf = fopen(tab, "rb");
	if (!pf)
	{
		blad_plik(pf, file_desc);
	}

	if (fread(&items, sizeof(unsigned int), 1, pf) != 1)
	{
		blad_plik(pf, file_desc);
	}

	file_desc = (__int64*)malloc((items + 1) * sizeof(__int64));
	if (!file_desc)
	{
		blad_plik(pf, file_desc);
	}

	if (fread(file_desc, sizeof(file_desc[0]), items + 1, pf) != items + 1)
	{
		blad_plik(pf, file_desc);
	}

	for (item_s = 0; item_s < items; ++item_s)
	{
		record = items - item_s - 1;
		_fseeki64(pf, file_desc[record], SEEK_SET);

		void* ptrdata = wczytajp(pf);
		if (!push_stos(ptrdata))
		{
			blad_plik(pf, file_desc);
		}


	}

	if (pf) {
		fclose(pf);
		pf = NULL;
	}

	if (file_desc) {
		free(file_desc);
		file_desc = NULL;
	}
}
