#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include "kerdesek.h"
#define MAXLEN 4096

void kerdesek_kivalasztasa(int[], Question[]);

int main(){
    srand(time(NULL));
    int loop = 0, loop2;
    pid_t parent;
    int random[3];
    char uzenet[MAXLEN];
    int pipe;
    int valaszok[3][4] = {0,0,0,0,0,0,0,0,0,0,0,0};
    int valaszt = 0;
    Question questions[3];
    
    int kerdesek_szama = /*create_questions()*/ 8;
    //kerdesek_szama = kerdesek_szama/2;
    for(loop = 0; loop < 3; loop++){
        random[loop] = (rand() % kerdesek_szama) + 1;
        CHECK:for(loop2 = 0; loop2 < loop; loop2++){
            if(random[loop] == random[loop2]){
                random[loop] = (rand() % kerdesek_szama) + 1;
                goto CHECK;
            }
        }
    }    
    parent = fork();
    if(parent == -1){
        perror("Forking hiba.\n");
        exit(-1);
    }

    if(parent == 0){
        printf("Starting child process...\n");
        kerdesek_kivalasztasa(random, questions);        
        int number_of_people = ((rand() % 10) + 1) + 10, loop, loop2;
            for(loop = 0; loop < number_of_people; loop++){
                for(loop2 = 0; loop2 < 3; loop2++){
                    valaszt = 0;
                    valaszt = (rand() % 4);
                    valaszok[loop2][valaszt] += 1;
                }
            }

    }else{
        printf("Starting parent process... \n");
        wait();
        
    }
    for(loop = 0; loop < 3; loop++){
        //printf("A(z) %i. kérdésre ", loop);
        for(loop2 = 0; loop2 < 4; loop2++){
            //printf("a(z) %i. válasz: %i, ", loop2, valaszok[loop][loop2]);
        }
        printf("\n");
    }
    return 0;
}

void kerdesek_kivalasztasa(int rand[], Question q[]){
    int loop, locale_id, loop2,valasz, checker = 0;
    int talalat = 0;
    char sor[MAXLEN];
    FILE *file = fopen("vegleges_temp.txt", "r");
    Question *qq;
    for(loop = 0; loop < 3; loop++){
        while(fgets(sor, MAXLEN, file) != NULL){
            if(sor[0] == 'Q'){
                talalat = 0;
                valasz = 0;
                locale_id = sor[2] - '0';
                for(loop2 = 0; loop2 < 3; loop2++){
                    if(rand[loop2] == locale_id){
                        if(loop > 0){
                            checker++;
                        }
                        /*if(q->question != NULL && loop != 3){
                            q++;
                        }*/
                        talalat = 1;
                        //printf("A(z) %i. kérdés: %s \n", loop, sor);
                        qq = realloc(NULL, sizeof(Question));
                        strcpy(qq->question, sor);
                        //printf("Kérdés: %s\n", qq->question);
                        //printf("Kérdés: %s\n", sor);
                        
                        if(qq->question != NULL){
                            //q->question = qq->question;
                            strcpy(q[loop].question, qq->question);
                            //q->number_of_answers = 0;
                            /*if(q->question == NULL){
                                printf("Kérdés másolás hiba.\n");
                            }   */                                                     
                        }
                        loop++;
                    }
                    
                }             
            }
            if(talalat == 1){                
                if(sor[1] == 'A'){
                    //printf("Választ?: %s\b", sor);
                    strcpy(qq->answers[valasz], sor);
                    if(qq->answers[valasz] != NULL){
                        strcpy(q[checker].answers[valasz], qq->answers[valasz]);      
                        if(strlen(q->answers[valasz]) != 0){
                            
                            //q->number_of_answers += 1;
                            //printf("ASDASD\n");
                        }                  
                    }   
                    valasz++;                 
                }
            }            
        }
    }
    /*Ellenörzésre*/
    /*printf("A kiválasztott kérdések: \n");
    q -= 2;
    for(loop = 0; loop < 3; loop++){
        printf("Kérdések: %s\n", q->question);
        
        for(loop2 = 0; loop2 < 4; loop2++){
            if(strlen(q->answers[loop2]) != 0){
                printf("Válasz: %s\n", q->answers[loop2]);
            }
        }
        q++;
    }*/
}
