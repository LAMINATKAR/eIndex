// eIndex.cpp : Defines the entry point for the application.
//

#include "eIndex.h"
#include "general_fun.h"
#include <stdio.h>

using namespace std;

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

	while (1) {
		int editovanie = 1;
		int vybr_predmet = vyber_predmetu(predmet);
		while (editovanie) {
			zapis_znamok(predmet, predmet_txt, vybr_predmet);
			printf("\nChcete pokracovat v editacii? (1 = ano, 0 = spat do vyberu predmetu): ");
			scanf_s("%d", &editovanie);
			vycistenie();
		}
	}
}