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


int AddOnHead(Position pos);
int AddOnEnd(Position pos);
Position FindBySurname(Position first);
int Delete(Position head, Position pos);
int AddAfter(Position head, Position pos);
int AddBefore(Position head, Position pos);
int PrintingList(Position pos);
int WriteListInFile(Position first);
int ReadListFromFile();
int SortList(Position first);
int SwapValues(Position first, Position second);
int Menu();

int main()
{
	Person headPerson = { {0}, {0}, 0, NULL };

	Menu();

	return 0;
}

int Menu() {

	Person head = { {0}, {0}, 0, NULL };

	char choice = '\0';

	while (1) {
		printf("Enter your option: H-(Add on Head), E-(Add on End), F-(Find by Surname), D-(Delete by Surname), A-(Add after Person), B-(Add before Person), P-(Print List), W-(Write list in File), R-(Read list from File), S-(Sort list by Surname), X-(Exit)");
		scanf(" %c", &choice);
		switch (toupper(choice)) {
		case 'H':
			AddOnHead(&head);
			continue;
		case 'E':
			AddOnEnd(&head);
			continue;
		case 'F':
			FindBySurname(head.next);
			continue;
		case 'D':
			Delete(&head, FindBySurname(head.next));
			continue;
		case 'A':
			AddAfter(&head, FindBySurname(head.next));
			continue;
		case 'B':
			AddBefore(&head, FindBySurname(head.next));
			continue;
		case 'P':
			PrintingList(head.next);
			continue;
		case 'W':
			WriteListInFile(head.next);
			continue;
		case 'R':
			ReadListFromFile();
			continue;
		case 'S':
			SortList(head.next);
			continue;
		case 'X':
			break;
		default:
			printf("Wrong letter.\n");
			continue;
		}
		break;
	}

	return 0;
}

int AddOnHead(Position pos) {

	Position newMember;
	newMember = (Position)malloc(sizeof(Person));

	char name[MAX_SIZE] = { 0 }, surname[MAX_SIZE] = {0};
	int birthyear = 0;

	printf("Enter Person's name\n");
	scanf(" %s", name);
	printf("Enter Person's surname\n");
	scanf(" %s", surname);
	printf("Enter Person's birthyear\n");
	scanf(" %d", &birthyear);

	strcpy(newMember->name, name);
	strcpy(newMember->surname, surname);
	newMember->birthyear = birthyear;

	newMember->next = pos->next;
	pos->next = newMember;

	/*printf("Testing data entry... Person name and surname: %s %s, birthyear: %d\n",
		newMember->name, newMember->surname, newMember->birthyear);*/

	return 0;
}

int AddOnEnd(Position pos) {

	Position newMember;
	newMember = (Position)malloc(sizeof(Person));

	char name[MAX_SIZE] = { 0 }, surname[MAX_SIZE] = { 0 };
	int birthyear = 0;

	printf("Enter Person's name\n");
	scanf(" %s", name);
	printf("Enter Person's surname\n");
	scanf(" %s", surname);
	printf("Enter Person's birthyear\n");
	scanf(" %d", &birthyear);

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

Position FindBySurname(Position first)
{

	char surname[MAX_SIZE] = { 0 };

	printf("Enter the Person's surname.\n");
	scanf(" %s",surname);

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

int AddAfter(Position head, Position pos) {

	Position newPerson = NULL;
	newPerson = (Position)malloc(sizeof(Person));
	if (!newPerson)
	{
		return -1;
	}

	char name[MAX_SIZE] = { 0 }, surname[MAX_SIZE] = { 0 };
	int birthyear = 0;

	printf("Enter Person's name\n");
	scanf(" %s", name);
	printf("Enter Person's surname\n");
	scanf(" %s", surname);
	printf("Enter Person's birthyear\n");
	scanf(" %d", &birthyear);

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

int AddBefore(Position head, Position pos) {

	Position newPerson = NULL;
	newPerson = (Position)malloc(sizeof(Person));
	if (!newPerson)
	{
		return -1;
	}

	char name[MAX_SIZE] = { 0 }, surname[MAX_SIZE] = { 0 };
	int birthyear = 0;

	printf("Enter Person's name\n");
	scanf(" %s", name);
	printf("Enter Person's surname\n");
	scanf(" %s", surname);
	printf("Enter Person's birthyear\n");
	scanf(" %d", &birthyear);

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

	FILE* f;
	f = fopen("persons.txt", "r");

	while (!feof(f)) {
		char name[MAX_SIZE], surname[MAX_SIZE];
		int birthyear;
		fscanf(f, "%s %s %d\n", name, surname, &birthyear);
		printf("%s %s %d\n", name, surname, birthyear);
	}

	printf("List read successfully.\n");
	fclose(f);

	return 0;
}

int SortList(Position first) {

	Position lastRead = NULL;
	Position start = first;

	int swapped = 0;

	if (!first) {
		printf("List empty.\n");
		return -2;
	}
	else if (!first->next) {
		printf("List has only 1 element.\n");
		return -1;
	}

	do {
		swapped = 0;
		Position pos = start;
		
		while (pos->next != lastRead) {
			if (strcmp(pos->surname,pos->next->surname) > 0) {

				SwapValues(pos, pos->next);
				swapped = 1;
			}
			pos = pos->next;
		}

		lastRead = pos;

	} while (swapped);

	printf("Sorted successfully.\n");

	return 0;
}

int SwapValues(Position first, Position second) {

	char tempName[MAX_SIZE], tempSurname[MAX_SIZE];
	int tempBirthyear;

	strcpy(tempName, first->name);
	strcpy(tempSurname, first->surname);
	tempBirthyear = first->birthyear;

	strcpy(first->name, second->name);
	strcpy(first->surname, second->surname);
	first->birthyear = second->birthyear;

	strcpy(second->name, tempName);
	strcpy(second->surname, tempSurname);
	second->birthyear = tempBirthyear;

	return 0;
}

int PrintingList(Position pos) {

	if (!pos) {
		printf("Empty list.");
	}

	while (pos) {
		printf("Person name and surname: %s %s, birthyear: %d\n",
			pos->name, pos->surname, pos->birthyear);
		pos = pos->next;
	}

	return 0;
}