#ifndef KERDESEK_H_
#define KERDESEK_H_
#define MAXLEN 4096
#include <time.h>

typedef struct Question{
    char question[MAXLEN];
    //char answers[4][MAXLEN];
    char answers[4][MAXLEN];
    time_t date;
    int number_of_answers;
}Question;

void menu(int);
void lista(int);
void hozzaad_kerdes();
void modosit(int);
void torol();
int dont();
void fajl_ment(char *, char *);
void szerk_kerdes(FILE*, int);
int kerdes_veglegesites();
int create_questions();

#endif // KERDESEK_H_