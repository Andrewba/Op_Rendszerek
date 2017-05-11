#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>


typedef struct Answer{
  int id;
  char *answer;
}Answers;

typedef struct Question{
  char *question;
  int id;
  Answers answers[4];
  time_t date;
}Question;

char *beolvas(FILE *fp, size_t size, size_t max){
  char *input;
  int ch;
  size_t len = 0;
  input = realloc(NULL, sizeof(char)*size);
  if(!input) return input;
  
  while(EOF != (ch=fgetc(fp)) && ch != '\n'){
    input[len++] = ch;
    if(len == size){
      if(max == 0){
        input = realloc(input, sizeof(char)*(size+=16));
      }else{
    	break;
      }
      if(!input) return input;
    }
  }
  
  input[len++] = '\0';
  return realloc(input, sizeof(char)*len);
}

char* main_menu(int menu_szint){
  switch(menu_szint){
    case(0):
      printf("1. Új kérdéssor készítése. \n");
      printf("2. Kérdéssor szerkesztése. \n");
      printf("3. Kérdéssor megtekintése. \n");
      printf("4. Kilépés. \n");
//      return beolvas(stdin, 1, 1);
      break;
    case(1):
      printf("1. Új kérdés felvétele. \n");
      printf("2. Kérdéssor mentése. \n");
      printf("3. Vissza. \n");
      break;
    case(2):
      printf("1. Kérdés szerkesztése.\n");
      printf("2. Kérdés törlése.\n");
      printf("3. Válasz megadása kérdéshez\n");
      printf("4. Vissza. \n");
      break;
    case(3):
      printf("1. Kérdéssor szerkesztése. \n");
      printf("2. Vissza. \n");
    default:
      return 0;
  }
  char *c = beolvas(stdin, sizeof(char), 10);
  //return beolvas(stdin, 1, 1);
  return c;
}

Question* kerdes_hozzadas(){
  Question *q;
  	printf("Adjon meg egy kérdést: \n");
		q = malloc(sizeof(Question));
		q->question = beolvas(stdin, 200, 0);
    q->id = 1;
    q->date = time(NULL);
		
    return q;
}

void kerdessor_mentes(Question *questionArray){
  FILE *file;
  int i,j;
  char *printed_line;
  printf("Adja meg a fájl nevét. \n");
  fopen(beolvas(stdin, 20, 0), "rw");
  for(i = 0; i < sizeof(questionArray); ++i){
    printed_line = (char *) malloc(sizeof(questionArray[i].question)+5);
    strcpy(printed_line, "Q: ");
    strcpy(printed_line, questionArray[i].question);
    strcpy(printed_line, "\n");
    fprintf(file, printed_line);
    free(printed_line);
    for(j = 0; j < sizeof(questionArray[i].answers); ++j){
      printed_line = (char *) malloc(sizeof(questionArray[i].answers[j])+5);
      strcpy(printed_line, "A: ");
      strcpy(printed_line, questionArray[i].answers[j].answer);
      strcpy(printed_line, "\n");
      fprintf(file, printed_line);
      free(printed_line);
    }
  }
  fclose(file);
}

int main(){
  
  int dontes = 1;
  Question questions[4];
//  FILE *file;
  MainLoop: while(dontes != 4){
    if(sizeof(questions) != 4){
      dontes = *main_menu(0);
      switch(dontes){
        case(1):
//	 BelWhile: while(dontes != 3){
	  dontes = *main_menu(1);
          switch(dontes){
             case('1'):                           
               questions[sizeof(questions)/sizeof(questions[0])] = *kerdes_hozzadas();
               break;
	           case('2'):
    	       //kerdessor_mentes(questions);
//	           goto MainLoop;
	             break;
             case('3'):
  //           goto MainLoop;
               break;
             default:
               break;
          }
//	}
	  break;
	case('2'):
	  printf("Main 2.");
	  //goto Fomenu;
	  break;
 	case('3'):
	  printf("Main 3.");
	  break;
	case('4'):
	  dontes = 4;
	  break;
	default:
          printf("Nincs ilyen menüpont.\n");
	  break;
      }
    }
  }
  return 0;
}
