#include "cli/history.h"
#include <stdio.h>
#include <time.h>
#include <sys/stat.h> // This is POSIX, not standard C, need to test for cross platform compatibility

static void trim_history(void) {
    FILE *f = fopen(MATHINATOR_HISTORY_FILE, "r");
    if (!f)
        return;

    fseek(f, 0, SEEK_END);
    long pos = ftell(f);
    char *buf = (char*)malloc(MAX_HISTORY_FILESIZE);
    if (buf == NULL) {
      fclose(f);
      return;
    }
    rewind(f); // same as fseek(f, 0, SEEK_SET)
    size_t file_bytes = fread(buf, 1, pos, f);
    buf[pos] = '\0';
    if (file_bytes < (size_t)pos) { //pos should not negative
      fclose(f);
      free(buf);
      return;
    }
    fclose(f);
    char** lines = malloc((MAX_HISTORY + 2) * sizeof(char *)); // plus some margin to be incorporated
    int n = 0;
    char* token = strtok(buf, "\n");
    while (token != NULL && n < MAX_HISTORY + 1) {
      lines[n++] = token;
      token = strtok(NULL, "\n");
    }
    if (n <= MAX_HISTORY){
      free(lines);
      free(buf);
      return;
    }

    FILE *overwrite = fopen(MATHINATOR_HISTORY_TMP, "w");
    if (!overwrite) {
      free(buf);
        return;
    }

    for (int i = n - MAX_HISTORY; i < n; i++){
      fprintf(overwrite, "%s\n", lines[i]);
    }
    fclose(overwrite);
    free(lines);
    free(buf);
    remove(MATHINATOR_HISTORY_FILE);
    rename(MATHINATOR_HISTORY_TMP,MATHINATOR_HISTORY_FILE);
    return;
}

int log_entry(int argc, char *argv[], result_t answer) {
    // Opening the history file in append mode
    FILE *file = fopen(MATHINATOR_HISTORY_FILE, "a");
    if (file == NULL) {
        fprintf(stderr, "Error opening history file.\n");
        return -1;
    }
    // Getting the current time and formatting it for the log entry
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    fprintf(file, "[%04d-%02d-%02d %02d:%02d:%02d] ",
            t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
            t->tm_hour, t->tm_min, t->tm_sec);

    // Logging the command and result to the history file
    for (int i = 1; i < argc; i++) {
        fprintf(file, "%s%s", argv[i], (i != argc - 1) ? " " : "");
    }
    fprintf(file, ">>> %g\n", answer.result_val);

    // Close the file
    fclose(file);

    /* check file size */
    struct stat st;
  if (stat(MATHINATOR_HISTORY_FILE, &st) == 0){
    if (st.st_size > MAX_HISTORY_FILESIZE) trim_history();
  }
    return 0;
}