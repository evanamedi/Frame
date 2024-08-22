#include "help.h"
#include "new.h"
#include "newfile.h"
#include "style.h"
#include "update.h"
#include "delete.h"
#include <stdio.h>
#include <string.h>

void handle_command(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Use command 'frame' followed by a command\n");
        return;
    }

    const char *command = argv[1];

    if (strcmp(command, "help") == 0) {
        frameHelp();
    } else if (strcmp(command, "new") == 0) {
        frameNewProject();
    } else if (strcmp(command, "newfile") == 0) {
        frameNewFile();
    } else if (strcmp(command, "style") == 0) {
        frameStyle();
    } else if (strcmp(command, "update") == 0) {
        frameUpdate();
    } else if (strcmp(command, "delete") == 0) {
        frameDelete();
    } else {
        printf("Unknown command: %s\n", command);
    }
}
