#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include "commands.h"

void handle_command(int argc, char *argv[]) {
	(void)argc;
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
	printf("Frame CLI Tool - Available Commands:\n");
    printf("  help       - Display this help message\n");
    printf("  new        - Create a new C project\n");
    printf("  newfile    - Create a new C file and its header\n");
    printf("  style      - Enforce code style\n");
}

void frameNewProject() {
	char projectName[256];
	char mainDir[256];

	printf("Enter Project name: ");
	fgets(projectName, sizeof(projectName), stdin);
	projectName[strcspn(projectName, "\n")] = 0;

	printf("Enter main directory name (default: src): ");
	fgets(mainDir, sizeof(mainDir), stdin);
	mainDir[strcspn(mainDir, "\n")] = 0;

	if (strlen(mainDir) == 0) {
		strcpy(mainDir, "src");
	}

	if (mkdir(projectName, 0755) != 0) {
		perror("Error creating project directory");
		return;
	}

	char fullMainDir[512];
	snprintf(fullMainDir, sizeof(fullMainDir), "%s/%s", projectName, mainDir);
	if (mkdir(fullMainDir, 0755) != 0) {
		perror("Error creating main directory");
		return;
	}

	char makefilePath[512];
	snprintf(makefilePath, sizeof(makefilePath), "%s/Makefile", projectName);
	FILE *makefile = fopen(makefilePath, "w");
	if (makefile == NULL) {
		perror("Error creating Makefile");
		return;
	}

	fprintf(makefile, "CC = gcc\n");
    fprintf(makefile, "CFLAGS = -Wall -Wextra -std=c99\n");
    fprintf(makefile, "SRCS = $(wildcard %s/*.c)\n", mainDir);
    fprintf(makefile, "OBJS = $(SRCS:.c=.o)\n");
    fprintf(makefile, "TARGET = %s\n\n", projectName);
    fprintf(makefile, "all: $(TARGET)\n\n");
    fprintf(makefile, "$(TARGET): $(OBJS)\n");
    fprintf(makefile, "\t$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)\n\n");
    fprintf(makefile, "clean:\n");
    fprintf(makefile, "\trm -f $(TARGET) $(OBJS)\n");

    fclose(makefile);

    char configPath[512];
    snprintf(configPath, sizeof(configPath), "%s/config.conf", projectName);
    FILE *config = fopen(configPath, "w");
    if (config == NULL) {
    	perror("Error creating configuration file");
    	return;
    }

    fprintf(config, "[General]\n");
    fprintf(config, "ProjectName=%s\n", projectName);
    fprintf(config, "MainDirectory=%s\n", mainDir);

    fclose(config);

    printf("Project '%s' created successfully\n", projectName);
}

void frameNewFile() {
	char filename[256];
	char projectDir[256] = ".";
	char mainDir[256] = "src";

	printf("Enter new C file name (without extension): ");
	fgets(filename, sizeof(filename), stdin);
	filename[strcspn(filename, "\n")] = 0;

	char srcDirPath[512];
	snprintf(srcDirPath, sizeof(srcDirPath), "%s/%s", projectDir, mainDir);
	if (mkdir(srcDirPath, 0755) != 0 && errno != EEXIST) {
		perror("Error creating src directory");
		return;
	}

	char cFilePath[512];
	char hFilePath[512];
	snprintf(cFilePath, sizeof(cFilePath), "%s/%s/%s.c", projectDir, mainDir, filename);
	snprintf(hFilePath, sizeof(hFilePath), "%s/%s/%s.h", projectDir, mainDir, filename);

	FILE *cFile = fopen(cFilePath, "w");
	if (cFile == NULL) {
		perror("Error creating C file");
		return;
	}
	fprintf(cFile, "$include \"%s.h\"\n\n", filename);
	fclose(cFile);

	FILE *hFile = fopen(hFilePath, "w");
	if (hFile == NULL) {
		perror("Error creating header file");
		return;
	}
	fprintf(hFile, "#ifndef %s_H\n", filename);
	fprintf(hFile, "$define %s_H\n\n", filename);
	fprintf(hFile, "#endif // %s_H\n", filename);
	fclose(hFile);

	printf("Created %s and %s\n", cFilePath, hFilePath);
}

void toggleAutoStyle(const char *configPath) {
	FILE *config = fopen(configPath, "r+");
	if (config == NULL) {
		perror("Error opening configuration file");
		return;
	}

	char line[256];
	int found = 0;
	long int pos;
	while (fgets(line, sizeof(line), config)) {
		if (strncmp(line, "autoStyle=", 10) == 0) {
			found = 1;
			pos = ftell(config) - strlen(line);
			break;
		}
	}

	if (found) {
		fseek(config, pos, SEEK_SET);
		if (strstr(line, "true")) {
			fprintf(config, "autoStyle=false\n");
			printf("Code style enforcement deactivated\n");
		} else {
			fprintf(config, "autoStyle=true \n");
			printf("Code style enforcement activated\n");
		}
	} else {
		fseek(config, 0, SEEK_END);
		fprintf(config, "autoStyle=true \n");
		printf("Code style enforcement activated\n");
	}

	fclose(config);
}

void frameStyle() {
	char configPath[512];
	snprintf(configPath, sizeof(configPath), "./config.conf");

	toggleAutoStyle(configPath);
}
