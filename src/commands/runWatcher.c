#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "runWatcher.h"

void frameRunWatcher() {
	const char *configFilePath = "config/config.conf";

	char *configContent = readConfigFile(configFilePath);
	if (configContent == NULL) {
		fprintf(stderr, "Error: Unable to read configuration file\n");
		return;
	}

	ConfigState configState = parseConfig(configContent);

	if (!configState.autoStyle) {
		configState = updateAutoStyle(configState);
		if (!writeConfigFile(configFilePath, configState.parsedData)) {
			fprintf(stderr, "Error: Unable to write to configuration file\n");
			free(configContent);
			return;
		}
		printf("autoStyle Enabled\n");
	}

	if (configState.autoStyle) {
		printf("Starting watcher...\n");
	}

	free(configContent);
}


char* readConfigFile(const char *configFilePath) {
	FILE *file = fopen(configFilePath, "r");
	if (file == NULL) {
		perror("Failed to open configuration file");
		return NULL;
	}

	fseek(file, 0, SEEK_END);
	long fileSize = ftell(file);
	fseek(file, 0, SEEK_SET);

	char *content = malloc(fileSize + 1);
	if (content == NULL) {
		perror("Failed to allocate memory");
		fclose(file);
		return NULL;
	}

	fread(content, 1, fileSize, file);
	content[fileSize] = '\0';

	fclose(file);
	return content;
}



ConfigState parseConfig(const char *configContent) {
	ConfigState state = {false, false, ""};
	char line[256];
	bool inGeneralSection = false;

	const char *contentPtr = configContent;
	while (sscanf(contentPtr, "%[^\n]\n", line) == 1) {
		contentPtr += strlen(line) + 1;
		char *trimmedLine = strtok(line, "\n\r");

		if (trimmedLine[0] == '[') {
			if (strcmp(trimmedLine, "[General]") == 0) {
				inGeneralSection = true;
			} else {
				inGeneralSection = false;
			}
		} else if (inGeneralSection) {
			char key[256], value[256];
			if (sscanf(trimmedLine, "%s = %s", key, value) == 2) {
				if (strcmp(key, "autoStyle") == 0) {
					state.autoStyle = (strcmp(value, "true") == 0);
					state.foundAutoStyle = true;
					snprintf(line, 
							sizeof(line), 
							"autoStyle = %s", 
							state.autoStyle ? "true" : "false");
				}
			}
		}

		strncat(state.parsedData, 
				line, 
				sizeof(state.parsedData) - strlen(state.parsedData) - 1);
		strncat(state.parsedData, 
				"\n", 
				sizeof(state.parsedData) - strlen(state.parsedData) - 1);
	}

	return state;
}

ConfigState updateAutoStyle(ConfigState state) {
	if (!state.foundAutoStyle) {
		strcat(state.parsedData, "[General]\n");
		strcat(state.parsedData, "autoStyle = true\n");
	} else if (!state.autoStyle) {
		char *position = strstr(state.parsedData, "autoStyle = false");
		if (position) {
			strncpy(position + 12, "true", 4);
		}
	}
	state.autoStyle = true;
	return state;
}

bool writeConfigFile(const char *configFilePath, const char *content) {
	FILE *file = fopen(configFilePath, "w");
	if (file == NULL) {
		perror("Failed to open configuration file for writing");
		return false;
	}

	fputs(content, file);
	fclose(file);
	return true;
}
