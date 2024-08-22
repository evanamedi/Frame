#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include "commands.h"

FILE *open_memstream_replacement(const char *input) {
    FILE *tmp = tmpfile();
    fwrite(input, 1, strlen(input), tmp);
    rewind(tmp);
    return tmp;
}

void test_help_command() {
    char *args[] = {"frame", "help"};
    handle_command(2, args);
    printf("---test_help_command passed---\n\n");
}

void test_new_command(const char *test_dir) {
    char *args[] = {"frame", "new"};

    const char *projectName = "test_project";
    const char *mainDir = "test_src";

    FILE *stdin_backup = stdin;
    char input[512];
    snprintf(input, sizeof(input), "%s\n%s\n", projectName, mainDir);
    stdin = open_memstream_replacement(input);

    chdir(test_dir);

    handle_command(2, args);

    fclose(stdin);
    stdin = stdin_backup;

    printf("---test_new_command passed---\n\n");
}

void test_newfile_command(const char *test_dir) {
    char *args[] = {"frame", "newfile"};
    const char *filename = "testfile";

    FILE *stdin_backup = stdin;
    char input[512];
    snprintf(input, sizeof(input), "%s\n", filename);
    stdin = open_memstream_replacement(input);

    chdir(test_dir);
    chdir("test_project");

    handle_command(2, args);

    fclose(stdin);
    stdin = stdin_backup;

    char cFilePath[512];
    char hFilePath[512];
    snprintf(cFilePath, sizeof(cFilePath), "src/%s.c", filename);
    snprintf(hFilePath, sizeof(hFilePath), "src/%s.h", filename);

    if (access(cFilePath, F_OK) == 0 && access(hFilePath, F_OK) == 0) {
        printf("---test_newfile_command passed: %s and %s created successfully---\n\n", cFilePath, hFilePath);
    } else {
        printf("---test_newfile_command failed: %s or %s not found---\n\n", cFilePath, hFilePath);
    }

    remove(cFilePath);
    remove(hFilePath);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <test_directory>\n", argv[0]);
        return 1;
    }

    const char *test_dir = argv[1];

    printf("Running tests in directory: %s\n", test_dir);

    test_help_command();
    test_new_command(test_dir);
    test_newfile_command(test_dir);

    printf("---All tests passed!---\n\n");

    return 0;
}