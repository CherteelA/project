cmake_minimum_required(VERSION 3.27)
project(laba C)

set(CMAKE_C_STANDARD 11)

add_executable(laba main.c
        library/array.c
        library/bitset.c
        library/ordered_array.c
        library/unordered_array.c
        test.c
        test.h
        library/vector.c
        library/vector.h
        library/vectorVoid.h
        library/vectorVoid.c
        library/matrix.c
        library/matrix.h)
