
#ifndef LABA_VECTOR_H
#define LABA_VECTOR_H

#include <stddef.h>
#include <stdbool.h>
typedef struct vector {
    int *data; // указатель на элементы вектора
    size_t size; // размер вектора
    size_t capacity; // вместимость вектора
} vector;
//создание вектора
vector createVector(size_t n);
// изменяет количество памяти
void reserve(vector *v, size_t newCapacity);
//удаляет элементы из контейнера, но не освобождает выделенную память
void clear(vector *v);
//освобождает память, выделенную под
//неиспользуемые элементы.
void shrinkToFit(vector *v);
//освобождает память, выделенную вектору
void deleteVector(vector *v);
//true если пустой
bool isEmpty(vector *v);
//true если полный
bool isFull(vector *v);
//которая
//возвращает i-ый элемент вектора v
int getVectorValue(vector *v, size_t i) ;
//добавляет элемент x в конец вектора v
void pushBack(vector *v, int x);
//удаляет последний элемент из вектора
void popBack(vector *v);
//возвращает указатель на
//index-ый элемент вектора
int* atVector(vector *v, size_t index);
//указатель на последний элемент
int* back(vector *v);
// указатель на первый элемент
int* front(vector *v);
#endif //LABA_VECTOR_H
