// eIndex.cpp : Defines the entry point for the application.
//

#include "eIndex.h"
#include "general_fun.h"
#include <stdio.h>

using namespace std;

int main()
{

	struct student stud_kom[POCET_STUDENT];

	struct student stud_ma1[POCET_STUDENT];

	struct student stud_pc1t[POCET_STUDENT];

	struct student stud_pna[POCET_STUDENT];

	struct student stud_zkr[POCET_STUDENT];

	int pct_stud_aktual[5];

	fill_strukt(stud_kom, 0, &pct_stud_aktual[0]);
	fill_strukt(stud_ma1, 1, &pct_stud_aktual[1]);
	fill_strukt(stud_pc1t, 2, &pct_stud_aktual[2]);
	fill_strukt(stud_pna, 3, &pct_stud_aktual[3]);
	fill_strukt(stud_zkr, 4, &pct_stud_aktual[4]);

	/*printf("\npocet student v 1: %d\n", pct_stud_aktual[0]);
	for (int ii = 0; ii < pct_stud_aktual[2] ; ii++) {
		printf("%s %d %d %d\n", stud_pc1t[ii].student_str, stud_pc1t[ii].cviceni_int, stud_pc1t[ii].testy_int, stud_pc1t[ii].skuska_int);
	}*/
	// len sem si skusal si funguje
	//printf("pocet studentov kom:%d", pct_stud); nic
	////


    char predmet[POCET_PREDMET][DLZKA_STRING] = {
	    "BPC-MA1",
    	"BPC-ZKR",
    	"BPC-PC1T",
    	"BPC-KOM",
    	"BPC-PNA",
    	"\0"
    };
	char predmet_txt[POCET_PREDMET][DLZKA_STRING] = {
		"BPC-MAT1.txt",
		"BPC-ZKR.txt",
		"BPC-PC1T.txt",
		"BPC-KOM.txt",
		"BPC-PNA.txt",
		"\0"
	};

	printf("\n=== ELEKTRONICKY INDEX ===\n");

    if (overenie()) {
        return 0; // neuspesne prihlasenie
    }

	while (1) {
		int editovanie = 1;
		int vybr_predmet = vyber_predmetu(predmet);
		int valid_case = 1;

		while (editovanie) {

			// na zaklade vybraneho predmetu sa posiela struct spravneho predmetu
			switch(vybr_predmet) {
				case 0:
					zapis_znamok(predmet, predmet_txt, vybr_predmet, stud_ma1, pct_stud_aktual[0]);
					break;
				case 1:
					zapis_znamok(predmet, predmet_txt, vybr_predmet, stud_zkr, pct_stud_aktual[1]);
					break;
				case 2:
					zapis_znamok(predmet, predmet_txt, vybr_predmet, stud_pc1t, pct_stud_aktual[2]);
					break;
				case 3:
					zapis_znamok(predmet, predmet_txt, vybr_predmet, stud_kom, pct_stud_aktual[3]);
					break;
				case 4:
					zapis_znamok(predmet, predmet_txt, vybr_predmet, stud_pna, pct_stud_aktual[4]);
					break;
				default:
					valid_case = 0;
					editovanie = 0;
					break;
			}

			if (valid_case) {
				printf("\nChcete pokracovat v editacii tohoto predmetu? (1 = ano, 0 = spat do vyberu predmetu): ");
				scanf_s("%d", &editovanie);
				vycistenie();
			} else {
				printf("\nStlacte Enter pre ukoncenie programu...");
				getchar(); // čaká na stlačenie Enter
				return 0;
			}
		}
	}
}