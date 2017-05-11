#include <stdlib.h>
#include <stdio.h>
#include "kerdesek.h"

int main(){
    Question *questions = malloc(sizeof(Question));
    size_t number_of_q = 0;
    run_program(questions, number_of_q);
    printf("Kérdések véglegesek.\n");
    return 0;
}