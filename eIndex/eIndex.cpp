// eIndex.cpp : Defines the entry point for the application.
//

#include "eIndex.h"
#include <stdio.h>
#include <string.h>
#include "funkcie.h"

const int POCET_PREDMET = 6;
const int DLZKA_STRING = 50;

char urci_znamku(float percenta) {
	if (percenta >= 90) return 'A';
	else if (percenta >= 80) return 'B';
	else if (percenta >= 70) return 'C';
	else if (percenta >= 60) return 'D';
	else if (percenta >= 50) return 'E';
	else return 'F';
}

void vycistenie();
int overenie(char usnm[DLZKA_STRING]);
int vyber_predmetu(char predmet[POCET_PREDMET][DLZKA_STRING]);
void zapis_znamok(char predmet[POCET_PREDMET][DLZKA_STRING], char predmet_txt[POCET_PREDMET][DLZKA_STRING], int vybr_predmet);
void zobraz_vysledky(char predmety[POCET_PREDMET][DLZKA_STRING], char predmety_txt[POCET_PREDMET][DLZKA_STRING], int vybr_predmet);

//using namespace std;

int main()
{

    char us_name[DLZKA_STRING];
    char predmet[POCET_PREDMET][DLZKA_STRING] = {
	    "BPC-MAT1",
    	"BPC-ZKR",
    	"BPC-PC1T",
    	"BPC-KOM",
    	"BPC-PNA",
    	"\0"
    };
    //char predmet_txt[POCET_PREDMET][DLZKA_STRING] = { "../../../BPC-MAT1.txt", "../../../BPC-ZKR.txt", "../../../BPC-PC1T.txt", "../../../BPC-KOM.txt", "../../../BPC-PNA.txt", "\0" };
	char predmet_txt[POCET_PREDMET][DLZKA_STRING] = {
		"BPC-MAT1.txt",
		"BPC-ZKR.txt",
		"BPC-PC1T.txt",
		"BPC-KOM.txt",
		"BPC-PNA.txt",
		"\0"
	};

	printf("\n=== ELEKTRONICKY INDEX ===\n");

    if (overenie(us_name)) {
        return 0; // neuspesne prihlasenie
    }

	int rezim = 0;
	while (1) {
		printf("Vyberte rezim:\n");
		printf("1. Rezim editacie\n");
		printf("2. Rezim zobrazenia\n");
		printf("0. Ukoncit program\n");
		printf("Volba: ");
		scanf_s("%d", &rezim);

		if (rezim == 1) {
			vycistenie();
			int editovanie = 1;
			int vybr_predmet = vyber_predmetu(predmet);
			while (editovanie) {
				zapis_znamok(predmet, predmet_txt, vybr_predmet);

				printf("\nChcete pokracovat v editacii? (1 = ano, 0 = spat do vyberu rezimu): ");
				scanf_s("%d", &editovanie);
				vycistenie();
			}
		}
		else if (rezim == 2) {
			vycistenie();
			int zobrazovanie = 1;
			int vybr_predmet = vyber_predmetu(predmet);
			zobraz_vysledky(predmet, predmet_txt, vybr_predmet);
		}
		else if (rezim == 0) {
			printf("Koniec programu.\n");
			break;
		}
		else {
			printf("Neplatna volba, skuste znova.\n");
		}
	}
    return 0;
}

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
					printf("Uspesne prihlaseny ako: %s\n\n", buff);
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

	int volba_predm = 0;

	while (1) {
		printf("Zadajte cislo predmetu ktory chcete otvorit: \n");
		for (int i = 0; i < POCET_PREDMET-1; i++) {
			printf("%d) %s\n", i + 1, predmet[i]);
		}
		printf("Volba: ");
		scanf_s("%d", &volba_predm);

		if (volba_predm <= 0 || volba_predm > POCET_PREDMET-1) {
			printf("Nespravna volba! Skuste znova.\n\n");
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
	printf("Vybrany predmet: %s\n", predmety[predmet]);

	FILE* fptr;
	fptr = fopen(predmety_txt[predmet], "r");
	char buff[DLZKA_STRING];
	int id = 1;

	char* student = NULL;
	char* cviceni = NULL;
	char* testy = NULL;
	char* skuska = NULL;
	char* stud_id_string = NULL;


	//vypis studentov
	while (fgets(buff, DLZKA_STRING, fptr)) {
		buff[strcspn(buff, "\n")] = 0;

		//parsovanie podla :
		student = strtok(buff, ":");
		cviceni = strtok(NULL, ":");
		testy = strtok(NULL, ":");
		skuska = strtok(NULL, ":");

		printf("%d) Student: %s, Cvicenia: %s, Testy: %s, Skuska: %s\n", id, student, cviceni, testy, skuska);
		id++;
	}

	int cviceni_int = 0;
	int testy_int = 0;
	int skuska_int = 0;
	int stud_id_int = 0;
	int student_id = 0;

	while (1) {
		printf("\nVyberte studenta, ktoremu chcete zapisat body: ");
		scanf_s("%d", &student_id);
		if (student_id == 0 || student_id > id-1) {
			printf("Nespravna volba! Skuste znova.\n");
		}
		else {
			break; // ukonci while(1)
		}
	}

    rewind(fptr); // znova citanie suboru od zaciatku
    id = 1;

    while (fgets(buff, DLZKA_STRING, fptr)) {

        buff[strcspn(buff, "\n")] = 0;

    	// parsovanie podla :
        student = strtok(buff, ":");
        cviceni = strtok(NULL, ":");
        testy = strtok(NULL, ":");
        skuska = strtok(NULL, ":");
        stud_id_string = strtok(NULL, ":");

        // konverzia na na int
        stud_id_int = atoi(stud_id_string);
        cviceni_int = atoi(cviceni);
        testy_int = atoi(testy);
        skuska_int = atoi(skuska);

        if (student_id == stud_id_int) {
            printf("Vybrali ste: %d) Student: %s\n\n", stud_id_int, student);
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
    case 1:
        cviceni_int += pocet_bodov;
        break;
    case 2:
        testy_int += pocet_bodov;
        break;
    case 3:
        skuska_int += pocet_bodov;
        break;
    }

	printf("\nBody boli uspesne pridane. Aktualizovany stav:\n");
    printf("%d) Student: %s, Cvicenia: %d, Testy: %d, Skuska: %d\n", stud_id_int, student, cviceni_int, testy_int, skuska_int);
    fclose(fptr);
}

void zobraz_vysledky(char predmety[POCET_PREDMET][DLZKA_STRING], char predmety_txt[POCET_PREDMET][DLZKA_STRING], int predmet) {

	printf("Vybrany predmet: %s\n", predmety[predmet]);

	FILE* fptr = fopen(predmety_txt[predmet], "r");
	if (fptr == NULL) {
		printf("Chyba: nepodarilo sa otvoriť súbor predmetu %s.\n", predmety[predmet]);
		return;
	}

	char riadok[DLZKA_STRING];
	printf("\n%-20s %-10s %-10s %-10s %-10s %-10s\n", "Meno", "Cvicenia", "Testy", "Skuska", "Percenta", "Znamka");
	printf("--------------------------------------------------------------------------\n");

	while (fgets(riadok, sizeof(riadok), fptr)) {
		char *meno, *cvicenia, *testy, *skuska, *id_str;
		int cvicenia_int, testy_int, skuska_int;
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

			// Výpočet percent (napr. váhy: cvičenia 20 %, testy 30 %, skúška 50 %)
			percenta = (cvicenia_int * 0.2f) + (testy_int * 0.3f) + (skuska_int * 0.5f);
			znamka = urci_znamku(percenta);

			printf("%-20s %-10d %-10d %-10d %-10.1f %-10c\n", meno, cvicenia_int, testy_int, skuska_int, percenta, znamka);
		}
	}

	printf("\nPre vratenie do hlavneho menu stlacte Enter.");
	getchar(); // zachytí starý znak '\n' z predchádzajúceho scanf
	getchar(); // čaká na stlačenie Enter

	fclose(fptr);
	vycistenie();
}