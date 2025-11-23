#include "general_fun.h"
#include "help_fun.h"
#include <stdio.h>
#include <string.h>
#include <iostream>

//char *opravnenia[POCET_PREDMET];
char opravnenia[POCET_PREDMET][DLZKA_STRING];

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

					/*int i = 0;
					char *token = strtok(file_predmety, ",");
					while (token != NULL && i < POCET_PREDMET) {
						opravnenia[i++] = token;
						token = strtok(NULL, ",");
					}*/

					int i = 0;
					char *token = strtok(file_predmety, ",");
					while (token != NULL && i < POCET_PREDMET) {
						// skopírujeme reťazec do pevného poľa
						strcpy(opravnenia[i], token); // opravnenia[i] je char[DLZKA_STRING]
						i++;
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
		printf("0) Ulozit zmeny a ukoncit program\n");
		printf("Volba: ");
		scanf_s("%d", &volba_predm);

		if (volba_predm < 0 || volba_predm > pocet_povolene) {
			printf("Nespravna volba! Skuste znova.\n\n");
		}
		else if (volba_predm == 0) {
			return -1;
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
		//printf("vybrany student cislo: %d", vybrany_student);

		if (vybrany_student < 0 || vybrany_student > pct_stud) {
			printf("\nNespravna volba! skuste znova.\n");
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
		printf("Pridat body za: \n1.cvicenie \n2.test \n3.skusku\n0.Zrusit\nVolba: ");
		scanf_s("%d", &body_volba);
		if (body_volba < 0 || body_volba > 3) {
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

	//printf("sem to dojde\n");

	for (int i = 0; i < pct_stud; i++) {
		spolu = studenti[i].cviceni_int + studenti[i].testy_int + studenti[i].skuska_int;

		percenta = (float)spolu / max_body * 100.0f;

		if (percenta >= ZN_A) znamka = 'A';
		else if (percenta >= ZN_B) znamka = 'B';
		else if (percenta >= ZN_C) znamka = 'C';
		else if (percenta >= ZN_D) znamka = 'D';
		else if (percenta >= ZN_E) znamka = 'E';
		else znamka = 'F';

		printf("%-4d %-20s %-10d %-10d %-10d %-10d %-10c\n", i+1, studenti[i].student_str, studenti[i].cviceni_int, studenti[i].testy_int, studenti[i].skuska_int, spolu, znamka);
	}

	//printf("\npocet studentov vo zobraz vysledky: %d\n", pct_stud);
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
	//printf("Zatial sa neda :)\n\n");
	//return;

	int volba_upravy = -1;

	while (1) {
		printf("Aku zmenu chcete vykonat: \n");
		printf("1) Pridat studenta\n2) Vymazat studenta\n3) Zmenit pocet maximalnych bodov\n0) Odist\n");
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
			switch (volba_upravy) {
				case 1: pridanie_stud;
				case 2: vymazanie_stud;
				case 3: zmena_max_bodov;
			}
			break; // ukonci while(1)
		}
	}
}

void pridanie_stud(){
	printf("Zatial sa neda :)\n\n");

	/*if (pocet_stud >= POCET_STUDENT) {
		printf("Bol dosiahnuty maximalny pocet studentov!\n\n");
		return;
	}

	printf("Zadajte meno studenta: ");
	scanf_s("%s", zoznam[pocet_stud].meno);

	pocet_stud++;
	printf("Student bol uspesne pridany!\n\n");*/
};

void vymazanie_stud(){
	printf("Zatial sa neda :)\n\n");

	/*if (pocet_stud == 0) {
		printf("Zoznam studentov je prazdny!\n\n");
		return;
	}

	int index;
	printf("Zadaj index studenta na vymazanie (0 - %d): ", pocet_stud - 1);
	scanf("%d", &index);

	if (index < 0 || index >= pocet_stud) {
		printf("Neplatny index!\n\n");
		return;
	}

	// posunutie pola doľava
	for (int i = index; i < pocet_stud - 1; i++) {
		zoznam[i] = zoznam[i + 1];
	}

	pocet_stud--;
	printf("Student bol vymazany!\n\n");*/
};

void zmena_max_bodov(){
	printf("Zatial sa neda :)\n\n");
};