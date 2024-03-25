#include "vector.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

//создание вектора
vector createVector(size_t n){
    vector res;
    if(n == 0){
        res.data = NULL;
    } else{
        res.data = malloc(sizeof(int) * n);
        if(!res.data){
            fprintf(stderr, "bad alloc");
            exit(1);
        }
    }
    res.size = 0;
    res.capacity = n;
    return res;
}

// изменяет количество памяти
void reserve(vector *v, size_t newCapacity){
    if(newCapacity == 0){
        free(v->data);
        v->size = 0;
        v->capacity = 0;
    }
    v->data = realloc(v->data, newCapacity);
    v->capacity = newCapacity;
}

//удаляет элементы из контейнера, но не освобождает выделенную память
void clear(vector *v){
    v->size = 0;
}

//освобождает память, выделенную под
//неиспользуемые элементы.
void shrinkToFit(vector *v){
    v->data = realloc(v->data, v->size * sizeof(int));
    v->capacity = v->size;
}

//освобождает память, выделенную вектору
void deleteVector(vector *v){
    free(v->data);
    v->size = 0;
    v->capacity = 0;

}
//true если пустой
bool isEmpty(vector *v){
    return v->size == 0;
}

//true если полный
bool isFull(vector *v){
    return v->size == v->capacity;
}

//которая
//возвращает i-ый элемент вектора v
int getVectorValue(vector *v, size_t i){
    return v->data[i];
}

//добавляет элемент x в конец вектора v
void pushBack(vector *v, int x){
    if(v->size == v->capacity && v->size != 0){
        reserve(v, v->capacity*2);
    }
    if(v->capacity == 0){
        reserve(v, 1);
    }
    v->data[v->size] = x;
    v->size++;
}

//удаляет последний элемент из вектора
void popBack(vector *v){
    if(v->size==0){
        fprintf(stderr, "vector is empty");
        exit(1);
    }
    v->size--;
}

//возвращает указатель на
//index-ый элемент вектора
int* atVector(vector *v, size_t index){
    if(index >= v->size){
        fprintf(stderr, "IndexError: a[%Iu]  is not exists", index);
        exit(1);
    }
    return &(v->data[index]);
}

// указатель на последний элемент
int* back(vector *v){
    if(v->size == 0){
        fprintf(stderr, "vector is empty");
        exit(1);
    }
    return &(v->data[v->size-1]);
}

// указатель на первый элемент
int* front(vector *v){
    if(v->size == 0){
        fprintf(stderr, "vector is empty");
        exit(1);
    }
    return &(v->data[0]);
}
