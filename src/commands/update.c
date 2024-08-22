#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void frameUpdate() {
	const char *repo_dir = getenv("HOME");
	const char *local_repo_dir = "/frame";
	char path[512];
	snprintf(path, sizeof(path), "%s%s", repo_dir, local_repo_dir);

	printf("Checking for updates...\n");

	if (chdir(path) != 0) {
		printf("Error: Could not navigate to the repository directory\n");
		return;
	}

	if (system("git fetch") != 0) {
		printf("Error: Failed to fetch updates from the remote repository\n");
		return;
	}

	if (system("git status -uno | grep 'Your branch is up to date' > /dev/null") == 0) {
		printf("Already up to date\n");
		return;
	}

	if (system("git pull") != 0) {
		printf("Error: Failed to pull updates from the remote repository\n");
		return;
	}

	printf("Building project with the lastest updates...\n");
	if (system("make clean && make") != 0) {
		printf("Error: Failed to rebuild the project\n");
		return;
	}

	const char *install_dir = getenv("HOME");
	char install_cmd[512];
	snprintf(install_cmd, sizeof(install_cmd), "cp frame %s/.local/bin/frame", install_dir);
	if (system(install_cmd) != 0) {
		printf("Error: Failed to reinstall the executable\n");
		return;
	}

	printf("Update complete. Run 'frame help' to see the available commands\n");
}
