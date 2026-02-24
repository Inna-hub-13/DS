#include "set.h"

// Returns an array initialised with unrepeated random numbers
unsigned* random_generator(unsigned number_of_blocks, unsigned max, unsigned min){

	unsigned * array = (unsigned*)malloc(sizeof(unsigned)*number_of_blocks);

    if(!array)
        return NULL;

	unsigned count, r, i = 0;

	while(i<number_of_blocks){

		r = rand()%(max + 1 - min) + min;

		for(count = 0; count < i; count++) {

			if(*(array + count) == r)
				count = i + 1;
		
        }

		if (count == i) {

			*(array + i) = r;
			i++;
		}

	}

	return array;
}

Set *set (unsigned number_of_elements, unsigned max, unsigned min){

	Set* set = (Set*)malloc(sizeof(Set));
    
    if(!set)
        return NULL;

	set->array = random_generator(number_of_elements, max, min);
    if(!set->array){

        free(set);
        return NULL;
    }

	set->length = number_of_elements;

	return set;
}

void print(const Set * set){

	if (!set)
		return;

	unsigned i;
	for(i = 0; i < set->length; i++)
		printf("%c\t", set->array[i]);

	printf("\n");
}

Relation* cartesian_product(const Set * A, const Set * B){

	Relation * relation = (Relation*)malloc(sizeof(Relation));

    if(!relation)
        return NULL;

	relation->length = A->length * B->length;
	relation->pairs = (Pair*)malloc(sizeof(Pair) * relation->length);
	
    if(!relation->pairs){

        free(relation);
        return NULL;
    }


	unsigned i, j, index = 0;

	for(i = 0; i <A->length; i++)
		for(j = 0; j <B->length; j++){
			
			relation->pairs[index].x = A->array[i];
			relation->pairs[index].y = B->array[j];
			index++;
		}

	return relation;
}

void print_cartesian_product(const Relation * cartesian_product) {

	printf("Length of cartesian product is %d.\n", cartesian_product->length);

	unsigned i;
	printf("{");

	for(i=0; i < cartesian_product->length; i++){
		
		printf("(%c, %c)", cartesian_product->pairs[i].x, 
            cartesian_product->pairs[i].y);

		if(i <= cartesian_product->length - 2)
			printf(",");
		
    }

	printf("}\n");
}

void free_set(Set* A) {

    if(A){

        free(A->array);
        free(A);
    }
}

void free_relation(Relation* AB){

    if(AB){

        free(AB->pairs);
        free(AB);
    }
}
