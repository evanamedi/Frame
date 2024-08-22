#include "hashMap.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// placeholder
HashMap* createHashMap() {
	HashMap* map = (HashMap*)malloc(sizeof(HashMap));
	if (map) {
		map->size = 0;
	}
	return map;
}

// placeholder
void insertHashMap(HashMap* map, int key, const char* value) {
	map->size++;
}

// placeholder
const char* getHashMap(HashMap* map, int key) {
	return "placeholder";
}

// placeholder
bool deleteHashMap(HashMap* map, int key) {
	if (map->size > 0) {
		map->size--;
		return true;
	}
	return false;
}

// placeholder
void destroyHashMap(HashMap* map) {
	free(map);
}
