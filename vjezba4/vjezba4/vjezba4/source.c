#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include <stdlib.h>
#include<malloc.h>
#include<string.h>

#define MAX_LINE (1024)
#define MAX_SIZE (50)
#define FILE_NOT_FOUND (-1)
#define FAILED_MEMORY_ALLOCATION (NULL)
#define EMPTY_LISTS (-2)

struct _Element;
typedef struct _Element* Position;
typedef struct _Element
{
	int coefficient;
	int exponent;
	Position next;
} Element;

int readPolynomialsFromFile(Position head1, Position head2, char* file);
int printPolynomial(char* polynomialName, Position first);
int addPolynomial(Position resultHead, Position head1, Position head2);
int multiplyPolynomial(Position resultHead, Position head1, Position head2);
int freeMemory(Position head);
int parseStringIntoList(Position head, char* buffer);
Position createElement(int coefficient, int exponent);
int insertSorted(Position head, Position newElement);
int mergeAfter(Position current, Position newElement);
int insertAfter(Position current, Position newElement);
int deleteAfter(Position previous);
int createAndInsertAfter(int coefficient, int exponent, Position current);
int sortPolynomial(Position head);

int main()
{
	Element head1 = { .coefficient = 0, .exponent = 0, .next = NULL };
	Element head2 = { .coefficient = 0, .exponent = 0, .next = NULL };
	Element headAdd = { .coefficient = 0, .exponent = 0, .next = NULL };
	Element headMultiply = { .coefficient = 0, .exponent = 0, .next = NULL };
	char* file = "polynomials.txt";

	if(readPolynomialsFromFile(&head1, &head2, file) == EXIT_SUCCESS)
	{
		printPolynomial("First polynomial: ", head1.next);
		printPolynomial("Second polynomial: ", head2.next);

		addPolynomial(&headAdd, head1.next, head2.next);
		printPolynomial("Added polynomials: ", headAdd.next);
		//printf("%d\n", headAdd.next->exponent);
		sortPolynomial(headAdd.next);
		printPolynomial("Sorted added polynomials: ", headAdd.next);
		multiplyPolynomial(&headMultiply, head1.next, head2.next);

		printPolynomial("Multiplied polynomials: ", headMultiply.next);

		freeMemory(&head1);
		freeMemory(&head2);
		freeMemory(&headAdd);
		freeMemory(&headMultiply);
	}
	return 0;
}

int readPolynomialsFromFile(Position head1, Position head2, char* file)
{
	FILE* filePointer = NULL;
	char buffer[MAX_LINE] = { 0 };
	int status = EXIT_SUCCESS;

	filePointer = fopen("polynomials.txt", "r");
	if(!filePointer)
	{
		printf("File not found!\n");
		return FILE_NOT_FOUND;
	}

	fgets(buffer, MAX_LINE, filePointer);
	status = parseStringIntoList(head1, buffer);
	if(status != EXIT_SUCCESS)
	{
		return EXIT_FAILURE;
	}

	fgets(buffer, MAX_LINE, filePointer);
	status = parseStringIntoList(head2, buffer);
	if(status != EXIT_SUCCESS)
	{
		return EXIT_FAILURE;
	}

	fclose(filePointer);

	return EXIT_SUCCESS;
}

int printPolynomial(char* polynomialName, Position first)
{
	printf(" %s = ", polynomialName);
	if(first)
	{
		if(first->exponent < 0)
		{
			if(first->coefficient == 1)
			{
				printf("x^(%d)", first->exponent);
			}
			else
			{
				printf("%dx^(%d)", first->coefficient, first->exponent);
			}
		}
		else
		{
			if(first->coefficient == 1)
			{
				printf("x^%d", first->exponent);
			}
			else
			{
				printf("%dx^%d", first->coefficient, first->exponent);
			}
		}

		first = first->next;
	}

	while(first!=NULL)
	{
		if(first->coefficient < 0)
		{
			if(first->exponent < 0)
			{
				printf(" - %dx^(%d)", abs(first->coefficient), first->exponent);
			}
			else
			{
				printf(" - %dx^%d", abs(first->coefficient), first->exponent);
			}
		}
		else
		{
			if(first->exponent < 0)
			{
				if(first->coefficient == 1)
				{
					printf(" + x^(%d)", first->exponent);
				}
				else
				{
					printf(" + %dx^(%d)", first->coefficient, first->exponent);
				}
			}
			else
			{
				if(first->coefficient == 1)
				{
					printf(" + x^%d", first->exponent);
				}
				else
				{
					printf(" + %dx^%d", first->coefficient, first->exponent);
				}
			}
		}
		first = first->next;
	}

	printf("\n");
	return EXIT_SUCCESS;
}

int addPolynomial(Position resultHead, Position head1, Position head2)
{
	Position currentPoly1 = head1;
	Position currentPoly2 = head2;
	Position currentResult = resultHead;
	Position remainingPoly = NULL;

	while(currentPoly1 != NULL && currentPoly2 != NULL)
	{
		if(currentPoly1->exponent == currentPoly2->exponent)
		{
			createAndInsertAfter(currentPoly1->coefficient + currentPoly2->coefficient, currentPoly1->exponent, currentResult);
			currentPoly1 = currentPoly1->next;
			currentPoly2 = currentPoly2->next;
			currentResult = currentResult->next;
		}
		else if(currentPoly1->exponent < currentPoly2->exponent)
		{
			createAndInsertAfter(currentPoly1->coefficient, currentPoly1->exponent, currentResult);
			currentPoly1 = currentPoly1->next;
			currentResult = currentResult->next;
		}
		else
		{
			createAndInsertAfter(currentPoly2->coefficient, currentPoly2->exponent, currentResult);
			currentPoly2 = currentPoly2->next;
			currentResult = currentResult->next;
		}

	}
	if(currentPoly1 == NULL)
	{
		remainingPoly = currentPoly2;
	}
	else
	{
		remainingPoly = currentPoly1;
	}

	while(remainingPoly != NULL)
	{
		createAndInsertAfter(remainingPoly->coefficient, remainingPoly->exponent, currentResult);
		remainingPoly = remainingPoly->next;
		currentResult = currentResult->next;
	}
	
	return EXIT_SUCCESS;
}

int multiplyPolynomial(Position resultHead, Position head1, Position head2)
{
	if(head1 != NULL || head2 != NULL)
	{
		for(Position currentPoly1 = head1; currentPoly1 != NULL; currentPoly1 = currentPoly1->next)
		{
			for(Position currentPoly2 = head2; currentPoly2 != NULL; currentPoly2 = currentPoly2->next)
			{
				Position newElement = createElement(currentPoly1->coefficient * currentPoly2->coefficient, currentPoly1->exponent + currentPoly2->exponent);
				if(!newElement)
				{
					return EXIT_FAILURE;
				}

				insertSorted(resultHead, newElement);
			}
		}
		return EXIT_SUCCESS;
	}
	return EMPTY_LISTS;
}

int freeMemory(Position head)
{
	Position current = head;

	while(current->next)
	{
		deleteAfter(current);
	}

	return EXIT_SUCCESS;
}

int parseStringIntoList(Position head, char* buffer)
{
	char* currentBuffer = buffer;
	int coefficient = 0;
	int exponent = 0;
	int numBytes = 0;
	int status = 0;
	Position newElement = NULL;

	while(strlen(currentBuffer) > 0)
	{
		status = sscanf(currentBuffer, " %dx^%d %n", &coefficient, &exponent, &numBytes);
		if(status != 2)
		{
			printf("This file is not good!\n");
			return EXIT_FAILURE;
		}

		newElement = createElement(coefficient, exponent);
		if(!newElement)
		{
			return EXIT_FAILURE;
		}

		insertSorted(head, newElement);

		currentBuffer += numBytes;
	}

	return EXIT_SUCCESS;
}

Position createElement(int coefficient, int exponent)
{
	Position element = NULL;

	element = (Position)malloc(sizeof(Element));
	if(!element)
	{
		printf("Can't allocate memory!\n");
		return FAILED_MEMORY_ALLOCATION;
	}

	element->coefficient = coefficient;
	element->exponent = exponent;
	element->next = NULL;

	return element;
}

int insertSorted(Position head, Position newElement)
{
	Position current = head;

	while(current->next != NULL && current->next->exponent > newElement->exponent)
	{
		current = current->next;
	}

	mergeAfter(current, newElement);

	return EXIT_SUCCESS;
}

int mergeAfter(Position current, Position newElement)
{
	if(current->next == NULL || current->next->exponent != newElement->exponent)
	{
		insertAfter(current, newElement);
	}
	else
	{
		int resultCoefficient = current->next->coefficient + newElement->coefficient;
		if(resultCoefficient == 0)
		{
			deleteAfter(current);
		}
		else
		{
			current->next->coefficient = resultCoefficient;
		}
		free(newElement);
	}

	return EXIT_SUCCESS;
}

int insertAfter(Position current, Position newElement)
{
	newElement->next = current->next;
	current->next = newElement;

	return EXIT_SUCCESS;
}

int deleteAfter(Position previous)
{
	Position toDelete = NULL;

	toDelete = previous->next;
	previous->next = toDelete->next;
	free(toDelete);

	return EXIT_SUCCESS;
}

int createAndInsertAfter(int coefficient, int exponent, Position current)
{
	Position newElement = createElement(coefficient, exponent);
	if(!newElement)
	{
		return EXIT_FAILURE;
	}

	insertAfter(current, newElement);

	return EXIT_SUCCESS;
}

int sortPolynomial(Position first)
{
	Position temp;
	Position second = first->next;
	for(first; first->next != NULL; first = first->next)
	{
		for(second; second->next!=NULL; second=second->next)
		{
			if (first->exponent < second->exponent)
			{
				temp = first;
				first = second;
				second = temp;
			}
		}
	}

	return EXIT_SUCCESS;
}