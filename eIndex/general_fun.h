#pragma once

#include <iostream>

const int POCET_PREDMET = 6;
const int DLZKA_STRING = 50;
const int POCET_STUDENT = 50;

struct student {

	char* student;
	char* cviceni;
	char* testy;
	char* skuska;
	char* stud_id_string;


	char student_str[50];
	char cviceni_str[50];
	char testy_str[50];
	char skuska_str[50];
	char stud_id_str[50];

	int cviceni_int;
	int testy_int;
	int skuska_int;
	int studID_int;
	int vybrany_student;
};



void vycistenie();
int overenie(char usnm[DLZKA_STRING]);
int vyber_predmetu(char predmet[POCET_PREDMET][DLZKA_STRING]);
void zapis_znamok(char predmet[POCET_PREDMET][DLZKA_STRING], char predmet_txt[POCET_PREDMET][DLZKA_STRING], int vybr_predmet, struct student* studenti, int pct_stud);
int zobraz_vysledky(char predmety[POCET_PREDMET][DLZKA_STRING], char predmety_txt[POCET_PREDMET][DLZKA_STRING], int vybr_predmet, struct student* studenti, int pct_stud);
void edit_predmetu();
void fill_strukt(struct student* studenti, int predm_cislo, int* count_stud);