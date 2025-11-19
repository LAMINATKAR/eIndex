#include "general_fun.h"
#include "edit_sub_fun.h"
#include <stdio.h>
#include <string.h>

char *opravnenia[POCET_PREDMET];

void vycistenie() {
	system("cls");
	printf("\n=== ELEKTRONICKY INDEX ===\n\n");
}

int overenie()
{
	char usnm[DLZKA_STRING];
	char uspass[DLZKA_STRING];
	int pokusy = 0;

	while (pokusy < 3) {

		printf("Zadajte prihlasovacie meno: ");
		fgets(usnm, DLZKA_STRING, stdin);
		usnm[strcspn(usnm, "\n")] = 0;

		printf("Zadajte heslo: ");
		fgets(uspass, DLZKA_STRING, stdin);
		uspass[strcspn(uspass, "\n")] = 0;

		unsigned long uspass_hash = simple_hash(uspass);

		//printf("[DEBUG] Heslo: '%s', Hash: %lu\n", uspass, uspass_hash); // DEBUG a zaroven sluzi na vytvaranie hesiel NEMAZAT

		if (usnm != NULL) {
			FILE* fptr;
			fptr = fopen("users.txt", "r");
			if (fptr == NULL) {
				perror("Chyba pri otvarani suboru users.txt");
				return 1;
			}

			char buff[DLZKA_STRING*2];

			// Reading strings till fgets returns NULL
			while (fgets(buff, DLZKA_STRING*2, fptr)) {
				char file_meno[DLZKA_STRING];
				char file_heslo[DLZKA_STRING];
				char file_predmety[DLZKA_STRING];
				file_predmety[0] = '\0';

				sscanf(buff, "%[^:]:%[^:]:%[^\n]", file_meno, file_heslo, file_predmety); // nacita a parsuje vo formate "meno:heslo:predmety"

				unsigned long file_heslo_hash = strtoul(file_heslo, NULL, 10); // konverzia hesla zo stringu na unsigned long

				if (strcmp(file_meno, usnm) == 0 && file_heslo_hash == uspass_hash) {
					printf("Vitaj v eIndexe, %s!\n\n", file_meno);

					int i = 0;
					char *token = strtok(file_predmety, ",");
					while (token != NULL && i < POCET_PREDMET) {
						opravnenia[i++] = token;
						token = strtok(NULL, ",");
					}

					fclose(fptr);
					return 0;
				}
			}

			fclose(fptr);
			pokusy++;
			if (pokusy < 3) {
				printf("Prihlasenie neuspesne! (%d/3 pokusov) Skuste znova.\n\n", pokusy);
			} else {
				printf("Prihlasenie neuspesne! Dosiahli ste maximalny pocet pokusov (3). Program bude ukonceny.\n");
				return 1;
			}
		}
	}
}

// Jednoduchý hash (DJB2)
unsigned long simple_hash(const char *str) {
	unsigned long hash = 5381;
	int c;
	while ((c = *str++))
		hash = ((hash << 5) + hash) + c; // hash * 33 + c
	return hash;
}

int vyber_predmetu(char predmet[POCET_PREDMET][DLZKA_STRING]) {

	int volba_predm = -1;
	char *povolene_predmety[POCET_PREDMET]; // ukazovatele na povolené predmety
	int indexy_povolene[POCET_PREDMET];     // pôvodné indexy v poli predmet
	int pocet_povolene = 0;

	for (int i = 0; i < POCET_PREDMET-1; i++) {           // pre každý predmet
		for (int j = 0; j < POCET_PREDMET; j++) {        // pre každý prvok v opravnenia
			if (opravnenia[j] == NULL) break;           // koniec platných oprávnení
			if (strcmp(predmet[i], opravnenia[j]) == 0) {
				povolene_predmety[pocet_povolene] = predmet[i];
				indexy_povolene[pocet_povolene] = i;
				pocet_povolene++;
				break;
			}
		}
	}

	if (pocet_povolene == 0) {
		printf("Nemate opravnenie na ziadny predmet.\n");
		return -1;
	}

	while (1) {
		printf("Zadajte cislo predmetu ktory chcete otvorit: \n");
		for (int i = 0; i < pocet_povolene; i++) {
			printf("%d) %s\n", i + 1, povolene_predmety[i]);
		}
		//printf("0) Ukoncit program\n");
		printf("Volba: ");
		scanf_s("%d", &volba_predm);

		if (volba_predm <= 0 || volba_predm > pocet_povolene) {
			printf("Nespravna volba! Skuste znova.\n\n");
		}
		else {
			//printf("Vybrany predmet: %s.\n", predmet[volba_predm - 1]);
			break; // ukonci while(1)
		}
	}

	vycistenie();

	// DEBUG vypis
	//printf("[DEBUG] Vybrany predmet: %s (index v hlavnom poli: %d)\n", [indexy_povolene[volba_predm-1]], indexy_povolene[volba_predm-1]);

	return indexy_povolene[volba_predm-1];
}

void zapis_znamok(char predmety[POCET_PREDMET][DLZKA_STRING], char predmety_txt[POCET_PREDMET][DLZKA_STRING], int predmet, struct student* studenti, int pct_stud) {
	int pocet_studentov = zobraz_vysledky(predmety, predmety_txt, predmet, studenti, pct_stud);

	

	int vybrany_student = -1;

	while (1) {
		printf("\nvyberte studenta, ktoremu chcete zapisat body: ");
		scanf_s("%d", &vybrany_student);

		//test
		printf("vybrany student cislo: %d", vybrany_student);

		if (vybrany_student < 0 || vybrany_student > pct_stud) {
			printf("nespravna volba! skuste znova.\n");
		}
		else if (vybrany_student == 0) {
			edit_predmetu();
			//fclose(fptr);
			return;
		}
		else {
			break; // ukonci while(1)
		}
	}

 

    int body_volba = 0;
	while (1) {
		printf("Pridat body za: \n1.cvicenie \n2.test \n3.skusku\nVolba: ");
		scanf_s("%d", &body_volba);
		if (body_volba == 0 || body_volba > 3) {
			printf("Nespravna volba! Skuste znova.\n\n");
		}
		else {
			break; // ukonci while(1)
		}
	}

    int pocet_bodov = 0;
    printf("\nKolko bodov chcete pridat?: ");
    scanf_s("%d", &pocet_bodov);

    switch (body_volba) {
    case 1: studenti[vybrany_student-1].cviceni_int += pocet_bodov; break;
    case 2: studenti[vybrany_student-1].testy_int += pocet_bodov; break;
    case 3: studenti[vybrany_student-1].skuska_int += pocet_bodov; break;
    }

	printf("\nBody boli uspesne pridane. Aktualizovany stav:\n");
    printf("%d) Student: %s, Cvicenia: %d, Testy: %d, Skuska: %d\n", vybrany_student, studenti[vybrany_student - 1].student_str, studenti[vybrany_student - 1].cviceni_int, studenti[vybrany_student - 1].testy_int, studenti[vybrany_student - 1].skuska_int);
    //fclose(fptr);
}

int zobraz_vysledky(char predmety[POCET_PREDMET][DLZKA_STRING], char predmety_txt[POCET_PREDMET][DLZKA_STRING], int predmet, struct student* studenti, int pct_stud) {

	printf("Vybrany predmet: %s\n", predmety[predmet]);

	FILE* fptr = fopen("subjects.txt", "r");
	if (fptr == NULL) {
		printf("Chyba: nepodarilo sa otvorit súbor subjects.txt");
		return 0;
	}

	char riadok[DLZKA_STRING];
	int max_body = 0;
	int pocet_studentov = 0;
	char upr_riadok[DLZKA_STRING];
	char riadok_prdmt[DLZKA_STRING];

	// načítanie max. bodov
	while (fgets(riadok, sizeof(riadok), fptr)) {
		riadok[strcspn(riadok, "\r\n")] = 0;
		//printf("\n-----%s %s-------\n", riadok + 9, predmety[predmet]);
		
		if(strcmp(riadok + 9, predmety[predmet]) != 0){
			continue;
		}
		else {
			fgets(riadok, sizeof(riadok), fptr);
			riadok[strcspn(riadok, "\r\n")] = 0;
			max_body = atoi(riadok + 10);
			break;
		}

		/*if (strncmp(riadok, "#MAX_BODY:", 10) == 0) {
			max_body = atoi(riadok + 10);
		} else if (strncmp(riadok, "#---DATA---", 11) == 0) {
			break;
		}*/
	}

	printf("Maximalny pocet bodov: ");
	if (max_body <= 0) {
		printf("Nedefinovany!\n");
	}
	else {
		printf("%d\n", max_body);
	}

	printf("\n%-4s %-20s %-10s %-10s %-10s %-10s %-10s\n", "ID", "Meno", "Cvicenia", "Testy", "Skuska", "Spolu", "Znamka");
	printf("----------------------------------------------------------------------------------------\n");


	

	/*hali nove*/

	int spolu;
	float percenta;
	char znamka;

	printf("sem to dojde\n");

	for (int i = 0; i < pct_stud; i++) {
		spolu = studenti[i].cviceni_int + studenti[i].testy_int + studenti[i].skuska_int;

		percenta = (float)spolu / max_body * 100.0f;

		if (percenta >= 90) znamka = 'A';
		else if (percenta >= 80) znamka = 'B';
		else if (percenta >= 70) znamka = 'C';
		else if (percenta >= 60) znamka = 'D';
		else if (percenta >= 50) znamka = 'E';
		else znamka = 'F';

		printf("%-4d %-20s %-10d %-10d %-10d %-10d %-10c\n", i+1, studenti[i].student_str, studenti[i].cviceni_int, studenti[i].testy_int, studenti[i].skuska_int, spolu, znamka);
	}

	printf("\npocet studentov vo zobraz vysledky: %d\n", pct_stud);
	//spolu = studenti[].cvicenia_int + testy_int + skuska_int;

	/*hali nove*/


	if (pct_stud <= 0) {
		printf("!    V tomto predmete nie su ziadni studenti!\n");
	}
	printf("%-4d Odist/Upravit predmet\n", 0);

	//printf("\nPre vratenie do hlavneho menu stlacte Enter.");
	//getchar(); // zachytí starý znak '\n' z predchádzajúceho scanf
	//getchar(); // čaká na stlačenie Enter

	fclose(fptr);
	//vycistenie();

	return pct_stud;
}

void edit_predmetu() {
	printf("Zatial sa neda :)\n\n");
	return;

	int volba_upravy = -1;

	while (1) {
		printf("Aku zmenu chcete vykonat: \n");
		printf("1) Zmenit nazov predmetu\n2) Zmenit maximalny pocet bodov\n3) Pridat studenta\n4) Vymazat studenta\n0) Odist\n");
		printf("Volba: ");
		scanf_s("%d", &volba_upravy);

		if (volba_upravy < 0 || volba_upravy > 4) {
			printf("Nespravna volba! Skuste znova.\n\n");
		}
		else if (volba_upravy == 0) {
			return;
		}
		else {
			/*switch (volba_upravy) {
				case 1: zmena_nazvu;
				case 2: zmena_max_bodov;
				case 3: pridanie_stud;
				case 4: vymazanie_stud;
			}*/
			break; // ukonci while(1)
		}
	}
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

		if (strcmp(buff, "#MAX_BODY:100") == 0 || strcmp(buff, "#---DATA---") == 0) {
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