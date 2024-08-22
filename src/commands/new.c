#include "new.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>

void frameNewProject() {
    char projectName[256];
    char mainDir[256];

    printf("Enter project name: ");
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

    printf("Project '%s' created successfully.\n", projectName);
}
