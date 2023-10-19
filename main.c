#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

static int xgetchar(void)
{
	const int ch = getchar();

	if (ch == EOF)
	{
		if (ferror(stdin))
			perror("Fehler beim Lesen von der Standardeingabe");
		else
			fputs("Unerwartetes Dateiende beim Lesen von der Standardeingabe\n", stderr);

		exit(EXIT_FAILURE);
	}

	return ch;
}

static void swallow(void)
{
	while (xgetchar() != '\n')
		;
}

static void swallowWhitespace(void)
{
	int input;

	while ((input = xgetchar()) != '\n' && isspace(input))
		;

	ungetc(input, stdin);
}

static int menu(void)
{
	for (;;)
	{
		puts("[N]euen Eintrag anlegen");
		puts("[L]iste ausgeben");
		puts("Eintrag entfe[r]nen");
		puts("B[e]enden");

		fputs("Was möchten Sie tun: ", stdout);

		swallowWhitespace();

		int selection = xgetchar();
		if (selection != '\n')
		{
			swallow();

			selection = toupper(selection);
			if (selection != '\0' && strchr("NLRE", selection) != NULL)
				return selection;
		}

		puts("Falsche Eingabe!");
	}
}

static void prompt(const char *msg, char *buffer, size_t size)
{
	assert(msg != NULL);
	assert(buffer != NULL);
	assert(size > 0);

	for (;;)
	{
		fputs(msg, stdout);
		fputs(": ", stdout);

		for (size_t i = 0; i < size; ++i)
		{
			int ch = xgetchar();
			if (ch == '\n')
			{
				buffer[i] = '\0';
				return;
			}
			else
				buffer[i] = (char)ch;
		}

		printf("Eingabe zu lang, maximal %zu Bytes!\n", size - 1U);
		swallow();
	}
}

/*
 * TODO: Add static helper functions as needed.
 */

static void printUser(ListNode *currentUser)
{
	printf("\n------------------------\nName: %s\nNummer: %s\n------------------------\n\n", currentUser->name, currentUser->number);
}

int main(void)
{
	// TODO: un-comment when you have implemented listRemoveAll()
	// atexit(listRemoveAll);

	bool running = true;
	while (running)
	{
		const int selection = menu();
		switch (selection)
		{
		case 'N':
			char newName[32];
			const char newNamePromtMessage[] = "\nBitte den Namen der neuen Person eingeben!\n";
			const char newNumberPromtMessage[] = "Bitte Telefonnummer der neuen Person eingeben\n";

			prompt(newNamePromtMessage, newName, 32);

			ListNode *newListNode = listAdd(newName);

			prompt(newNumberPromtMessage, newListNode->number, 32);

			printUser(newListNode);

			break;
		case 'L':
			listForEach(printUser);
			break;
		case 'R':
			// TODO: handle command
			puts("R or r was pressed\n");
			break;
		case 'E':
			puts("Programm wird beendet.\n");
			running = false;
			break;
		default:
			abort(); // should never be reached, menu() never returns something else
			break;
		}
	}

	return EXIT_SUCCESS;
}
