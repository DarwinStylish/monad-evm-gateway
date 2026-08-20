CC       = gcc
CFLAGS = -O3 -Wall -Wextra -Werror -std=c11 -fstack-protector-strong -D_FORTIFY_SOURCE=2
CORE_INC = ../../engine/private/include
INCLUDES = -I$(CORE_INC)

BUILD_DIR = build

TEST_MONAD = $(BUILD_DIR)/test_monad_evm

.PHONY: all test clean

all: $(TEST_MONAD)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(TEST_MONAD): tests/test_monad_evm.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) $< -o $@

test: $(TEST_MONAD)
	@$(TEST_MONAD)

clean:
	rm -rf $(BUILD_DIR)
