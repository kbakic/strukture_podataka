#define _CRT_SECURE_NO_WARNINGS
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 128

#define YES 9
#define NO 8
#define INVALID_LIST_COUNT -2
#define MEMORY_ALLOCATION_ERROR -1
#define NO_BOOKS_TRANSFERRED 1
#define BOOKS_TRANSFERRED 2
#define FILE_ERROR -3

typedef struct _book* BPosition;
typedef struct _book {
	char name[MAX_LINE], author[MAX_LINE];
	int releaseYear, availableCopies;
	BPosition next;
} Book;

typedef struct _user* UPosition;
typedef struct _user {
	char name[MAX_LINE];
	BPosition books[5];
	UPosition next;
} User;

int PrintBooksAlphabetically(BPosition head);
int PrintUsersAlphabetically(UPosition head);
int AddBook(BPosition head, char name[MAX_LINE], char author[MAX_LINE], int releaseYear, int availableCopies);
UPosition AddUser(UPosition head, char name[MAX_LINE]);
int PrintBooks(BPosition head);
int SwapBookValues(BPosition first, BPosition second);
int PrintUsers(UPosition head);
int SwapUserValues(UPosition first, UPosition second);
int SearchBooksByYear(BPosition head, int year);
int SearchBooksByAuthor(BPosition head, char author[MAX_LINE]);
int LendABook(UPosition user, BPosition book);
int ReturnABook(UPosition user);
int YesNoPrompt();
int SaveInventory(BPosition book, UPosition user);
int LoadInventory(BPosition book, UPosition user);

int main() {

	Book hBook = { .author = {0},.availableCopies = 0,.name = {0},.releaseYear = 0,.next = NULL };
	User hUser = { .name = {0},.books = NULL,.next = NULL };

	/*AddBook(&hBook, "Vlak u snijegu", "Mato Lovrak", 1930, 10);
	AddBook(&hBook, "Kiklop", "Ranko Marinkovic", 1965, 3);
	AddBook(&hBook, "Poezija", "Tin Ujevic", 1920, 1);
	AddBook(&hBook, "Mali princ", "Antoine de Saint-Exupery", 1943, 8);
	AddBook(&hBook, "Preobrazba", "Franz Kafka", 1915, 5);
	AddBook(&hBook, "Zlocin i kazna", "Fjodor Dostojevski", 1866, 12);*/

	LoadInventory(&hBook, &hUser);

	/*AddUser(&hUser, "Karlo Bakic");
	AddUser(&hUser, "Vedran Delic");
	AddUser(&hUser, "Luka Bosnic");
	AddUser(&hUser, "Mate Bakovic");
	AddUser(&hUser, "Ivona Delic");
	AddUser(&hUser, "Laura Bauk");*/

	while (1) {
		printf("Pick a choice: 1) Print Books alphabetically 2) Print Users alphabetically 3) Search Books by year 4) Search Books by author 5)	Create new User 6) Lend a Book 7) Return a Book 8) Save Inventory 9) Print Books 10) Print Users 0) Exit\n");
		int choice;
		scanf(" %d", &choice);

		if (choice == 1) {
			PrintBooksAlphabetically(&hBook);
		}
		else if (choice == 2) {
			PrintUsersAlphabetically(&hUser);
		}
		else if (choice == 3) {
			printf("Enter a release year of a Book you are searching for: \n");
			int year;
			scanf(" %d", &year);
			SearchBooksByYear(&hBook, year);
		}
		else if (choice == 4) {
			printf("Enter a author of a Book you are searching for: \n");
			char author[MAX_LINE];
			scanf(" %[^\n]s", author);
			SearchBooksByAuthor(&hBook, author);
		}
		else if (choice == 5) {
			printf("Enter new User's full name: \n");
			char name[MAX_LINE];
			scanf(" %[^\n]s", name);
			AddUser(&hUser, name);
		}
		else if (choice == 6) {
			LendABook(&hUser, &hBook);
		}
		else if (choice == 7) {
			ReturnABook(&hUser);
		}
		else if (choice == 8) {
			SaveInventory(&hBook, &hUser);
		}
		else if (choice == 9) {
			PrintBooks(&hBook);
		}
		else if (choice == 10) {
			PrintUsers(&hUser);
		}
		else if (choice == 0) {
			return EXIT_SUCCESS;
		}
	}

	return EXIT_SUCCESS;
}

int PrintBooksAlphabetically(BPosition head) {
	
	BPosition lastRead = NULL;
	BPosition start = head;

	int swapped = 0;

	if (!head) {
		printf("List empty.\n");
		return INVALID_LIST_COUNT;
	}
	else if (!head->next) {
		printf("List has only 1 element.\n");
		return INVALID_LIST_COUNT;
	}

	do {
		swapped = 0;
		BPosition pos = start;

		while (pos->next != lastRead) {
			if (strcmp(pos->name, pos->next->name) > 0) {

				SwapBookValues(pos, pos->next);
				swapped = 1;
			}
			pos = pos->next;
		}

		lastRead = pos;

	} while (swapped);

	PrintBooks(head);
	
	return EXIT_SUCCESS;
}

int AddBook(BPosition head, char name[MAX_LINE], char author[MAX_LINE], int releaseYear, int availableCopies) {
	BPosition newBook = NULL;
	newBook = (BPosition)malloc(sizeof(Book));

	if (newBook == NULL) {
		printf("Can't allocate memory\n");
		return MEMORY_ALLOCATION_ERROR;
	}

	strcpy(newBook->name, name);
	strcpy(newBook->author, author);
	newBook->releaseYear = releaseYear;
	newBook->availableCopies = availableCopies;

	newBook->next = head->next;
	head->next = newBook;

	return EXIT_SUCCESS;
}

UPosition AddUser(UPosition head, char name[MAX_LINE]) {

	UPosition newUser = NULL;
	newUser = (UPosition)malloc(sizeof(User));

	if (!newUser) {
		printf("Can't allocate memory\n");
		return MEMORY_ALLOCATION_ERROR;
	}

	strcpy(newUser->name, name);
	for (int i = 0; i < 5; i++) {
		newUser->books[i] = NULL;
	}

	newUser->next = head->next;
	head->next = newUser;

	return newUser;
}

int PrintBooks(BPosition head) {
	while (head->next != NULL) {
		head = head->next;
		printf("%s by %s written in %d, available copies: %d.\n", head->name, head->author, head->releaseYear, head->availableCopies);
	}
	return EXIT_SUCCESS;
}

int SwapBookValues(BPosition first, BPosition second) {

	char tempName[MAX_LINE], tempAuthor[MAX_LINE];
	int tempYear, tempCopies;

	strcpy(tempName, first->name);
	strcpy(tempAuthor, first->author);
	tempYear = first->releaseYear;
	tempCopies = first->availableCopies;

	strcpy(first->name, second->name);
	strcpy(first->author, second->author);
	first->releaseYear = second->releaseYear;
	first->availableCopies = second->availableCopies;

	strcpy(second->name, tempName);
	strcpy(second->author, tempAuthor);
	second->releaseYear = tempYear;
	second->availableCopies = tempCopies;

	return EXIT_SUCCESS;
}

int PrintUsers(UPosition head) {
	while (head->next != NULL) {
		head = head->next;
		printf("%s.\n", head->name);
	}
	return EXIT_SUCCESS;
}

int PrintUsersAlphabetically(UPosition head) {

	UPosition lastRead = NULL;
	UPosition start = head;

	int swapped = 0;

	if (!head) {
		printf("List empty.\n");
		return INVALID_LIST_COUNT;
	}
	else if (!head->next) {
		printf("List has only 1 element.\n");
		return INVALID_LIST_COUNT;
	}

	do {
		swapped = 0;
		UPosition pos = start;

		while (pos->next != lastRead) {
			if (strcmp(pos->name, pos->next->name) > 0) {

				SwapUserValues(pos,pos->next);

				swapped = 1;
			}
			pos = pos->next;
		}

		lastRead = pos;

	} while (swapped);

	PrintUsers(head);

	return EXIT_SUCCESS;
}

int SwapUserValues(UPosition first, UPosition second) {

	char tempName[MAX_LINE];

	strcpy(tempName, first);
	strcpy(first, second);
	strcpy(second, tempName);

	BPosition tempBooks[5];

	*tempBooks = *first->books;
	*first->books = *second->books;
	*second->books = *tempBooks;

	return EXIT_SUCCESS;
}

int SearchBooksByYear(BPosition head, int year) {
	
	int counter = 0;

	while (head->next) {
		head = head->next;
		if (head->releaseYear == year) {
			counter++;
			printf("%s by %s written in %d, available copies: %d.\n", head->name, head->author, head->releaseYear, head->availableCopies);
		}
	}
	if (counter == 0)
		printf("No Books found.\n");
	else {
		printf("Found %d Books.\n", counter);
	}

	return EXIT_SUCCESS;
}

int SearchBooksByAuthor(BPosition head, char author[MAX_LINE]) {

	int counter = 0;

	while (head->next) {
		head = head->next;
		if (strcmp(head->author, author) == 0) {
			counter++;
			printf("%s by %s written in %d, available copies: %d.\n", head->name, head->author, head->releaseYear, head->availableCopies);
		}
	}

	if (counter == 0)
		printf("No Books found.\n");
	else {
		printf("Found %d Books.\n", counter);
	}

	return EXIT_SUCCESS;
}

int LendABook(UPosition user, BPosition book) {

	BPosition head = book;

	printf("Enter a full name of a User who wants to lend a book: \n");
	char userName[MAX_LINE];
	scanf(" %[^\n]s", userName);

	int userFound = 0;

	while (user->next) {
		user = user->next;
		if (strcmp(user->name, userName) == 0) {
			userFound = 1;
			if (CheckUserBooks(user)==0) {
				printf("This User has to return some books first before lending another.\n");
				return NO_BOOKS_TRANSFERRED;
			}
			printf("Lending a Book to %s.\n", user->name);
			break;
		}
	}

	if (userFound == 0) {
		printf("User not found.\n");
		return NO_BOOKS_TRANSFERRED;
	}

	PrintBooks(head);

	printf("Enter a name of a Book which %s wants to lend: \n", user->name);
	char bookName[MAX_LINE];
	scanf(" %[^\n]s", bookName);

	while (book->next) {
		book = book->next;
		if (strcmp(book->name, bookName) == 0) {
			if (book->availableCopies == 0) {
				printf("No copies available for %s by %s.\n", book->name, book->author);
				return NO_BOOKS_TRANSFERRED;
			}
			printf("%s wants to lend %s by %s written in %d.\n%d copies are available. How many do you want: \n", user->name, book->name,
				book->author, book->releaseYear, book->availableCopies);
			break;
		}
	}

	
	
	int booksAvailableForUser = CheckUserBooks(user);

	while (1) {
		int wantedCopies;
		scanf(" %d", &wantedCopies);

		if (wantedCopies < 0) {
			printf("Invalid number, try again.\n");
		}
		else if (wantedCopies == 0) {
			printf("No Books lended.\n");
			return NO_BOOKS_TRANSFERRED;
		}
		else if (wantedCopies > booksAvailableForUser) {
			printf("You can't take that many because you are currently renting %d books (which would go over 5 books per User).\n"
				, 5 - booksAvailableForUser);
			printf("Suggestion: Maximum you can take is %d.\n"
				, (book->availableCopies > booksAvailableForUser) ? booksAvailableForUser : book->availableCopies);
		}
		else if (wantedCopies > book->availableCopies) {
			printf("There are not enough copies available (%d available copies).\n", book->availableCopies);
			printf("Suggestion: Maximum you can take is %d.\n"
				, (book->availableCopies > booksAvailableForUser) ? booksAvailableForUser : book->availableCopies);
				}
		else {
			int counter = 0;
			book->availableCopies -= wantedCopies;
			for (int i = 0; i < 5; i++) {
				if (user->books[i] == NULL) {
					user->books[i] = book;
					++counter;
					if (counter == wantedCopies) {
						break;
					}
				}
			}
			printf("Successfully lended %d copies of a %s by %s to %s.\n", wantedCopies, book->name, book->author, user->name);
			return BOOKS_TRANSFERRED;
		}
	}

	return EXIT_SUCCESS;
}

int CheckUserBooks(UPosition user) {

	int availableBooks = 0;

	for (int i = 0; i < 5; i++) {
		if (user->books[i] == NULL) {
			availableBooks++;
		}
	}

	return availableBooks;
}

int ReturnABook(UPosition user) {

	printf("Enter a full name of a User who wants to return a book: \n");
	char userName[MAX_LINE];
	scanf(" %[^\n]s", userName);

	int userFound = 0;

	while (user->next) {
		user = user->next;
		if (strcmp(user->name, userName) == 0) {
			userFound = 1;
			if (CheckUserBooks(user) == 5) {
				printf("This User has no books to return.\n");
				return NO_BOOKS_TRANSFERRED;
			}
			printf("Returning a Book from %s.\n", user->name);
			break;
		}
	}

	if (userFound == 0) {
		printf("User not found.\n");
		return NO_BOOKS_TRANSFERRED;
	}


	while (1) {
		int wantedBooks = 0;
		int wantedIndex;
		printf("What Book does %s want to return (type \"cancel\" to cancel):\n", user->name);
		for (int i = 0; i < 5; i++) {
			if (user->books[i] != NULL) {
				printf("%s by %s, written in %d.\n", user->books[i]->name, user->books[i]->author, user->books[i]->releaseYear);
			}
		}
	
		char bookName[MAX_LINE];
		scanf(" %[^\n]s", bookName);

		if (strcmp(bookName, "cancel") == 0) {
			printf("Return of a Book canceled.\n");
			return NO_BOOKS_TRANSFERRED;
		}

		for (int i = 0; i < 5; i++) {
			if (user->books[i] != NULL) {
				if (strcmp(user->books[i], bookName) == 0) {
					wantedBooks++;
					wantedIndex = i;
				}
			}
		}
		if (wantedBooks == 0) {
			printf("Wrong Book name, try again.\n");
		}
		else if (wantedBooks == 1) {
			printf("You want to return %s by %s. Y/N?\n", user->books[wantedIndex]->name, user->books[wantedIndex]->author);
			int answer = YesNoPrompt();

			if (answer == YES) {
				printf("Successfully returned %s by %s from %s.\n", user->books[wantedIndex]->name
					, user->books[wantedIndex]->author, user->name);
				user->books[wantedIndex]->availableCopies += wantedBooks;
				user->books[wantedIndex] = NULL;
				return BOOKS_TRANSFERRED;
			}
			else if (answer == NO) {
				printf("Books not returned.\n");
			}
		}
		else if (wantedBooks > 1) {
			printf("You want to return %s by %s. You are currently ledning %d copies of that Book. How many do you want to return (0-%d): \n"
				, user->books[wantedIndex]->name, user->books[wantedIndex]->author, wantedBooks, wantedBooks);
			int copies;
			scanf(" %d", &copies);
			
			if (copies < 0) {
				printf("Invalid number of Books, try again.\n");
			}
			else if (copies == 0) {
				printf("No Books returned.\n");
				return NO_BOOKS_TRANSFERRED;
			}
			else if (copies > wantedBooks) {
				printf("You aren't lending that many copies. Maximum you can return is %d.\n", wantedBooks);
			}
			else {
				printf("Successfully returned %d copies of %s by %s from %s.\n", copies, user->books[wantedIndex]->name
					, user->books[wantedIndex]->author, user->name);
				user->books[wantedIndex]->availableCopies += copies;
				int counter = 0;
				for (int i = 0; i < 5; i++) {
					if (user->books[i] != NULL) {
						if (strcmp(user->books[i]->name, bookName) == 0) {
							if (counter<copies) {
								user->books[i] = NULL;
								counter++;
							}
						}
					}
				}
				return BOOKS_TRANSFERRED;
			}
		}
	}
	
	return EXIT_SUCCESS;
}

int YesNoPrompt() {

	char choice;

	while (1) {
		scanf(" %c", &choice);
		switch (choice) {
		case 'y':
		case 'Y':
			return YES;
			break;
		case 'n':
		case 'N':
			return NO;
			break;
		default:
			printf("Invalid choice pick Y/N (Yes or No).\n");
			continue;
		}
	}

}

int SaveInventory(BPosition book, UPosition user) {

	FILE* file;
	file = fopen("inventory.txt", "w");
	if (!file) {
		printf("Can't open file.\n");
		return FILE_ERROR;
	}
	fprintf(file, "BOOKS\n");
	while (book->next) {
		book = book->next;
		fprintf(file, "%s,%s,%d %d\n", book->name, book->author, book->releaseYear, book->availableCopies);
	}
	printf("Successfully saved Books.\n");
	fprintf(file, "USERS\n");
	while (user->next) {
		user = user->next;
		fprintf(file, "%s,", user->name);

		for (int i = 0; i < 5; i++) {
			if (user->books[i] == NULL) {
				fprintf(file, "NULL,");
			}
			else {
				fprintf(file, "%s,", user->books[i]->name);
			}
		}
		fprintf(file, "\n");
	}
	fprintf(file, "END");

	fclose(file);
	printf("Successfully saved Users.\n");
	return EXIT_SUCCESS;
}

int LoadInventory(BPosition book, UPosition user) {

	BPosition start = book;

	FILE* file;
	file = fopen("inventory.txt", "r");
	if (!file) {
		printf("Can't open file.\n");
		return FILE_ERROR;
	}
	char tmp[MAX_LINE];
	fgets(tmp, MAX_LINE, file);

	int paramsRead=4;
	while (paramsRead==4) {
		char name[MAX_LINE], author[MAX_LINE];
		int year, copies;

		fgets(tmp, MAX_LINE, file);
		if (strcmp(tmp, "USERS\n") == 0) {
			paramsRead = 0;
			continue;
		}
		paramsRead = sscanf(tmp, " %[^,]%*c%[^,]%*c%d %d", name, author, &year, &copies);
		AddBook(book, name, author, year, copies);
	}
	printf("Successfully loaded Books.\n");
	while (!feof(file)) {
		
		char name[MAX_LINE];
		char names[5][MAX_LINE];

		fgets(tmp, MAX_LINE, file);
		if (strcmp(tmp, "END") == 0) {
			continue;
		}

		paramsRead=sscanf(tmp, "%[^,]%*c%[^,]%*c%[^,]%*c%[^,]%*c%[^,]%*c%[^,]%*c"
			, name, names[0], names[1], names[2], names[3], names[4]);

		UPosition currentUser = AddUser(user, name);
		int counter = 0;
		while (book->next) {
			book = book->next;
			for (int i = 0; i < 5; i++) {
				if (strcmp(book->name, names[i]) == 0) {
					currentUser->books[counter]=book;
					counter++;
				}
			}
		}
		book = start;
		
	}
	printf("Successfully loaded Users.\n");
	return EXIT_SUCCESS;
}