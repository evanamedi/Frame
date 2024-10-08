#ifndef RUN_WATCHER_H
#define RUN_WATCHER_H

#include <stdbool.h>

typedef struct {
	bool autoStyle;
	bool foundAutoStyle;
	char parsedData[1024];
} ConfigState;

void frameRunWatcher();

char* readConfigFile(const char *configFilePath);
ConfigState parseConfig(const char *configContent);
ConfigState updateAutoStyle(ConfigState state);
bool writeConfigFile(const char *configFilePath, const char *content);

#endif
