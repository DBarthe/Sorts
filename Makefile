
CC ?= clang

INCPATH := ./include
SRCPATH := ./src

CFLAGS := -Wall -Wextra -I $(INCPATH)/ -DINLINE=inline
LDFLAGS := 
OFLAGS := -O3
DBGFLAGS := -ggdb3 -DDEBUG
NDBGFLAGS := -DNDEBUG


MODULES := heapsort quicksort mergesort

SRC := $(foreach module,$(MODULES),$(wildcard $(SRCPATH)/$(module)/*.c))
OBJ := $(SRC:.c=.o)

AR := ar -rc
RM := rm -vf

TARGET := libSort.a

TEST_PATH := ./test
TEST_SRC := $(wildcard $(TEST_PATH)/*.c)
TEST_TARGET_PRE := $(TEST_PATH)/test
TEST_SCRIPT := test.sh

default: CFLAGS += $(NDBGFLAGS) $(OFLAGS)
default: $(TARGET)

infos: CFLAGS += -DINFOS
infos: default

debug: CFLAGS += $(DBGFLAGS)
debug: $(TARGET)

$(TARGET): $(OBJ)
	$(AR) $(TARGET) $(OBJ)

clean:
	@$(RM) $(OBJ)
fclean:	clean
	@$(RM) $(TARGET)


re:	fclean default
re-infos: fclean infos
re-debug: fclean debug

tests:
	$(foreach module,$(MODULES),$(CC) -I $(INCPATH) $(PRINT_FLAG) -DFUNCTION_NAME=$(module) -o $(TEST_TARGET_PRE)_$(module) $(TEST_SRC) $(TARGET);)
