#define MAX_INTERVAL 50

typedef struct {

    unsigned * array;
    unsigned length;
} set;

unsigned* random_generator(unsigned number_of_blocks);
set* create_set(unsigned number_of_elements);
void print_set(const set* set);
unsigned find_element(const set* set, unsigned element);
set* intersection(const set* A, const set* B);
set* unions(const set* A, const set* B);
set* difference(const set* A, const set* B);
set* symmetric_difference(const set* A, const set* B);
void free_set(set* A);