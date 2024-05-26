#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

struct clan {
	char ime[30];
	int dob;       //u godinama
	int clanarina; //u mjesecima
};

void dodajClana(int brojClanova, int maksClanova, struct clan* clanovi, FILE* file) {
	if (brojClanova > maksClanova) {
		printf("Dostigli ste maksimalni broj clanova");
		return 0;
	}
	else {
		struct clan noviClan;
		printf("---DODAVANJE CLANOVA---\n");
		printf("Unesi ime clana:");
		scanf("%s", noviClan.ime);
		printf("Unesi dob clana(godine)");
		scanf("%d", &noviClan.dob);
		printf("Unesi clanarinu clana(mjeseci)\n");
		scanf("%d", &noviClan.clanarina);

		clanovi[brojClanova] = noviClan;
		brojClanova++;

		printf("Clan uspjesno dodan!\n");

		file = fopen("clanovi.bin", "ab");
		if (file == NULL) {
			printf("Nije moguce otvoriti datoteku za pisanje.\n");
			return 1;
		}
		fwrite(&noviClan, sizeof(struct clan), 1, file);
		fclose(file);
	}
}
void obrisiClana(int brojClanova, int redniBroj, FILE* file, struct clan* clanovi) {

	if (redniBroj > brojClanova) {
		printf("Taj clan ne postoji!\n");
		return -1;
	}


	redniBroj--;

	file = fopen("clanovi.bin", "rb+");
	if (file == NULL) {
		printf("Nije moguce otvoriti datoteku za citanje i pisanje.\n");
		return 1;
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
		printf("Nije moguce otvoriti datoteku za pisanje.\n");
		return 1;
	}
	fwrite(clanovi, sizeof(struct clan), brojClanova, file);
	fclose(file);

	printf("Clan uspjesno izbrisan!\n");
}

void sortirajClanove(struct clan* clanovi, int brojClanova) {
	struct clan temp;
	for (int i = 0; i < brojClanova - 1; i++) {
		for (int j = i + 1; j < brojClanova; j++) {
			if (clanovi[i].clanarina < clanovi[j].clanarina) {
				temp = clanovi[i];
				clanovi[i] = clanovi[j];
				clanovi[j] = temp;
			}
		}
	}
}

void produziClanarinu(int redniBroj, int brojClanova, struct clan* clanovi, int produzivanje, FILE* file) {
	printf("---PRODUZIVANJE CLANARINE---\n");
	printf("Upisi broj clana kojem zelis produziti clanarinu: ");
	scanf("%d", &redniBroj);
	if (redniBroj < 1 || redniBroj > brojClanova || clanovi[redniBroj - 1].ime[0] == '\0') {
		printf("Neispravan broj clana.\n");
		return 1;
	}
	printf("Za koliko mjeseci zelis clanu %d produziti clanarinu: ", redniBroj);
	scanf("%d", &produzivanje);
	clanovi[redniBroj - 1].clanarina += produzivanje;
	printf("Clanarina clana %d produzena za %d mjeseci!\n", redniBroj, produzivanje);
	file = fopen("clanovi.bin", "rb+");
	if (file == NULL) {
		printf("Nije moguce otvoriti datoteku za pisanje.\n");
		return 1;
	}
	fseek(file, (redniBroj - 1) * sizeof(struct clan), SEEK_SET);
	fwrite(&clanovi[redniBroj - 1], sizeof(struct clan), 1, file);
	fclose(file);
}

void pokaziClanove(int brojClanova, struct clan* clanovi) {
	int i;
	printf("---PRIKAZ CLANOVA IZ FILEA---\n");
	for (i = 0; i < brojClanova; i++) {
		if (clanovi[i].ime[0] != '\0') {
			printf("          ------------------------------\n");
			printf("          |Broj clana: %d\n", i + 1);
			printf("          |Ime: %s\n", clanovi[i].ime);
			if (clanovi[i].dob != 0) {
				printf("          |Dob clana(godine): %d\n", clanovi[i].dob);
			}
			if (clanovi[i].clanarina != 0) {
				printf("          |Clanarina(mjeseci): %d\n", clanovi[i].clanarina);
			}
			printf("          ------------------------------\n");
		}
	}
}

void prikazClanarina(FILE* file, struct clan* clanovi, int maksClanova, int brojClanova) {
	int i;
	printf("---CLANOVI PO CLANARINI---\n");
	file = fopen("clanovi.bin", "rb");
	if (file == NULL) {
		printf("Nije moguce otvoriti datoteku za citanje.\n");
		return 1;
	}
	brojClanova = fread(clanovi, sizeof(struct clan), maksClanova, file);
	fclose(file);

	if (brojClanova == 0) {
		printf("Nema clanova\n");
		return 1;
	}

	sortirajClanove(clanovi, brojClanova);

	printf("---PRIKAZ SORTIRANIH CLANOVA---\n");
	for (i = 0; i < brojClanova; i++) {
		if (clanovi[i].ime[0] != '\0') {
			printf("----------\n");
			printf("Broj clana: %d\n", i + 1);
			printf("Ime: %s\n", clanovi[i].ime);
			if (clanovi[i].dob != 0) {
				printf("Dob clana(godine): %d \n", clanovi[i].dob);
			}
			if (clanovi[i].clanarina != 0) {
				printf("Clanarina(mjeseci): %d \n", clanovi[i].clanarina);
			}
		}
	}
}