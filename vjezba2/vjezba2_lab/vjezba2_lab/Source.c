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


int AddOnHead(Position pos, char name[MAX_SIZE], char surname[MAX_SIZE], int birthyear);
int AddOnEnd(Position pos, char name[MAX_SIZE], char surname[MAX_SIZE], int birthyear);
Position FindBySurname(Position first, char surname[MAX_SIZE]);
int Delete(Position head, Position pos);
int AddAfter(Position head, Position pos, char name[MAX_SIZE], char surname[MAX_SIZE], int birthyear);
int AddBefore(Position head, Position pos, char name[MAX_SIZE], char surname[MAX_SIZE], int birthyear);
int PrintingList(Position pos);
int WriteListInFile(Position first);

int main()
{
	Person headPerson = { {0}, {0}, 0, NULL };

	Position posOfWantedPerson;//in case we want addy of the wanted person saved

	AddOnHead(&headPerson, "Karlo", "Bakic", 2004);
	AddOnHead(&headPerson, "Luka", "Bosnic", 2003);
	AddOnEnd(&headPerson, "Laura", "Bauk", 2003);
	AddAfter(&headPerson, FindBySurname(headPerson.next, "Bauk"),"Mate","Bakovic", 2003);
	AddBefore(&headPerson, FindBySurname(headPerson.next, "Bakic"), "Vedran", "Delic", 2003);
	posOfWantedPerson = FindBySurname(headPerson.next, "Bakic");//harcoded input just for example
	Delete(&headPerson, posOfWantedPerson);//reuse the variable from finding for deleting
	WriteListInFile(headPerson.next);

	PrintingList(headPerson.next);

	return 0;
}

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

int AddOnEnd(Position pos, char name[MAX_SIZE], char surname[MAX_SIZE], int birthyear) {

	Position newMember;
	newMember = (Position)malloc(sizeof(Person));

	strcpy(newMember->name, name);
	strcpy(newMember->surname, surname);
	newMember->birthyear = birthyear;
	while (pos->next != NULL)
	{
		pos = pos->next;
	}

	pos->next = newMember;
	newMember->next = NULL;

	/*printf("Testing data entry... Person name and surname: %s %s, birthyear: %d\n",
		newMember->name, newMember->surname, newMember->birthyear);*/

	return 0;
}

Position FindBySurname(Position first, char surname[MAX_SIZE])
{
	while ( first != NULL && strcmp(first->surname, surname) != 0) {
		first = first->next;
	}
	if (first == NULL)
		printf("Person not found and returned NULL.\n");
	else
		printf("Person with surname %s found with name %s and returned.\n", first->surname, first->name);
	return first;
}

int Delete(Position head, Position pos) {

	if (pos == NULL) {
		printf("Invalid person input.\n");
		return -1;
	}

	while (head->next != NULL && head->next != pos) {
		head = head->next;
	}
	if (head->next = NULL) {
		printf("Person not found.\n");
		return -1;
	}
	else {
		head->next = pos->next;
		free(pos);
		printf("Person successfully found and deleted.\n");
	}

	return 0;
}

int AddAfter(Position head, Position pos, char name[MAX_SIZE], char surname[MAX_SIZE], int birthyear) {

	Position newPerson = NULL;
	newPerson = (Position)malloc(sizeof(Person));
	if (!newPerson)
	{
		return -1;
	}
	strcpy(newPerson->name, name);
	strcpy(newPerson->surname, surname);
	newPerson->birthyear = birthyear;
	
	while (head != NULL && head != pos) {
		head = head->next;
	}
	if (head == NULL) {
		printf("Person not found.\n");
		return -1;
	}
	else {
		newPerson->next = pos->next;
		pos->next = newPerson;
		printf("Added person %s %s, after person %s %s\n",
			newPerson->name, newPerson->surname, pos->name, pos->surname);
	}

	return 0;
}

int AddBefore(Position head, Position pos, char name[MAX_SIZE], char surname[MAX_SIZE], int birthyear) {

	Position newPerson = NULL;
	newPerson = (Position)malloc(sizeof(Person));
	if (!newPerson)
	{
		return -1;
	}
	strcpy(newPerson->name, name);
	strcpy(newPerson->surname, surname);
	newPerson->birthyear = birthyear;

	while (head != NULL && head->next != pos) {
		head = head->next;
	}
	if (head == NULL) {
		printf("Person not found.\n");
		return -1;
	}
	else {
		head->next = newPerson;
		newPerson->next = pos;
		printf("Added person %s %s, before person %s %s\n",
			newPerson->name, newPerson->surname, pos->name, pos->surname);
	}

	return 0;
}

int WriteListInFile(Position first) {

	FILE* f;
	f = fopen("persons.txt", "w");

	while (first != NULL) {
		fprintf(f, "%s %s %d\n", first->name, first->surname, first->birthyear);
		first = first->next;
	}

	fclose(f);
	printf("List written successfully.\n");

	return 0;
}

int ReadListFromFile() {

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