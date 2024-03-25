#include "library/ordered_array.h"
#include "library/unordered_array.h"
#include "library/bitset.h"
#include <stdlib.h>
#include "test.h"


void test(){
    test_bitset_union();
    test_bitset_intersection();
    test_bitset_difference();
    test_bitset_symmetricDifference();
    test_bitset_complement();
    test_unordered_array_set_union();
    test_unordered_array_set_intersection();
    test_unordered_array_set_difference();
    test_unordered_array_set_complement();
    test_unordered_array_set_symmetricDifference();
    test_ordered_array_set_union();
    test_ordered_array_set_intersection();
    test_ordered_array_set_difference();
    test_ordered_array_set_symmetricDifference();
    test_ordered_array_set_complement();
}


void test_bitset_union1(){
    bitset set1 = bitset_create(25);
    bitset_insert(&set1, 1);
    bitset_insert(&set1, 3);
    bitset_insert(&set1, 5);
    bitset_insert(&set1, 7);
    bitset_insert(&set1, 9);

    bitset set2 = bitset_create(26);
    bitset_insert(&set2, 2);
    bitset_insert(&set2, 4);
    bitset_insert(&set2, 6);
    bitset_insert(&set2, 8);
    bitset_insert(&set2, 25);

    bitset res = bitset_union(set1,set2);

    bitset exp_res = bitset_create(26);
    bitset_insert(&exp_res, 2);
    bitset_insert(&exp_res, 4);
    bitset_insert(&exp_res, 6);
    bitset_insert(&exp_res, 8);
    bitset_insert(&exp_res, 25);
    bitset_insert(&exp_res, 1);
    bitset_insert(&exp_res, 3);
    bitset_insert(&exp_res, 5);
    bitset_insert(&exp_res, 7);
    bitset_insert(&exp_res, 9);
    assert(bitset_isEqual(res, exp_res));
}

void test_bitset_union2(){
    bitset set1 = bitset_create(25);
    bitset_insert(&set1, 1);
    bitset_insert(&set1, 3);
    bitset_insert(&set1, 5);
    bitset_insert(&set1, 7);
    bitset_insert(&set1, 9);

    bitset set2 = bitset_create(25);


    bitset res = bitset_union(set1,set2);

    bitset exp_set = bitset_create(25);
    bitset_insert(&exp_set, 1);
    bitset_insert(&exp_set, 3);
    bitset_insert(&exp_set, 5);
    bitset_insert(&exp_set, 7);
    bitset_insert(&exp_set, 9);
    assert(bitset_isEqual(res, exp_set));
}
void test_bitset_union(){
    test_bitset_union1();
    test_bitset_union2();
}


void test_bitset_intersection1(){
    bitset set1 = bitset_create(25);
    bitset_insert(&set1, 1);
    bitset_insert(&set1, 3);
    bitset_insert(&set1, 5);
    bitset_insert(&set1, 7);
    bitset_insert(&set1, 9);

    bitset set2 = bitset_create(25);
    bitset_insert(&set2, 9);
    bitset_insert(&set2, 4);
    bitset_insert(&set2, 5);
    bitset_insert(&set2, 7);
    bitset_insert(&set2, 23);

    bitset res = bitset_intersection(set2,set1);

    bitset exp_res = bitset_create(25);
    bitset_insert(&exp_res, 9);
    bitset_insert(&exp_res, 7);
    bitset_insert(&exp_res, 5);
    assert(bitset_isEqual(res, exp_res));
}

void test_bitset_intersection2(){
    bitset set1 = bitset_create(25);
    bitset_insert(&set1, 1);
    bitset_insert(&set1, 0);
    bitset_insert(&set1, 5);
    bitset_insert(&set1, 7);
    bitset_insert(&set1, 9);

    bitset set2 = bitset_create(25);
    bitset_insert(&set2, 0);
    bitset_insert(&set2, 1);
    bitset_insert(&set2, 7);
    bitset_insert(&set2, 5);
    bitset_insert(&set2, 9);

    bitset res = bitset_intersection(set2,set1);

    bitset exp_res = bitset_create(25);
    bitset_insert(&exp_res, 9);
    bitset_insert(&exp_res, 5);
    bitset_insert(&exp_res, 7);
    bitset_insert(&exp_res, 1);
    bitset_insert(&exp_res, 0);
    assert(bitset_isEqual(res, exp_res));
}

void test_bitset_intersection(){
    test_bitset_intersection2();
    test_bitset_intersection1();
}

void test_bitset_difference1(){
    bitset set1 = bitset_create(25);
    bitset_insert(&set1, 1);
    bitset_insert(&set1, 0);
    bitset_insert(&set1, 5);
    bitset_insert(&set1, 7);
    bitset_insert(&set1, 9);

    bitset set2 = bitset_create(25);
    bitset_insert(&set2, 7);
    bitset_insert(&set2, 0);
    bitset_insert(&set2, 10);
    bitset_insert(&set2, 11);

    bitset res = bitset_difference(set1,set2);

    bitset exp_res = bitset_create(25);
    bitset_insert(&exp_res, 9);
    bitset_insert(&exp_res, 5);
    bitset_insert(&exp_res, 1);

    assert(bitset_isEqual(res, exp_res));
}
void test_bitset_difference2(){
    bitset set1 = bitset_create(25);
    bitset_insert(&set1, 1);
    bitset_insert(&set1, 0);
    bitset_insert(&set1, 5);
    bitset_insert(&set1, 7);
    bitset_insert(&set1, 9);

    bitset set2 = bitset_create(25);
    bitset_insert(&set2, 7);
    bitset_insert(&set2, 0);
    bitset_insert(&set2, 5);
    bitset_insert(&set2, 11);

    bitset res = bitset_difference(set1,set2);

    bitset exp_res = bitset_create(25);
    bitset_insert(&exp_res, 9);
    bitset_insert(&exp_res, 1);

    assert(bitset_isEqual(res, exp_res));
}
void test_bitset_difference(){
    test_bitset_difference1();
    test_bitset_difference2();
}

void test_bitset_symmetricDifference1(){
    bitset set1 = bitset_create(25);
    bitset_insert(&set1, 1);
    bitset_insert(&set1, 0);
    bitset_insert(&set1, 5);
    bitset_insert(&set1, 7);
    bitset_insert(&set1, 9);

    bitset set2 = bitset_create(25);
    bitset_insert(&set2, 7);
    bitset_insert(&set2, 0);
    bitset_insert(&set2, 5);

    bitset res = bitset_symmetricDifference(set1,set2);

    bitset exp_res = bitset_create(25);
    bitset_insert(&exp_res, 9);
    bitset_insert(&exp_res, 1);

    assert(bitset_isEqual(res, exp_res));
}
void test_bitset_symmetricDifference2(){
    bitset set1 = bitset_create(25);
    bitset_insert(&set1, 1);
    bitset_insert(&set1, 0);
    bitset_insert(&set1, 5);
    bitset_insert(&set1, 7);
    bitset_insert(&set1, 9);

    bitset set2 = bitset_create(25);
    bitset_insert(&set2, 7);
    bitset_insert(&set2, 0);
    bitset_insert(&set2, 5);
    bitset_insert(&set2, 11);
    bitset res = bitset_symmetricDifference(set1,set2);

    bitset exp_res = bitset_create(25);
    bitset_insert(&exp_res, 9);
    bitset_insert(&exp_res, 1);
    bitset_insert(&exp_res, 11);

    assert(bitset_isEqual(res, exp_res));
}
void test_bitset_symmetricDifference(){
    test_bitset_symmetricDifference1();
    test_bitset_symmetricDifference2();
}

void test_bitset_complement1(){
    bitset set1 = bitset_create(10);
    bitset_insert(&set1, 1);
    bitset_insert(&set1, 0);
    bitset_insert(&set1, 5);
    bitset_insert(&set1, 7);

    bitset res = bitset_complement(set1);

    bitset exp_res = bitset_create(10);
    bitset_insert(&exp_res, 2);
    bitset_insert(&exp_res, 3);
    bitset_insert(&exp_res, 4);
    bitset_insert(&exp_res, 6);
    bitset_insert(&exp_res, 8);
    bitset_insert(&exp_res, 9);


    assert(bitset_isEqual(res, exp_res));


}
void test_bitset_complement2(){
    bitset set1 = bitset_create(8);
    bitset_insert(&set1, 1);
    bitset_insert(&set1, 0);
    bitset_insert(&set1, 5);
    bitset_insert(&set1, 7);

    bitset res = bitset_complement(set1);

    bitset exp_res = bitset_create(8);
    bitset_insert(&exp_res, 2);
    bitset_insert(&exp_res, 3);
    bitset_insert(&exp_res, 4);
    bitset_insert(&exp_res, 6);


    assert(bitset_isEqual(res, exp_res));
}
void test_bitset_complement(){
    test_bitset_complement2();
    test_bitset_complement1();
}

void test_unordered_array_set_union1() {
    int arr1[] = {1, 2, 3, 4,};
    unordered_array_set set1 = unordered_array_set_create_from_array(arr1, 4, 4);
    int arr2[] = {4, 5, 6, 7,};
    unordered_array_set set2 = unordered_array_set_create_from_array(arr2, 4, 4);

    int arr_exp[] = {1, 2, 3, 4, 5, 6, 7};
    unordered_array_set exp_set = unordered_array_set_create_from_array(arr_exp, 7, 7);
    unordered_array_set res = unordered_array_set_union(set1, set2);

    assert(unordered_array_set_isEqual(res, exp_set));
    free(set1.data);
    free(set2.data);
    free(res.data);
    free(exp_set.data);

}

void test_unordered_array_set_union2() {
    int arr1[] = {1, 2, 3, 10,};
    unordered_array_set set1 = unordered_array_set_create_from_array(arr1, 4, 4);
    int arr2[] = {4, 5, 6, 7,};
    unordered_array_set set2 = unordered_array_set_create_from_array(arr2, 4, 4);

    int arr_exp[] = {1, 2, 3, 4, 5, 6, 7, 10};
    unordered_array_set exp_set = unordered_array_set_create_from_array(arr_exp, 8, 8);
    unordered_array_set res = unordered_array_set_union(set1, set2);

    assert(unordered_array_set_isEqual(res, exp_set));
    free(set1.data);
    free(set2.data);
    free(res.data);
    free(exp_set.data);
}
void test_unordered_array_set_union(){
    test_unordered_array_set_union2();
    test_unordered_array_set_union1();
}

void test_unordered_array_set_intersection1(){
    int arr1[] = {1, 2, 3, 4};
    unordered_array_set set1 = unordered_array_set_create_from_array(arr1, 4, 4);
    int arr2[] = {4, 5, 6, 7,};
    unordered_array_set set2 = unordered_array_set_create_from_array(arr2, 4, 4);

    int arr_exp[] = {4};
    unordered_array_set exp_set = unordered_array_set_create_from_array(arr_exp, 1, 1);

    unordered_array_set res = unordered_array_set_intersection(set1, set2);

    assert(unordered_array_set_isEqual(res, exp_set));
    free(set1.data);
    free(set2.data);
    free(res.data);
    free(exp_set.data);

}
void test_unordered_array_set_intersection2(){
    int arr1[] = {7, 6, 5, 4};
    unordered_array_set set1 = unordered_array_set_create_from_array(arr1, 4, 4);
    int arr2[] = {4, 5, 6, 7,};
    unordered_array_set set2 = unordered_array_set_create_from_array(arr2, 4, 4);

    int arr_exp[] = {4, 7, 6, 5};
    unordered_array_set exp_set = unordered_array_set_create_from_array(arr_exp, 4, 4);

    unordered_array_set res = unordered_array_set_intersection(set1, set2);

    assert(unordered_array_set_isEqual(res, exp_set));
    free(set1.data);
    free(set2.data);
    free(res.data);
    free(exp_set.data);
}
void test_unordered_array_set_intersection(){
    test_unordered_array_set_intersection1();
    test_unordered_array_set_intersection2();
}

void test_unordered_array_set_difference1(){
    int arr1[] = {7, 6, 5, 4};
    unordered_array_set set1 = unordered_array_set_create_from_array(arr1, 4, 4);
    int arr2[] = {3, 5, 6, 7,};
    unordered_array_set set2 = unordered_array_set_create_from_array(arr2, 4, 4);
    int arr_exp[] = { 4};
    unordered_array_set exp_set = unordered_array_set_create_from_array(arr_exp, 1, 1);

    unordered_array_set res = unordered_array_set_difference(set1, set2);

    assert(unordered_array_set_isEqual(res, exp_set));
    free(set1.data);
    free(set2.data);
    free(res.data);
    free(exp_set.data);
}
void test_unordered_array_set_difference2(){
    int arr1[] = {1, 2, 3, 4};
    unordered_array_set set1 = unordered_array_set_create_from_array(arr1, 4, 4);
    int arr2[] = {4, 3, 6, 7,};
    unordered_array_set set2 = unordered_array_set_create_from_array(arr2, 4, 4);

    int arr_exp[] = {1, 2};
    unordered_array_set exp_set = unordered_array_set_create_from_array(arr_exp, 2, 2);

    unordered_array_set res = unordered_array_set_difference(set1, set2);

    assert(unordered_array_set_isEqual(res, exp_set));
    free(set1.data);
    free(set2.data);
    free(res.data);
    free(exp_set.data);
}
void test_unordered_array_set_difference(){
    test_unordered_array_set_difference1();
    test_unordered_array_set_difference2();
}


void test_unordered_array_set_complement1(){
    int arr1[] = {1, 2, 3, 4};
    unordered_array_set set1 = unordered_array_set_create_from_array(arr1, 4, 4);
    int arr2[] = {4, 3, 2, 1,};
    unordered_array_set set2 = unordered_array_set_create_from_array(arr2, 4, 4);

    int arr_exp[] = {};
    unordered_array_set exp_set = unordered_array_set_create_from_array(arr_exp, 0, 0);

    unordered_array_set res = unordered_array_set_complement(set1, set2);

    assert(unordered_array_set_isEqual(res, exp_set));
    free(set1.data);
    free(set2.data);
    free(res.data);
    free(exp_set.data);
}
void test_unordered_array_set_complement2(){
    int arr1[] = {1, 2, 3, 4};
    unordered_array_set set1 = unordered_array_set_create_from_array(arr1, 4, 4);
    int arr2[] = {1, 2, 3,4,5,6,7,8,9,10};
    unordered_array_set set2 = unordered_array_set_create_from_array(arr2, 10, 10);

    int arr_exp[] = {5,6,7,8,9,10};
    unordered_array_set exp_set = unordered_array_set_create_from_array(arr_exp, 6, 6);

    unordered_array_set res = unordered_array_set_complement(set1, set2);

    assert(unordered_array_set_isEqual(res, exp_set));
    free(set1.data);
    free(set2.data);
    free(res.data);
    free(exp_set.data);
}
void test_unordered_array_set_complement(){
    test_unordered_array_set_complement2();
    test_unordered_array_set_complement1();
}

void test_unordered_array_set_symmetricDifference1(){
    int arr1[] = {1, 2, 3, 4, 11, 12, 13};
    unordered_array_set set1 = unordered_array_set_create_from_array(arr1, 7, 7);
    int arr2[] = {1, 2, 3,4,5,6,7,8,9,10};
    unordered_array_set set2 = unordered_array_set_create_from_array(arr2, 10, 10);

    int arr_exp[] = {5,6,7,8,9,10, 11, 12, 13};
    unordered_array_set exp_set = unordered_array_set_create_from_array(arr_exp, 9, 9);

    unordered_array_set res = unordered_array_set_symmetricDifference(set1, set2);

    assert(unordered_array_set_isEqual(res, exp_set));
    free(set1.data);
    free(set2.data);
    free(res.data);
    free(exp_set.data);

}
void test_unordered_array_set_symmetricDifference2(){
    int arr1[] = {1, 2, 3, 4, 11, 12, 13};
    unordered_array_set set1 = unordered_array_set_create_from_array(arr1, 7, 7);
    int arr2[] = {25,26,23};
    unordered_array_set set2 = unordered_array_set_create_from_array(arr2, 3, 3);

    int arr_exp[] = {1,2,3,4,11,12,13,25,26,23};
    unordered_array_set exp_set = unordered_array_set_create_from_array(arr_exp, 10, 10);

    unordered_array_set res = unordered_array_set_symmetricDifference(set1, set2);

    assert(unordered_array_set_isEqual(res, exp_set));
    free(set1.data);
    free(set2.data);
    free(res.data);
    free(exp_set.data);
}
void test_unordered_array_set_symmetricDifference(){
    test_unordered_array_set_symmetricDifference2();
    test_unordered_array_set_symmetricDifference1();
}
void test_ordered_array_set_union1(){
    int arr1[] = {8,7,5,6,4};
    ordered_array_set set1 = ordered_array_set_create_from_array(arr1, 5,5);
    int arr2[] = {5,4,3,2,1,};
    ordered_array_set set2 = ordered_array_set_create_from_array(arr2, 5,5);
    ordered_array_set res = ordered_array_set_union(set1, set2);
    int arr_exp[] = {1,2,3,4,5,6,7,8};
    ordered_array_set exp_res = ordered_array_set_create_from_array(arr_exp, 8,8);
    assert(ordered_array_set_isEqual(exp_res, res));
    free(set1.data);
    free(set2.data);
    free(res.data);
    free(exp_res.data);


}
void test_ordered_array_set_union2(){
    int arr1[] = {8,7,5,6,4};
    ordered_array_set set1 = ordered_array_set_create_from_array(arr1, 5,5);
    int arr2[] = {4,5,6,7,8};
    ordered_array_set set2 = ordered_array_set_create_from_array(arr2, 5,5);
    ordered_array_set res = ordered_array_set_union(set1, set2);
    int arr_exp[] = {4,5,6,7,8};
    ordered_array_set exp_res = ordered_array_set_create_from_array(arr_exp, 5,5);

    assert(ordered_array_set_isEqual(exp_res, res));
    free(set1.data);
    free(set2.data);
    free(res.data);
    free(exp_res.data);
}
void test_ordered_array_set_union(){
    test_ordered_array_set_union1();
    test_ordered_array_set_union2();
}

void test_ordered_array_set_intersection1(){
    int arr1[] = {8,7,5,6,4};
    ordered_array_set set1 = ordered_array_set_create_from_array(arr1, 5,5);
    int arr2[] = {4,5,6,7,8};
    ordered_array_set set2 = ordered_array_set_create_from_array(arr2, 5,5);
    ordered_array_set res = ordered_array_set_intersection(set1, set2);
    int arr_exp[] = {4,5,6,7,8};
    ordered_array_set exp_res = ordered_array_set_create_from_array(arr_exp, 5,5);

    assert(ordered_array_set_isEqual(exp_res, res));
    free(set1.data);
    free(set2.data);
    free(res.data);
    free(exp_res.data);
}
void test_ordered_array_set_intersection2(){
    int arr1[] = {8,7,5,6,4};
    ordered_array_set set1 = ordered_array_set_create_from_array(arr1, 5,5);
    int arr2[] = {8,7,22,33,55};
    ordered_array_set set2 = ordered_array_set_create_from_array(arr2, 5,5);
    ordered_array_set res = ordered_array_set_intersection(set1, set2);
    int arr_exp[] = {7,8};
    ordered_array_set exp_res = ordered_array_set_create_from_array(arr_exp, 2,2);

    assert(ordered_array_set_isEqual(exp_res, res));
    free(set1.data);
    free(set2.data);
    free(res.data);
    free(exp_res.data);
}
void test_ordered_array_set_intersection(){
    test_ordered_array_set_intersection1();
    test_ordered_array_set_intersection2();
}

void test_ordered_array_set_difference1(){
    int arr1[] = {8,7,5,6,4};
    ordered_array_set set1 = ordered_array_set_create_from_array(arr1, 5,5);
    int arr2[] = {8,7,22,33,55};
    ordered_array_set set2 = ordered_array_set_create_from_array(arr2, 5,5);
    ordered_array_set res = ordered_array_set_difference(set1, set2);
    int arr_exp[] = {4,5,6};
    ordered_array_set exp_res = ordered_array_set_create_from_array(arr_exp, 3,3);

    assert(ordered_array_set_isEqual(exp_res, res));
    free(set1.data);
    free(set2.data);
    free(res.data);
    free(exp_res.data);
}
void test_ordered_array_set_difference2(){
    int arr1[] = {8,7,5,6,4};
    ordered_array_set set1 = ordered_array_set_create_from_array(arr1, 5,5);
    int arr2[] = {4,5,6,7,8};
    ordered_array_set set2 = ordered_array_set_create_from_array(arr2, 5,5);
    ordered_array_set res = ordered_array_set_difference(set1, set2);
    int arr_exp[] = {};
    ordered_array_set exp_res = ordered_array_set_create_from_array(arr_exp, 0,0);

    assert(ordered_array_set_isEqual(exp_res, res));
    free(set1.data);
    free(set2.data);
    free(res.data);
    free(exp_res.data);
}
void test_ordered_array_set_difference(){
    test_ordered_array_set_difference2();
    test_ordered_array_set_difference1();

}

void test_ordered_array_set_symmetricDifference1(){
    int arr1[] = {8,7,5,6,4};
    ordered_array_set set1 = ordered_array_set_create_from_array(arr1, 5,5);
    int arr2[] = {4,5,6,7,8};
    ordered_array_set set2 = ordered_array_set_create_from_array(arr2, 5,5);
    ordered_array_set res = ordered_array_set_symmetricDifference(set1, set2);
    int arr_exp[] = {};
    ordered_array_set exp_res = ordered_array_set_create_from_array(arr_exp, 0,0);

    assert(ordered_array_set_isEqual(exp_res, res));
    free(set1.data);
    free(set2.data);
    free(res.data);
    free(exp_res.data);
}
void test_ordered_array_set_symmetricDifference2(){
    int arr1[] = {8,7,5,6,4};
    ordered_array_set set1 = ordered_array_set_create_from_array(arr1, 5,5);
    int arr2[] = {8,7,22,33,55};
    ordered_array_set set2 = ordered_array_set_create_from_array(arr2, 5,5);
    ordered_array_set res = ordered_array_set_symmetricDifference(set1, set2);
    int arr_exp[] = {4,5,6, 22, 33, 55};
    ordered_array_set exp_res = ordered_array_set_create_from_array(arr_exp, 6,6);

    assert(ordered_array_set_isEqual(exp_res, res));
    free(set1.data);
    free(set2.data);
    free(res.data);
    free(exp_res.data);
}
void test_ordered_array_set_symmetricDifference(){
    test_ordered_array_set_symmetricDifference2();
    test_ordered_array_set_symmetricDifference1();
}

void test_ordered_array_set_complement1(){
    int arr1[] = {8,7,5,6,4};
    ordered_array_set set1 = ordered_array_set_create_from_array(arr1, 5,5);
    int arr2[] = {8,7,22,33,55};
    ordered_array_set set2 = ordered_array_set_create_from_array(arr2, 5,5);
    ordered_array_set res = ordered_array_set_complement(set1, set2);
    int arr_exp[] = {22, 33, 55};
    ordered_array_set exp_res = ordered_array_set_create_from_array(arr_exp, 3,3);

    assert(ordered_array_set_isEqual(exp_res, res));
    free(set1.data);
    free(set2.data);
    free(res.data);
    free(exp_res.data);
}
void test_ordered_array_set_complement2(){
    int arr1[] = {1,2,3,4,5,6,7,8,9,11};
    ordered_array_set set1 = ordered_array_set_create_from_array(arr1, 10,10);
    int arr2[] = {9,10,11,12,13,14,15};
    ordered_array_set set2 = ordered_array_set_create_from_array(arr2, 7,7);
    ordered_array_set res = ordered_array_set_complement(set1, set2);
    int arr_exp[] = {10,12,13,14,15};
    ordered_array_set exp_res = ordered_array_set_create_from_array(arr_exp, 5,5);

    assert(ordered_array_set_isEqual(exp_res, res));
    free(set1.data);
    free(set2.data);
    free(res.data);
    free(exp_res.data);
}
void test_ordered_array_set_complement(){
    test_ordered_array_set_complement1();
    test_ordered_array_set_complement2();
}