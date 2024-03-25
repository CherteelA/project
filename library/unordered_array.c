#include <stdlib.h>
#include "unordered_array.h"


// возвращает пустое множество для capacity элементов
unordered_array_set unordered_array_set_create(size_t capacity) {
    return (unordered_array_set) {malloc(sizeof(int) * capacity), 0, capacity};
}

// возвращает множество, состоящее из элементов массива a размера size.
unordered_array_set unordered_array_set_create_from_array (const int *a , size_t size, size_t capacity){
    int *data = malloc(sizeof(int) * size);
    for(int i = 0; i < size; i++){
        data[i] = a[i];
    }
    return (unordered_array_set) {data, size, capacity};
}

// возвращает позицию элемента в множестве,
// если значение value имеется в множестве set, иначе - n
size_t unordered_array_set_in ( unordered_array_set *set , int value ){
    for(size_t i = 0; i < set->size; i++){
        if (set->data[i] == value)
            return i;
    }
    return set->size;
}

// истина если элемент есть в множестве
bool unordered_array_value_in_set(unordered_array_set *set , int value ){
    if(set->size == 0){
        return true;
    }
    for(size_t i = 0; i < set->size; i++){
        if (set->data[i] == value)
            return true;
    }
    return false;
}

// возвращает значение ’истина’, если subset является подмножеством set
// иначе - ’ложь’
bool unordered_array_set_isSubset ( unordered_array_set subset ,unordered_array_set set ){
    for(int i = 0; i < subset.size; i++){
        if(!unordered_array_value_in_set(&set, subset.data[i]))
            return false;
    }
    return true;
}

// возвращает значение ’истина’, если элементы множеств set1 и set2 равны
// иначе - ’ложь’
bool unordered_array_set_isEqual (unordered_array_set set1 , unordered_array_set set2){
    if(set2.size != set1.size)
        return false;
    for(int i = 0; i < set1.size; i++){
        if(!unordered_array_value_in_set(&set2, set1.data[i]))
            return false;
    }
    return true;
}

// возбуждает исключение, если в множество по адресу set
// нельзя вставить элемент value
void unordered_array_set_isAbleAppend(unordered_array_set *set, int value) {
    assert(set->size < set->capacity);
    assert(!unordered_array_value_in_set(set, value));
}

// добавляет элемент value в множество set
void unordered_array_set_insert (unordered_array_set * set , int value){
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
void unordered_array_set_deleteElement (unordered_array_set * set , int value){
    for(size_t i = unordered_array_set_in(set, value); i < set->size; i++){
           set->data[i] = set->data[i+1];
    }
    set->size--;
    unordered_array_set_delete((unordered_array_set *) &set);
}

// возвращает объединение множеств set1 и set2.
unordered_array_set unordered_array_set_union (unordered_array_set set1 , unordered_array_set set2){
    unordered_array_set res = unordered_array_set_create(set1.size + set2.size);
    for(int i = 0; i < set1.size; i++){
        res.data[i] = set1.data[i];
    }
    res.size = set1.size;
    for(int i = 0; i < set2.size; i++){
        if(!unordered_array_value_in_set(&set1, set2.data[i])){

            unordered_array_set_insert(&res, set2.data[i]);
        }
    }
    unordered_array_set_delete(&res);
    return res;
}

// возвращает пересечение множеств set1 и set2
unordered_array_set unordered_array_set_intersection(unordered_array_set set1 , unordered_array_set set2){
    unordered_array_set res = unordered_array_set_create(set1.size + set2.size);
    for(int i = 0; i < set1.size; i++){
        if(unordered_array_value_in_set(&set2, set1.data[i])){
            unordered_array_set_insert(&res, set1.data[i]);
        }
    }
    unordered_array_set_delete(&res);
    return res;
}

// возвращает разность множеств set1 и set2
unordered_array_set unordered_array_set_difference (unordered_array_set set1 , unordered_array_set set2){
    unordered_array_set res = unordered_array_set_create(set1.size + set2.size);
    for(int i = 0; i < set1.size; i++) {
        if(!unordered_array_value_in_set(&set2, set1.data[i])){
            unordered_array_set_insert(&res, set1.data[i]);
        }
    }
    unordered_array_set_delete(&res);
    return res;
}
// возвращает дополнение до универсума множества set
unordered_array_set unordered_array_set_complement (unordered_array_set set , unordered_array_set universumSet){
    unordered_array_set res = unordered_array_set_create(set.size);
    for(int i = 0; i < universumSet.size; i++){
        if(!unordered_array_value_in_set(&set, universumSet.data[i])){
            unordered_array_set_insert(&res, universumSet.data[i]);
        }
    }
    unordered_array_set_delete(&res);
    return res;
}

// возвращает симметрическую разность множеств set1 и set2
unordered_array_set unordered_array_set_symmetricDifference (unordered_array_set set1 , unordered_array_set set2){
    unordered_array_set res = unordered_array_set_create(set1.size + set2.size);
    for(int i = 0; i < set1.size; i++){
        if(!unordered_array_value_in_set(&set2, set1.data[i])){
            unordered_array_set_insert(&res, set1.data[i]);
        }
    }
    for(int i = 0; i < set2.size; i++){
        if(!unordered_array_value_in_set(&set1, set2.data[i])){
            unordered_array_set_insert(&res, set2.data[i]);
        }
    }
    unordered_array_set_delete(&res);
    return res;
}

// проверяет, является ли множество set1 включенным в множество set2.
bool unordered_array_set_isInclusion(unordered_array_set set1, unordered_array_set set2) {
    int co = 0;
    for(int i = 0; i < set1.size; i++){
        bool flag = false;
        for(int j = 0; j < set2.size; j++){
            if(set1.data[i] == set2.data[j]){
                flag = true;
            }
        }
        if(flag)
            co++;
    }
    return co == set1.size;
}

//проверяет, является ли set1 строгим подмножеством set2, то есть содержит ли set1 все элементы set2 и имеет меньшее количество элементов.
bool unordered_array_set_isStrictInclusion(unordered_array_set set1, unordered_array_set set2){
    int co = 0;
    for(int i = 0; i < set1.size; i++){
        bool flag = false;
        for(int j = 0; j < set2.size; j++){
            if(set1.data[i] == set2.data[j]){
                flag = true;
            }
        }
        if(flag)
            co++;
    }
    return co == set1.size;
}

// вывод множества set
void unordered_array_set_print ( unordered_array_set set ){
    for(int i = 0; i < set.size; i++){
        printf("%d", set.data[i]);
    }
    printf("\n");
}

//читска памяти
void unordered_array_set_delete(unordered_array_set *set){
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