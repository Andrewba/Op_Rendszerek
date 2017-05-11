#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
//#include <unistd.h>


typedef struct Answer {
	int id;
	char *answer;
}Answer;

typedef struct Question {
	char *question;
	Answer *answers;
	time_t date;
}Question;

char *beolvas(FILE *fp, size_t size, size_t max) {
	char *input;
	int ch;
	size_t len = 0;
	//input = realloc(NULL, sizeof(char)*size);
	input = malloc(sizeof(char)*size);
	if (!input) return input;

	while (EOF != (ch = fgetc(fp)) && ch != '\n') {
		input[len++] = ch;
		if (len == size) {
			if (max == 0) {
				input = realloc(input, sizeof(char)*(size += 20));
			}
			if (!input) return input;
		}
	}

	input[len + 2] = '\0';
	//printf("INPUT: %s\n", input);
	return realloc(input, sizeof(char)*len);
}

void main_menu(int menu_szint) {
	switch (menu_szint) {
	case(0):
		printf("1. �j k�rd�ssor k�sz�t�se. \n");
		printf("2. K�rd�ssor szerkeszt�se. \n");
		printf("3. K�rd�ssor megtekint�se. \n");
		printf("4. Kil�p�s. \n");
		break;
	case(1):
		printf("1. �j k�rd�s felv�tele. \n");
		printf("2. K�rd�ssor ment�se. \n");
		printf("3. Vissza. \n");
		break;
	case(2):
		printf("1. K�rd�s szerkeszt�se.\n");
		printf("2. K�rd�s t�rl�se.\n");
		printf("3. V�lasz megad�sa k�rd�shez\n");
		printf("4. Vissza. \n");
		break;
	case(3):
		printf("1. K�rd�ssor szerkeszt�se. \n");
		printf("2. Vissza. \n");
		break;
	default:
		break;
	}
}

Question* kerdes_hozzadas() {
	Question *q;
	printf("Adjon meg egy k�rd�st: \n");
	char *c = realloc(NULL, sizeof(char));
	c = beolvas(stdin, 200, 0);
	q->question = c;
	q->date = time(NULL);
	q->answers = malloc(sizeof(Answer) * 4);
	return q;
}

void kerdessor_mentes(Question *questionArray, int size) {
	FILE *file;
	int i, j;
	char *printed_line;
	printed_line = malloc(sizeof(char));

	//printf("K�rd�s els� eleme: %s\n", questionArray->question);
	printf("Adja meg a f�jl nev�t. \n");
	//char *fname = realloc(NULL, sizeof(char));
	char *fname/* = malloc(sizeof(char))*/;
	fname = beolvas(stdin, 200, 0);
	printf("Ide bemegy.\n");
	file = fopen(fname, "wt");

	for (i = 0; i < size; ++i) {
		if (i > 0) {
			fprintf(file, "\n");
		}
		printf("Van k�rd�s. Size: %i, Question: %s\n", size, questionArray[i].question);
		printed_line = realloc(NULL, strlen(questionArray[i].question));
		snprintf(printed_line, strlen(questionArray[i].question), "%s", questionArray[i].question);
		fprintf(file, printed_line);
	}
	free(printed_line);
	//free(fname);
	//free(questionArray);
	fclose(file);
}

Question* kerdessor_megnyitas(char *fname) {
	FILE *file;
	ssize_t read;
	size_t len = 200;
	char *line = malloc(len);
	int size = 0;
	Question *q = malloc(sizeof(Question));
	Question *temp = malloc(sizeof(Question));
	if (access(fname, F_OK) != -1) {
		file = fopen(fname, "r");
		//q = realloc(NULL, sizeof(Question));
		while (!feof(file)) {
			if (fgets(line, len, file) != NULL) {
				Question *tempp = malloc(sizeof(q));
				tempp = realloc(q, 30);
				if (tempp == NULL) {
					printf("De null.\n");
				}
				else {
					q = tempp;
				}
				temp = malloc(sizeof(Question));
				temp->question = realloc(NULL, sizeof(line));
				strcpy(temp->question, line);

				temp->answers = malloc(sizeof(Answer) * 4);

				temp->date = time(NULL);

				q[size] = *temp;

				if (temp != NULL) {
					free(temp);
					size++;
				}

				printf("Sor: %s\n", line);
				if (feof(file)) {
					fclose(file);
					break;
				}
				free(tempp);
			}
		}
	}
	else {
		printf("Nincs ilyen f�jl.\n");
		//free(q);
		//free(line);
		return NULL;
	}
	//free(fname);
	//free(line);
	//fclose(file);
	//q++;
	//printf("Size: %i, Elso kerdes: %s\n",size, q[0].question);
	/*Question *tempp = malloc(sizeof(q));
	tempp = realloc(q, sizeof(q));
	if(tempp != NULL){
	printf("NEm nulla.\n");
	return realloc(tempp, sizeof(tempp));
	}else{
	printf("De nulla.\n");
	return NULL;
	}*/
	return realloc(q, sizeof(Question) * 10);
}

char *kerdes_szerkesztes() {
	printf("Adja meg az �j k�rd�st. \n");
	char *asd = malloc(sizeof(char));
	asd = beolvas(stdin, sizeof(char), 0);
	return realloc(asd, strlen(asd));
}

int main() {
	Question *d;
	Question *szerk;
	int dontes = 1;
	int size = 0;
	int loop = 1;
	//Question questions[4];
	Question *questions = malloc(sizeof(Question));
	//Question questions[4];
	while (dontes != 4) {
	MAINMENU: main_menu(0);
		dontes = (int)*beolvas(stdin, sizeof(int), 1);
		switch (dontes) {
		case('1'):
		SUBMENU: main_menu(1);
			dontes = (int)*beolvas(stdin, sizeof(int), 1);
			switch (dontes) {
			case('1'):
				d = realloc(NULL, sizeof(Question));
				d = kerdes_hozzadas(size);
				Question *temp = malloc(sizeof(questions));
				temp = realloc(questions, sizeof(questions) + sizeof(Question));
				/*if(size > 0){

				questions = realloc(questions, sizeof(questions) + sizeof(Question));
				}*/
				if (temp != NULL) {
					questions = temp;
				}
				questions[size] = *d;
				if (d != NULL) {
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
				printf("Hib�s men�pont. \n");
				goto SUBMENU;
				break;
			}

			break;
		case('2'):
			printf("Adja meg a f�jl nev�t. \n");
			char *fname = malloc(sizeof(char));
			fname = beolvas(stdin, sizeof(char), 0);
			free(questions);
			Question *questions = realloc(NULL, sizeof(Question));
			questions = kerdessor_megnyitas(fname);
			printf("Itt mivan. \n");
			if (questions == NULL) {
				goto MAINMENU;
			}
		SUBMENU2: main_menu(2);
			dontes = (int)*beolvas(stdin, sizeof(char), 1);
			switch (dontes) {
			case('1'):
				for (loop = 1; questions->question != NULL; loop++/*, ++questions*/) {
					//printf("%i. %s \n", loop, questions->question);
				}
				printf("Adja meg melyik k�rd�st akarja szerkeszteni. \n");
				char *kar = malloc(sizeof(char));
				kar = beolvas(stdin, sizeof(char), 1);
				int ker = (int)*kar - '0';
				szerk = realloc(NULL, sizeof(Question));
				szerk = kerdes_hozzadas();
				questions[ker].question = szerk->question;
				printf("Ezen �tjut: %s\n", questions[ker].question);
				kerdessor_mentes(questions, loop - 1);
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
			printf("Nincs ilyen men�pont.\n");
			break;
		}

	}
	free(questions);
	free(d);
	free(szerk);
	printf("V�ge a programnak.\n");
	return 0;
}
