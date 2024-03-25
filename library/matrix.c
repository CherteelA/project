#include <malloc.h>
#include "matrix.h"
#include <stdio.h>


matrix getMemMatrix(int nRows, int nCols) {
    int **values = (int **) malloc(sizeof(int*) * nRows);
    for (int i = 0; i < nRows; i++)
        values[i] = (int *) malloc(sizeof(int) * nCols);
    return (matrix){values, nRows, nCols};
}
matrix *getMemArrayOfMatrices(int nMatrices,int nRows, int nCols) {
    matrix *ms = (matrix*) malloc(sizeof(matrix) * nMatrices);
    for (int i = 0; i < nMatrices; i++)
        ms[i] = getMemMatrix(nRows, nCols);
    return ms;
}
//освобождает память, выделенную под
//хранение матрицы m
void freeMemMatrix(matrix *m){
    for(int i = 0; i < m->nRows; i++){
        free(m->values[i]);
    }
    free(m->values);
    m->nRows = 0;
    m->nCols = 0;
}
//освобождает память, выделенную под хранение массива ms из nMatrices матриц.
void freeMemMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++) {
        freeMemMatrix(&ms[i]);
    }
    free(ms);
}
//вывод матрицы
void  outputMatrix(matrix m){
    for(int i = 0; i < m.nRows; i++){
        for(int j = 0; j < m.nCols; j++){
            printf("%d ", m.values[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
//вывод матриц из массива ms
void outputMatrices(matrix *ms, int nMatrices){
    for(int a = 0;a < nMatrices; a++)
    {
        for (int i = 0; i < ms[a].nRows; i++) {
            for (int j = 0; j < ms[a].nCols; j++) {
                printf("%d ", ms[a].values[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }
    printf("\n");
}
//ввод массива
void inputMatrix(matrix *m){
    for(int i = 0; i < m->nRows; i++){
        for(int j = 0; j < m->nCols; j++){
            int t;
            scanf("%d", &t);
            m->values[i][j] = t;
        }
    }
}
//ввод матриц из массива ms
void inputMatrices(matrix *ms, int nMatrices){
    for(int a = 0;a < nMatrices; a++)
    {
        for (int i = 0; i < ms[a].nRows; i++) {
            for (int j = 0; j < ms[a].nCols; j++) {
                int t;
                scanf("%d", &t);
                ms[a].values[i][j] = t;
            }
        }
    }
}
// обмен строк с порядковыми
//номерами i1 и i2 в матрице m
void swapRows(matrix *m, int i1, int i2){
    int *p = m->values[i1];
    m->values[i1] = m->values[i2];
    m->values[i2] = p;
}
//обмен колонок с порядковыми номерами j1 и j2 в матрице m.
void swapColumns(matrix *m, int j1, int j2){
    for(int i = 0; i < m->nRows; i++){
        int value = m->values[i][j1];
        m->values[i][j1] = m->values[i][j2];
        m->values[i][j2] = value;
    }
}


//выполняет сортировку вставками строк
//матрицы m по неубыванию значения
void insertionSortRowsMatrixByRowCriteria(matrix *m, int (*criteria)(int*, int)){
    int arr[m->nRows];
    for(int i = 0; i < m->nRows; i++){
        arr[i] = criteria(m->values[i], m->nCols);
    }
    for (int i = 0; i < m->nRows; i++) {
        for (int j = i; j < m->nCols; j++) {
            if (arr[i] > arr[j]) {

                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
                swapRows(m, i, j);
            }
        }
    }
}

void copyMatrix(matrix *src, matrix *dest) {
    dest->nRows = src->nRows;
    dest->nCols = src->nCols;
    for (int i = 0; i < src->nRows; i++) {
        for (int j = 0; j < src->nCols; j++) {
            dest->values[i][j] = src->values[i][j];
        }
    }
}
// выполняет сортировку выбором столбцов
//матрицы m по неубыванию значения функции criteria применяемой для
//столбцов
void selectionSortColsMatrixByColCriteria(matrix *m,int (*criteria)(int*, int)){
    matrix temp_m = getMemMatrix(m->nRows, m->nCols);
    copyMatrix(m, &temp_m);
    transposeMatrix(&temp_m);
    int arr[temp_m.nRows];
    for(int i = 0; i < temp_m.nRows; i++){
        arr[i] = criteria(temp_m.values[i], temp_m.nCols);
    }
    freeMemMatrix(&temp_m);
    for (int i = 0; i < m->nRows; i++) {
        for (int j = i; j < m->nCols; j++) {
            if (arr[i] > arr[j]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
                swapColumns(m, i, j);
            }
        }
    }
}

//возвращает значение ’истина’, если
//матрица m является квадратной, ложь – в противном случае
bool isSquareMatrix(matrix *m){
    return m->nCols = m->nRows;
}
//возвращает значение ’истина’, если матрицы m1 и m2 равны, ложь – в противном случае
bool areTwoMatricesEqual(matrix *m1, matrix *m2){
    if(m1->nRows == m2->nRows && m1->nCols == m2->nCols){
        for(int i = 0; i<m1->nRows;i++){
            for(int j = 0; j < m1->nCols; j++){
                if(m1->values[i][j] != m2->values[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }
    return false;
}
//возвращает значение ’истина’, если матрица
//m является единичной, ложь – в противном случае.
bool isEMatrix(matrix *m){
    for(int i = 0; i<m->nRows;i++) {
        for (int j = i; j < m->nCols; j++) {
            if(j != i && m->values[i][j] != 0){
                return false;
            }
            if(m->values[i][i] != 1){
                return false;
            }
        }
    }
    return true;
}
//возвращает значение ’истина’, если матрица m является симметричной, ложь – в противном случае
bool isSymmetricMatrix(matrix *m){
    if(!isSquareMatrix(m))
        return false;

    for(int i = 0; i<m->nRows;i++) {
        for (int j = 0; j < m->nCols; j++) {
            if (m->values[i][j] != m->values[j][i]) {
                return false;

            }
        }
    }
    return true;
}
//транспонирует квадратную
//матрицу m
void transposeSquareMatrix(matrix *m){
    for(int i = 0; i<m->nRows-1;i++) {
        for (int j = i+1; j < m->nCols; j++) {
            int temp = m->values[i][j];
            m->values[i][j] = m->values[j][i];
            m->values[j][i] = temp;
        }
    }
}
//транспонирует матрицу m
void transposeMatrix(matrix *m){
    matrix matrix_temp = getMemMatrix(m->nCols, m->nRows);
    for(int i = 0; i < m->nRows; i++){
       for(int j = 0; j < m->nCols; j++){
           matrix_temp.values[j][i] = m->values[i][j];
       }
    }
    freeMemMatrix(m);
    *m = matrix_temp;
}
//возвращает позицию минимального элемента матрицы m
position getMinValuePos(matrix m){
    position min;
    int temp = m.values[0][0];
    min.colIndex = 0;
    min.rowIndex = 0;
    for(int i = 0; i < m.nRows; i++){
        for(int j = 0; j < m.nCols; j++){
            if(temp > m.values[i][j]) {
                temp = m.values[i][j];
                min.colIndex = j;
                min.rowIndex = i;
            }
        }
    }
    return min;
}
//возвращает позицию максимального элемента матрицы m
position getMaxValuePos(matrix m){
    position max;
    int temp = m.values[0][0];
    max.colIndex = 0;
    max.rowIndex = 0;
    for(int i = 0; i < m.nRows; i++){
        for(int j = 0; j < m.nCols; j++){
            if(temp < m.values[i][j]) {
                temp = m.values[i][j];
                max.colIndex = j;
                max.rowIndex = i;
            }
        }
    }
    return max;
}

//возвращает матрицу размера nRows на nCols, построенную из элементов массива a:
matrix createMatrixFromArray(const int *a, size_t nRows, size_t nCols){
    matrix new_matrix = getMemMatrix((int)nRows, (int)nCols);
    int index = 0;
    for(int i = 0; i < new_matrix.nRows; i++){
        for(int j = 0; j < new_matrix.nCols; j++){
            new_matrix.values[i][j] = a[index++];
        }
    }
    return new_matrix;
}
//возвращает указатель на нулевую матрицу массива из nMatrices матриц, размещенных
//в динамической памяти, построенных из элементов массива a:
matrix *createArrayOfMatrixFromArray(const int *values, size_t nMatrices, size_t nRows, size_t nCols) {
matrix *ms = getMemArrayOfMatrices((int)nMatrices, (int)nRows, (int)nCols);
    int l = 0;
    for (size_t k = 0; k < nMatrices; k++)
        for (size_t i = 0; i < nRows; i++)
            for (size_t j = 0; j < nCols; j++)
                ms[k].values[i][j] = values[l++];
    return ms;
}

//произведение матрицы m1 на матрицу m2
matrix matrix_multiplication(matrix m1, matrix m2){
    matrix result = getMemMatrix(m1.nRows, m2.nCols);
    for (int i = 0; i < result.nRows; i++) {
        for (int j = 0; j < result.nCols; j++) {
            result.values[i][j] = 0;
            for (int k = 0; k < m1.nCols; k++) {
                result.values[i][j] += m1.values[i][k] * m2.values[k][j];
            }
        }
    }
    return result;
}
