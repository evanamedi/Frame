#include <stdio.h>
#include "commands.h"

int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("Usage: frame <command>\n");
		return 1;
	}

	// call command handler with provided argument
	handle_command(argc, argv);

	return 0;
}