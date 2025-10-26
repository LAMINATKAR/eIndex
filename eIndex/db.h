#ifndef DB_H // tzv. include guard (ochrana proti viacerému zahrnutiu súboru)
#define DB_H

#include <stdio.h>

#define MAX_MENO 50
#define MAX_PREDMET 50
#define MAX_STUDENTOV 200 // V C/C++ nemôžeme jednoducho deklarovať pole s dynamickou veľkosťou v štruktúre (ak nepoužívame dynamickú alokáciu, malloc).
#define MAX_PREDMETOV 20 // Preto často preddefinujeme maximálne možné veľkost
#define MAX_UCITELOV 20

typedef struct {
    int cvicenia;   // body za cvicenia (0-100)
    int testy;      // body za testy (0-100)
    int skuska;     // body za zaverecnu skuskku (0-100)
    char vysledna;  // A-F alebo '-'
} Znamka;

typedef struct {
    char meno[MAX_MENO];
    char priezvisko[MAX_MENO];
    Znamka znamky[MAX_PREDMETOV]; // indeksované podľa poradia predmetov učiteľa
} Student;

typedef struct {
    char nazov[MAX_PREDMET];
} Predmet;

typedef struct {
    char meno_ucitela[MAX_MENO];
    Predmet predmety[MAX_PREDMETOV];
    int pocetPredmetov;
    Student studenti[MAX_STUDENTOV];
    int pocetStudentov;
} Ucitel;

typedef struct {
    Ucitel ucitelia[MAX_UCITELOV];
    int pocetUcit;
} Databaza;

/* DATABAZA */
int load_db(Databaza *db, const char *filename);
int save_db(Databaza *db, const char *filename);

/* UCITEL */
int najdi_ucitela(Databaza *db, const char *meno); // vracia index alebo -1
//int vytvorenie_uzivatela(Databaza *db); // vytvori noveho ucitela, vrati index
void UI_vyber_predmet_a_pracuj(Ucitel *u); // zobrazi predmety, necha vybrat a prejde do spravy znamok

#endif