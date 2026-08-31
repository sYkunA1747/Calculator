CC=gcc
CFLAGS= -Wall -Wextra -Werror -std=c99 -g -Wpedantic -Wshadow -Wformat=2 -fstack-protector-strong -D_FORTIFY_SOURCE=2 -D_POSIX_C_SOURCE=200809L -O2 -MMD -MP
LDFLAGS=-lm
DEBUG_FLAGS= -O0 -g3 -fsanitize=address,undefined -fno-omit-frame-pointer
RELEASE_FLAGS= -O3 -DNDEBUG -march=native

TARGET_APP=calculator
TARGET_TEST=run_math_test
SRC_DIR=src
OBJ_DIR=obj
TEST_DIR=test

SRCS = $(shell find $(SRC_DIR) -name "*.c")
OBJS_COMMON = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(filter-out $(SRC_DIR)/main/main.c, $(SRCS)))

TEST_SRCS = $(shell find $(TEST_DIR) -name "*.c" ! -name "mainTest.c")
TEST_OBJS = $(patsubst $(TEST_DIR)/%.c, $(OBJ_DIR)/test/%.o, $(TEST_SRCS))

all: $(TARGET_APP) $(TARGET_TEST)

debug: CFLAGS += $(DEBUG_FLAGS)
debug: clean all

release: CFLAGS += $(RELEASE_FLAGS)
release: clean all

test: $(TARGET_TEST)
	./$(TARGET_TEST)

valgrind_test: $(TARGET_TEST)
	valgrind --leak-check=full --error-exitcode=1 ./$(TARGET_TEST)

valgrind_main: $(TARGET_APP)
	valgrind --leak-check=full --error-exitcode=1 ./$(TARGET_APP)


$(TARGET_APP): $(OBJS_COMMON) $(OBJ_DIR)/main/main.o
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

$(TARGET_TEST): $(OBJS_COMMON) $(TEST_OBJS) $(OBJ_DIR)/test/mainTest.o
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/test/%.o: $(TEST_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	rm -rf $(OBJ_DIR) $(TARGET_APP) $(TARGET_TEST)

check:
	cppcheck --enable=all --inconclusive --std=c99 --suppress=missingIncludeSystem $(SRC_DIR)/ $(TEST_DIR)/

format:
	clang-format -i $(SRCS) $(shell find $(TEST_DIR) -name "*.c") $(shell find . -name "*.h")

format-check:
	clang-format --dry-run --Werror $(SRCS) $(shell find $(TEST_DIR) -name "*.c") $(shell find . -name "*.h")	

-include $(OBJS_COMMON:.o=.d)
-include $(TEST_OBJS:.o=.d)
-include $(OBJ_DIR)/main/main.d
-include $(OBJ_DIR)/test/mainTest.d

.PHONY: all clean check format format-check debug release test valgrind_test valgrind_main

