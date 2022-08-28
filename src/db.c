#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "db.h"
#include "ui.h"

sqlite3* pkgdb_init(char* path) {
	struct stat st = {0};
	if (stat(path, &st) == -1) {
		mkdir(path, 0700);
	}

	char packagedb[strlen(path) + strlen("/pkg.db")];
	sprintf(packagedb, "%s/pkg.db", path);

	sqlite3* db;
	int rc = sqlite3_open(packagedb, &db);
	if (rc) {
		TRIX_ERR("Can't open package database for writing");
	} else {
		// TRIX_INFO("Writing new database...");
		sqlite3_exec(db, "CREATE TABLE pkgdb", NULL, 0, NULL);
	}
	return db;
}

sqlite3* pkgdb_open(char* path) {

}

void pkgdb_close(sqlite3* db) {
	sqlite3_close(db);
}
