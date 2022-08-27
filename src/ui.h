#ifndef __UI_H
#define __UI_H

#include <stdbool.h>

#define TRIX_ERR(str) printf("[\033[0;31mXXX\033[0m] %s\n", str)
#define TRIX_INFO(str) printf("[\033[0;32m***\033[0m] %s\n", str)

bool trix_ask(char* question);

#endif
