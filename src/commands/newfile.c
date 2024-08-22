#include "newfile.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>

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
    snprintf(cFilePath, sizeof(cFilePath), "%s/%s.c", srcDirPath, filename);
    snprintf(hFilePath, sizeof(hFilePath), "%s/%s.h", srcDirPath, filename);

    FILE *cFile = fopen(cFilePath, "w");
    if (cFile == NULL) {
        perror("Error creating C file");
        return;
    }
    fprintf(cFile, "#include \"%s.h\"\n\n", filename);
    fclose(cFile);

    FILE *hFile = fopen(hFilePath, "w");
    if (hFile == NULL) {
        perror("Error creating header file");
        return;
    }
    fprintf(hFile, "#ifndef %s_H\n", filename);
    fprintf(hFile, "#define %s_H\n\n", filename);
    fprintf(hFile, "#endif // %s_H\n", filename);
    fclose(hFile);

    printf("Created %s and %s\n", cFilePath, hFilePath);
}
