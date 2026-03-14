#ifndef MATHINATOR_CLI_HISTORY_H
#define MATHINATOR_CLI_HISTORY_H

#include "core/types.h"

// Defining maximum history size
#define MAX_HISTORY 1000
#define MAX_HISTORY_FILESIZE (240 * 1024) // 240 KB

// Defining the history file name
#define HISTORY_BASENAME "mathinator_history"
#define MATHINATOR_HISTORY_FILE HISTORY_BASENAME ".log"
#define MATHINATOR_HISTORY_TMP HISTORY_BASENAME ".tmp"
/* TODO: resolve history file to absolute path beside executable
   or user home dir for cross-platform portability */

int log_entry(int argc, char* argv[], result_t answer);
void show_history(int n);

#endif // MATHINATOR_CLI_HISTORY_H