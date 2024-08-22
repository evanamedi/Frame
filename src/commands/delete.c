#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void frameDelete() {
	const char *install_dir = getenv("HOME");
	char executable_path[512];
	snprintf(executable_path, sizeof(executable_path), "%s/.local/bin/frame", install_dir);

	printf("Deleting Frame tool...\n");

	if (access(executable_path, F_OK) != 0) {
		printf("Error: The executable does not exist at %s\n", executable_path);
		return;
	}

	if (remove(executable_path) != 0) {
		printf("Error: Failed to delete the executable at %s\n", executable_path);
		return;
	}

	const char *repo_dir = getenv("HOME");
	const char *local_repo_dir = "/frame";
	char repo_path[512];
	snprintf(repo_path, sizeof(repo_path), "%s%s", repo_dir, local_repo_dir);

	printf("Removing the local repository at %s...\n", repo_path);
	char remove_cmd[1024];
	snprintf(remove_cmd, sizeof(remove_cmd), "rm -rf %s", repo_path);
	if (system(remove_cmd) != 0) {
		printf("Error: Failed to remove the local repository at %s\n", repo_path);
		return;
	}

	printf("Frame tool deleted successfully\n");
}
