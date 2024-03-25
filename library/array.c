#include <stdio.h>
#include <assert.h>
#include "array.h"

//ввод
void inputArray_ (int * a , size_t n ){
    for(int i = 0; i < n; i++){
        scanf("%d", &a[i]);
    }
}
//ввывод
void outputArray_ ( const int *a , size_t n ){
    for(int i = 0; i < n; i++){
        printf("%d", a[i]);
    }
}

//нахождение индекса по значению
size_t linearSearch_ ( const int *a , const size_t n , int x ){
    for(int i = 0; i < n; i++){
        if(a[i] == x)
            return i;
    }
    return n;
}

//истина если элемент есть в массиве
bool if_value_in_array(int a[], int size, int value){
    for(int i = 0; i < size; i++){
        if(a[i] == value)
            return true;
    }
    return false;
}

// возвращает позицию вхождения элемента x
// в отсортированном массиве a размера n при его наличии, иначе - SIZE_MAX
int binarySearch_( const int *a , size_t n , int x ) {
    size_t left = 0;
    size_t right = n - 1;
    while (left <= right) {
        size_t middle = left + (right - left) / 2;
        if (a[middle] < x)
            left = middle + 1;
        else if (a[middle] > x)
            right = middle - 1;
        else {
            return middle;
            }
        }
    return n;
    }
// возвращает позицию первого элемента равного или большего x
// в отсортированном массиве a размера n
// при отсутствии такого элемента возвращает n
size_t binarySearchMoreOrEqual_ ( const int *a , const size_t n , int x ){
    size_t left = 0;
    size_t right = n - 1;
    int f = 1;
    size_t middle = left + (right - left) / 2;
    while (right - left > 1) {
         if (f == 1) {
             middle = left + (right - left) / 2;
         }
        if (a[middle] < x)
            left = middle + 1;
        else if (a[middle] > x & a[middle - 1] >= x) {
            middle--;
            f = 0;
        }
        else
            return middle;
    }
    return n;
}

// вставка элемента со значением value
// в массив data размера n на позицию pos
void insert_ (int * const a , size_t * const n , const size_t pos , const int value ){
    assert(pos<*n) ;
    if (* n != 0){
        size_t lowBound = ( pos == 0) ? *n : pos;
        (*n)++;
        for ( size_t i = * n ; i !=lowBound; i--)
            a [i] = a[i-1];
        a [pos] = value;
        }else {
            (*n)++;
            a[pos] = value;
    }
}

// добавление элемента value в конец массива data размера n
void append_ (int *a , size_t *n , int value ){

    int t = *n;
    a[t] = value;
    (*n)++;
}

// удаление из массива data размера n элемента на позиции pos
// с сохранением порядка оставшихся элементов
void deleteByPosSaveOrder_ (int *a , size_t *n , size_t pos ){
    if(*n > 0){
        for(size_t i = pos; i < *n-1;i++){
            a[i] = a[i+1];
        }
        (*n)--;
    }
}

// удаление из массива data размера n элемента на позиции pos
// без сохранения порядка оставшихся элементов
// размер массива data уменьшается на единицу
void deleteByPosUnsaveOrder_(int *a , size_t *n , size_t pos){
    a[pos] = a[*n-1];
    (*n)--;
}

// возвращает значение ’истина’ если все элементы
// массива data размера n соответствует функции-предикату predicate
// иначе - ’ложь’
bool all_ ( const int* a , size_t n , int (* predicate ) (int) ) {
    for (size_t i = 0; i < n; ++i) {
        if (!predicate(a[i]))
            return false;
    }
    return true;
}

// возвращает значение ’истина’ если хотя бы один элемент
// массива data размера n соответствует функции-предикату predicate
// иначе - ’ложь’
bool any_ ( const int *a , size_t n , int (* predicate ) (int) ) {
    for (size_t i = 0; i < n; ++i) {
        if (predicate(a[i]))
            return true;
    }
    return false;
}

// применяет функцию predicate ко всем элементам массива source
// размера n и сохраняет результат в массиве dest размера n
void forEach_ ( const int * source , int * dest , size_t n , const int (*
predicate ) ( int) ) {
    for(size_t i = 0; i < n; i++) {
        dest[i] = predicate(source[i]);
    }
}

// возвращает количество элементов массива data размера n
// удовлетворяющих функции-предикату predicate
int countIf_ ( const int * a , size_t n , int (* predicate ) (int) ) {
    int count = 0;
    for (size_t i = 0; i < n; ++i) {
        count += predicate(a[i]);
    }
    return count;
}

// удаляет из массива data размера n все элементы, удовлетворяющие
// функции-предикату deletePredicate, записывает в n новый размер
// массива
void deleteIf_ (int * const a , size_t * const n , int (* deletePredicate ) (int) ) {
    size_t i_read = 0;
    while (i_read < *n && !deletePredicate(a[i_read]))
        i_read++;
    size_t i_write = i_read;
    while (i_read < *n) {
        if (!deletePredicate(a[i_read])){
            a[i_write] = a[i_read];
            i_write++;
        }
        i_read++;
    }
    *n = i_write;
}