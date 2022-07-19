#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

static void usage() {
	fprintf(stderr, "usage: trix [-hv]\n");
}

int main(int argc, char** argv) {
	if (argc == 1) {
		usage();
		return 0;
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
	return 0;
}
