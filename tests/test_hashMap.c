#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include "hashMap.h"
#include "test_hashMap.h"


void runAllTestsForHashMap() {
	// Memory Managment
	memoryManagementTest1();
	memoryManagementTest2();
	memoryManagementTest3();

	// Collision Handling
	collisionHandlingTest1();
	collisionHandlingTest2();
	collisionHandlingTest3();

	// Performance
	performanceTest1();
	performanceTest2();
	performanceTest3();

	// Edge Cases
	edgeCaseTest1();
	edgeCaseTest2();
	edgeCaseTest3();
	edgeCaseTest4();
	edgeCaseTest5();
	edgeCaseTest6();
}

void generateRandomString(char *str, size_t length) {
	static const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	for (size_t i = 0; i < length; i++) {
		str[i] = charset[rand() % (sizeof(charset) - 1)];
	}
	str[length] = '\0';
}





// - - - - - Memory Management Tests - - - - -

void memoryManagementTest1() {
	printf("Running Memory Management Test 1 (1000 entries)...\n");
	HashMap *map = createHashMap();

	for (int i = 0; i < 1000; i++) {
		char value[20];
		if (i % 2 == 0) {
			snprintf(value, 20, "%d", rand());
		} else {
			generateRandomString(value, 19);
		}
		insertHashMap(map, i, value);
	}

	if (map->size != 1000) {
		printf("Memory Managment Test Failed: Expected size 1000, but got %d\n", map->size);
	} else {
		printf("Memory Managment Test Passed\n");
	}

	destroyHashMap(map);
}

void memoryManagementTest2() {
	printf("Running Memory Management Test 2 (10000 entries)...\n");
	HashMap *map = createHashMap();

	for (int i = 0; i < 10000; i++) {
		char value[50];
		if (i % 2 == 0) {
			snprintf(value, 50, "%d", rand());
		} else {
			generateRandomString(value, 49);
		}
		insertHashMap(map, i, value);
	}

	if (map->size != 10000) {
		printf("Memory Managment Test 2 Failed: Expected size 10000, but got %d\n", map->size);
	} else {
		printf("Memory Managment Test 2 Passed\n");
	}

	destroyHashMap(map);
}

void memoryManagementTest3() {
	printf("Running Memory Management Test 3 (100000 entries)...\n");
	HashMap *map = createHashMap();

	for (int i = 0; i < 100000; i++) {
		char value[100];
		if (i % 2 == 0) {
			snprintf(value, 100, "%d", rand());
		} else {
			generateRandomString(value, 99);
		}
		insertHashMap(map, i, value);
	}

	if (map->size != 100000) {
		printf("Memory Managment Test 3 Failed: Expected size 100000, but got %d\n", map->size);
	} else {
		printf("Memory Managment Test 3 Passed\n");
	}

	destroyHashMap(map);
}





// - - - - - Collison Handling Tests - - - - -

void collisionHandlingTest1() {
	printf("Running Collision Handling Test 1...\n");
	HashMap *map = createHashMap();

	insertHashMap(map, 1, "value1");
	insertHashMap(map, 11, "value11");
	insertHashMap(map, 21, "value21");

	if (strcmp(getHashMap(map, 1), "value1") != 0 ||
		strcmp(getHashMap(map, 11), "value11") != 0 ||
		strcmp(getHashMap(map, 21), "value21") != 0) {

		printf("Collision Handling Test 1 Failed\n");
	} else {
		printf("Collision Handling Test 1 Passed\n");
	}

	destroyHashMap(map);
}

void collisionHandlingTest2() {
	printf("Running Collision Handling Test 2 (100 collisions)...\n");
	HashMap *map = createHashMap();

	for (int i = 0; i < 100; i++) {
		char value[20];
		snprintf(value, 20, "value%d", i);
		insertHashMap(map, i * 11, value);
	}

	for (int i = 0; i < 100; i++) {
		char expectedValue[20];
		snprintf(expectedValue, 20, "value%d", i);
		if (strcmp(getHashMap(map, i * 11), expectedValue) != 0) {
			printf("Collision Handling Test 2 Failed\n");
			destroyHashMap(map);
			return;
		}
	}
	printf("Collision Handling Test 2 Passed\n");

	destroyHashMap(map);
}

void collisionHandlingTest3() {
	printf("Running Collision Handling Test 3 (1000 collisions)...\n");
	HashMap *map = createHashMap();

	for (int i = 0; i < 1000; i++) {
		char value[50];
		generateRandomString(value, 49);
		insertHashMap(map, i * 11, value);
	}

	for (int i = 0; i < 1000; i++) {
		if (getHashMap(map, i * 11) == NULL) {
			printf("Collision Handling Test 3 Failed\n");
			destroyHashMap(map);
			return;
		}
	}
	printf("Collision Handling Test 3 Passed\n");

	destroyHashMap(map);
}





// - - - - - Performance Tests - - - - -
// see documentation for O analysis

void performanceTest1() {
	printf("Running Performance Test 1 (10000 insertions)...\n");
	HashMap *map = createHashMap();

	clock_t start = clock();

	for (int i = 0; i < 1000000; i++) {
		char value[20];
		snprintf(value, 20, "value%d", i);
		insertHashMap(map, i, value);
	}

	clock_t end = clock();
	double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
	printf("Performance Test: Time taken for 1,000,000 insertions: %f seconds\n", time_spent);

	destroyHashMap(map);
}

void performanceTest2() {
	printf("Running Performance Test 2 (100000 insertions)...\n");
	HashMap *map = createHashMap();

	clock_t start = clock();

	for (int i = 0; i < 100000; i++) {
		char value[50];
		generateRandomString(value, 49);
		insertHashMap(map, i, value);
	}

	clock_t end = clock();
	double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
	printf("Performance Test 2: Time taken for 100,000 insertions: %f seconds\n", time_spent);

	destroyHashMap(map);
}

void performanceTest3() {
	printf("Running Performance Test 3 (1000000 insertions)...\n");
	HashMap *map = createHashMap();

	clock_t start = clock();

	for (int i = 0; i < 1000000; i++) {
		char value[100];
		generateRandomString(value, 99);
		insertHashMap(map, i, value);
	}

	clock_t end = clock();
	double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
	printf("Performance Test 3: Time taken for 1,000,000 insertions: %f seconds\n", time_spent);

	destroyHashMap(map);
}





// - - - - - Edge Case Tests - - - - -

void edgeCaseTest1() {
	printf("Running Edge Case Test 1 (update existing key)...\n");
	HashMap *map = createHashMap();

	insertHashMap(map, 1, "initialValue");
	insertHashMap(map, 1, "updatedValue");

	if (strcmp(getHashMap(map, 1), "updatedValue") != 0) {
		printf("Edge Case Test 1 Failed: Expected 'updatedValue', but got '%s'\n", getHashMap(map, 1));
	} else {
		printf("Edge Case Test 1 Passed: Key updated correctly\n");
	}

	destroyHashMap(map);
}

void edgeCaseTest2() {
	printf("Running Edge Case Test 2 (delete non-existent key)...\n");
	HashMap *map = createHashMap();

	if (deleteHashMap(map, 2)) {
		printf("Edge Case Test 2 Failed: Deleting non-existent key returned true\n");
	} else {
		printf("Edge Case Test 2 Passed: Non-existent key deletion handled correctly\n");
	}

	destroyHashMap(map);
}

void edgeCaseTest3() {
	printf("Running Edge Case Test 3 (handling NULL values)...\n");
	HashMap *map = createHashMap();

	insertHashMap(map, 1, NULL);

	if (getHashMap(map, 1) != NULL) {
		printf("Edge Case Test 3 Failed: Expected NULL, but got a non-null value\n");
	} else {
		printf("Edge Case Test 3 Passed: NULL value handled correctly\n");
	}

	destroyHashMap(map);
}

void edgeCaseTest4() {
	printf("Running Edge Case Test 4 (large keys)...\n");
	HashMap *map = createHashMap();

	insertHashMap(map, INT_MAX, "maxIntValue");
	insertHashMap(map, INT_MIN, "minIntValue");

	if (strcmp(getHashMap(map, INT_MAX), "maxIntValue") != 0 ||
		strcmp(getHashMap(map, INT_MAX), "maxIntValue") != 0) {
		printf("Edge Case Test 4 Failed: Large key handling failed\n");
	} else {
		printf("Edge Case Test 4 Passed: Large keys handled correctly\n");
	}

	destroyHashMap(map);
}

void edgeCaseTest5() {
	printf("Running Edge Case Test 5 (frequent insertions and deletions)...\n");
	HashMap *map = createHashMap();

	for (int i = 0; i < 1000; i++) {
		char value[20];
		snprintf(value, 20, "value%d", i);
		insertHashMap(map, i, value);

		if (!deleteHashMap(map, i)) {
			printf("Edge Case Test 5 Failed: Failed to delete key %d\n", i);
			destroyHashMap(map);
			return;
		}
	}

	printf("Edge Case Test 5 Passed: Frequent insertions and deletions handled correctly\n");

	destroyHashMap(map);
}

void edgeCaseTest6() {
	printf("Running Edge Case Test 6 (re-using deleted keys)...\n");
	HashMap *map = createHashMap();

	insertHashMap(map, 1, "firstValue");
	destroyHashMap(map);

	insertHashMap(map, 1, "secondValue");

	if (strcmp(getHashMap(map, 1), "secondValue") != 0) {
		printf("Edge Case Test 6 Failed: Re-using deleted key failed\n");
	} else {
		printf("Edge Case Test 6 Passed: Re-using deleted key handled correctly\n");
	}

	destroyHashMap(map);
}
