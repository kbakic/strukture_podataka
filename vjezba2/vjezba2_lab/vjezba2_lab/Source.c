/*
2. Definirati strukturu osoba (ime, prezime, godina ro?enja) i napisati program koji:
A.dinamicki dodaje novi element na početak liste,
B.ispisuje listu,
C.dinamicki dodaje novi element na kraj liste,
D.pronalazi element u listi(po prezimenu),
E.briše odredeni element iz liste,
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

int AddOnHead(Position pos, char name[MAX_SIZE], char surname[MAX_SIZE], int birthyear) {

	Position newMember;
	newMember = (Position)malloc(sizeof(Person));

	strcpy(newMember->name, name);
	strcpy(newMember->surname, surname);
	newMember->birthyear = birthyear;

	newMember->next = pos->next;
	pos->next = newMember;

	/*printf("Testing data entry... Person name and surname: %s %s, birthyear: %d\n",
		newMember->name, newMember->surname, newMember->birthyear);*/

	return 0;
}

int PrintingList(Position pos) {

	while (pos != NULL) {
		printf("Person name and surname: %s %s, birthyear: %d\n",
			pos->name, pos->surname, pos->birthyear);
		pos = pos->next;
	}

	return 0;
}

int main()
{
	Person headPerson;
	headPerson.next = NULL;

	AddOnHead(&headPerson, "Karlo", "Bakic", 2004);
	AddOnHead(&headPerson, "Luka", "Bosnic", 2003);

	PrintingList(headPerson.next);

	return 0;
}