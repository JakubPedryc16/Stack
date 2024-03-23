#include <stdlib.h>
#include <stdio.h>
#include "bledy.h"
#include "stos.h"

static char* bledywiad[] =
{
	(char*)"E!!!Memory allocation error!!!",

	(char*)"W!!!Stack underflow!!!",

	(char*)"E!!!Fatal error!!!"
};

void blad(enum bledy_mess num){


	puts(bledywiad[num] + 1);

	if (bledywiad[num][0] == 'E'){


		zwolnij_stos();

		system("pause");
	}

	return;
}

void blad_plik(FILE* ptrplik, __int64* fd){


	if (ptrplik) {
		fclose(ptrplik);
	}

	if (fd) {
		free(fd);
	}
	blad(FATAL_ERR);
	system("pause");
	exit(1);
}