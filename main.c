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
//tusk 8
int getMinInArea(matrix m){
    position max_el = getMaxValuePos(m);
    int min = m.values[max_el.rowIndex][max_el.colIndex];
    if(max_el.rowIndex!=0){
        for(int i = 1; i <= max_el.rowIndex; i++) {
            for(int j = max_el.colIndex - i; j <= max_el.colIndex+i; j++){
                if(j == m.nCols){
                    break;
                }
                if(j >= 0) {
                    min = min > m.values[max_el.rowIndex - i][j] ? m.values[max_el.rowIndex - i][j] : min;
                }
            }
        }
    }
    return min;
}

//обычный случай
void test_getMinInArea_base(){
    int arr[]= {1,2,3,4,
                5,6,7,8,
                9,10,11,12,
                13,14,16,15};
    matrix m = createMatrixFromArray(arr, 4, 4);

    assert(getMinInArea(m) == 1);
    freeMemMatrix(&m);
}
//максимальное значение у края
void test_getMinInArea_atBorder(){
    int arr[]= {0,2,3,4,
                5,6,7,8,
                9,10,11,12,
                16,14,13,15};
    matrix m = createMatrixFromArray(arr, 4, 4);

    assert(getMinInArea(m) == 0);
    freeMemMatrix(&m);
}
//максимальное значение в первой строке
void test_getMinInArea_inFirstRow(){
    int arr[]= {16,2,3,4,
                5,6,7,8,
                9,10,11,12,
                0,14,13,15};
    matrix m = createMatrixFromArray(arr, 4, 4);

    assert(getMinInArea(m) == 16);
    freeMemMatrix(&m);
}

//максимальное значение у правого края во второй строке
void test_getMinInArea_inSecondRow(){
    int arr[]= {8,2,3,4,
                5,6,7,16,
                9,10,11,12,
                0,14,13,15};
    matrix m = createMatrixFromArray(arr, 4, 4);

    assert(getMinInArea(m) == 3);
    freeMemMatrix(&m);
}
//.........................................................................................
//tusk 9
float getDistance(int *a, int n){
    float distance;
    for(int i = 0; i < n; i++){
        distance += a[i]*a[i];
    }
    return sqrtf(distance);
}
void insertionSortRowsMatrixByRowCriteriaF(matrix m,float (*criteria)(int *, int)){
    float arr[m.nRows];
    for(int i = 0; i < m.nRows; i++){
        arr[i] = criteria(m.values[i], m.nCols);
        printf("");
    }
    for (int i = 0; i < m.nRows; i++) {
        for (int j = i; j < m.nCols; j++) {
            if (arr[i] > arr[j]) {
                float temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
                swapRows(&m, i, j);
            }
        }
    }
}

void sortByDistances(matrix m){
    insertionSortRowsMatrixByRowCriteriaF(m, getDistance);
}
//обычный случай
void test_sortByDistances_base(){
    int arr[]= {3,3,3,1,
                1,1,1,1,
                2,2,2,2,
                0,1,3,4};
    matrix m = createMatrixFromArray(arr, 4, 4);
    int expected_a[]= {1,1,1,1,
                       2,2,2,2,
                       0,1,3,4,
                       3,3,3,1};
    matrix expected_m = createMatrixFromArray(expected_a, 4, 4);
    sortByDistances(m);
    assert(areTwoMatricesEqual(&m, &expected_m));
    freeMemMatrix(&expected_m);
    freeMemMatrix(&m);
}
//одинаковые дистанции
void test_sortByDistances_equaleDist(){
    int arr[]= {3,3,3,1,
                1,1,1,0,
                0,1,1,1,
                0,1,3,4};
    matrix m = createMatrixFromArray(arr, 4, 4);
    int expected_a[]= {1,1,1,0,
                       0,1,1,1,
                       0,1,3,4,
                       3,3,3,1};
    matrix expected_m = createMatrixFromArray(expected_a, 4, 4);
    sortByDistances(m);
    assert(areTwoMatricesEqual(&m, &expected_m));
    freeMemMatrix(&expected_m);
    freeMemMatrix(&m);
}
//уже отсортирован
void test_sortByDistances_alreadySort(){
    int arr[]= {1,1,1,0,
                0,1,1,1,
                0,1,3,4,
                3,3,3,1};
    matrix m = createMatrixFromArray(arr, 4, 4);
    int expected_a[]= {1,1,1,0,
                       0,1,1,1,
                       0,1,3,4,
                       3,3,3,1};
    matrix expected_m = createMatrixFromArray(expected_a, 4, 4);
    sortByDistances(m);
    assert(areTwoMatricesEqual(&m, &expected_m));
    freeMemMatrix(&expected_m);
    freeMemMatrix(&m);
}
//...........................................................................................
//tusk 10

int countNUnique(long long *arr, int n){
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (arr[i] > arr[j]) {

                long long temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
    int ans = 1;
    for(int i = 0; i < n-1; i++){
        if(arr[i] != arr[i+1]){
            ans++;
        }
    }
    return ans;
}
int countEqClassesByRowsSum(matrix m){
    long long arr[m.nRows];
    for(int i = 0; i < m.nRows; i++){
        arr[i] = 0;
        for (int j = 0; j < m.nCols; j++){
            arr[i] += m.values[i][j];
        }
    }
    return countNUnique(arr, m.nRows);
}
//обычный тест, все суммы строк различны
void test_countEqClassesByRowsSum_base(){
    int arr[]= {22,5,
                6,12,
                3,1,
                1,1,
                10,1,
                5,2,
                6,0,
                0,0};
    matrix m = createMatrixFromArray(arr, 8, 2);
    assert(countEqClassesByRowsSum(m) == 8);
    freeMemMatrix(&m);
}
//используя INT_MAX
void test_countEqClassesByRowsSum_INT_MAX(){
    int arr[]= {22,INT_MAX,
                INT_MAX,12,
                3,1,
                INT_MAX,1,
                10,1,
                5,2,
                6,INT_MAX,
                0,INT_MAX};
    matrix m = createMatrixFromArray(arr, 8, 2);
    assert(countEqClassesByRowsSum(m) == 8);
    freeMemMatrix(&m);
}
//есть одинаковые
void test_countEqClassesByRowsSum_equale(){
    int arr[]= {1,INT_MAX,
                INT_MAX,12,
                3,1,
                INT_MAX,1,
                10,1,
                1,3,
                6,INT_MAX,
                0,INT_MAX};
    matrix m = createMatrixFromArray(arr, 8, 2);
    assert(countEqClassesByRowsSum(m) == 6);
    freeMemMatrix(&m);
}
//нет уникальных
void test_countEqClassesByRowsSum_ALLequale(){
    int arr[]= {1,INT_MAX,
                INT_MAX,1,
                INT_MAX,1,
                INT_MAX,1,
                INT_MAX,1,
                INT_MAX,1,
                INT_MAX,1,
                INT_MAX,1};
    matrix m = createMatrixFromArray(arr, 8, 2);
    assert(countEqClassesByRowsSum(m) == 1);
    freeMemMatrix(&m);
}
//.............................................................................................
//tusk 11
int getNSpecialElement(matrix m){
    int count = 0;
    for(int j = 0; j < m.nCols; j++){
        int max_value = INT_MIN;
        int sum = 0;
        for(int i = 0; i < m.nRows; i++){
            max_value = max_value > m.values[i][j] ? max_value : m.values[i][j];
            sum += m.values[i][j];
        }
        if(max_value > sum - max_value)
            count++;
    }
    return count;
}

//обычный случай
void test_getNSpecialElement_base(){
    int arr[]= {3,5,5,4,
                2,3,6,7,
                12,2,1,2};
    matrix m = createMatrixFromArray(arr, 3, 4);
    assert(getNSpecialElement(m) == 2);
    freeMemMatrix(&m);
}
//нет особых чисел
void test_getNSpecialElement_voidValue(){
    int arr[]= {3,5,5,4,
                2,3,6,5,
                4,2,1,2};
    matrix m = createMatrixFromArray(arr, 3, 4);
    assert(getNSpecialElement(m) == 0);
    freeMemMatrix(&m);
}
//в каждом столбце особое число
void test_getNSpecialElement_AllCols(){
    int arr[]= {3,5,5,4,
                2,3,8,7,
                12,10,1,2};
    matrix m = createMatrixFromArray(arr, 3, 4);
    assert(getNSpecialElement(m) == m.nCols);
    freeMemMatrix(&m);
}
//.......................................................................................................
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
    test_getMinInArea_base(); //обычный случай
    test_getMinInArea_atBorder();//максимальное значение у края
    test_getMinInArea_inFirstRow();//максимальное значение в первой строке
    test_getMinInArea_inSecondRow(); //максимальное значение у правого края во второй строке
    test_sortByDistances_base();//обычный случай
    test_sortByDistances_equaleDist();//одинаковые дистанции
    test_sortByDistances_alreadySort();//уже отсортирован
    test_countEqClassesByRowsSum_base(); //обычный тест, все суммы строк различны
    test_countEqClassesByRowsSum_INT_MAX(); //используя INT_MAX
    test_countEqClassesByRowsSum_equale(); //есть одинаковые
    test_countEqClassesByRowsSum_ALLequale(); //нет уникальных
    test_getNSpecialElement_base(); //обычный случай
    test_getNSpecialElement_voidValue(); //нет особых чисел
    test_getNSpecialElement_AllCols(); //в каждом столбце особое число
}

int main(){
    test_matrix();
    return 0;
}