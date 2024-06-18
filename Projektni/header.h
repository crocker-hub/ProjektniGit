#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>


typedef struct clan {
	char ime[30];
	int dob;       //u godinama
	int clanarina; //u mjesecima
}Clan;

void dodajClana(int brojClanova, int maksClanova, struct clan* clanovi, FILE* file);
void obrisiClana(int brojClanova, int redniBroj, FILE* file, struct clan* clanovi);
void sortirajClanove(struct clan* clanovi, int brojClanova);
void produziClanarinu(int redniBroj, int brojClanova, struct clan* clanovi, int produzivanje, FILE* file, int maksClanova);
void pokaziClanove(int brojClanova, struct clan* clanovi);
void prikazClanarina(FILE* file, struct clan* clanovi, int maksClanova, int brojClanova);
int usporedi(const void* a, const void* b);

//#ifndef GLOBALS_H
//#define GLOBALS_H
//
//extern int brojClanova;
//extern int maksClanova;
//
//#endif
