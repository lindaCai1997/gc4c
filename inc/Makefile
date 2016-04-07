OBJS_DIR = .objs

# define all of student executables
EXE1=dataStructure
EXE2=test
EXES_STUDENT=$(EXE1) $(EXE2)

# list object file dependencies for each
OBJS_PART1=dataStructure.o dataStructure_test.o
OBJS_PART2=test.o malloc.o mark_and_sweep.o dataStructure.o

# set up compiler
CC = gcc
WARNINGS = -Wall Wno-error=unused-parameter

CFLAGS_DEBUG   = -O0 $(WARNINGS) -g -std=c99 -c -MMD -MP -D_GNU_SOURCE -lpthread
CFLAGS_RELEASE = -O2 $(WARNINGS)    -std=c99 -c -MMD -MP -D_GNU_SOURCE -lpthread

# set up linker
LD = gcc
LDFLAGS = -lpthread

.PHONY: all
all: release

# build types
.PHONY: release
.PHONY: debug

release: $(EXES_STUDENT)
debug:   clean $(EXES_STUDENT:%=%-debug)

# include dependencies
-include $(OBJS_DIR)/*.d

$(OBJS_DIR):
    @mkdir -p $(OBJS_DIR)

# patterns to create objects
# keep the debug and release postfix for object files so that we can always
# separate them correctly
$(OBJS_DIR)/%-debug.o: %.c | $(OBJS_DIR)
    $(CC) $(CFLAGS_DEBUG) $< -o $@

$(OBJS_DIR)/%-release.o: %.c | $(OBJS_DIR)
    $(CC) $(CFLAGS_RELEASE) $< -o $@

# exes
# you will need a pair of exe and exe-debug targets for each exe
$(EXE1)-debug: $(OBJS_PART1:%.o=$(OBJS_DIR)/%-debug.o)
    $(LD) $^ $(LDFLAGS) -o $@

$(EXE1): $(OBJS_PART1:%.o=$(OBJS_DIR)/%-release.o)
    $(LD) $^ $(LDFLAGS) -o $@

$(EXE2)-debug: $(OBJS_PART2:%.o=$(OBJS_DIR)/%-debug.o)
    $(LD) $^ $(LDFLAGS) -o $@

$(EXE2): $(OBJS_PART2:%.o=$(OBJS_DIR)/%-release.o)
    $(LD) $^ $(LDFLAGS) -o $@

.PHONY: clean
clean:
    rm -rf .objs $(EXES_STUDENT) $(EXES_STUDENT:%=%-debug)
