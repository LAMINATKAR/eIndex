#pragma once

#include <iostream>

const int POCET_PREDMET = 6;
const int DLZKA_STRING = 50;
const int POCET_STUDENT = 150;

// Mimimalne percenta na danu znamku
const int ZN_A = 90;
const int ZN_B = 80;
const int ZN_C = 70;
const int ZN_D = 60;
const int ZN_E = 50;

struct student {

	char* student;
	char* cviceni;
	char* testy;
	char* skuska;
	char* stud_id_string;

	char student_str[DLZKA_STRING];
	char cviceni_str[DLZKA_STRING];
	char testy_str[DLZKA_STRING];
	char skuska_str[DLZKA_STRING];
	char stud_id_str[DLZKA_STRING];

	int cviceni_int;
	int testy_int;
	int skuska_int;
	int studID_int;
	int vybrany_student;
};

void vycistenie();
int overenie();
unsigned long simple_hash(const char *str);
int vyber_predmetu(char predmet[POCET_PREDMET][DLZKA_STRING]);
void zapis_znamok(char predmet[POCET_PREDMET][DLZKA_STRING], char predmet_txt[POCET_PREDMET][DLZKA_STRING], int vybr_predmet, struct student* studenti, int pct_stud);
int zobraz_vysledky(char predmety[POCET_PREDMET][DLZKA_STRING], char predmety_txt[POCET_PREDMET][DLZKA_STRING], int vybr_predmet, struct student* studenti, int pct_stud);
void edit_predmetu();
void fill_strukt(struct student* studenti, int predm_cislo, int* count_stud);
void zapis_subor(struct student* studenti, int pct_stud, char* predmet);
void update_subor();