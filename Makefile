CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude

OBJDIR = build
TEST_DIR = test_dir

# find all .c files in src and its subdirectories
SRCS = $(shell find src -name '*.c')
# create corresponding .o file names in build directory, preserving paths
OBJS = $(SRCS:src/%.c=$(OBJDIR)/%.o)

# test sources
TEST_SRCS = $(filter-out src/main.c, $(SRCS)) $(wildcard tests/*.c)
TEST_OBJS = $(TEST_SRCS:src/%.c=$(OBJDIR)/%.o)

TARGET = frame
TEST_TARGET = $(OBJDIR)/run_tests

all: $(TARGET) $(TEST_TARGET) run

# ensure the build directory exists
$(OBJDIR):
	@mkdir -p $(OBJDIR)

# ensure subdirectories in build/ mirror src/
$(OBJDIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# ensure subdirectories in build/ mirror tests/
$(OBJDIR)/%.o: tests/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# link all object files to create final executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# link test object files into the test executable
$(TEST_TARGET): $(TEST_OBJS)
	$(CC) $(CFLAGS) -o $(TEST_TARGET) $(TEST_OBJS)

# run tests in a separate test directory
run: $(TEST_TARGET)
	@mkdir -p $(TEST_DIR)
	./$(TEST_TARGET) $(TEST_DIR)
	@rm -rf $(TEST_DIR)

clean:
	rm -rf $(TARGET) $(OBJDIR) $(TEST_DIR)