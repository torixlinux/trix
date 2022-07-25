#include "ui.h"

#include <stdio.h>

bool trix_ask(char* question) {
	printf("%s [Y,n]: ", question);
	char answer;
	scanf("%c", &answer);
	if (answer == 'y' || answer == 'Y' || answer == '\n') {
		return true;
	} else {
		return false;
	}
}
