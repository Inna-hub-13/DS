#include "set.h"

char* random_generator(unsigned number_of_blocks){

	char* array = (char*)malloc(sizeof(char)*number_of_blocks);

    if(!array)
        return NULL;

	unsigned count, i = 0;
    char r;

	while(i<number_of_blocks){

		r = (char)(rand() % 26 + 65);

		for(count=0; count < i; count++){

			if(*(array + count) == r)
				count = i+1;
		
        }

		if (count == i) {

			*(array + i) = r;
			i++;
		}

	}

	return array;
}

void free_set(Set* A) {

    if(A){

        free(A->array);
        free(A);
    }
}

Set *set (unsigned number_of_elements){

	Set* set = (Set*)malloc(sizeof(Set));
    
    if(!set)
        return NULL;

	set->array = random_generator(number_of_elements);
	set->length = number_of_elements;

	return set;
}

void print(const Set * set){

	if (!set)
		return;

	unsigned i;
	for(i = 0; i < set->length; i++)
		printf("%c ", set->array[i]);
	printf("\n");
}

unsigned find_element (const Set * set, char element) {
	
	unsigned i;
	for(i = 0; i < set->length; i++) 
		if (element == set->array[i])
			return 1;

	return 0;
}

Set * intersection_two_sets(const Set * A, const Set * B) {

	if(A == NULL || B == NULL)
		return NULL;

	unsigned i, j, index = 0;

	Set* result_set = (Set*)malloc(sizeof(Set));

    if(!result_set)
        return NULL;

	char* temp = (char*)malloc(sizeof(char) *
    (A->length < B->length ? A->length : B->length));

    if(!temp){

        free(result_set);
        return NULL;
    }
    
	for (i = 0; i < B->length; i++)
		
		for (j = 0; j < A->length; j++) 

			if (A->array[j] == B->array[i]){

                *(temp + index) = A->array[j];
                index++;
            }

	if (index == 0) {

		free(result_set);
		free(temp);
		return NULL;
	}

	result_set->length = index;
	result_set->array = (char*)malloc(sizeof(char) * index);

	if (!result_set->array) {

		free(result_set);
		free(temp);
		return NULL;
	}

    for(i = 0; i < index; i++)
        result_set->array[i]=*(temp + i);
        
    free(temp);
	return result_set;
}

Set * intersection(const Set *A, const Set *B, const Set *C) {

    Set* intersection_AB = intersection_two_sets(A, B);
    Set* intersection_ABC = intersection_two_sets(intersection_AB, C);
    free_set(intersection_AB);
	return intersection_ABC;
}

Set * union_two_sets(const Set *A, const Set *B){

    Set* set_I = intersection_two_sets(A, B);

    if(!set_I)
        return NULL;

	Set *result_set = (Set*)malloc(sizeof(Set));

    if(!result_set)
        return NULL;

    result_set->length = A->length + B->length - set_I->length;
	result_set->array=(char*)malloc(sizeof(char)* result_set->length);

	if(!result_set->array){

		free_set(set_I);
		free(result_set);
		return NULL;
	}
	
	unsigned i, count = 0; 

    for(i = 0; i < A->length; i++, count++)
        result_set->array[count] = A->array[i];

	
	for(i = 0; i <B->length;i++)
		if(!find_element(A, B->array[i]))
			result_set->array[count++]=B->array[i];

	free_set(set_I);
	return result_set;
}

Set * unions(const Set *A, const Set *B, const Set *C) {

	Set* union_AB = union_two_sets(A, B);
	Set* union_ABC = union_two_sets(union_AB, C);
	free_set(union_AB);
	return union_ABC;
}

Set * difference_two_sets(const Set *A, const Set *B) {

	Set* set_I = intersection_two_sets(A, B);

	if(!set_I)
		return NULL;
	
	if(set_I->length == 0)
		return A;
	
	Set* result_set = (Set*)malloc(sizeof(Set));

	if(!result_set){

		free_set(set_I);
		return NULL;
	}

	result_set->length = A->length - set_I->length;
	result_set->array = (char*)malloc(sizeof(char)*result_set->length);

	if(!result_set->array){

		free_set(set_I);
		free(result_set);
		return NULL;
	}

	unsigned i, count;
	for(i = 0, count = 0; i<A->length; i++)
		if(!find_element(set_I, A->array[i]))
			result_set->array[count++]=A->array[i];

	free_set(set_I);
	return result_set;
}

Set * difference(const Set *A,const Set *B, const Set *C) {

	Set* difference_AB = difference_two_sets(A, B);
	Set* result_set = difference_two_sets(difference_AB, C);
	free_set(difference_AB);
	return result_set;
}

Set * symmetric_difference(const Set *A, const Set *B, const Set *C){

	Set* union_ABC = unions(A, B, C);
	
	if(!union_ABC)
		return NULL;
	
	Set* intersection_ABC = intersection(A, B, C);

	if(!intersection_ABC){

		free_set(union_ABC);
		return NULL;
	}
		
	
	Set* result_set = difference_two_sets(union_ABC, intersection_ABC);
	free_set(union_ABC);
	free_set(intersection_ABC);
	return result_set;
}
