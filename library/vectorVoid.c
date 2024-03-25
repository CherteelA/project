#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include "vectorVoid.h"

//создание вектора
vectorVoid createVectorV(size_t n, size_t baseTypeSize){
    vectorVoid vecV;
    if(n == 0){
        vecV.data = NULL;
        vecV.size = 0;
        vecV.capacity = 0;
        vecV.baseTypeSize = baseTypeSize;
        return vecV;
    }

    vecV.data = malloc(n * sizeof(int));

    if(vecV.data == NULL){
        fprintf(stderr, "bad alloc");
        exit(1);
    }
    vecV.size = 0;
    vecV.capacity = n;
    vecV.baseTypeSize = baseTypeSize;
    return vecV;
}

// изменяет количество памяти
void reserveV(vectorVoid *v, size_t newCapacity) {
    if (newCapacity > v->capacity) {
        void *newData = realloc(v->data, newCapacity * v->baseTypeSize);
        if (newData == NULL) {
            fprintf(stderr, "Failed to reallocate memory for the vector\n");
            exit(1);
        }
        v->data = newData;
        v->capacity = newCapacity;
    } else if (newCapacity == 0) {
        v->data = NULL;
    } else if (newCapacity < v->size) {
        v->size = newCapacity;
    }
}
//освобождает память, выделенную под
//неиспользуемые элементы.
void shrinkToFitV(vectorVoid *v){
    *v->data = realloc(v->data, v->size * v->baseTypeSize);
    v->capacity = v->size;
}
//удаляет элементы из контейнера, но не освобождает выделенную память
void clearV(vectorVoid *v){
    v->size = 0;
}
//освобождает память, выделенную вектору
void deleteVectorV(vectorVoid *v){
    free(v->data);
    v->capacity = 0;
    v->size = 0;
    v->data = NULL;
}

//true если пустой
bool isEmptyV(vectorVoid *v){
    return v->size == 0;
}
//true если полный
bool isFullV(vectorVoid *v){
    return v->size == v->capacity;
}
//записывает по адресу destination index-ый элемент вектора v
void getVectorValueV(vectorVoid *v, size_t index, void *destination){
    char *source = (char *) v->data + index * v->baseTypeSize;
    memcpy(destination, source, v->baseTypeSize);
}
//записывает на index-ый элемент вектора v значение, расположенное по
//адресу source
void setVectorValueV(vectorVoid *v, size_t index, void *source){
    char *destination = (char *) v->data + index * v->baseTypeSize;
    memcpy(destination, source, v->baseTypeSize);
}
//удаляет последний элемент из вектора
void popBackV(vectorVoid *v){
    if(v->size == 0){
        fprintf(stderr, "vector is empty");
        exit(1);
    }
    v->size--;
}

void pushBackV(vectorVoid *v, void *source) {
    if (v == NULL || source == NULL) {
        return;
    }
    if (v->capacity == 0) {
        reserveV(v, 1);
    } else if (v->capacity == v->size) {
        reserveV(v, v->capacity * 2);
    }
    setVectorValueV(v, v->size, source);
    v->size++;
}