#pragma once
#pragma warning (disable : 4996)

enum KIERUNEK{

	INFORMATYKA,

	MATEMATYKA,
	MATEMATYKA_STOSOWANA,
	KIERUNEK_ALL
	};


struct MY_STUDENT
{
	int rok;
	enum KIERUNEK stopien;
	size_t dl;
	char* nazwisko;

	
};

void d_wyczysc(void* ptr);

void* d_init(char* lim, int rok, enum KIERUNEK kr);

void* d_push(char* nazwisko, int rok, enum KIERUNEK kr);

int d_nazwisko(void* cur_d, void* szuk_d);

int d_rok(void* cur_d, void* szuk_d);

int d_kierunek(void* cur_d, void* szuk_d);

void d_wypisz(void* ptr);

void* d_zaladuj(FILE *PLIK);

int d_zapisz(void* ptr, FILE* PLIK);




