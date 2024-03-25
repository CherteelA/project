
#include <stdio.h>
#include <stdlib.h>
#include "ordered_array.h"
#include "unordered_array.h"
#include <math.h>

// возвращает пустое множество, в которое можно вставить capacity элементов
ordered_array_set ordered_array_set_create (size_t capacity){
    return (ordered_array_set) {malloc(sizeof(int) * capacity), 0, capacity};
}

// возвращает множество, состоящее из элементов массива a размера size
ordered_array_set ordered_array_set_create_from_array (const int *a, size_t size, size_t capacity){
    ordered_array_set res = ordered_array_set_create(capacity);
    for(int i = 0; i < size; i++){
        res.data[i] = a[i];
    }
    res.size = size;
    return res;
}

// возвращает значение позицию элемента в множестве,
// если значение value имеется в множестве set,
// иначе - n
size_t ordered_array_set_in (ordered_array_set *set, int value){
    for(int i = 0; i < set->size; i++){
        if (set->data[i] == value){
            return i;
        }
    }
    return set->size-1;
}

// истина если элемент есть в множестве
bool ordered_array_value_in_set(ordered_array_set set, int value){
    for(size_t i = 0; i < set.size; i++){
        if (set.data[i] == value)
            return true;
    }
    return false;
}

// возвращает значение ’истина’, если элементы множеств set1 и set2 равны
// иначе - ’ложь’
bool ordered_array_set_isEqual (ordered_array_set set1, ordered_array_set set2){
    if (set1.size != set2.size) {
        return 0;
    }
    return memcmp(set1.data, set2.data, sizeof(int) * set1.size) == 0;
}

// возвращает значение ’истина’, если subset является подмножеством set
// иначе - ’ложь’
bool ordered_array_set_isSubset (ordered_array_set subset, ordered_array_set set){
    int co = 0;
    for(int i = 0; i < subset.size; i++){
        if(ordered_array_value_in_set(set, subset.data[i])){
            co++;
        }
    }
    return co == subset.size;
}

// возбуждает исключение, если в множество по адресу set
// нельзя вставить элемент
void ordered_array_set_isAbleAppend (ordered_array_set *set){
    assert(set->size < set->capacity);
}

// добавляет элемент value в множество set
void ordered_array_set_insert (ordered_array_set *set, int value){

    assert(!ordered_array_value_in_set(*set, value));

    if(set->size == set->capacity) {
        int a[set->size];
        for(int i = 0; i < set->size; i++){
            a[i] = set->data[i];
        }
        free(set->data);
        set->data = malloc(sizeof(int) * (set->capacity*2));
        set->capacity*=2;
        for(int i = 0; i < set->size; i++){
            set->data[i] = a[i];
        }
    }
    set->data[set->size] = value;
    set->size++;
}

// удаляет элемент value из множества set
void ordered_array_set_deleteElement (ordered_array_set *set, int value){
    for(size_t i = ordered_array_set_in(set, value); i < set->size; i++){
        set->data[i] = set->data[i+1];
    }
    set->size--;
    ordered_array_set_delete(set);
}

// возвращает объединение множеств set1 и set2
ordered_array_set ordered_array_set_union (ordered_array_set set1 , ordered_array_set set2){
    int a[set1.size + set2.size];
    for (int i = 0; i < set1.size; i++){
        a[i] = set1.data[i];
    }
    printf("\n");
    size_t size = set1.size;
    for(int i = 0; i < set2.size; i++){
        if(!if_value_in_array(set1.data, set1.size, set2.data[i])){
            a[size] = set2.data[i];
            size++;
        }
    }
    ordered_array_set ans = ordered_array_set_create_from_array(a, size, size);
    order(&ans);
    return ans;
}
//расставляет по порядку
void order(ordered_array_set *set){
    if(set->size > 3) {
        int min1 = pow(10, 8);
        for (int i = 0; i < set->size; i++) {
            if (min1 > set->data[i]) {
                min1 = set->data[i];
            }
        }


        int min2 = pow(10, 8);
        for (int i = 0; i < set->size; i++) {
            if (min2 > set->data[i] && set->data[i] > min1) {
                min2 = set->data[i];
            }
        }
        int min3 = pow(10, 8);
        for (int i = 0; i < set->size; i++) {
            if (min3 > set->data[i] && set->data[i] > min2) {
                min3 = set->data[i];
            }
        }
        int min4 = pow(10, 8);
        for (int i = 0; i < set->size; i++) {
            if (min4 > set->data[i] && set->data[i] > min3) {
                min4 = set->data[i];
            }
        }

        set->data[ordered_array_set_in(set, min1)] = set->data[0];
        set->data[0] = min1;
        set->data[ordered_array_set_in(set, min2)] = set->data[1];
        set->data[1] = min2;
        set->data[ordered_array_set_in(set, min3)] = set->data[2];
        set->data[2] = min3;
        set->data[ordered_array_set_in(set, min4)] = set->data[3];
        set->data[3] = min4;
        for (int i = 2; i < set->size - 1; i++) {
            if (set->data[i + 1] < set->data[i]) {
                int t = set->data[i];
                set->data[i] = set->data[i + 1];
                set->data[i + 1] = t;
                i -= 2;
            }
        }
    }
    if(set->size == 3){
        int min1 = pow(10, 8);
        for (int i = 0; i < set->size; i++) {
            if (min1 > set->data[i]) {
                min1 = set->data[i];
            }
        }


        int min2 = pow(10, 8);
        for (int i = 0; i < set->size; i++) {
            if (min2 > set->data[i] && set->data[i] > min1) {
                min2 = set->data[i];
            }
        }
        int min3 = pow(10, 8);
        for (int i = 0; i < set->size; i++) {
            if (min3 > set->data[i] && set->data[i] > min2) {
                min3 = set->data[i];
            }
        }
        set->data[0] = min1;
        set->data[1] = min2;
        set->data[2] = min3;

    }
    if(set->size == 2){
        if(set->data[0] > set->data[1]){
            int t = set->data[0];
            set->data[0] = set->data[1];
            set->data[1] = t;
        }
    }
}

// освобождает память, занимаемую множеством set
void ordered_array_set_delete (ordered_array_set * set){
    if(set->size < set->capacity/2){
        int a[set->size];
        for(int i = 0; i < set->size; i++){
            a[i] = set->data[i];
        }
        free(set->data);
        set->data = malloc(sizeof(int) * (set->capacity/2));
        set->capacity/=2;
        for(int i = 0; i < set->size; i++){
            set->data[i] = a[i];
        }
    }
}

// возвращает пересечение множеств set1 и set2
ordered_array_set ordered_array_set_intersection (ordered_array_set set1, ordered_array_set set2){

    ordered_array_set res = ordered_array_set_create(set1.size + set2.size);
    int a[set1.size + set2.size];
    size_t size = 0;
    for(int i = 0; i < set1.size; i++){

        if(ordered_array_value_in_set(set2, set1.data[i])){
            append_(a, &size, set1.data[i]);
        }
    }

    res = ordered_array_set_create_from_array(a, size, size);
    order(&res);
    return res;
}

// возвращает разность множеств set1 и set2
ordered_array_set ordered_array_set_difference (ordered_array_set set1, ordered_array_set set2){
    ordered_array_set res = ordered_array_set_create(set1.size + set2.size);
    int a[set1.size + set2.size];
    size_t size = 0;
    for(int i = 0; i < set1.size; i++)
    {
        if(!ordered_array_value_in_set(set2, set1.data[i])){
            append_(a, &size, set1.data[i]);
        }
    }

    res = ordered_array_set_create_from_array(a, size, size);

    order(&res);
    return res;
}

// возвращает симметрическую разность множеств set1 и set2
ordered_array_set ordered_array_set_symmetricDifference(ordered_array_set set1, ordered_array_set set2){
    ordered_array_set res_first;
    ordered_array_set res_second;
    ordered_array_set res = ordered_array_set_create(set1.size + set2.size);
    res_first = ordered_array_set_difference(set2, set1);
    res_second = ordered_array_set_difference(set1, set2);

    res = ordered_array_set_union(res_first, res_second);
    order(&res);
    free(res_second.data);
    free(res_first.data);
    return res;
}
ordered_array_set ordered_array_set_complement(ordered_array_set set, ordered_array_set universumSet){
    ordered_array_set res = ordered_array_set_create(set.size);
    for(int i = 0; i < universumSet.size; i++){
        if(!ordered_array_value_in_set(set, universumSet.data[i])){
            ordered_array_set_insert(&res, universumSet.data[i]);
        }
    }
    ordered_array_set_delete(&res);
    order(&res);
    return res;
}

// проверяет, является ли множество set1 включенным в множество set2
bool ordered_array_set_isInclusion(ordered_array_set const set1, ordered_array_set const set2){
    if(set2.size < set1.size)
        return false;
    int count = 0;
    for(int i = 0; i < set1.size; i++){
        if(ordered_array_value_in_set(set2, set1.data[i])){
            count++;
        }
    }
    return count == set1.size;
}

//проверяет, является ли set1 строгим подмножеством set2, то есть содержит ли set1 все элементы set2 и имеет меньшее количество элементов.
bool ordered_array_set_isStrictInclusion(ordered_array_set const set1, ordered_array_set const set2){
    if(set2.size < set1.size)
        return false;
    int count = 0;
    for(int i = 0; i < set1.size; i++){
        if(ordered_array_value_in_set(set2, set1.data[i])){
            count++;
        }
    }
    return count == set1.size && set1.size!=set2.size;
}

// вывод множества set
void ordered_array_set_print (ordered_array_set set){
    for(int i = 0; i < set.size; i++)
        printf("%d ", set.data[i]);
    printf("\n");
}
