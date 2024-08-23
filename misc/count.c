#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

void countLinesAndCharsInFile(const char *filePath, int *fileCount, int *totalLines, int *totalChars) {
    FILE *file = fopen(filePath, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }

    int lines = 0, chars = 0;
    char buffer[1024];

    while (fgets(buffer, sizeof(buffer), file)) {
        lines++;
        chars += strlen(buffer);
    }

    fclose(file);

    *totalLines += lines;
    *totalChars += chars;
    (*fileCount)++;
    
    printf("File: %s, Lines: %d, Characters: %d\n", filePath, lines, chars);
}

void exploreDirectory(const char *directory, int *totalLines, int *totalChars, int *fileCount) {
    struct dirent *entry;
    DIR *dp = opendir(directory);

    if (!dp) {
        perror("Error opening directory");
        return;
    }

    while ((entry = readdir(dp))) {
        if (entry->d_type == DT_DIR) {
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                char path[1024];
                snprintf(path, sizeof(path), "%s/%s", directory, entry->d_name);
                exploreDirectory(path, totalLines, totalChars, fileCount);
            }
        } else if (entry->d_type == DT_REG) {
            if (strstr(entry->d_name, ".c") != NULL) {
                char filePath[1024];
                snprintf(filePath, sizeof(filePath), "%s/%s", directory, entry->d_name);
                countLinesAndCharsInFile(filePath, totalLines, totalChars, fileCount);
            }
        }
    }

    closedir(dp);
}

int main(void) {
    printf("\n");
    printf("=================================================================\n");
	int fileCount = 0;
	int totalLines = 0;
	int totalChars = 0;
	
	exploreDirectory(".", &fileCount, &totalLines, &totalChars);
    printf("=================================================================\n");

	printf("\n      Total\n");
	printf("====================\n");
	printf("Files:     %d\n", fileCount);
	printf("Lines:     %d \n", totalLines);
	printf("Chars:     %d \n", totalChars);
	printf("====================\n");

	return 0;
}
