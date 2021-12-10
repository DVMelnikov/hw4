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
void comboVer (char* arr, int beginInd, int endInd);
int checkLoop (int* arr, int indRib, int countRib, int str);

int main(int argc, const char** argv) {

    if (argc < 2) {
        printf("ERR_ARGS_COUNT - 20");
        return ERR_ARGS_COUNT;
    }
    
    FILE * text = fopen("mat_inc.txt", "r");

    if (!text) 
        return NOT_OPEN_FILE;

    rewind(text);

    int str = 0;
    int column = 1;

    while (!feof(text)) // строки
         if (fgetc(text) == '\n')
             str++;

    rewind(text);

    while (fgetc(text) != '\n')  //столбцы
        column++;
    
    int **mat_inc;
    mat_inc = (int**)calloc(str, sizeof(int*));

    if (mat_inc == NULL) {
        printf("FAILED_ALLOCATE_MEMORY - 46");
        return FAILED_ALLOCATE_MEMORY;
    }
    for (int i = 0; i < str; i++) {
        mat_inc[i] = (int*)calloc(column, sizeof(int));

        if (mat_inc[i] == NULL) {
            printf("FAILED_ALLOCATE_MEMORY - 53");
            return FAILED_ALLOCATE_MEMORY;
        }
    }

    rewind(text);

    for (int i = 0; i < str; i++) { // ввод в масисив с файла
        for (int j = 0; j < column; j++) {
            if (!feof(text))
                mat_inc[i][j] = fgetc(text);
        }
    }
    fclose(text);

    int count_rib_graph = 0; // кол-во рёбер в графе
    for (int j = 0; j < column; j++) {
            if ((mat_inc[0][j] >= 'a') && (mat_inc[0][j] <= 'z')) {
                count_rib_graph++;
            }
    }
    
    int * two_dem_in_one_dem = (int *)calloc(count_rib_graph*(str - 1), sizeof(int)); 

    if (two_dem_in_one_dem == NULL) {
        printf("FAILED_ALLOCATE_MEMORY - 78");
        return FAILED_ALLOCATE_MEMORY;
    }

    int counter_tdInod = 0;
    
    for (int i = 1; i < str; i++) {  // Представление двумерного массива в одномерном
        for (int j = 2; j < column; j++) {
            if ((mat_inc[i][j] == '1') || (mat_inc[i][j] == '0')) {
                two_dem_in_one_dem[counter_tdInod++] = mat_inc[i][j] - '0';
            }
        }
    }

    int * verDeg = (int *)calloc(count_rib_graph, sizeof(int));
    if (verDeg == NULL) {
        printf("FAILED_ALLOCATE_MEMORY - 94");
        return FAILED_ALLOCATE_MEMORY;
    }

    int degree = 0;

    for (int altStr = 0; altStr < str - 1; altStr++) {
        for (int altCol = 0; altCol < count_rib_graph; altCol++) {
            if (two_dem_in_one_dem[altStr*count_rib_graph + altCol])
                degree++;
        }
        verDeg[altStr] = degree;
        degree = 0;
    }

    /*for (int i = 0; i < str - 1; i++) {
        if (verDeg[i] == 1) {
            for (int j = 0; j < count_rib_graph; j++) {
                if (two_dem_in_one_dem[i*count_rib_graph + j])
                    if(!checkLoop(two_dem_in_one_dem, j, count_rib_graph, str))
                        verDeg[i] = 0;
            }
        }
    }*/
    
    int degreeVertices = atoi(argv[1]);
    char* arrVer = (char *)calloc(BEGIN_LENGTH_ARRVER, sizeof(char));
    int curInd = 0;
    int bouInd = BEGIN_LENGTH_ARRVER - 1;

    // объявить массив ребер, выделить како-ето нач кол-во памяти
    for (int i = 0; i < str - 1; i++) {
        if (verDeg[i] == degreeVertices) {
            for (int j = 0; j < column; j++) {
                if (mat_inc[i + 1][j] == '1') {
                    if ((char)mat_inc[0][j] != ' ')
                        if (addAdjVer((char)mat_inc[0][j], arrVer, &curInd, &bouInd)) {
                            printf("FAILED_ALLOCATE_MEMORY - 120");
                            return FAILED_ALLOCATE_MEMORY;
                        }
                }
            }
            addAdjVer('0', arrVer, &curInd, &bouInd);
        }
    }
    addAdjVer('\0', arrVer, &curInd, &bouInd);
    
    int i = 0;
    int curVer = -1;
    while (arrVer[i] != '\0') {
        for (int j = curVer + 1; j < str - 1; j++) {
            if (verDeg[j] == degreeVertices) {
                printf("Смежные ребра для вершины с номером %d: ", j);
                curVer = j;
                break;
            }
        }
        if (degreeVertices == 1) {
            printf("%c", arrVer[i]);
            printf("\n");
        } else {
            comboVer(arrVer, i, i + degreeVertices - 1);
        }
        i += degreeVertices + 1;
    }

    for (int i = 0; i < str; i++) {
        free(mat_inc[i]);
    }
    free(mat_inc);
    free(two_dem_in_one_dem);
    free(verDeg);
    free(arrVer); 
    return 0;
}

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

void comboVer (char* arr, int beginInd, int endInd) {
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
