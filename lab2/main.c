#include "set.h"

int main() {

	srand((unsigned) time(NULL));
   
	Set * A = set (10);
	Set * B = set (10);
	Set * C = set (10);

	printf("Set A: \n");
	print(A);
	printf("Set B: \n");
	print(B);
	printf("Set C: \n");
	print(C);

	Set* ABI = intersection_two_sets(A, B);
	Set* BCI = intersection_two_sets(B, C);
	Set* CAI = intersection_two_sets(C, A);

	printf("Set ABI: \n");
	print(ABI);
	printf("Set BCI: \n");
	print(BCI);
	printf("Set CAI: \n");
	print(CAI);

  	Set* U = unions(A, B, C);
    Set* I = intersection(A, B, C);
    Set* D = difference(A, B, C);
    Set* SD = symmetric_difference(A, B, C);

    printf("Union between A, B and C is:\n");
    print(U);
    printf("Difference between A, B and C is:\n");
    print(D);
    printf("Intersection between A, B and C is:\n");
    print(I);
    printf("Symmetric difference between A, B and C is:\n");
    print(SD);


    free_set(A);
    free_set(B);
	free_set(C);
    free_set(U);
    free_set(I);
    free_set(D);
    free_set(SD);
	free_set(ABI);
	free_set(BCI);
	free_set(CAI);

    return 0;
}
