#pragma once

#ifndef bledy_H
#define bledy_H

enum bledy_mess {
	ALLOC_ERR, 
	STACK_UNDERFLOW, 
	FATAL_ERR, 
	TOTAL_ERR
};

void blad(enum bledy_mess num);

void blad_plik(FILE* ptrplik, __int64* fd);

#endif
