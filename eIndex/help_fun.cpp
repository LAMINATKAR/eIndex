#include "general_fun.h"
#include <stdio.h>
#include <string.h>
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

void fill_strukt(struct student* studenti, int predm_cislo, int *count_stud, int max_body[POCET_PREDMET]) {
	FILE* fptr = fopen(SUBJECTS_FILE, "r");

	if (fptr == NULL) {
		printf("Chyba: nepodarilo sa otvorit subor SUBJECTS_FILE\n");
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

		if (strncmp(buff, "#MAX_BODY:", 10) == 0) {
			max_body[predm_cislo] = atoi(buff + 10);
			continue;
		}

		if (strcmp(buff, "#---DATA---") == 0) continue;

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
	fclose(fptr);
}

void zapis_subor(struct student* studenti, int pct_stud, char *predmet, int max_body) {
	FILE* fptr = fopen(SUBJECTS_TEMP_FILE, "a");

	if (!fptr) {
		perror("Chyba: nepodarilo sa otvorit alebo vytvorit SUBJECTS_TEMP_FILE");
		return;
	}

	fprintf(fptr, "#PREDMET:%s\n", predmet);
	fprintf(fptr, "#MAX_BODY:%d\n", max_body);
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
	const char* original = SUBJECTS_FILE;
	const char* temp = SUBJECTS_TEMP_FILE;

	if (remove(original) != 0) {
		perror("Chyba pri mazani SUBJECTS_FILE");
		// aj tak pokracujeme, mozno neexistoval
	}

	if (rename(temp, original) != 0) {
		perror("Chyba pri premenovani SUBJECTS_TEMP_FILE na SUBJECTS_FILE");
	} else {
		printf("Databaza bola uspesne aktualizovana.\n");
	}
}