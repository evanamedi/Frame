#include "style.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
            printf("Code style enforcement deactivated.\n");
        } else {
            fprintf(config, "autoStyle=true \n");
            printf("Code style enforcement activated.\n");
        }
    } else {
        
        fseek(config, 0, SEEK_END);
        fprintf(config, "autoStyle=true \n");
        printf("Code style enforcement activated.\n");
    }

    fclose(config);
}

void frameStyle() {
    char configPath[512];
    snprintf(configPath, sizeof(configPath), "./config.conf");

    toggleAutoStyle(configPath);
}
