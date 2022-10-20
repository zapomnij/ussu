#include <dirent.h>
#include <signal.h>
#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include "cleanup.h"

#ifndef PERSIST_DISABLE
void cleanup() {
	DIR *d = opendir("/run/ussu");
	if (!d)
		return;

	struct dirent *dt = readdir(d);
	while (dt) {
		pid_t pid;
		sscanf(dt->d_name, "%u", &pid);
		if (kill(pid, 0)) {
			char path[PATH_MAX];
			sprintf(path, "/run/ussu/%s", dt->d_name);
			unlink(path);
		}

		dt = readdir(d);
	}
}

void fullclean() {
	DIR *d = opendir("/run/ussu");
	if (!d)
		return;

	struct dirent *dt = readdir(d);
	while (dt) {
		char path[PATH_MAX];
		sprintf(path, "/run/ussu/%s", dt->d_name);
		unlink(path);

		dt = readdir(d);
	}

	rmdir("/run/ussu");
}
#endif