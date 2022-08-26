#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <sqlite3.h>

#include "ui.h"

#define TRIX_GLOBAL_HOME "/var/trix/"

static void usage() {
	fprintf(stderr, "usage: %s [action]\n", EXECNAME);
}

static void pkgdb_init(char* path) {
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

	}
}

int main(int argc, char** argv) {
	if (argc == 1) {
		usage();
		return 0;
	}

	char* action;
	if (argv[1][0] != '-') {
		action = argv[1];
		argv++;
		argc--;
	}

	int ch;
	while ((ch = getopt(argc, argv, "hv")) != -1) {
		switch (ch) {
		case 'h':
			usage();
			break;
		case 'v':
			break;
		default:
			usage();
		}
	}

	if (access(TRIX_GLOBAL_HOME, F_OK) != 0) {
		char* usrhome = getenv("HOME");
		if (usrhome != NULL) {
			char trixhome[strlen(usrhome) + strlen("/.trix/") + strlen("pkg.db")];
			sprintf(trixhome, "%s/.trix", usrhome);
			if (access(trixhome, F_OK) != 0) {
				if (trix_ask("Coudn't find a writable package database, do you want to initialize one now?")) {
					/* only create a global package database if running as root */
					if (getuid() == 0) {
						pkgdb_init(TRIX_GLOBAL_HOME);
					} else {
						pkgdb_init(trixhome);
					}
				
				} else {
					puts("Aborting.");
					return 1;
				}
			}
		}
	}


	return 0;
}
