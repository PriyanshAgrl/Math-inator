# ============================================================
# Math-inator — Cross-Platform Makefile
# Supports: Windows (MinGW/mingw32-make) and Linux (GCC/make)
# Usage:
#   mingw32-make         → release build (default)
#   mingw32-make debug   → debug build (with GDB symbols)
#   mingw32-make clean   → remove build artifacts
#   mingw32-make help    → show available targets
# ============================================================

# --- Compiler ------------------------------------------------------------------
CC = gcc

# --- Flags --------------------------------------------------------------------
CFLAGS_COMMON  = -Wall -Wextra -Iinclude -std=c11
CFLAGS_DEBUG   = $(CFLAGS_COMMON) -g -O0
CFLAGS_RELEASE = $(CFLAGS_COMMON) -O2

# --- Source Files --------------------------------------------------------------
SRC = src/main.c \
	src/math/arithmetic.c \
	src/math/trigo.c \
	src/math/stats.c \
	src/cli/history.c \
	src/cli/parser.c \
	src/core/types.c

# --- OS Detection --------------------------------------------------------------
EXE_NAME = mathinator

ifeq ($(OS), Windows_NT)
	TARGET_DEBUG   = build/debug/$(EXE_NAME).exe
	TARGET_RELEASE = build/release/$(EXE_NAME).exe
	RM_DEBUG       = rm -f build/debug/$(EXE_NAME).exe
	RM_RELEASE     = rm -f build/release/$(EXE_NAME).exe
else
	TARGET_DEBUG   = build/debug/$(EXE_NAME)
	TARGET_RELEASE = build/release/$(EXE_NAME)
	RM_DEBUG       = rm -f build/debug/$(EXE_NAME)
	RM_RELEASE     = rm -f build/release/$(EXE_NAME)
endif

# These are now identical on both platforms
MKDIR_DEBUG   = mkdir -p build/debug
MKDIR_RELEASE = mkdir -p build/release

# --- Phony Targets -------------------------------------------------------------
.PHONY: all release debug clean help

# --- Default Target ------------------------------------------------------------
all: release

# --- Release Build ------------------------------------------------------------
release:
	$(MKDIR_RELEASE)
	$(CC) $(SRC) $(CFLAGS_RELEASE) -o $(TARGET_RELEASE) -lm
	@echo [Release build complete] $(TARGET_RELEASE)

# --- Debug Build --------------------------------------------------------------
debug:
	$(MKDIR_DEBUG)
	$(CC) $(SRC) $(CFLAGS_DEBUG) -o $(TARGET_DEBUG) -lm
	@echo [Debug build complete] $(TARGET_DEBUG)

# --- Clean --------------------------------------------------------------------
clean:
	-$(RM_DEBUG)
	-$(RM_RELEASE)
	@echo [Clean complete]

# --- Help ---------------------------------------------------------------------
help:
	@echo Available targets:
	@echo   make release  (default) - optimized build
	@echo   make debug              - build with GDB debug symbols
	@echo   make clean              - remove build artifacts