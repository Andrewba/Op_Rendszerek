#include <stdlib.h>
#include <stdio.h>
#include "kerdesek.h"
#define MAXLEN 4096





Question *initNewQuestionArray(){
    return malloc(sizeof(Question));
}

char *beolvas(){
    //char input[MAXLEN];
    char *input;
    input = malloc(sizeof(char)*MAXLEN);
    size_t size = 0;
    fgets(input, MAXLEN, stdin);
    size = sizeof(input)/sizeof(input[0]);
    printf("Input: %s\n", input );
    if(input){
        return realloc(input, sizeof(input));
    }
    return NULL;
}

int menu_dontes(){
    char *dontesChar = malloc(sizeof(char));    
    dontesChar = fgets(dontesChar, sizeof(dontesChar), stdin);
    return (int) *dontesChar - '0';
}

void kerdesek_lisazasa(Question *ptr, size_t size){
    int i;
    printf("Kérdések listázása... size: %i\n", size);
    if(size > 0){
        //Question *ptr = *questions[0];
        for(i = 0; i < size; i++){
         printf("Az %i. kerdes: %s\n", ptr->id, ptr->question);
         ptr++;
    }
    }    
}

Question *kerdes_hozzadas(size_t size){
    /*printf("Kérdés hozzáadás, size: %d, Q1: %s \n", size, questions->question);
    if(questions->question != NULL){
        printf("Léptet...\n");
        questions = realloc(questions, sizeof(Question)*2);
        questions++;
    } */
    Question *q = malloc(sizeof(Question));   
    printf("Adja meg a kérdést. \n");
    q->question = beolvas();
    q->id = size;    
    q->answers = realloc(NULL, sizeof(Answer)*4);
    Answer *ptr = q->answers;
    int kilep = 0;
    int darab = 0;
    printf("Adjon meg legalább kettő, maximum 4 választ a kérdéshez.\n");
    while(darab != 4 || kilep != 1 || darab < 2){
        //ptr = realloc(ptr, sizeof(Answer)*4);
        if(darab >= 2){
            printf("Ha nem akar több választ megadni, 1-es gomb.\n");
            int dont = menu_dontes();
            if(dont == 1){
                break;
            }
        }
        ptr->answer = beolvas();
        ptr->id = darab;
        ptr++;
        darab++;
    }
    printf("QQ: %s\n", q->question);
    //return realloc(questions, sizeof(Question)*(size+1));        
    //return questions;
    return realloc(q, sizeof(Question));
}

void kerdes_modosit(Question *questions, int ind){

}

void kerdes_torol(Question *questions, int ind){

}

void menu(int dont){
    //int dont = menu_dontes();
    switch(dont){
        case(1):
            printf("1. Uj kerdessor keszitese. \n");
            printf("2. Kerdessor szerkesztese. \n");
            printf("3. Kerdessor megtekintese. \n");
            printf("4. Kerdessor veglegesitese és elküldése. \n");
            printf("5. Kilepes. \n");
            break;
        case(2):
            printf("1. Uj kerdes megadasa.\n");
            printf("2. Vissza.\n");
            break;
        case(3):
            printf("1. Kerdes szerkesztese.\n");
            printf("2. Kerdes torlese.\n");
            printf("3. Vissza.\n");
            break;
        case(4):
            printf("1. Vissza.\n");
            break;
        default:
            printf("Nincs ilyen menu.\n");
            break;
    }
}

void kerdes_veglegesites(Question *questions){

}

void run_program(Question *questions, size_t size){ 
    printf("Init...\n");  
    MAINMENU:menu(1);
    size_t array_size = 0;
    int dontes = 0;
    switch(menu_dontes()){
        case(1):
            HOZZAD:menu(2);
            switch(menu_dontes()){
                case(1):     
                    printf("SIZE: %d\n", size );
                    Question *q = realloc(NULL, sizeof(Question));
                    q = kerdes_hozzadas(size);
                    if(q->question != NULL){
                        size++;
                        printf("Ide még elmegy, size: %i.\n", size);
                        questions = realloc(questions, sizeof(Question)*(size));
                        if(size > 1){
                            questions++;
                        }
                        questions[size-1] = *q;
                        printf("Első kérdés: %s\n", questions[0].question);
                        printf("Siekres hozzáadás: %s\n", questions->question);
                    }
                    goto HOZZAD;
                    break;
                case(2):
                    goto MAINMENU;
                    break;
                default:
                    printf("Ilyen menupont nincs.");
                    goto HOZZAD;
                    break;
            }
            break;
        case(2):
               SZERKESZT: menu(3);
               switch(menu_dontes()){
                case(1):
                    printf("Adja meg melyik kerdest szerkesztene.\n");
                    dontes = menu_dontes();
                    kerdes_modosit(questions, menu_dontes());
                    goto SZERKESZT;
                    break;
                case(2):{
                    printf("Adja meg melyik kerdest torolne.\n");
                    dontes = menu_dontes();
                    printf("Torles balbla.\n");
                    kerdes_torol(questions, menu_dontes());
                    goto SZERKESZT;
                    break;
                }
                case(3):
                    goto MAINMENU;
                    break;
                default:
                    printf("Ilyen menupont nincs.\n");
                    goto SZERKESZT;
                    break;
               }
            break;
        case(3):        
            kerdesek_lisazasa(&questions[0], size);
            LISTA: menu(4);
            switch(menu_dontes()){
                case(1):
                    goto MAINMENU;
                    break;
                default:
                    printf("Ilyen menupont nincs.\n");
                    goto LISTA;
                    break;
            }
            break;
        case(4):
            kerdes_veglegesites(questions);
            goto MAINMENU;
            break;
        case(5):
            return;
            //exit(0);
        default:
            printf("Hibas menu.");
            goto MAINMENU;
    }
}

