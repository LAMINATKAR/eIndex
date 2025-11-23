#include "general_fun.h"
#include <stdio.h>
#include <string.h>
#include <process.h>
#include <iostream>

void vycistenie() {
	system("cls");
	printf("\n=== ELEKTRONICKY INDEX ===\n\n");
}

// Jednoduchý hash (DJB2)
unsigned long simple_hash(const char *str) {
	unsigned long hash = 5381;
	int c;
	while ((c = *str++))
		hash = ((hash << 5) + hash) + c; // hash * 33 + c
	return hash;
}

void fill_strukt(struct student* studenti, int predm_cislo, int *count_stud) {
	FILE* fptr = fopen("subjects.txt", "r");

	if (fptr == NULL) {
		printf("Chyba: nepodarilo sa otvorit subor subjects.txt\n");
		return;
	}

	char buff[DLZKA_STRING];
	char predm_str[DLZKA_STRING];

	switch (predm_cislo) {
		case 0:
			strcpy(predm_str,"#PREDMET:BPC-KOM");
			break;
		case 1:
			strcpy(predm_str, "#PREDMET:BPC-MA1");
			break;
		case 2:
			strcpy(predm_str, "#PREDMET:BPC-PC1T");
			break;
		case 3:
			strcpy(predm_str, "#PREDMET:BPC-PNA");
			break;
		case 4:
			strcpy(predm_str, "#PREDMET:BPC-ZKR");
			break;
	}


	while (fgets(buff, DLZKA_STRING, fptr)) {
		buff[strcspn(buff, "\n")] = 0;
		if (strcmp(buff, predm_str) == 0) {
			break;
		}
	}

	int prm = 0;

	while (fgets(buff, DLZKA_STRING, fptr)) {
		buff[strcspn(buff, "\n")] = 0;

		if (strncmp(buff, "#MAX_BODY:", 10) == 0 || strcmp(buff, "#---DATA---") == 0) {
			continue;
		}

		if (strcmp(buff, "#END") == 0) {
			*count_stud = prm;
			break;
		}

		studenti[prm].student = strtok(buff, ":");
		studenti[prm].cviceni = strtok(NULL, ":");
		studenti[prm].testy = strtok(NULL, ":");
		studenti[prm].skuska = strtok(NULL, ":");
		studenti[prm].stud_id_string = strtok(NULL, ":");


		strcpy(studenti[prm].student_str, studenti[prm].student);
		strcpy(studenti[prm].cviceni_str, studenti[prm].cviceni);
		strcpy(studenti[prm].testy_str, studenti[prm].testy);
		strcpy(studenti[prm].skuska_str, studenti[prm].skuska);
		strcpy(studenti[prm].stud_id_str, studenti[prm].stud_id_string);

		// konverzia na na int
		studenti[prm].studID_int = atoi(studenti[prm].stud_id_string);
		studenti[prm].cviceni_int = atoi(studenti[prm].cviceni);
		studenti[prm].testy_int = atoi(studenti[prm].testy);
		studenti[prm].skuska_int = atoi(studenti[prm].skuska);

		prm++;
	}
}

void zapis_subor(struct student* studenti, int pct_stud, char *predmet) {

	FILE* fptr = fopen("subjects_temp.txt", "r");

	if (fptr) {
		// Existuje
		fclose(fptr);
		fptr = fopen("subjects_temp.txt", "a");
	}
	else {
		// Neexistuje
		fptr = fopen("subjects_temp.txt", "w+");
	}

	if (!fptr) {
		perror("Chyba: nepodarilo sa otvorit alebo vytvorit subjects_temp.txt");
		return;
	}

	fprintf(fptr, "#PREDMET:");
	fprintf(fptr, "%s\n", predmet);
	fprintf(fptr, "#MAX_BODY:100\n");
	fprintf(fptr, "#---DATA---\n");

	for (int i = 0; i < pct_stud; i++) {
		fprintf(fptr, "%s:%d:%d:%d:%d:\n",
			studenti[i].student_str,
			studenti[i].cviceni_int,
			studenti[i].testy_int,
			studenti[i].skuska_int,
			studenti[i].studID_int);
	}

	fprintf(fptr, "#END\n\n");
	fclose(fptr);

}

void update_subor() {

	const char* filename = "subjects.txt";

	if (remove(filename) == 0) {
		printf("Subor zmazany uspesne.\n");
	}
	else {
		perror("Chyba pri mazani suboru");
	}

	const char* stary = "subjects_temp.txt";
	const char* novy = "subjects_novy.txt";

	if (rename(stary, novy) == 0) {
		printf("Subor premenovany uspesne.\n");
	}
	else {
		perror("Chyba pri premenovani suboru");
	}


}