#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct{
    char *answer;
    int id;
}Answer;

typedef struct{
    char *question;
    int id;
    Answer answers[4];
}Question;

typedef struct{
    Question *questionArray;
    size_t size;
    size_t used_size;
}Array;

void initArray(QuestionArray *a, size_t size){
    a->questionArray = (Question *)malloc(size*sizeof(Question));
    a->size = size;
    a->used_size = 0;
}

void addElement(QuestionArray *a, char *element){
    if(a->used_size == a->size){
        a->size += 1;
        a->questionArray = realloc(a->questionArray, sizeof(Question)*a->size );
    }    
    Question *q = (Question*)malloc(sizeof(Question));
    q->question = (char *)malloc(strlen(element)*sizeof(char));
    strcpy(q->question, element);
    q->id = a->used_size+1;
    a->questionArray[a->used_size] = *q;
    a->used_size++;    
}

int main(){
    QuestionArray a;
    int loop;
    initArray(&a, 1);
    char testQ[200] = "Hogy vagy ma te Gazsi?";
    char testQQ[200] = "Második kérdés?";
    addElement(&a, testQ);
    addElement(&a, testQQ);
    printf("sizeof(a[0]): %d\n", sizeof(a.questionArray));
    printf("sizeof array: %d\n", sizeof(a.questionArray)/sizeof(a.questionArray[0]));
    return 0;
}