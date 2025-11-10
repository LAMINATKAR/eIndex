// eIndex.cpp : Defines the entry point for the application.
//

#include "eIndex.h"
#include <stdio.h>
#include <string.h>
#include "funkcie.h"

const int POCET_PREDMET = 6;
const int DLZKA_STRING = 50;

void vycistenie();
int overenie(char usnm[DLZKA_STRING]);
int vyber_predmetu(char predmet[POCET_PREDMET][DLZKA_STRING]);
void zapis_znamok(char predmet[POCET_PREDMET][DLZKA_STRING], char predmet_txt[POCET_PREDMET][DLZKA_STRING], int vybr_predmet);

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

    //int vybr_predmet = vyber_predmetu(predmet);
	//zapis_znamok(predmet, predmet_txt, vybr_predmet);

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
			while (editovanie) {
				int vybr_predmet = vyber_predmetu(predmet);
				zapis_znamok(predmet, predmet_txt, vybr_predmet);

				printf("\nChcete pokracovat v editacii? (1 = ano, 0 = spat do vyberu rezimu): ");
				scanf_s("%d", &editovanie);
				vycistenie();
			}
		}
		else if (rezim == 2) {
			printf("Zatial nemame :)\n\n");
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
		printf("Zadajte cislo predmetu, do ktoreho chcete zadavat body: \n");
		for (int i = 0; i < POCET_PREDMET; i++) {
			printf("%d) %s\n", i + 1, predmet[i]);
		}
		printf("Volba: ");
		scanf_s("%d", &volba_predm);

		if (volba_predm <= 0 || volba_predm > POCET_PREDMET) {
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

    printf("\nVyberte studenta, ktoremu chcete zapisat body: ");
    scanf_s("%d", &student_id);
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

        //printf("mali by byt integers:::%d)Student: %s Cvicenia: %d, Testy: %d, Skuska: %d\n",id ,student, cviceni_int, testy_int, skuska_int);

        if (student_id == stud_id_int) {
            printf("Vybrali ste: %d) Student: %s\n\n", stud_id_int, student);
            break;
        }

        id++;
    }

    //printf("\n--mali by byt integers:::%d)Student: %s Cvicenia: %d, Testy: %d, Skuska: %d\n--",id ,student, cviceni_int, testy_int, skuska_int);
    //printf("\nrychly debug--%d--\n", stud_id_int);

    int body_volba = 0;
    printf("Pridat body za: \n1.cvicenie \n2.test \n3.skusku\nVolba: ");
    scanf_s("%d", &body_volba);

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

    printf("\nnove hodnoty len docasne:::%d)Student: %s  Cvicenia: %d, Testy: %d, Skuska: %d\n", stud_id_int, student, cviceni_int, testy_int, skuska_int);
    fclose(fptr);
}