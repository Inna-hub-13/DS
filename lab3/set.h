#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {

	unsigned * array;
	unsigned length;
} Set;

typedef struct {

	unsigned x;
	unsigned y;
} Pair;

typedef struct {

	Pair * pairs;
	unsigned length;
} Relation;

unsigned* random_generator(unsigned number_of_blocks, unsigned max, unsigned min);
Set* set(unsigned number_of_elements, unsigned max, unsigned min);
void print(const Set* set);
void free_set(Set* A);
void free_relation(Relation* AB);
Relation* cartesian_product(const Set * A, const Set * B);
void print_cartesian_product(const Relation * cartesian_product);