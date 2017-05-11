#ifndef KERDESEK_H_
#define KERDESEK_H_
#include <time.h>
#define MAXLEN 4096

typedef struct Answer{
    int id;
    char *answer;
}Answer;

typedef struct Question{
    char *question;
    Answer *answers;
    time_t date;
    int id;
}Question;

char *beolvas();
int menu_dontes();
void menu();
Question *initNewQuestionArray();
void kerdesek_lisazasa(Question*, size_t);
Question *kerdes_hozzadas(size_t);
void kerdes_modosit(Question *, int);
void kerdes_torol(Question *, int);
void kerdes_veglegesites(Question *);
void run_program(Question*, size_t);

#endif // KERDESEK_H_