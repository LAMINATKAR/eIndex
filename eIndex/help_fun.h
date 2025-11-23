#pragma once

void vycistenie();
unsigned long simple_hash(const char *str);
void fill_strukt(struct student* studenti, int predm_cislo, int* count_stud, int max_body[POCET_PREDMET]);
void zapis_subor(struct student* studenti, int pct_stud, char* predmet, int max_body);
void update_subor();