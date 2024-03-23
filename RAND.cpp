#include <stdlib.h>
#include <stdio.h>
#include "RAND.h"

#pragma warning (disable : 4996)

int int_num(){
	int numer;

	int pom = 1;

	while (pom) {
		if (scanf("%d", &numer) == 1 && numer >= 0)
			pom = 0;
		else{
			printf("Podaj liczbe wieksza lub rowna 0\n");
		}

		while (getchar() != '\n');
	}

	return numer;
}

int int_max_num(int max){
	int numer;
	int pom = 1;

	while (pom) {
		if (scanf("%d", &numer) == 1 && numer >= 0 && numer < max)
			pom = 0;
		else{
			printf("Podaj liczbe X taka, ze (X>=0 i X<=2)\n");
		}

		while (getchar() != '\n');
	}

	return numer;
}