CC=gcc
CFLAGS= -fPIE -Wall -Wextra -Werror -std=c99 -g -Wpedantic -Wshadow -Wformat=2 -fstack-protector-strong -D_FORTIFY_SOURCE=2 -D_POSIX_C_SOURCE=200809L -O2 -MMD -MP
LDFLAGS=-pie -Wl,-z,relro -Wl,-z,now -lm
DEBUG_FLAGS= -O1 -g3 -fsanitize=address,undefined -fno-omit-frame-pointer
RELEASE_FLAGS= -O3 -DNDEBUG -march=native


LOG_TIME = $(shell date +%Y-%m-%d_%H-%M-%S)


TARGET_APP=calculator
TARGET_TEST=run_math_test
SRC_DIR=src
OBJ_DIR=obj
TEST_DIR=test

FUZZ_TARGET = fuzz_calculator
FUZZ_DIR = fuzz

SRCS = $(shell find $(SRC_DIR) -name "*.c")
OBJS_COMMON = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(filter-out $(SRC_DIR)/main/main.c, $(SRCS)))

TEST_SRCS = $(shell find $(TEST_DIR) -name "*.c" ! -name "mainTest.c")
TEST_OBJS = $(patsubst $(TEST_DIR)/%.c, $(OBJ_DIR)/test/%.o, $(TEST_SRCS))

all: $(TARGET_APP) $(TARGET_TEST)

fuzz: $(FUZZ_TARGET)
	@mkdir -p logs
	@echo "Запуск фаззинга белого ящика... Лог пишется в logs/fuzz_$(LOG_TIME).log"
	./$(FUZZ_TARGET) fuzz/corpus -max_total_time=60 -max_len=128 > logs/fuzz_$(LOG_TIME).log 2>&1

$(FUZZ_TARGET): $(FUZZ_DIR)/fuzz_main.c $(SRCS)
	clang -fsanitize=fuzzer,address,undefined -g -O1 -D_POSIX_C_SOURCE=200809L \
		$(filter-out src/main/main.c, $(SRCS)) $< -lm -o $@

debug: CFLAGS += $(DEBUG_FLAGS)
debug: clean all

release: CFLAGS += $(RELEASE_FLAGS)
release: clean all

test: $(TARGET_TEST)
	@mkdir -p logs
	./$(TARGET_TEST) > logs/test_log$(LOG_TIME).log 2>&1


tree:
	@echo "=== АВТОМАТИЧЕСКАЯ ГЕНЕРАЦИЯ СТРУКТУРЫ ПРОЕКТА ==="
	@echo "" >> README.md
	@echo "\`\`\`" >> README.md
	@find . -not -path '*/.*' -not -path './obj*' -not -path './logs*' -not -path './fuzz/corpus*' -not -path './README.md' -not -name 'calculator' -not -name 'run_math_test' -not -name 'fuzz_calculator' | sort | sed -e 's|^\./||' -e 's|[^/]*/|  |g' -e 's|  \([^ ]\)|├── \1|' >> README.md
	@echo "\`\`\`" >> README.md
	@echo "✨ Дерево проекта успешно достроено и вшито в конец README.md!"

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
	rm -rf $(OBJ_DIR) $(TARGET_APP) $(TARGET_TEST) $(FUZZ_TARGET)

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

.PHONY: all clean check format format-check debug release test valgrind_test valgrind_main fuzz
