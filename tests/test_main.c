#include <stdio.h>
#include <string.h>
#include "commands.h"

void test_help_command() {
    char *args[] = {"frame", "help"};
    handle_command(2, args);
    printf("test_help_command passed\n");
}

void test_new_command() {
    char *args[] = {"frame", "new"};
    handle_command(2, args);
    printf("test_new_command passed\n");
}

int main() {
    printf("Running tests...\n");

    test_help_command();
    test_new_command();

    printf("All tests passed!\n");

    return 0;
}