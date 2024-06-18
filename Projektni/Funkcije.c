#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "header.h"




void dodajClana(int brojClanova, int maksClanova, struct clan* clanovi, FILE* file) {

	if (brojClanova >= maksClanova) {
		printf("Dostigli ste maksimalni broj clanova\n");
		return;
	}
	else {
		struct clan noviClan;
		printf("---DODAVANJE CLANOVA---\n");

		printf("Unesi ime clana: ");
		scanf("%29s", noviClan.ime);




		printf("Unesi dob clana (godine): ");
		if (scanf("%d", &noviClan.dob) != 1 || noviClan.dob >= 100 || noviClan.dob <= 0) {
			printf("Neispravan unos za dob clana.\n");
			int c;
			while ((c = getchar()) != '\n' && c != EOF);
			return;
		}

		printf("Unesi clanarinu clana (mjeseci): ");
		if (scanf("%d", &noviClan.clanarina) != 1 || noviClan.clanarina <= 0 || noviClan.clanarina >= 120) {
			printf("Neispravan unos za clanarinu clana.\n");
			int c;
			while ((c = getchar()) != '\n' && c != EOF);
			return;
		}

		clanovi[brojClanova] = noviClan;
		brojClanova++;

		printf("Clan uspjesno dodan!\n");

		file = fopen("clanovi.bin", "ab");
		if (file == NULL) {
			printf("Nije moguce otvoriti datoteku za pisanje. Error: %s\n", strerror(errno));
			return;
		}
		fwrite(&noviClan, sizeof(struct clan), 1, file);
		fclose(file);
	}
}
void obrisiClana(int brojClanova, int redniBroj, FILE* file, struct clan* clanovi) {

	if (redniBroj > brojClanova) {
		printf("Taj clan ne postoji!\n");
		return;
	}
	redniBroj--;

	file = fopen("clanovi.bin", "rb+");
	if (file == NULL) {
		printf("Nije moguce otvoriti datoteku za citanje i pisanje. Error: %s\n", strerror(errno));
		return;
	}

	fseek(file, redniBroj * sizeof(struct clan), SEEK_SET);

	struct clan prazanClan = { 0 };
	fwrite(&prazanClan, sizeof(struct clan), 1, file);

	fclose(file);

	for (int i = redniBroj + 1; i < brojClanova; i++) {
		clanovi[i - 1] = clanovi[i];
	}

	brojClanova--;

	file = fopen("clanovi.bin", "wb");
	if (file == NULL) {
		printf("Nije moguce otvoriti datoteku za pisanje. Error: %s\n", strerror(errno));
		return;
	}
	fwrite(clanovi, sizeof(struct clan), brojClanova, file);
	fclose(file);

	printf("Clan uspjesno izbrisan!\n");
}

void sortirajClanove(struct clan* clanovi, int brojClanova) {
	qsort(clanovi, brojClanova, sizeof(struct clan), usporedi);

}
int usporedi(const void* a, const void* b) {
	Clan* clanA = (Clan*)a;
	Clan* clanB = (Clan*)b;
	return clanB->clanarina - clanA->clanarina;
}


void produziClanarinu(int redniBroj, int brojClanova, struct clan* clanovi, int produzivanje, FILE* file, int maksClanova) {
	file = fopen("clanovi.bin", "rb");
	if (file == NULL) {
		printf("Nije moguce otvoriti datoteku za citanje. Error: %s\n", strerror(errno));
		return;
	}

	brojClanova = fread(clanovi, sizeof(struct clan), maksClanova, file);
	fclose(file);


	printf("---PRODUZIVANJE CLANARINE---\n");
	printf("Upisi broj clana kojem zelis produziti clanarinu: ");
	if (scanf("%d", &redniBroj) != 1) {
		printf("Probaj upisati broj clana.\n");
		return;
	}

	if (redniBroj < 1 || redniBroj > brojClanova || clanovi[redniBroj - 1].ime[0] == '\0') {
		printf("Neispravan broj clana.\n");
		return;
	}

	printf("Za koliko mjeseci zelis clanu %d produziti clanarinu: ", redniBroj);
	if (scanf("%d", &produzivanje) != 1 || produzivanje >= 120 || produzivanje <= 0) {
		printf("Neispravan unos za clanarinu clana. Molimo unesite broj.\n");
		int c;
		while ((c = getchar()) != '\n' && c != EOF);
		return;
	}


	clanovi[redniBroj - 1].clanarina += produzivanje;
	printf("Clanarina clana %d produzena za %d mjeseci!\n", redniBroj, produzivanje);
	file = fopen("clanovi.bin", "rb+");
	if (file == NULL) {
		printf("Nije moguce otvoriti datoteku za pisanje. Error: %s\n", strerror(errno));
		return;
	}


	fseek(file, (redniBroj - 1) * sizeof(struct clan), SEEK_SET);
	fwrite(&clanovi[redniBroj - 1], sizeof(struct clan), 1, file);
	fclose(file);
}

void pokaziClanove(int brojClanova, struct clan* clanovi) {
	int i;

	printf("                                 ---PRIKAZ CLANOVA IZ FILEA---\n");
	for (i = 0; i < brojClanova; i++) {
		if (clanovi[i].ime[0] != '\0') {
			printf("                         ------------------------------\n");
			printf("                         |Broj clana: %d\n", i + 1);
			printf("                         |Ime: %s\n", clanovi[i].ime);
			if (clanovi[i].dob != 0) {
				printf("                         |Dob clana(godine): %d\n", clanovi[i].dob);
			}
			if (clanovi[i].clanarina != 0) {
				printf("                         |Clanarina(mjeseci): %d\n", clanovi[i].clanarina);
			}
			printf("                         ------------------------------\n");
		}
	}
}

void prikazClanarina(FILE* file, struct clan* clanovi, int maksClanova, int brojClanova) {
	int i;
	printf("---CLANOVI PO CLANARINI---\n");
	file = fopen("clanovi.bin", "rb");
	if (file == NULL) {
		printf("Nije moguce otvoriti datoteku za citanje. Error: %s\n", strerror(errno));
		return;
	}

	brojClanova = fread(clanovi, sizeof(struct clan), maksClanova, file);
	fclose(file);

	if (brojClanova == 0) {
		printf("Nema clanova\n");
		return;
	}

	sortirajClanove(clanovi, brojClanova);

	printf("                    ---PRIKAZ SORTIRANIH CLANOVA---\n");
	for (int i = 0; i < brojClanova; i++) {
		printf("Ime: %s, Dob: %d, Clanarina: %d\n", clanovi[i].ime, clanovi[i].dob, clanovi[i].clanarina);
	}
}
