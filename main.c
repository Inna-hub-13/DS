#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "set.h"
#define MAX_INTERVAL 50


int main() {

    srand((unsigned)time(NULL));

    set* set_A = create_set(5);

    printf("Set A is:\n");
    print_set(set_A);

    set* set_B = create_set(5);
    printf("Set B is:\n");
    print_set(set_B);


    set* set_U = unions(set_A, set_B);
    set* set_I = intersection(set_A, set_B);
    set* set_D = difference(set_A, set_B);
    set* set_SD = symmetric_difference(set_A, set_B);

    printf("Union between A and B is:\n");
    print_set(set_U);
    printf("Difference between A and B is:\n");
    print_set(set_D);
    printf("Intersection between A and B is:\n");
    print_set(set_I);
    printf("Symmetric difference between A and B is:\n");
    print_set(set_SD);


    free_set(set_A);
    free_set(set_B);
    free_set(set_U);
    free_set(set_I);
    free_set(set_D);
    free_set(set_SD);

    return 0;
}

// This fuction returns an array, that is initialised with 
// Random unrepeated numbers from a given interval (50-100)
unsigned* random_generator(unsigned number_of_blocks) {

    unsigned* arr = (unsigned*)malloc(sizeof(unsigned) * number_of_blocks);

    if (!arr)
        return NULL;

    unsigned i = 0, c;
    unsigned r = 0;

    while (i < number_of_blocks) {

        r = rand() % (MAX_INTERVAL + 1) + MAX_INTERVAL;

        for (c = 0; c < i; c++)
            if (*(arr + c) == r)
                c = i + 1;

        if (c == i) {

            *(arr + i) = r;
            i++;
        }
    }

    return arr;
}

void free_set(set* set) {

    if (set) {
        free(set->array);
        free(set);
    }
}

// This fuction allocates memory for one element of type <set>
// And initialises its members
set* create_set(unsigned number_of_elements) {

    set* set_struct = (set*)malloc(sizeof(set));

    if (!set_struct)
        return NULL;

    set_struct->length = number_of_elements;
    set_struct->array = random_generator(number_of_elements);

    return set_struct;
}

void print_set(const set* set) {

    unsigned i;
    for (i = 0; i < set->length; i++)
        printf("%d\t", set->array[i]);

    printf("\n");
}


unsigned find_element(const set* set, unsigned element) {

    int i;
    for (i = 0; i < set->length; i++)
        if (set->array[i] == element)
            return 1;

    return 0;
}

set* intersection(const set* A, const set* B) {

    set* set_I = (set*)malloc(sizeof(set));

    if (!set_I)
        return NULL;

    // We can't know from the start if there is an intersection between set A and B
    // Because of that let <temp> be the maximum possible size
    unsigned* temp = (unsigned*)malloc(sizeof(unsigned) *
        (A->length < B->length ? A->length : B->length));

    if (!temp) {

        free(set_I);
        return NULL;
    }

    int i, count = 0;

    for (i = 0; i < B->length; i++)
        if (find_element(A, B->array[i])) {

            temp[count] = B->array[i];
            count++;
        }

    set_I->length = count;
    set_I->array = (unsigned*)malloc(sizeof(unsigned)*count);

    if (!set_I->array) {

        free(set_I);
        free(temp);
        return NULL;
    }

    for (i = 0; i < count; i++)
        set_I->array[i] = *(temp + i);

    free(temp);

    return set_I;
}

set* unions(const set* A, const set* B) {

    set* set_U = (set*)malloc(sizeof(set));

    if (!set_U)
        return NULL;

    unsigned* temp = (unsigned*)malloc(sizeof(unsigned) * (A->length + B->length));

    if (!temp) {

        free(set_U);
        return NULL;
    }

    int i, count = 0;

    for (i = 0; i < A->length; i++, count++)
        *(temp + count) = A->array[i];

    for (i = 0; i < B->length; i++)
        if (!find_element(A, B->array[i])) {

            *(temp + count) = B->array[i];
            count++;
        }

    set_U->length = count;
    set_U->array = (unsigned*)malloc(sizeof(unsigned)*count);

    if (!set_U->array) {

        free(set_U);
        free(temp);
        return NULL;
    }

    for (i = 0; i < count; i++)
        set_U->array[i] = *(temp + i);

    free(temp);

    return set_U;
}


set* difference(const set* A, const set* B) {

    set* set_D = (set*)malloc(sizeof(set));

    if (!set_D)
        return NULL;

    unsigned* temp = (unsigned*)malloc(sizeof(unsigned) * A->length);

    if (!temp) {

        free(set_D);
        return NULL;
    }

    int i, count = 0;

    for (i = 0; i < A->length; i++)
        if (!find_element(B, A->array[i])) {

            *(temp + count) = A->array[i];
            count++;
        }

    set_D->length = count;
    set_D->array = (unsigned*)malloc(sizeof(unsigned)*count);

    if (!set_D->array) {

        free(set_D);
        free(temp);
        return NULL;
    }

    for (i = 0; i < count; i++)
        set_D->array[i] = *(temp + i);

    free(temp);

    return set_D;
}

set* symmetric_difference(const set* A, const set* B) {

    set* set_D1 = difference(A, B);

    if (!set_D1)
        return NULL;

    set* set_D2 = difference(B, A);

    if (!set_D2) {

        free(set_D1);
        return NULL;
    }

    return unions(set_D1, set_D2);
}