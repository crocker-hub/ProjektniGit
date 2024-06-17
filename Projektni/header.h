#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

void dodajClana(int brojClanova, int maksClanova, struct clan* clanovi, FILE* file);
void obrisiClana(int brojClanova, int redniBroj, FILE* file, struct clan* clanovi);
void sortirajClanove(struct clan* clanovi, int brojClanova);
void produziClanarinu(int redniBroj, int brojClanova, struct clan* clanovi, int produzivanje, FILE* file, int maksClanova);
void pokaziClanove(int brojClanova, struct clan* clanovi);
void prikazClanarina(FILE* file, struct clan* clanovi, int maksClanova, int brojClanova);
