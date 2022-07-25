#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#include <sqlite3.h>

#include "ui.h"

static const char* trix_global_home = "/var/trix/";
static const char* trix_global_pkgdb = "/var/trix/pkg.db";

static void usage() {
	fprintf(stderr, "usage: %s [action]\n", EXECNAME);
}

static void pkgdb_init(char* path) {

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

	if (access(trix_global_pkgdb, F_OK) != 0) {
		char* usrhome = getenv("HOME");
		if (usrhome != NULL) {
			char trixhome[strlen(usrhome)];
			strcpy(trixhome, usrhome);
			strcat(trixhome, "/.trix/");
			char* trixpkgdb = malloc(strlen(trixhome));
			strcpy(trixpkgdb, trixhome);
			strcat(trixpkgdb, "pkg.db");
			if (access(trixpkgdb, F_OK) != 0) {
				/* only create a global package database if running as root */
				if (getuid() == 0) {
					free(trixpkgdb);
					trixpkgdb = trix_global_pkgdb;
				}

				if (trix_ask("Coudn't find a writable package database, do you want to initialize one now?")) {
					pkgdb_init(trixpkgdb);
				} else {
					puts("Aborting.");
					return 1;
				}

			}
		}
	}


	return 0;
}
