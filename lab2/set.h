#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define NUMBER_OF_RAND_NUMBERS 10

typedef struct {
	
	char* array;
	unsigned length;
	
}Set;

Set *set(unsigned number_of_blocks);
char*random_generator(unsigned);
void print (const Set * set);
unsigned find_element(const Set * set, char element);
void free_set(Set* A);

Set * unions(const Set *A, const Set *B, const Set *C);
Set * union_two_sets(const Set *A, const Set *B);
Set * intersection(const Set *A, const Set *B, const Set *C);
Set * intersection_two_sets(const Set *A, const Set *B);
Set * difference(const Set *A,const Set *B, const Set *C);
Set * difference_two_sets(const Set *A, const Set *B);
Set * symmetric_difference(const Set *A, const Set *B, const Set *C);