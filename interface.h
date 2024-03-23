#pragma once
#ifndef INTERFACE_H
#define INTERFACE_H

enum INTERFACE{
	INTERFACE_PUSH,

	INTERFACE_POP,

	INTERFACE_WYCZYSC,

	INTERFACE_SZUKAJ,

	INTERFACE_ZAPISZ,

	INTERFACE_ZALADUJ,

	INTERFACE_WYJDZ,

	INTERFACE_TOTAL

	};

enum SEARCH_DATA{

	NAZWISKO_SEARCH,

	ROK_SEARCH,

	KIERUNEK_SEARCH,

	SEARCH_TOTAL

	};

void display();


void push();

void pop();

void wyczysc();

void znajdz();

void find_nazwisko();

void find_rok();

void find_kierunek();

void zapisz();

void zaladuj();

void show_menu();

void show_kierunki();

void Menu();


#endif

