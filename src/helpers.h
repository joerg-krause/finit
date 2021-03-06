/* Misc. utility functions and C-library extensions for finit and its plugins
 *
 * Copyright (c) 2008-2010  Claudio Matsuoka <cmatsuoka@gmail.com>
 * Copyright (c) 2008-2015  Joachim Nilsson <troglobit@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef FINIT_HELPERS_H_
#define FINIT_HELPERS_H_

#include <sys/types.h>
#include <lite/lite.h>
#include "log.h"

#ifndef HAVE_GETFSENT
struct fstab {
	char       *fs_spec;       /* block device name */
	char       *fs_file;       /* mount point */
	char       *fs_vfstype;    /* file-system type */
	char       *fs_mntops;     /* mount options */
	const char *fs_type;       /* rw/rq/ro/sw/xx option */
	int         fs_freq;       /* dump frequency, in days */
	int         fs_passno;     /* pass number on parallel dump */
};

int           setfsent  (void);
void          endfsent  (void);
struct fstab *getfsent  (void);
#endif	/* HAVE_GETFSENT */

char   *strip_line      (char *line);

int     pid_alive       (pid_t pid);
char   *pid_get_name    (pid_t pid, char *name, size_t len);

void    printv          (const char *fmt, va_list ap);
void    print           (int action, const char *fmt, ...);
void    print_desc      (char *action, char *desc);
int     print_result    (int fail);

int     start_process   (char *cmd, char *args[], int console);
int     getuser         (char *username, char **home);
int     getgroup        (char *group);
void    set_hostname    (char **hostname);

int     complete        (char *cmd, int pid);
int     run             (char *cmd);
int     run_interactive (char *cmd, char *fmt, ...);
int     exec_runtask    (char *cmd, char *args[]);
pid_t   run_getty       (char *tty, char *speed, char *term, int noclear, int nowait, int console);
pid_t   run_getty2      (char *tty, char *cmd, char *args[], int noclear, int nowait, int console);
int     run_parts       (char *dir, char *cmd);

static inline void create(char *path, mode_t mode, uid_t uid, gid_t gid)
{
	if (touch(path) || chmod(path, mode) || chown(path, uid, gid))
		_w("Failed creating %s properly.", path);
}

#endif /* FINIT_HELPERS_H_ */

/**
 * Local Variables:
 *  indent-tabs-mode: t
 *  c-file-style: "linux"
 * End:
 */
