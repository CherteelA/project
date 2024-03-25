// 25.02.2024 20:55
#include <assert.h>
#include "library/matrix.h"
#include <stdio.h>
#include <math.h>

//tusk 1
void change_min_max_Rows(matrix *m){
    position max = getMaxValuePos(*m);
    position min = getMinValuePos(*m);
    swapRows(m, max.rowIndex, min.rowIndex);
}
//обычный случай
void test_change_min_max_base(){
    int a[]= {0,8,7,63,
              54,58,57,23,
              26,99,16,55,
              35,45,69,2};
    matrix m = createMatrixFromArray(a, 4, 4);
    int expected_a[]= {26,99,16,55,
                       54,58,57,23,
                       0,8,7,63,
                       35,45,69,2};
    matrix expected_m = createMatrixFromArray(expected_a, 4, 4);
    change_min_max_Rows(&m);
    assert(areTwoMatricesEqual(&m,&expected_m));
    freeMemMatrix(&expected_m);
    freeMemMatrix(&m);
}
//в одной строке
void test_change_min_max_oneRow(){
    int a[]= {55,8,7,63,
              54,58,57,23,
              0,99,16,55,
              35,45,69,2};
    matrix m = createMatrixFromArray(a, 4, 4);
    int expected_a[]= {55,8,7,63,
                       54,58,57,23,
                       0,99,16,55,
                       35,45,69,2};
    matrix expected_m = createMatrixFromArray(expected_a, 4, 4);
    change_min_max_Rows(&m);
    assert(areTwoMatricesEqual(&m,&expected_m));
    freeMemMatrix(&expected_m);
    freeMemMatrix(&m);
}
//на границе строк
void test_change_min_max_border(){
    int a[]= {55,8,7,63,
              54,58,57,0,
              33,99,16,55,
              35,45,69,2};
    matrix m = createMatrixFromArray(a, 4, 4);
    int expected_a[]= {55,8,7,63,
                       33,99,16,55,
                       54,58,57,0,
                       35,45,69,2};
    matrix expected_m = createMatrixFromArray(expected_a, 4, 4);
    change_min_max_Rows(&m);
    assert(areTwoMatricesEqual(&m,&expected_m));
    freeMemMatrix(&expected_m);
    freeMemMatrix(&m);
}
//..............................................................................................................................
//tusk 2
int getMax(const int *a, int n){
    int max = INT_MIN;
    for(int i = 0; i < n; i++){
        if(max < a[i])
            max = a[i];
    }
    return max;
}
void sortRowsByMinElement(matrix m){
    int arr[m.nRows];
    for(int i = 0; i<m.nRows;i++){
        arr[i] = getMax(m.values[i], m.nCols);
    }
    for (int i = 0; i < m.nRows; i++) {
        for (int j = i; j < m.nCols; j++) {
            if (arr[i] > arr[j]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
                swapRows(&m, i, j);
            }
        }
    }
}

//обычный случай
void test_sortRowsByMinElement_base(){
    int a[]= {0,8,7,63,
              54,58,57,23,
              26,99,16,55,
              35,45,69,2};
    matrix m = createMatrixFromArray(a, 4, 4);
    sortRowsByMinElement(m);
    int expected_a[]= {54,58,57,23,
                       0,8,7,63,
                       35,45,69,2,
                       26,99,16,55};
    matrix expected_m = createMatrixFromArray(expected_a, 4, 4);
    assert(areTwoMatricesEqual(&m,&expected_m));
    freeMemMatrix(&expected_m);
    freeMemMatrix(&m);
}

//если max повторяется
void test_sortRowsByMinElement_moreMax(){
    int a[]= {0,8,7,63,
              54,58,57,23,
              26,99,16,55,
              99,45,69,2};
    matrix m = createMatrixFromArray(a, 4, 4);
    sortRowsByMinElement(m);
    int expected_a[]= {54,58,57,23,
                       0,8,7,63,
                       26,99,16,55,
                       99,45,69,2};
    matrix expected_m = createMatrixFromArray(expected_a, 4, 4);
    assert(areTwoMatricesEqual(&m,&expected_m));
    freeMemMatrix(&expected_m);
    freeMemMatrix(&m);
}
//если изменения не нужны
void test_sortRowsByMinElement_alreadyChange(){
    int a[]= {54,58,57,23,
              0,8,7,63,
              35,45,69,2,
              26,99,16,55};
    matrix m = createMatrixFromArray(a, 4, 4);
    sortRowsByMinElement(m);
    int expected_a[]= {54,58,57,23,
                       0,8,7,63,
                       35,45,69,2,
                       26,99,16,55};
    matrix expected_m = createMatrixFromArray(expected_a, 4, 4);
    assert(areTwoMatricesEqual(&m,&expected_m));
    freeMemMatrix(&expected_m);
    freeMemMatrix(&m);
}
//.............................................................................................
//tusk 3
int getMin(int *a, int n){
    int min = INT_MAX;
    for(int i = 0; i < n; i++){
        if(min > a[i])
            min = a[i];
    }
    return min;
}
void sortColsByMinElement(matrix m){
    selectionSortColsMatrixByColCriteria(&m, getMin);
}
//обычный тест
void test_sortColsByMinElement_base(){
    int arr[]= {54,58,57,23,
                0,8,7,63,
                35,45,69,2,
                26,99,16,55};
    matrix m = createMatrixFromArray(arr, 4, 4);
    int expected_arr[]=    {54,23,57,58,
                            0,63,7,8,
                            35,2,69,45,
                            26,55,16,99};
    matrix expected_m = createMatrixFromArray(expected_arr, 4, 4);
    sortColsByMinElement(m);
    assert(areTwoMatricesEqual(&m,&expected_m));
    freeMemMatrix(&expected_m);
    freeMemMatrix(&m);
}
//уже отсортированный
void test_sortColsByMinElement_alreadyOrder(){
    int arr[]= {54,23,57,58,
                0,63,7,8,
                35,2,69,45,
                26,55,16,99};
    matrix m = createMatrixFromArray(arr, 4, 4);
    int expected_arr[]=    {54,23,57,58,
                            0,63,7,8,
                            35,2,69,45,
                            26,55,16,99};
    matrix expected_m = createMatrixFromArray(expected_arr, 4, 4);
    sortColsByMinElement(m);
    assert(areTwoMatricesEqual(&m,&expected_m));
    freeMemMatrix(&expected_m);
    freeMemMatrix(&m);
}
//повторяются минимальные элементы
void test_sortColsByMinElement_moreMin(){
    int arr[]= {54,23,57,58,
                1,63,1,1,
                35,2,69,45,
                26,55,16,99};
    matrix m = createMatrixFromArray(arr, 4, 4);
    int expected_arr[]=    {54,57,58,23,
                            1,1,1,63,
                            35,69,45,2,
                            26,16,99,55};
    matrix expected_m = createMatrixFromArray(expected_arr, 4, 4);
    sortColsByMinElement(m);
    assert(areTwoMatricesEqual(&m,&expected_m));
    freeMemMatrix(&expected_m);
    freeMemMatrix(&m);
}
//.............................................................
//tusk 4

matrix mulMatrices(matrix m1, matrix m2){
    matrix result = getMemMatrix(m1.nRows, m1.nCols);
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
void getSquareOfMatrixIfSymmetric(matrix *m){
    if(!isSymmetricMatrix(m)) {
        fprintf(stderr, "matrix is not symmetric");
        return;
    }
    matrix temp_matrix = getMemMatrix(m->nRows, m->nCols);
    copyMatrix(m, &temp_matrix);
    freeMemMatrix(m);
    *m = mulMatrices(temp_matrix, temp_matrix);
    freeMemMatrix(&temp_matrix);
}
//обычный случай
void test_getSquareOfMatrixIfSymmetric_base(){
    int arr[]= {2,1,6,7,
                1,1,8,10,
                6,8,3,5,
                7,10,5,4};
    matrix m = createMatrixFromArray(arr, 4, 4);
    int expected_arr[]=   {90,121,73,82,
                           121,166,88,97,
                           73,88,134,157,
                           82,97,157,190};
    matrix expected_m = createMatrixFromArray(expected_arr, 4, 4);
    getSquareOfMatrixIfSymmetric(&m);
    assert(areTwoMatricesEqual(&m,&expected_m));
    freeMemMatrix(&expected_m);
    freeMemMatrix(&m);
}
//если в матрице есть 0
void test_getSquareOfMatrixIfSymmetric_zero(){
    int arr[]= {2,1,6,0,
                1,1,8,10,
                6,8,3,5,
                0,10,5,4};
    matrix m = createMatrixFromArray(arr, 4, 4);
    int expected_arr[]=    {41,51,38,40,
                            51,166,88,90,
                            38,88,134,115,
                            40,90,115,141};
    matrix expected_m = createMatrixFromArray(expected_arr, 4, 4);
    getSquareOfMatrixIfSymmetric(&m);
    assert(areTwoMatricesEqual(&m,&expected_m));
    freeMemMatrix(&expected_m);
    freeMemMatrix(&m);
}
//если матрица единичная
void test_getSquareOfMatrixIfSymmetric_single(){
    int arr[] = {1,0,0,
                 0,1,0,
                 0,0,1};
    matrix m = createMatrixFromArray(arr, 3, 3);
    int expected_arr[]=    {1,0,0,
                            0,1,0,
                            0,0,1};
    matrix expected_m = createMatrixFromArray(expected_arr, 3, 3);
    getSquareOfMatrixIfSymmetric(&m);
    assert(areTwoMatricesEqual(&m,&expected_m));
    freeMemMatrix(&expected_m);
    freeMemMatrix(&m);
}
//....................................................................
//tusk 5
long long getSum(const int *a, int n){
    long long sum = 0;
    for(int i = 0; i < n; i++){
        sum += a[i];
    }
    return sum;
}
bool isUnique(const long long *a, int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(a[i] == a[j] && i!=j){
                return false;
            }
        }
    }
    return true;
}
void transposeIfMatrixHasNotEqualSumOfRows(matrix m){
    long long arr[m.nCols];
    for(int i = 0; i < m.nCols; i++){
        int* Row = m.values[i];
        arr[i] = getSum(Row, m.nCols);
    }
    if(!isUnique(arr, m.nCols)){
        fprintf(stderr, "sum is not unique");
        return;
    }
    transposeSquareMatrix(&m);
}
//обычный случай
void test_transposeIfMatrixHasNotEqualSumOfRows_base(){
    int arr[]= {54,23,57,58,
                1,63,1,1,
                35,2,69,45,
                26,55,16,99};
    matrix m = createMatrixFromArray(arr, 4, 4);
    int expected_arr[]=    {54,1,35,26,
                            23,63,2,55,
                            57,1,69,16,
                            58,1,45,99};
    matrix expected_m = createMatrixFromArray(expected_arr, 4, 4);
    transposeIfMatrixHasNotEqualSumOfRows(m);
    assert(areTwoMatricesEqual(&m,&expected_m));
    freeMemMatrix(&expected_m);
    freeMemMatrix(&m);
}
//если симетричная
void test_transposeIfMatrixHasNotEqualSumOfRows_IfSymmetric(){
    int arr[]= {54,1,35,26,
                1,63,2,55,
                35,2,69,16,
                26,55,16,99};
    matrix m = createMatrixFromArray(arr, 4, 4);
    int expected_arr[]=    {54,1,35,26,
                            1,63,2,55,
                            35,2,69,16,
                            26,55,16,99};
    matrix expected_m = createMatrixFromArray(expected_arr, 4, 4);
    transposeIfMatrixHasNotEqualSumOfRows(m);
    assert(areTwoMatricesEqual(&m,&expected_m));
    freeMemMatrix(&expected_m);
    freeMemMatrix(&m);
}

//.............................................................................
//tusk 6
bool isMutuallyInverseMatrices(matrix m1, matrix m2){
    matrix result;
    result = getMemMatrix(m1.nRows, m2.nCols);
    for (int i = 0; i < result.nRows; i++) {
        for (int j = 0; j < result.nCols; j++) {
            result.values[i][j] = 0;
            for (int k = 0; k < m1.nCols; k++) {
                result.values[i][j] += m1.values[i][k] * m2.values[k][j];
            }
        }
    }
    if(isEMatrix(&result)){
        freeMemMatrix(&result);
        return true;
    }
    freeMemMatrix(&result);
    return false;
}

//обычный случай
void test_isMutuallyInverseMatrices_base(){
    int arr1[]= {2, 5, 7,
                 6, 3, 4,
                 5, -2, -3};
    matrix m1= createMatrixFromArray(arr1, 3, 3);
    int arr2[]=    {1, -1, 1,
                    -38, 41, -34,
                    27, -29, 24};
    matrix m2 = createMatrixFromArray(arr2, 3, 3);

    assert(isMutuallyInverseMatrices(m1, m2));
    freeMemMatrix(&m1);
    freeMemMatrix(&m2);
}
//уже еденичная матрица
void test_isMutuallyInverseMatrices_alreadySingl(){
    int arr1[]= {1, 0, 0,
                 0, 1, 0,
                 0, 0, 1};
    matrix m1= createMatrixFromArray(arr1, 3, 3);
    int arr2[]=    {1, 0, 0,
                    0, 1, 0,
                    0, 0, 1};
    matrix m2 = createMatrixFromArray(arr2, 3, 3);
    assert(isMutuallyInverseMatrices(m1, m2));
    freeMemMatrix(&m1);
    freeMemMatrix(&m2);
}
//.................................................................................
//tusk 7
int max(int a, int b){
    return a > b ? a : b;
}

long long findSumOfMaxesOfPseudoDiagonal(matrix m){
    int arr[m.nCols+m.nRows-1];
    for (int i = 0; i < m.nCols+m.nRows-1; i++){
        arr[i] = INT_MIN;
    }
    int index = 0;
    for (int k = 1 - m.nRows; k < m.nCols; k++){
        for (int i = 0; i < m.nRows; i++){
            int j = k + i;
            if (j >= 0 && j < m.nCols){
                arr[index] = max(arr[index], m.values[i][j]);
            }
        }
        index++;
    }
    int sum = 0;
    for (int i = 0; i < m.nCols+m.nRows-1; i++){
        sum+=arr[i];
    }
    return sum;
}
//обычный случай
void test_findSumOfMaxesOfPseudoDiagonal_base(){
    int arr[]= {2, 5, 7, 8,
                6, 3, 4, -9,
                5, -2, -3, 3};
    matrix m= createMatrixFromArray(arr, 3, 4);
    findSumOfMaxesOfPseudoDiagonal(m);
    assert(findSumOfMaxesOfPseudoDiagonal(m)==34);
    freeMemMatrix(&m);
}
//если матрица квадратная
void test_findSumOfMaxesOfPseudoDiagonal_SquareMatrix(){
    int arr[]= {2, 5, 7,
                6, 3, 4,
                5, -2, -3};
    matrix m= createMatrixFromArray(arr, 3, 3);
    findSumOfMaxesOfPseudoDiagonal(m);
    assert(findSumOfMaxesOfPseudoDiagonal(m)==26);
    freeMemMatrix(&m);
}
//матрица 2*2
void test_findSumOfMaxesOfPseudoDiagonal_matrix_2on2(){
    int arr[]= {2, 5,
                6, 3};
    matrix m= createMatrixFromArray(arr, 2, 2);
    findSumOfMaxesOfPseudoDiagonal(m);
    assert(findSumOfMaxesOfPseudoDiagonal(m)==14);
    freeMemMatrix(&m);
}
//..............................................................................................
void test_matrix(){
    test_change_min_max_base();//обычный случай
    test_change_min_max_oneRow();//в одной строке
    test_change_min_max_border();//на границе строк
    test_sortRowsByMinElement_base();//обычный случай
    test_sortRowsByMinElement_moreMax();//если max повторяется
    test_sortRowsByMinElement_alreadyChange();//если изменения не нужны
    test_sortColsByMinElement_base();//обычный тест
    test_sortColsByMinElement_alreadyOrder();//уже отсортированный
    test_sortColsByMinElement_moreMin();//повторяются минимальные элементы
    test_getSquareOfMatrixIfSymmetric_base(); //обычный случай
    test_getSquareOfMatrixIfSymmetric_zero(); //если в матрице есть 0
    test_getSquareOfMatrixIfSymmetric_single(); //если матрица единичная
    test_transposeIfMatrixHasNotEqualSumOfRows_base(); //обычный случай
    test_transposeIfMatrixHasNotEqualSumOfRows_IfSymmetric(); // если симетричная
    test_isMutuallyInverseMatrices_base(); //обычный случай
    test_isMutuallyInverseMatrices_alreadySingl(); //уже еденичная матрица
    test_findSumOfMaxesOfPseudoDiagonal_base(); //обычный случай
    test_findSumOfMaxesOfPseudoDiagonal_SquareMatrix(); //если матрица квадратная
    test_findSumOfMaxesOfPseudoDiagonal_matrix_2on2(); //матрица 2*2
}

int main(){
    test_matrix();
    return 0;
}