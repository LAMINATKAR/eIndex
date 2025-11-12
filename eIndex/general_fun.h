#pragma once

#include <iostream>

const int POCET_PREDMET = 6;
const int DLZKA_STRING = 50;

void vycistenie();
int overenie(char usnm[DLZKA_STRING]);
int vyber_predmetu(char predmet[POCET_PREDMET][DLZKA_STRING]);
void zapis_znamok(char predmet[POCET_PREDMET][DLZKA_STRING], char predmet_txt[POCET_PREDMET][DLZKA_STRING], int vybr_predmet);
int zobraz_vysledky(char predmety[POCET_PREDMET][DLZKA_STRING], char predmety_txt[POCET_PREDMET][DLZKA_STRING], int vybr_predmet);
void edit_predmetu();