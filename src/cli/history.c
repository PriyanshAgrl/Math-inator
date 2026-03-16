#include "cli/history.h"
#include <stdio.h>
#include <time.h>
#include <sys/stat.h> // This is POSIX, not standard C, need to test for cross platform compatibility

static void trim_history(void)
{
  FILE *f = fopen(MATHINATOR_HISTORY_FILE, "rb");
  if (!f)
    return;

  fseek(f, 0, SEEK_END);
  long pos = ftell(f);
  if (pos < 0)
  {
    fclose(f);
    return;
  }
  char *buf = malloc(MAX_HISTORY_FILESIZE + 1);
  if (!buf) // buf == NULL
  {
    fclose(f);
    return;
  }
  if (pos > MAX_HISTORY_FILESIZE)
  {
    fseek(f, (pos - MAX_HISTORY_FILESIZE), SEEK_SET);
    int c;
    while ((c = fgetc(f)) != '\n' && c != EOF)
      ; // discarding first partial entry
  }
  else
  {
    rewind(f); // same as fseek(f, 0L, SEEK_SET);
  }
  size_t file_bytes = fread(buf, 1, MAX_HISTORY_FILESIZE, f);
  buf[file_bytes] = '\0';
  fclose(f);
  if (file_bytes == 0)
  {
    free(buf);
    buf = NULL;
    return;
  }
  char **lines = malloc((MAX_HISTORY + 1) * sizeof(char *)); // plus some margin to be incorporated
  if (!lines)
  { // lines == NULL
    free(buf);
    buf = NULL;
    return;
  }
  int n = 0;
  char *token = strtok(buf, "\n");
  while (token != NULL && n < MAX_HISTORY + 1)
  {
    lines[n++] = token;
    token = strtok(NULL, "\n");
  }
  if (n <= MAX_HISTORY)
  {
    free(lines);
    free(buf);
    lines = NULL;
    buf = NULL;
    return;
  }

  FILE *overwrite = fopen(MATHINATOR_HISTORY_TMP, "wb");
  if (!overwrite)
  {
    free(lines);
    free(buf);
    lines = NULL;
    buf = NULL;
    return;
  }

  for (int i = n - MAX_HISTORY; i < n; i++)
  {
    if (fprintf(overwrite, "%s\n", lines[i]) < 0)
    {
      fclose(overwrite);
      free(lines);
      free(buf);
      lines = NULL;
      buf = NULL;
      remove(MATHINATOR_HISTORY_TMP);
      return;
    }
  }
  fclose(overwrite);
  free(lines);
  free(buf);
  lines = NULL;
  buf = NULL;
  remove(MATHINATOR_HISTORY_FILE);
  rename(MATHINATOR_HISTORY_TMP, MATHINATOR_HISTORY_FILE);
  return;
}

int log_entry(int argc, char *argv[], result_t answer)
{
  // Opening the history file in append mode
  FILE *file = fopen(MATHINATOR_HISTORY_FILE, "ab");
  if (file == NULL)
  {
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
  for (int i = 1; i < argc; i++)
  {
    fprintf(file, "%s%s", argv[i], (i != argc - 1) ? " " : "");
  }
  fprintf(file, ">>> %g\n", answer.result_val);

  // Close the file
  fclose(file);

  /* check file size */
  struct stat st;
  if (stat(MATHINATOR_HISTORY_FILE, &st) == 0)
  {
    if (st.st_size > MAX_HISTORY_FILESIZE)
      trim_history();
  }
  return 0;
}