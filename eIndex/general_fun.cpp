#include "general_fun.h"
#include "edit_sub_fun.h"
#include <stdio.h>
#include <string.h>

void vycistenie() {
	system("cls");
	printf("\n=== ELEKTRONICKY INDEX ===\n\n");
}

int overenie(char usnm[DLZKA_STRING])
{
	int pokusy = 0;

	while (pokusy < 3) {
		printf("Zadajte prihlasovacie meno: ");
		scanf_s("%s", usnm);

		if (usnm != NULL) {
			FILE* fptr;
			//fptr = fopen("../../../users.txt", "r");
			fptr = fopen("users.txt", "r");
			if (fptr == NULL) {
				perror("Chyba pri otvarani suboru");
				return 1;
			}

			char buff[DLZKA_STRING];
			int status_meno = 1;

			// Reading strings till fgets returns NULL
			while (fgets(buff, DLZKA_STRING, fptr)) {
				buff[strcspn(buff, "\n")] = 0;

				if (strcmp(buff, usnm) == 0) {
					printf("Vitaj v eIndexe, %s!\n\n", buff);
					status_meno = 0;
				}
			}

			fclose(fptr);

			if (status_meno) {
				pokusy++;
				if (pokusy < 3) {
					printf("Prihlasenie neuspesne! (%d/3 pokusov) Skuste znova.\n\n", pokusy);
				} else {
					printf("Prihlasenie neuspesne! Dosiahli ste maximalny pocet pokusov (3). Program bude ukonceny.\n");
					return 1;
				}
			} else {
				//break; //meno bolo nájdené
				return 0;
			}
		}
	}
}

int vyber_predmetu(char predmet[POCET_PREDMET][DLZKA_STRING]) {

	int volba_predm = -1;

	while (1) {
		printf("Zadajte cislo predmetu ktory chcete otvorit: \n");
		for (int i = 0; i < POCET_PREDMET-1; i++) {
			printf("%d) %s\n", i + 1, predmet[i]);
		}
		printf("0) Pridat predmet\n");
		printf("Volba: ");
		scanf_s("%d", &volba_predm);

		if (volba_predm < 0 || volba_predm > POCET_PREDMET-1) {
			printf("Nespravna volba! Skuste znova.\n\n");
		}
		else if (volba_predm == 0) {
			add_predmet();
		}
		else {
			//printf("Vybrany predmet: %s.\n", predmet[volba_predm - 1]);
			break; // ukonci while(1)
		}
	}

	vycistenie();
	return volba_predm-1;
}

void zapis_znamok(char predmety[POCET_PREDMET][DLZKA_STRING], char predmety_txt[POCET_PREDMET][DLZKA_STRING], int predmet) {
	int pocet_studentov = zobraz_vysledky(predmety, predmety_txt, predmet);

	FILE* fptr = fopen(predmety_txt[predmet], "r");
	if (fptr == NULL) {
		printf("Chyba: nepodarilo sa otvoriť súbor %s\n", predmety_txt[predmet]);
		return;
	}

	char buff[DLZKA_STRING];
	char* student = NULL;
	char* cviceni = NULL;
	char* testy = NULL;
	char* skuska = NULL;
	char* stud_id_string = NULL;

	int cviceni_int = 0;
	int testy_int = 0;
	int skuska_int = 0;
	int studID_int = 0;
	int vybrany_student = -1;

	//vypis studentov
	/*while (fgets(buff, DLZKA_STRING, fptr)) {
		buff[strcspn(buff, "\n")] = 0;

		//parsovanie podla :
		student = strtok(buff, ":");
		cviceni = strtok(NULL, ":");
		testy = strtok(NULL, ":");
		skuska = strtok(NULL, ":");

		printf("%d) Student: %s, Cvicenia: %s, Testy: %s, Skuska: %s\n", id, student, cviceni, testy, skuska);
		id++;
	}*/

	while (1) {
		printf("\nVyberte studenta, ktoremu chcete zapisat body: ");
		scanf_s("%d", &vybrany_student);
		if (vybrany_student < 0 || vybrany_student > pocet_studentov) {
			printf("Nespravna volba! Skuste znova.\n");
		}
		else if (vybrany_student == 0) {
			edit_predmetu();
			fclose(fptr);
			return;
		}
		else {
			break; // ukonci while(1)
		}
	}

    rewind(fptr); // znova citanie suboru od zaciatku
    int id = 1;

    while (fgets(buff, DLZKA_STRING, fptr)) {
        buff[strcspn(buff, "\n")] = 0;

    	// parsovanie podla :
        student = strtok(buff, ":");
        cviceni = strtok(NULL, ":");
        testy = strtok(NULL, ":");
        skuska = strtok(NULL, ":");
        stud_id_string = strtok(NULL, ":");

        // konverzia na na int
        studID_int = atoi(stud_id_string);
        cviceni_int = atoi(cviceni);
        testy_int = atoi(testy);
        skuska_int = atoi(skuska);

        if (id == studID_int) {
            printf("Vybrali ste: %d) Student: %s\n\n", studID_int, student);
            break;
        }
        id++;
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
    case 1: cviceni_int += pocet_bodov; break;
    case 2: testy_int += pocet_bodov; break;
    case 3: skuska_int += pocet_bodov; break;
    }

	printf("\nBody boli uspesne pridane. Aktualizovany stav:\n");
    printf("%d) Student: %s, Cvicenia: %d, Testy: %d, Skuska: %d\n", studID_int, student, cviceni_int, testy_int, skuska_int);
    fclose(fptr);
}

int zobraz_vysledky(char predmety[POCET_PREDMET][DLZKA_STRING], char predmety_txt[POCET_PREDMET][DLZKA_STRING], int predmet) {

	printf("Vybrany predmet: %s\n", predmety[predmet]);

	FILE* fptr = fopen(predmety_txt[predmet], "r");
	if (fptr == NULL) {
		printf("Chyba: nepodarilo sa otvoriť súbor predmetu %s.\n", predmety[predmet]);
		return 0;
	}

	char riadok[DLZKA_STRING];
	int max_body = 0;
	int pocet_studentov = 0;

	// načítanie max. bodov
	while (fgets(riadok, sizeof(riadok), fptr)) {
		if (strncmp(riadok, "#MAX_BODY:", 10) == 0) {
			max_body = atoi(riadok + 10);
		} else if (strncmp(riadok, "#---DATA---", 11) == 0) {
			break;
		}
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


	while (fgets(riadok, sizeof(riadok), fptr)) {
		char *meno, *cvicenia, *testy, *skuska, *id_str;
		int cvicenia_int, testy_int, skuska_int, spolu;
		float percenta;
		char znamka;

		// rozdelenie riadku (formát: meno:cvicenia:testy:skuska:id)
		meno = strtok(riadok, ":");
		cvicenia = strtok(NULL, ":");
		testy = strtok(NULL, ":");
		skuska = strtok(NULL, ":");
		id_str = strtok(NULL, ":");

		if (meno && cvicenia && testy && skuska) {
			cvicenia_int = atoi(cvicenia);
			testy_int = atoi(testy);
			skuska_int = atoi(skuska);
			spolu = cvicenia_int + testy_int + skuska_int;

			percenta = (float)spolu / max_body * 100.0f;

			if (percenta >= 90) znamka = 'A';
			else if (percenta >= 80) znamka = 'B';
			else if (percenta >= 70) znamka = 'C';
			else if (percenta >= 60) znamka = 'D';
			else if (percenta >= 50) znamka = 'E';
			else znamka = 'F';

			printf("%-4d %-20s %-10d %-10d %-10d %-10d %-10c\n",
				   pocet_studentov + 1, meno, cvicenia_int, testy_int, skuska_int, spolu, znamka);

			pocet_studentov++;
		}
	}
	if (pocet_studentov <= 0) {
		printf("!    V tomto predmete nie su ziadni studenti!\n");
	}
	printf("%-4d Odist/Upravit predmet\n", 0);

	//printf("\nPre vratenie do hlavneho menu stlacte Enter.");
	//getchar(); // zachytí starý znak '\n' z predchádzajúceho scanf
	//getchar(); // čaká na stlačenie Enter

	fclose(fptr);
	//vycistenie();

	return pocet_studentov;
}

void edit_predmetu() {
	printf("Zatial sa neda :)\n\n");

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