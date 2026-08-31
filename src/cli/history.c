#include "cli/history.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h> // This is POSIX, not standard C, need to test for cross platform compatibility or explore options like minGW-w64 or gnulib
#include <time.h>

static char *read_history_tail(void) {
	FILE *f = fopen(MATHINATOR_HISTORY_FILE, "rb");
	if (!f)
		return NULL;
	// Going to EOF and getting file size
	if (fseek(f, 0, SEEK_END) != 0) {
		fclose(f);
		return NULL;
	}
	long pos = ftell(f);
	if (pos < 0) {
		fclose(f);
		return NULL;
	}

	// Allocating Buffer for Required History Window
	char *buf = malloc(MAX_HISTORY_FILESIZE + 1); // +1 Padding for '\0'
	if (!buf) {
		fclose(f);
		return NULL;
	}

	if (pos > MAX_HISTORY_FILESIZE) {
		// If file size > MAX_HISTORY_FILESIZE (240 KiB), jumping to last MAX_HISTORY_FILESIZE bytes window
		if (fseek(f, (pos - MAX_HISTORY_FILESIZE), SEEK_SET) != 0) {
			fclose(f);
			free(buf);
			buf = NULL;
			return NULL;
		}
		// In case landed in the middle of a line, discarding till a '\n' or EOF, start from fresh line without partial corruption
		int c;
		while ((c = fgetc(f)) != '\n' && c != EOF)
			; // discarding first partial entry
	} else {
		rewind(f); // same as fseek(f, 0L, SEEK_SET);
	}

	// Reading selected window into buffer
	size_t file_bytes = fread(buf, 1, MAX_HISTORY_FILESIZE, f);
	buf[file_bytes] = '\0';
	fclose(f);
	if (file_bytes == 0) {
		free(buf);
		buf = NULL;
		return NULL;
	}
	return buf;
}

static size_t fill_ring_buffer(char *buf, char **lines){
	// Counting total elements tokenized so far
	size_t total_count = 0;

	// Writing a MAX_HISTORY sized Ring Buffer 'lines' with each token delimited by '\n'
	char *token = strtok(buf, "\n");
	while (token != NULL) {
		lines[total_count % MAX_HISTORY] = token;
		total_count++;
		token = strtok(NULL, "\n");
	}

	return total_count;
}

static int write_trimmed_file(char **lines, size_t total_count){
	FILE *overwrite = fopen(MATHINATOR_HISTORY_TMP, "wb");
	if (!overwrite) return -1;

	size_t start = total_count % MAX_HISTORY; // Oldest retained line in ring buffer to start reading from

	for (size_t i = 0; i < MAX_HISTORY; i++) {
		// Writing temp file with each history lines from ring buffer
		if (fprintf(overwrite, "%s\n", lines[(start + i) % MAX_HISTORY]) < 0) {
			fclose(overwrite);
			remove(MATHINATOR_HISTORY_TMP); // Destroying temp file if any error occurs, retaining old log file
			return -1;
		}
	}
	fclose(overwrite);

	// Although rename() is atomic and doesn't require remove() in POSIX-like OS
	// Removing old Log file beforehand to make it portable with non-POSIX compliant OS like Windows as well
	remove(MATHINATOR_HISTORY_FILE); 
	if(rename(MATHINATOR_HISTORY_TMP, MATHINATOR_HISTORY_FILE) != 0){ // Replacing it with new Log file
		return -1;
	}
	return 0;
}

static int trim_history(void) {
	// Reading relevant part of history file
	char *buf = read_history_tail();
	if(!buf) return -1;

	// Tokenize buf by '\n' into ring buffer 'lines' containing each history log entry (capacity MAX_HISTORY)
	char *lines[MAX_HISTORY];
	size_t total_count = fill_ring_buffer(buf, lines);
	free(buf);
	buf = NULL;
	
	// Writing most newest MAX_HISTORY Logs
	if (total_count > MAX_HISTORY) return write_trimmed_file(lines, total_count);

	return 0;
}

int log_entry(int argc, char *argv[], result_t answer) {
	// Opening the history file in append mode
	FILE *file = fopen(MATHINATOR_HISTORY_FILE, "ab");
	if (file == NULL) {
		fprintf(stderr, "Error opening history file.\n");
		return -1;
	}

	// Getting the current time and formatting it for the log entry
	time_t now = time(NULL);
	struct tm *t = localtime(&now);
	if (!t) {
		fclose(file);
		return -1;
	}
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
	struct stat file_info;
	if (stat(MATHINATOR_HISTORY_FILE, &file_info) == 0) {
		if (file_info.st_size > MAX_HISTORY_FILESIZE)
			return trim_history();
	}
	return 0;
}