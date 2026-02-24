#include "set.h"

int main(int argc, const char* argv[]){

	srand((unsigned)time(NULL));

	Set * A = set (3, 90, 65);
	Set * B = set (4, 200, 65);
	Set * C = set (3, 90, 65);
	Set * D = set (3, 90, 65);

	printf("Set A: \n");
	print(A);
	printf("Set B: \n");
	print(B);
	printf("Set C: \n");
	print(C);
	printf("Set D: \n");
	print(D);

	printf("\n");
	printf("Cartesian product of A x A: \n");
	Relation* resultAA = cartesian_product(A, A);
	print_cartesian_product(resultAA);
	printf("\n\n");

	printf("Cartesian product of A x B: \n");
	Relation* resultAB = cartesian_product(A, B);
	print_cartesian_product(resultAB);
	printf("\n\n");

	printf("Cartesian product of B x A: \n");
	Relation* resultBA = cartesian_product(B, A);
	print_cartesian_product(resultBA);
	printf("\n\n");

	free_set(A);
	free_set(B);
	free_set(C);
	free_set(D);

	free_relation(resultAA);
	free_relation(resultAB);
	free_relation(resultBA);

	return 0;
}











