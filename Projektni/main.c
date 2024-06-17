#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "header.h"

typedef struct clan {
	char ime[30];
	int dob;       //u godinama
	int clanarina; //u mjesecima
};

int main(void) {
	int izbor;
	int brojClanova = 0;
	static int maksClanova = 100;
	struct clan* clanovi = NULL;
	clanovi = (struct clan*)malloc(maksClanova * sizeof(struct clan));
	if (clanovi == NULL) {
		printf("Neuspjela alokacija memorije.\n");
		return 1;
	}
	int produzivanje = 0, redniBroj = 0;
	FILE* file;
	file = fopen("clanovi.bin", "ab");
	if (file == NULL) {
		printf("file se ne moze otvoriti. Error: %s\n", strerror(errno));
		return 1;
	}

	do {
		system("cls");
		printf("                      |-------------------Gym Manager---------------------|\n");
		printf("                      |                 1.Dodaj clana                     |\n");
		printf("                      |                 2.Makni clana                     |\n");
		printf("                      |               3.Prikazi clanove                   |\n");
		printf("                      |              4.Produzi clanarinu                  |\n");
		printf("                      |     5.Prikazi clanove s obzirom na clanarinu      |\n");
		printf("                      |---------------------------------------------------|\n");
		
		while (1) {
			if (scanf("%d", &izbor) != 1) {
				printf("Neispravan unos. Probaj unjeti broj.\n");
				while (getchar() != '\n'); 
			}
			else {
				break;
			}
		}

		


		switch (izbor) {


		case 1:
			dodajClana(brojClanova, maksClanova, clanovi, file);
			break;

		case 2:
			file = fopen("clanovi.bin", "rb");
			if (file == NULL) {
				printf("Nije moguce otvoriti datoteku za citanje. Error: %s\n", strerror(errno));
				return 1;
			}
			brojClanova = fread(clanovi, sizeof(struct clan), maksClanova, file);
			fclose(file);
			printf("---BRISANJE CLANOVA---\n");
			if (brojClanova <= 0) {
				printf("Nema clanova za maknuti!\n");
				break;
			}

			printf("Upisi redni broj clana kojeg zelis maknuti: \n");
			if (scanf("%d", &redniBroj) != 1) {
				printf("Probaj upisati broj clana.\n");
				
			}
			else {
				obrisiClana(brojClanova, redniBroj, file, clanovi);
			}
			
			break;

		case 3:
			file = fopen("clanovi.bin", "rb");
			if (file == NULL) {
				printf("Nije moguce otvoriti datoteku za citanje. Error: %s\n", strerror(errno));
				return 1;
			}
			brojClanova = fread(clanovi, sizeof(struct clan), maksClanova, file);
			fclose(file);

			if (brojClanova == 0) {
				printf("Nema clanova\n");
				break;
			}

			pokaziClanove(brojClanova, clanovi);
			break;

		case 4:
			produziClanarinu(redniBroj, brojClanova, clanovi, produzivanje, file, maksClanova);
			break;

		case 5:
			prikazClanarina(file, clanovi, maksClanova, brojClanova);
			break;



		default:
			printf("Nisi odabrao ni jednu od ponudenih opcija\n");
			break;
		}
		system("pause");

	} while (izbor != 1 || izbor != 2 || izbor != 3 || izbor != 4 || izbor != 5);

	free(clanovi);
	return 1;
}
