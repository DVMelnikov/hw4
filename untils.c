#include "untils.h"

int addAdjVer (char c, char* arr, int* curInd, int* bouInd) {
    int errMemory;
    if (*bouInd == *curInd) {
        errMemory = addMemory(arr, bouInd);
        if (errMemory == FAILED_ALLOCATE_MEMORY)
            return FAILED_ALLOCATE_MEMORY;
    }
    arr[*curInd] = c;
    *curInd += 1;
    return 0;
}

int addMemory (char* arr, int* bouInd) {
    arr = (char*)realloc(arr, (*bouInd + 3)*sizeof(char));
    if (arr == NULL) 
        return FAILED_ALLOCATE_MEMORY;
    *bouInd += 1;
    return 0;
}

void outputVer (char* arr, int beginInd, int endInd) {
    for (int i = beginInd; i <= endInd; i++) {
            printf("%c", arr[i]);
    }
    printf("\n");
}

int checkLoop (int* arr, int indRib, int countRib, int str) {
    int flag = 0;
    for (int i = 0; i < str - 1; i++) {
        if (arr[indRib + countRib * i]) {
            flag++;
        }
    }
    if (flag == 1) {
        return 1;
    } else {
        return 0;
    }
}
