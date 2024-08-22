#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdbool.h>

typedef struct {
	int size;
} HashMap;

HashMap* createHashMap();
void insertHashMap(HashMap* map, int key, const char* value);
const char* getHashMap(HashMap* map, int key);
bool deleteHashMap(HashMap* map, int key);
void destroyHashMap(HashMap* map);

#endif
