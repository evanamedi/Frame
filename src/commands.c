#include <stdio.h>
#include <string.h>
#include "commands.h"

void handle_command(int argc, char *argv[]) {
	if (strcmp(argv[1], "help") == 0) {
		frameHelp();
	} else if (strcmp(argv[1], "new") == 0) {
		frameNewProject();
	} else if (strcmp(argv[1], "newfile") == 0) {
		frameNewFile();
	} else if (strcmp(argv[1], "style") == 0) {
		frameStyle();
	} else {
		printf("Unknown command: %s\n", argv[1]);
		printf("Use 'frame help' for list of avalible commands.\n");
	}
}

void frameHelp() {
	// placeholder
	printf("frame help: Display help information\n");
}

void frameNewProject() {
	// placeholder
	printf("frame new: Create a new project\n");
}

void frameNewFile() {
	// placeholder
	printf("frame newfile: create a new c file and its header\n");
}

void frameStyle() {
	// placeholder
	printf("frame style: Enforce code style\n");
}
