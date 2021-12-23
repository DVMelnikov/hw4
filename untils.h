#ifndef UNTILS_H
#define UNTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define COLUMN_FINAL_ARR 2
#define BEGIN_LENGTH_ARRVER 3

#define NOT_OPEN_FILE (1)
#define WRONG_MATRIX (2)
#define FAILED_ALLOCATE_MEMORY (3)
#define ERR_ARGS_COUNT (4)

int addMemory (char* arr, int* bouInd);
int addAdjVer (char c, char* arr, int* curInd, int* bouInd);
void outputVer (char* arr, int beginInd, int endInd);
int checkLoop (int* arr, int indRib, int countRib, int str);

#endif // UNTILS_H