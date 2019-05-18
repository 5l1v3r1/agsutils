#define _GNU_SOURCE
#include "DataFile.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "version.h"
#define ADS ":::AGSdisas " VERSION " by rofl0r:::"

__attribute__((noreturn))
void usage(char *argv0) {
	dprintf(2, ADS "\nusage:\n%s file.o [file.s]\n"
		       "pass input and optionally output filename.\n", argv0);
	exit(1);
}

static void disas(char *o, char *s) {
	//ARF_find_code_start
	AF f_b, *f = &f_b;
	ASI sc;
	if(AF_open(f, o)) {
		ASI *i = ASI_read_script(f, &sc) ? &sc : 0;
		dprintf(1, "disassembling %s -> %s", o, s);
		if(!i || !ASI_disassemble(f, i, s)) dprintf(1, " FAIL");
		dprintf(1, "\n");
		AF_close(f);
	}
}

int main(int argc, char**argv) {
	if(argc != 3 && argc != 2) usage(argv[0]);
	char *o = argv[1], *s, out[256];
	if(argc == 2) {
		size_t l = strlen(o);
		snprintf(out, 256, "%s", o);
		out[l-1] = 's'; // overflow me!
		s = out;
	} else s = argv[2];
	disas(o, s);
	return 0;
}
