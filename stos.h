#pragma once
#ifndef STOS_H
#define STOS_H

#pragma warning (disable : 4996)


struct STOS {
	void* PTR;
	struct STOS* nastep; 
};

typedef void(*Wypisz_O)(void* pdata);

typedef int(*Plik_O)(void* pdata, FILE* PLIK);

typedef void(*Brakdanych_O)(void* dptr);

//typedef void* (*Wczytaj_O)(FILE* PLIK);
typedef void* (*Load)(FILE* file);

typedef int(Znajdz_O)(void* cur_d, void* szuk_d);

void stworz_stos(Brakdanych_O ptr, Wypisz_O wypisz, Plik_O zapisz, Load wczytaj);

void wypisz_stos();

STOS * push_stos(void* ptrD);

void* pop_stos();

void zwolnij_stos();

void zapisz_stos();

void wczytaj_stos();

void* przeszukaj_stos(void* szuk, Znajdz_O szukptr, int pierwsz);



#endif