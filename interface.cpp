#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "interface.h"
#include "data.h"
#include "stos.h"
#include "bledy.h"
#include "RAND.h"

#pragma warning (disable : 4996)

static char* tab[] ={
	(char*)"0 - Push",
	(char*)"1 - Pop",
	(char*)"2 - Wyczysc stos",
	(char*)"3 - Szukaj w stosie",
	(char*)"4 - Zapisz do pliku",
	(char*)"5 - Wczytaj dane z pliku",
	(char*)"6 - Wyjdz"
	};

static char* kierunki[] =
{
	(char*)"0 - INFORMATYKA",
	(char*)"1 - MATEMATYKA",
	(char*)"2 - MATEMATYKA STOSOWANA"
};

static char *szukaj[] =
{
	(char*)"0 - NAZWISKO",
	(char*)"1 - ROKA",
	(char*)"2 - KIERUNEK"
};

void Menu()
{
	stworz_stos(d_wyczysc, d_wypisz, d_zapisz, d_zaladuj);
	int opt = 0;
	while (1)
	{

		display();
		show_menu();

		opt = int_max_num(INTERFACE_TOTAL);
		switch (opt)
		{
		case INTERFACE_PUSH: push();
			break;

		case INTERFACE_POP: pop();
			break;

		case INTERFACE_WYCZYSC: wyczysc();
			break;

		case INTERFACE_SZUKAJ: znajdz();
			break;

		case INTERFACE_ZAPISZ: zapisz();
			break;

		case INTERFACE_ZALADUJ: zaladuj();
			break;

		case INTERFACE_WYJDZ: wyczysc();
			return;

		default:
			printf("Brak takiego wyboru. Sprobuj ponownie \n\n");
		};
	}
}

void show_menu(){
	size_t k;

	for (k = 0; k < INTERFACE_TOTAL; ++k){
		printf("%s\n", tab[k]);
		}
	}

void show_kierunki() {
	size_t k;
	for (k = 0; k < KIERUNEK_ALL; ++k){
		printf("%s\n", kierunki[k]);
		}
	}

void display() {
	wypisz_stos();
}

void push(){
	char nazwisko[256];
	int rok;
	int kierunek;


	printf("Podaj nazwisko:\n");
	scanf_s("%s", nazwisko, (unsigned)sizeof(nazwisko));

	printf("Podaj rok:\n");
	rok = int_num();

	printf("Podaj kierunek:\n");
	show_kierunki();
	kierunek = int_max_num(KIERUNEK_ALL);

	printf("\n");

	void* ptrData = d_push(nazwisko, rok, (KIERUNEK) kierunek);
	if (!push_stos(ptrData))
		blad(ALLOC_ERR);

	}

void pop(){

	void* tp = pop_stos();

	if (tp != NULL) {
		printf("\n\nPopped:\n\n");
		d_wypisz(tp);
		printf("\n\n\n");
	}
	d_wyczysc(tp);
	}

void zapisz() {
	zapisz_stos();
}


void zaladuj() {
	wczytaj_stos();
}

void wyczysc(){
	zwolnij_stos();
	}

void znajdz(){

	size_t k, wybor;

	printf("\nCzego szukasz:\n");

	for (k = 0; k < SEARCH_TOTAL; ++k)
	{
		printf("%s\n", szukaj[k]);
	}
		wybor = int_max_num(KIERUNEK_ALL);
		switch (wybor){
		case NAZWISKO_SEARCH: find_nazwisko();
			break;

		case ROK_SEARCH: find_rok();
			break;

		case KIERUNEK_SEARCH: find_kierunek();
			break;


		default:
			printf("Sprobuj ponownie\n");
		};
	}

void find_nazwisko() {
	char szuk[256];
	printf("Podaj nazwisko:\n");

	scanf_s("%s", szuk, (unsigned)sizeof(szuk));

	MY_STUDENT* searchdata = (MY_STUDENT*)malloc(sizeof(MY_STUDENT));

	if (!searchdata) {
		blad(ALLOC_ERR);
		return;
	}

	memset(searchdata, 0, sizeof(MY_STUDENT));

	size_t size = strlen(szuk) + 1;

	searchdata->nazwisko = (char*)malloc(size * sizeof(char));

	if (!searchdata->nazwisko) {
		blad(ALLOC_ERR);
		return;
	}
		strcpy(searchdata->nazwisko, szuk);

		void* ptrszuk = przeszukaj_stos(searchdata, d_nazwisko, 1);

		if (ptrszuk) {
			printf("Wynik wyszukania: \n");
			d_wypisz(ptrszuk);
		}
		else {
			printf("NIE ZNALEZIONO");
		}

		while (ptrszuk)
		{
			ptrszuk = przeszukaj_stos(searchdata, d_nazwisko, 0);
			if (ptrszuk)
			{
				d_wypisz(ptrszuk);
			}
		}
		printf("\n\n");

		d_wyczysc(searchdata);
	}


void find_rok(){
	int szuk;
	printf("Podaj rok:\n");
	szuk = int_num();

	MY_STUDENT* szukdane = (MY_STUDENT*)malloc(sizeof(MY_STUDENT));

	if (!szukdane)
	{
		blad(ALLOC_ERR);
		return;
	}

	memset(szukdane, 0, sizeof(MY_STUDENT));

	szukdane->rok = szuk;

	void * ptrszuk = przeszukaj_stos( szukdane, d_rok, 1);

	if (ptrszuk){
		printf("Wynik wyszukiwania \n");
		d_wypisz(ptrszuk);
		}

	else {
		printf("NIE ZNALEZIONO");
	}

	while (ptrszuk){
		ptrszuk = przeszukaj_stos(szukdane, d_rok, 0);
		if (ptrszuk)
		{
			d_wypisz(ptrszuk);
		}
	}
	printf("\n\n");

	d_wyczysc(szukdane);

	}

void find_kierunek()
{
	int kszuk;
	printf("Wybierz kierunek:\n");
	show_kierunki();
	kszuk = int_max_num(KIERUNEK_ALL);

	MY_STUDENT* szukdane = (MY_STUDENT*)malloc(sizeof(MY_STUDENT));

	if (!szukdane)
	{
		blad(ALLOC_ERR);
		return;
	}

	memset(szukdane, 0, sizeof(MY_STUDENT));

	szukdane->stopien = (KIERUNEK)kszuk;

	void* ptrszuk = przeszukaj_stos(szukdane, d_kierunek, 1);

	if (ptrszuk)
	{
		printf("\n");
		d_wypisz(ptrszuk);
	}
	else
		printf("Nie znaleziono");

	while (ptrszuk)
	{
		ptrszuk = przeszukaj_stos(szukdane, d_kierunek, 0);
		if (ptrszuk)
		{
			d_wypisz(ptrszuk);
		}
	}
	printf("\n\n");

	d_wyczysc(szukdane);

}

