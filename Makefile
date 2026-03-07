# ======================================
# Math-inator — Cross-Platform Makefile
# ======================================

# --- Compiler ------------------------------------------------------------------
CC = gcc

# --- Flags --------------------------------------------------------------------
CFLAGS_COMMON  = -Wall -Wextra -Iinclude -std=c11
CFLAGS_DEBUG   = $(CFLAGS_COMMON) -g -O0
CFLAGS_RELEASE = $(CFLAGS_COMMON) -O2

# --- Source Files --------------------------------------------------------------
SRC = src/main.c \
      src/arithmetic.c \
      src/trigo.c \
      src/stats.c \
      src/history.c

# --- OS Detection --------------------------------------------------------------
ifeq ($(OS), Windows_NT)
    TARGET  = build/mathinator.exe
    MKDIR   = if not exist build mkdir build
    RM      = cmd /C del /Q /F
else
    TARGET  = build/mathinator
    MKDIR   = mkdir -p build
    RM      = rm -f
endif

# --- Phony Targets -------------------------------------------------------------
.PHONY: all release debug clean help

# --- Default Target ------------------------------------------------------------
all: release

# --- Ensure build directory exists --------------------------------------------
build:
	$(MKDIR)

# --- Release Build -------------------------------------------------------------
release: build
	$(CC) $(SRC) $(CFLAGS_RELEASE) -o $(TARGET) -lm
	@echo [Release build complete] $(TARGET)

# --- Debug Build ---------------------------------------------------------------
debug: build
	$(CC) $(SRC) $(CFLAGS_DEBUG) -o $(TARGET) -lm
	@echo [Debug build complete] $(TARGET)

# --- Clean --------------------------------------------------------------------
clean:
	$(RM) $(TARGET)
	@echo [Clean complete]

# --- Help ---------------------------------------------------------------------
help:
	@echo Available targets:
	@echo   make release  (default) - optimized build
	@echo   make debug              - build with GDB debug symbols
	@echo   make clean              - remove build artifacts