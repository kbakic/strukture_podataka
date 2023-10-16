#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE 1024
#define MAX_SIZE 128
#define MAX_POINTS 15
#define FILE_NOT_OPEN -1

//ovo je zadatak bakicu
//1. Napisati program koji prvo pročita koliko redaka ima datoteka, tj. koliko ima studenata
//zapisanih u datoteci. Nakon toga potrebno je dinamički alocirati prostor za niz struktura
//studenata (ime, prezime, bodovi) i učitati iz datoteke sve zapise. Na ekran ispisati ime,
//prezime, apsolutni i relativni broj bodova.
//Napomena: Svaki redak datoteke sadrži ime i prezime studenta, te broj bodova na kolokviju.
//relatvan_br_bodova = br_bodova/max_br_bodova*100

//ovo je random struktura za pocetak bakicu
typedef struct _student {
	char ime[MAX_SIZE];
	char prezime[MAX_SIZE];
	double bodovi;
} Student;

//ovde imamo nesto sta ne znan sta je bakicu
int brojRedovaUdadoteci() {
	int brojac = 0;
	FILE* file_pointer = NULL;
	char buffer[MAX_SIZE] = { 0 };
	file_pointer = fopen("dat.txt", "r");
	if(!file_pointer)
	{
		printf("Neuspjesno otvaranje datoteke!\n");
		return FILE_NOT_OPEN;
	}
	while (!feof(file_pointer))
	{
		fgets(buffer, MAX_SIZE, file_pointer);
		brojac++;
	}
	fclose(file_pointer); //kad smo nesto otvorili, MORAMO to i zatvorit
	return brojac;
}

Student* alocirajMemorijuIprocitajStudente(int brojStudenata)
{
	int brojac = 0;
	FILE* filePointer = NULL;
	Student* studenti = NULL;
	studenti = (Student*)malloc(brojStudenata * sizeof(Student));
	if (!studenti)
	{
		printf("Neuspjesna alokacija memorije!\n");
		return NULL;
	}

	filePointer = fopen("dat.txt", "r");
	if (!filePointer)
	{
		printf("Neuspjesno otvaranje datoteke!\n");
		return FILE_NOT_OPEN;
	}
	while (!feof(filePointer))
	{
		fscanf(filePointer, "%s %s %lf", studenti[brojac].ime, studenti[brojac].prezime, &studenti[brojac].bodovi);
		brojac++;
	}
	fclose(filePointer);
	return studenti;
}

int ispis(int brojStudenata, Student* studenti)
{
	for (int i = 0; i < brojStudenata; i++)
	{
		printf("%s %s - %lf\n", studenti[i].ime, studenti[i].prezime, studenti[i].bodovi);
	}
	return 0;
}
//ovo je oceigledno main bakicu
int main() {
	int red = 0;
	Student* studenti = NULL;
	red = brojRedovaUdadoteci();
	if (red > 0)
	{
		studenti=alocirajMemorijuIprocitajStudente(red);
		ispis(red, studenti);
		free(studenti);
	}
	


	return EXIT_SUCCESS;
}