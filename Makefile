CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude

OBJDIR = build
TEST_DIR = test_dir

# capture all .c files in src and src/commands
SRCS = $(wildcard src/*.c) $(wildcard src/commands/*.c)
OBJS = $(patsubst %.c,$(OBJDIR)/%.o,$(notdir $(SRCS)))
TARGET = frame

# test sources
TEST_SRCS = $(filter-out src/main.c, $(SRCS)) $(wildcard tests/*.c)
TEST_OBJS = $(patsubst %.c,$(OBJDIR)/%.o,$(notdir $(TEST_SRCS)))
TEST_TARGET = $(OBJDIR)/run_tests

all: $(TARGET) $(TEST_TARGET) run

# create directories
$(OBJDIR):
	@mkdir -p $(OBJDIR)

# compile source files to object files in OBJDIR
$(OBJDIR)/%.o: src/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $(OBJDIR)/$(notdir $@)

$(OBJDIR)/%.o: src/commands/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $(OBJDIR)/$(notdir $@)

# compile test source files to object files in OBJDIR
$(OBJDIR)/%.o: tests/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $(OBJDIR)/$(notdir $@)

# link the object files to create the final executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# link the object files for tests
$(TEST_TARGET): $(TEST_OBJS)
	$(CC) $(CFLAGS) -o $(TEST_TARGET) $(TEST_OBJS)

# run tests in a separate test directory
run: $(TEST_TARGET)
	@mkdir -p $(TEST_DIR)
	./$(TEST_TARGET) $(TEST_DIR)
	@rm -rf $(TEST_DIR)

clean:
	rm -rf $(TARGET) $(OBJDIR) $(TEST_DIR)