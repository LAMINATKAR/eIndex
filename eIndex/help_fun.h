#pragma once

void vycistenie();
unsigned long simple_hash(const char *str);
void fill_strukt(struct student* studenti, int predm_cislo, int* count_stud);
void zapis_subor(struct student* studenti, int pct_stud, char* predmet);
void update_subor();