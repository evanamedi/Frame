CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude

OBJDIR = build
TEST_OBJDIR = build_tests

SRCS = $(wildcard src/*.c)
OBJS = $(patsubst src/%.c,$(OBJDIR)/%.o,$(SRCS))
TARGET = frame

TEST_SRCS = $(filter-out src/main.c, $(SRCS)) $(wildcard tests/*.c)
TEST_OBJS = $(patsubst src/%.c,$(TEST_OBJDIR)/%.o,$(filter-out tests/%.c, $(TEST_SRCS)))
TEST_OBJS += $(patsubst tests/%.c,$(TEST_OBJDIR)/%.o,$(wildcard tests/*.c))
TEST_TARGET = $(TEST_OBJDIR)/run_tests

all: $(TARGET) $(TEST_TARGET) run

$(OBJDIR)/%.o: src/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST_OBJDIR)/%.o: tests/%.c
	@mkdir -p $(TEST_OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST_OBJDIR)/%.o: src/%.c
	@mkdir -p $(TEST_OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

$(TEST_TARGET): $(TEST_OBJS)
	@mkdir -p $(TEST_OBJDIR)
	$(CC) $(CFLAGS) -o $(TEST_TARGET) $(TEST_OBJS)

run: $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	rm -rf $(TARGET) $(OBJDIR) $(TEST_OBJDIR)