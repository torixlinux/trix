#ifndef __DB_H
#define __DB_H

#include <sqlite3.h>

sqlite3* pkgdb_init(char* path);
sqlite3* pkgdb_open(char* path);
void	 pkgdb_close(sqlite3* db);

#endif
