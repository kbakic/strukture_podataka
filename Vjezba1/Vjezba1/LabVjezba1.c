#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE 1024
#define MAX_SIZE 1024
//
//1. Napisati program koji prvo pročita koliko redaka ima datoteka, tj. koliko ima studenata
//zapisanih u datoteci. Nakon toga potrebno je dinamički alocirati prostor za niz struktura
//studenata (ime, prezime, bodovi) i učitati iz datoteke sve zapise. Na ekran ispisati ime,
//prezime, apsolutni i relativni broj bodova.
//Napomena: Svaki redak datoteke sadrži ime i prezime studenta, te broj bodova na kolokviju.
//relatvan_br_bodova = br_bodova/max_br_bodova*100
typedef struct _student {
	char ime[MAX_SIZE];
	char prezime[MAX_SIZE];
	int bodovi;
} Student;

int readNoRowsInFile() {
	int counter = 0;
	FILE* filePtr = NULL;
	char buffer[MAX_LINE] = { 0 };
}

int main() {
	int rows = 0;


	return EXIT_SUCCESS;
}