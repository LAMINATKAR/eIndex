// eIndex.cpp : Defines the entry point for the application.
//

#include "eIndex.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "db.h"

#define DB_FILENAME "db.bin"

int overenie(char usnm[50]);
int vyber_predmetu(char predmet[5][50]);


//using namespace std;

int main()
{
	//main kod hali

    char us_name[50];
    char predmet[6][50] = { "BPC-MAT1", "BPC-ZKR", "BPC-PC1T", "BPC-KOM", "BPC-PNA", "\0" };
    //char predmet_txt[6][50] = { "../../../BPC-MAT1.txt", "../../../BPC-ZKR.txt", "../../../BPC-PC1T.txt", "../../../BPC-KOM.txt", "../../../BPC-PNA.txt", "\0" };
	char predmet_txt[6][50] = {
		"BPC-MAT1.txt",
		"BPC-ZKR.txt",
		"BPC-PC1T.txt",
		"BPC-KOM.txt",
		"BPC-PNA.txt",
		"\0"
	};



	printf("\n=== ELEKTRONICKY INDEX ===\n");
	//printf("Zadajte prihlasovacie meno: ");
    //scanf_s("%s", us_name);


    if (overenie(us_name)) {
        //neuspesne prihlasenie
        return 0;
    }

    int vybr_predmet = vyber_predmetu(predmet);

    //printf("%s", predmet[vybr_predmet-1]);

    FILE* fptr;

    fptr = fopen(predmet_txt[vybr_predmet - 1], "r");
    char buff[50];
    int id = 1;

    char* student = NULL;
    char* cviceni = NULL;
    char* testy = NULL;
    char* skuska = NULL;
    char* stud_id_string = NULL;


    while (fgets(buff, 50, fptr)) {

        buff[strcspn(buff, "\n")] = 0;

        student = strtok(buff, ":");
        cviceni = strtok(NULL, ":");
        testy = strtok(NULL, ":");
        skuska = strtok(NULL, ":");

        printf("%d)Student: %s, Cvicenia: %s, Testy: %s, Skuska: %s\n", id, student, cviceni, testy, skuska);

        id++;
    }

    printf("\n");


    int cviceni_int = 0;
    int testy_int = 0;
    int skuska_int = 0;
    int stud_id_int = 0;
    int student_id = 0;


    printf("Vyberte studenta, ktoremu chcete zapisat body: ");
    scanf("%d", &student_id);

    //znova citanie suboru od zaciatku
    rewind(fptr);
    id = 1;

    while (fgets(buff, 50, fptr)) {

        buff[strcspn(buff, "\n")] = 0;

        student = strtok(buff, ":");
        cviceni = strtok(NULL, ":");
        testy = strtok(NULL, ":");
        skuska = strtok(NULL, ":");
        stud_id_string = strtok(NULL, ":");
        //premenna na int
        stud_id_int = atoi(stud_id_string);
        cviceni_int = atoi(cviceni);
        testy_int = atoi(testy);
        skuska_int = atoi(skuska);

        //printf("mali by byt integers:::%d)Student: %s Cvicenia: %d, Testy: %d, Skuska: %d\n",id ,student, cviceni_int, testy_int, skuska_int);


        if (student_id == stud_id_int) {

            printf("Vybrali ste: %d)Student: %s\n", stud_id_int, student);
            break;
        }

        id++;
    }

    //printf("\n--mali by byt integers:::%d)Student: %s Cvicenia: %d, Testy: %d, Skuska: %d\n--",id ,student, cviceni_int, testy_int, skuska_int);

    printf("\nrychly debug--%d--\n", stud_id_int);


    int body_volba = 0;
    printf("Chcete pridat body za: \n1.cvicenie \n2.test \n3.skusku\n? ");
    scanf("%d", &body_volba);
    printf("\n");

    int pocet_bodov = 0;

    printf("Kolko bodov chcete pripisat?: ");
    scanf("%d", &pocet_bodov);

    switch (body_volba) {

    case 1:
        cviceni_int += pocet_bodov;
        break;

    case 2:
        testy_int = testy_int + pocet_bodov;
        break;

    case 3:
        skuska_int += pocet_bodov;
        break;

    }

    printf("\nnove hodnoty len docasne:::%d)Student: %s  Cvicenia: %d, Testy: %d, Skuska: %d\n", stud_id_int, student, cviceni_int, testy_int, skuska_int);
    printf("naozaj chcete uskutocnit zmeny?");
    fclose(fptr);


    return 0;


	//main kod marek

	/*Databaza db;
	db.pocetUcit = 0;

	if (load_db(&db, DB_FILENAME)) {
		printf("\n=== ELEKTRONICKY INDEX ===\n");
		printf("Zadajte prihlasovacie meno: ");
		char meno[MAX_MENO];
		scanf(" %[^\n]s", meno);

		int idt = najdi_ucitela(&db, meno); // ulozime id ucitela ktory sa prihlasil do premennej ID Teacher (idt)
		if (idt == -1) {
			printf("Ucitel '%s' neexistuje. Pre vytvorenie uctu kontaktujte administratora.", meno);
			/*int a; scanf("%d", &a);
			if (a == 1) {
				strcpy(db.ucitelia[db.pocetUcit].meno_ucitela, meno); // predvyplnit meno
				int newIdx = vytvorenie_uzivatela(&db);
				if (newIdx >= 0) {
					uloz_databazu(&db, DB_FILENAME);
					UI_vyber_predmet_a_pracuj(&db.ucitelia[newIdx]);
				}
			} else {
				printf("Spat do prihlasenia.\n");
			}*/
		/*/} else {
			printf("%s úspešne prihlásený!\n", db.ucitelia[idt].meno_ucitela);
			UI_vyber_predmet_a_pracuj(&db.ucitelia[idt]);
			save_db(&db, DB_FILENAME); // po ukonceni prace ucitela sa ulozi db
		}

	} else {
		printf("Nepodarilo sa nacitat databazu. Program nebude spusteny.\n");
	}

	return 0;*/
}
/*
void InicializujUcitel(Databaza *db) {
	printf("Zadajte svoje meno: ");
	scanf(" %[^\n]s", db->ucitel);
	printf("Kolko predmetov budete spravovat? ");
	scanf("%d", &db->pocetPredmetov);

	for(int i=0;i<db->pocetPredmetov;i++){
		printf("Nazov predmetu %d: ", i+1);
		scanf(" %[^\n]s", db->predmety[i].nazov);
	}

	db->pocetStudentov = 0;
}
*/

int overenie(char usnm[50])
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

			char buff[50];
			int status_meno = 1;

			// Reading strings till fgets returns NULL
			while (fgets(buff, 50, fptr)) {
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

int vyber_predmetu(char predmet[5][50]) {

	int volba_predm = 0;

	while (1) {
		printf("Zadajte cislo predmetu, do ktoreho chcete zadavat body: \n");
		for (int i = 0; i < 5; i++) {
			printf("%d) %s\n", i + 1, predmet[i]);
		}

		scanf_s("%d", &volba_predm);

		if (volba_predm <= 0 || volba_predm > 5) {
			printf("Nespravna volba! Skuste znova.\n\n");
		}
		else {
			printf("Vybrany predmet: %s.\n", predmet[volba_predm - 1]);
			break; // ukonci while(1)
		}
	}

	return volba_predm;
}