/*
MIT License

Copyright (c) 2022 Jacek

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "util.h"
#include <stdlib.h>
#include <string.h>

// Free splitted text array
void split_free(char **buf) {
	unsigned long i = 0;
	for (; buf[i] != NULL; i++);
	free(buf[i + 1]);

	free(buf);
}

// Split string
char **split(const char *str, const char *splitter) {
	// Allocate string's array
	char **splitted = malloc(1 * sizeof(char *));
	if (!splitted) return NULL;
	size_t size = 1;
	long lenght = 0;

	// Duplicate string for splitting
	char *s = strdup(str);
	if (!s) {
		free(splitted);
		return NULL;
	}

	// Split first token
	char *token = strtok(s, splitter);
	while (token) {
		// Resize string's array, if it's not big enough to store splitted strings
		if (size == lenght) {
			size++;
			char **new = realloc(splitted, (size + 2) * sizeof(char *));
			if (!new) {
				free(splitted);
				free(s);
				return NULL;
			}
			splitted = new;
		}

		// Put token in string array
		splitted[lenght] = token;
		lenght++;

		// Next tokens
		token = strtok(NULL, splitter);
	}
	// Put NULL as signature of end of array
	splitted[lenght] = NULL;
	// Signature for deallocation which contains original memory address of duplicated string
	splitted[lenght + 1] = s;

	// Return splitted string
	return splitted;
}

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>

char *readFile(const char *path) {
	// Open file in read-only mode
	int fd = open(path, O_RDONLY);
	if (fd == -1) return NULL;

	// Get information about it
	struct stat st;
	if (fstat(fd, &st) == -1) {
		close(fd);
		return NULL;
	}

	// Allocate buffer of file size
	char *buf = malloc(st.st_size * sizeof(char));
	if (!buf) {
		close(fd);
		return NULL;
	}

	// Read file to allocated buffer
	if (read(fd, buf, st.st_size) != st.st_size) {
		close(fd);
		free(buf);
		return NULL;
	}

	// Close file and return buffer
	close(fd);
	return buf;
}

int touch(const char *path, mode_t perms) {
	// Open file in creation mode and close it
	int fd = open(path, O_RDONLY | O_CREAT, perms);
	if (fd == -1) {
		return -1;
	}

	close(fd);
	return 0;
}

// Function for checking if a path is a path to the file
bool is_file(const char *path) {
	struct stat st;
	if (stat(path, &st)) {
		return false;
	}

	return S_ISREG(st.st_mode);
}