// eIndex.cpp : Defines the entry point for the application.
//

#include "eIndex.h"
#include <stdio.h>
#include <string.h>
#include "db.h"

#define DB_FILENAME "db.bin"

using namespace std;

int main()
{
	Databaza db;
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
		} else {
			printf("%s úspešne prihlásený!\n", db.ucitelia[idt].meno_ucitela);
			UI_vyber_predmet_a_pracuj(&db.ucitelia[idt]);
			save_db(&db, DB_FILENAME); // po ukonceni prace ucitela sa ulozi db
		}

	} else {
		printf("Nepodarilo sa nacitat databazu. Program nebude spusteny.\n");
	}

	return 0;
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
*//*
void SelectSubject() {
	printf("Vyber predmed (zadaj ID): ");
	//scanf("%d", &predmet);

	printf("Zoznam predmetov: ");

}
*//*
void ListIndex() {
	printf("MENO PRIEZVISKO ZNAMKY\n");

}

void Marking() {
	printf("Rezim pridavania znamok");
}
*/