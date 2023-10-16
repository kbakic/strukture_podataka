/*
2. Definirati strukturu osoba (ime, prezime, godina ro?enja) i napisati program koji:
A.dinami?ki dodaje novi element na po?etak liste,
B.ispisuje listu,
C.dinami?ki dodaje novi element na kraj liste,
D.pronalazi element u listi(po prezimenu),
E.briše odre?eni element iz liste,
U zadatku se ne smiju koristiti globalne varijable.*/

#define _CRT_SECURE_NO_WARNINGS
#define MAX_SIZE 50
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
typedef struct _person*Position;
typedef struct _person
{
	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	int birthyear;
	Position next;
} Person;
int main()
{


	return 0;
}