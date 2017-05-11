#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


typedef struct Answer{
  int id;
  char *answer;
}Answer;

typedef struct Question{
  char *question;
  Answer *answers;
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
        	input = realloc(input, sizeof(char)*(size+=20));
		}
      if(!input) return input;
    }
  }
  
  input[len+2] = '\0';
  //printf("INPUT: %s\n", input);
  return realloc(input, sizeof(char)*len);
}

void main_menu(int menu_szint){
  switch(menu_szint){
    case(0):
      printf("1. Új kérdéssor készítése. \n");
      printf("2. Kérdéssor szerkesztése. \n");
      printf("3. Kérdéssor megtekintése. \n");
      printf("4. Kilépés. \n");
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
	  break;
    default:
		break;
  }
}

Question* kerdes_hozzadas(){
  Question *q;
  printf("Adjon meg egy kérdést: \n");	
	char *c = realloc(NULL, sizeof(char));
	c = beolvas(stdin, 200, 0);
	q->question = c;
  q->date = time(NULL);
	q->answers = malloc(sizeof(Answer)*4);	
  return q;
}

void kerdessor_mentes(Question *questionArray, int size){
  FILE *file;
  int i,j;
  char *printed_line;  
  printed_line = malloc(sizeof(char));
  //printf("Kérdés első eleme: %s\n", questionArray->question);
  printf("Adja meg a fájl nevét. \n");
  char *fname = realloc(NULL, sizeof(char));
  fname = beolvas(stdin, 200, 0);
  file = fopen(fname, "w+");
  for(i = 0; i < size; ++i, ++questionArray){    
		if(i > 0){
			fprintf(file, "\n");
		}
		printf("Van kérdés. Size: %i, Question: %s\n", size, questionArray[0].question);
		printed_line = realloc(NULL, strlen(questionArray->question));
		snprintf(printed_line, strlen(questionArray->question), "%s", questionArray->question);
		fprintf(file, printed_line);   
  }
  free(printed_line);
  free(fname);
  free(questionArray);
  fclose(file);
}

Question* kerdessor_megnyitas(char *fname){
	FILE *file;	
	ssize_t read;
	size_t len = 200;
	char *line = malloc(len);
	int size = 0;
	Question *q = malloc(sizeof(Question));
	Question *temp = malloc(sizeof(Question));
	if(access(fname, F_OK) != -1){
		file = fopen(fname, "r");
		//q = realloc(NULL, sizeof(Question));
		while(!feof(file)){	
			if(fgets(line, len, file) != NULL){	
					Question *tempp = malloc(sizeof(q));
					tempp = realloc(q, 30);
					if(tempp == NULL){
						printf("De null.\n");
					}else{
						q = tempp;
					}
				temp = malloc(sizeof(Question));				
				temp->question = realloc(NULL, sizeof(line));			
				strcpy(temp->question, line);
				
				temp->answers = malloc(sizeof(Answer)*4);
				
				temp->date = time(NULL);
				
				q[size] = *temp;	
				
				if(temp != NULL){		
					size++;
				}
				
				//free(temp);
				printf("Sor: %s\n", line);
				if(feof(file)){
					fclose(file);
					break;
				}
			
			}
		}
	}else{
		printf("Nincs ilyen fájl.\n");	
		free(q);
		free(line);
		return NULL;
	}
	free(fname);
	free(line);
	fclose(file);
	//q++;
	printf("Size: %i, Elso kerdes: %s\n",size, q[0].question);
	return realloc(q, sizeof(q));
}

char *kerdes_szerkesztes(){
	printf("Adja meg az új kérdést. \n");
	char *asd = malloc(sizeof(char));
	asd = beolvas(stdin, sizeof(char), 0);
	return realloc(asd, strlen(asd));
}

int main(){
  Question *d;
  Question *szerk;
  int dontes = 1;
  int size = 0;
  int loop = 1;
  //Question questions[4];
  Question *questions = malloc(sizeof(Question));
  //Question questions[4];
  while(dontes != 4){
	  MAINMENU: main_menu(0);
	  dontes =(int) *beolvas(stdin, sizeof(int), 1);
      switch(dontes){
        case('1'):
		 SUBMENU: main_menu(1);
		  dontes = (int) *beolvas(stdin, sizeof(int), 1);
          switch(dontes){
             case('1'):                           
			   d = realloc(NULL,sizeof(Question));
			   d = kerdes_hozzadas(size);			   
			   if(size > 0){
				   questions = realloc(questions, sizeof(questions) + sizeof(Question));
			   }
               questions[size] = *d;	
			   if(d != NULL){
				   size++;
			   }		   
			   goto SUBMENU;
               break;
	          case('2'):
			    kerdessor_mentes(questions, size);
				goto MAINMENU;
	            break;
             case('3'):			 
             goto MAINMENU;
               break;
             default:
			 	printf("Hibás menüpont. \n");
				goto SUBMENU;
               break;
          }
	
	  break;
	case('2'):
	  	printf("Adja meg a fájl nevét. \n");
		char *fname = malloc(sizeof(char));
		fname = beolvas(stdin, sizeof(char), 0);
		free(questions);
		questions = realloc(NULL, sizeof(Question));
		questions = kerdessor_megnyitas(fname);
		if(questions == NULL){
			goto MAINMENU;
		}
		//printf("Questions size: %i \n", sizeof(questions));
	  	SUBMENU2: main_menu(2);
	  	dontes = (int) *beolvas(stdin, sizeof(char), 1);
		switch(dontes){
			case('1'):
				// printf("Size of Question: %i \n", sizeof(questions)/sizeof(questions[0]));
				for(loop = 1; questions->question != NULL; loop++/*, ++questions*/){
					//printf("%i. %s \n", loop, questions->question);
				}
				printf("Adja meg melyik kérdést akarja szerkeszteni. \n");
				char *kar = malloc(sizeof(char));
				kar =  beolvas(stdin, sizeof(char), 1);
				int ker = (int) *kar - '0';
				/*char *uj_kerdes = malloc(sizeof(char));
				uj_kerdes = kerdes_szerkesztes();
				questions[ker].question = (char *) realloc(questions[ker].question, strlen(uj_kerdes));
				strcpy(questions[ker].question, uj_kerdes);			*/
				szerk = realloc(NULL, sizeof(Question));
				szerk = kerdes_hozzadas();
				questions[ker].question = szerk->question;
				printf("Ezen átjut: %s\n", questions[ker].question);				
				kerdessor_mentes(questions, loop-1);
				break;
			case('2'):
				break;
			case('3'):
				break;
			case('4'):
				goto MAINMENU;
				break;
		}
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
  free(questions);
  free(d);
  free(szerk);
	printf("Vége a programnak.\n");
  return 0;
}
