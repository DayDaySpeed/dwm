#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>
#include <X11/Xlib.h>

#define LENGTH(X)      (sizeof(X) / sizeof(X[0]))
#define CMDLENGTH      64
#define STATUSLENGTH   512
#define TICK_US          50000
#define TICKS_PER_SEC    10
#define MAX_SIGNAL       32
#define SCROLL_STEP_MAX  24
#define SCROLL_BTN4      4
#define SCROLL_BTN5      5

typedef struct {
	char *icon;
	char *command;
	unsigned int interval;
	unsigned int signal;
} Block;

void remove_all(char *str, char c);
void getcmds(int time);
#ifndef __OpenBSD__
void sighandler(int signum, siginfo_t *si, void *ucontext);
void setupsignals(void);
void processpending(void);
#endif
int getstatus(char *str, char *last);
void setroot(void);
void statusloop(void);
void termhandler(int signum);
void chldhandler(int signum);

#include "config.h"

static Display *dpy;
static Window root;
static char statusbar[LENGTH(blocks)][CMDLENGTH];
static char statusstr[2][STATUSLENGTH];
static int statusContinue = 1;
static int xdisplay_open;
static void (*writestatus)(void) = setroot;

#ifndef __OpenBSD__
static volatile sig_atomic_t pending_mask;
static volatile sig_atomic_t pending_click_mask;
static volatile sig_atomic_t scroll_steps[MAX_SIGNAL];
static sigset_t blocksigs;

static const char *scrollable_cmds[] = { "brightness", "volume", "mic" };

static int
block_scrollable(int i)
{
	const char *cmd = blocks[i].command;

	for (size_t j = 0; j < LENGTH(scrollable_cmds); j++)
		if (!strcmp(cmd, scrollable_cmds[j]))
			return 1;
	return 0;
}

static void
clamp_scroll(int sig, int delta)
{
	int cur = scroll_steps[sig] + delta;

	if (cur > SCROLL_STEP_MAX)
		cur = SCROLL_STEP_MAX;
	else if (cur < -SCROLL_STEP_MAX)
		cur = -SCROLL_STEP_MAX;
	scroll_steps[sig] = cur;
	pending_mask |= (1U << sig);
}

static void
exec_click(int i, int btn)
{
	char button[2] = { '0' + btn, '\0' };
	char *cmd[] = { "/bin/sh", "-c", blocks[i].command, NULL };
	int nullfd = open("/dev/null", O_WRONLY);

	if (nullfd >= 0) {
		dup2(nullfd, STDOUT_FILENO);
		dup2(nullfd, STDERR_FILENO);
		if (nullfd > STDERR_FILENO)
			close(nullfd);
	}

	setenv("BUTTON", button, 1);
	setsid();
	execvp(cmd[0], cmd);
	perror(cmd[0]);
	_exit(EXIT_FAILURE);
}
#endif

static int
blockindex(unsigned int signal)
{
	for (unsigned int i = 0; i < LENGTH(blocks); i++)
		if (blocks[i].signal == signal)
			return i;
	return -1;
}

void
remove_all(char *str, char c)
{
	char *r = str, *w = str;

	while (*r) {
		if (*r != c)
			*w++ = *r;
		r++;
	}
	*w = '\0';
}

void
getcmd(const Block *block, char *output)
{
	char *base = output;
	int maxlen, i;

	output[0] = '\0';
	if (block->signal)
		*output++ = block->signal;
	strcpy(output, block->icon);

	maxlen = CMDLENGTH - 1 - (int)(output - base);
	if (maxlen < 1)
		return;

	FILE *cmdf = popen(block->command, "r");
	if (!cmdf)
		return;

	i = strlen(output);
	if (fgets(output + i, maxlen - i + 1, cmdf)) {
		remove_all(output, '\n');
		i = strlen(output);
		if (delim && delim[0] && i > 0 && block != &blocks[LENGTH(blocks) - 1]) {
			size_t rem = CMDLENGTH - (size_t)strlen(output) - 1;

			if (rem > 0)
				strncat(output, delim, rem);
		}
	}
	pclose(cmdf);
}

#ifndef __OpenBSD__
static void
refresh_block(unsigned int i)
{
	unsigned int sig = blocks[i].signal;
	int steps = scroll_steps[sig];

	if (!steps) {
		getcmd(&blocks[i], statusbar[i]);
		return;
	}

	char env[16];

	scroll_steps[sig] = 0;
	snprintf(env, sizeof(env), "%d", steps);
	setenv("SCROLL_STEPS", env, 1);
	unsetenv("BUTTON");
	getcmd(&blocks[i], statusbar[i]);
	unsetenv("SCROLL_STEPS");
	if (scroll_steps[sig])
		pending_mask |= (1U << sig);
}
#endif

void
getcmds(int time)
{
	for (unsigned int i = 0; i < LENGTH(blocks); i++) {
		const Block *b = &blocks[i];

		if ((b->interval && time % (int)b->interval == 0) || time == -1)
			getcmd(b, statusbar[i]);
	}
}

#ifndef __OpenBSD__
void
processpending(void)
{
	unsigned int mask;
	sigset_t old;

	if (!pending_mask)
		return;

	mask = pending_mask;
	pending_mask = 0;

	sigprocmask(SIG_BLOCK, &blocksigs, &old);
	for (unsigned int i = 0; i < LENGTH(blocks); i++) {
		unsigned int sig = blocks[i].signal;

		if (sig && (mask & (1U << sig)))
			refresh_block(i);
	}
	sigprocmask(SIG_SETMASK, &old, NULL);

	writestatus();
}

void
dummysighandler(int signum)
{
	(void)signum;
}

void
setupsignals(void)
{
	struct sigaction sa = { .sa_sigaction = sighandler, .sa_flags = SA_SIGINFO };
	struct sigaction chld = { .sa_handler = chldhandler, .sa_flags = SA_NOCLDWAIT };

	sigemptyset(&blocksigs);
	for (int i = SIGRTMIN; i <= SIGRTMAX; i++) {
		signal(i, dummysighandler);
		sigaddset(&blocksigs, i);
	}

	for (unsigned int i = 0; i < LENGTH(blocks); i++) {
		if (blocks[i].signal > 0)
			sigaction(SIGRTMIN + blocks[i].signal, &sa, NULL);
	}

	sigaction(SIGCHLD, &chld, NULL);
}

void
sighandler(int signum, siginfo_t *si, void *ucontext)
{
	(void)ucontext;
	int sig = signum - SIGRTMIN;

	if (sig < 0 || sig >= MAX_SIGNAL)
		return;

	if (si->si_value.sival_int) {
		int btn = si->si_value.sival_int & 0xff;
		int i = blockindex(sig);
		pid_t pid;

		if (i < 0)
			return;

		/* Coalesce fast wheel: adjust in one script run, no fork storm */
		if (btn == SCROLL_BTN4 || btn == SCROLL_BTN5) {
			if (!block_scrollable(i))
				return;
			clamp_scroll(sig, btn == SCROLL_BTN4 ? 1 : -1);
			return;
		}

		/* Ignore click repeat while this block's handler is still running */
		if (pending_click_mask & (1U << sig))
			return;

		pending_click_mask |= (1U << sig);
		pid = fork();
		if (pid != 0) {
			if (pid < 0)
				pending_click_mask &= ~(1U << sig);
			return;
		}

		exec_click(i, btn);
	}

	pending_mask |= (1U << sig);
}
#endif

int
getstatus(char *str, char *last)
{
	size_t len = 0;

	/* Save previous str so strcmp detects real changes (required for setroot). */
	strcpy(last, str);
	str[0] = '\0';
	for (unsigned int i = 0; i < LENGTH(blocks); i++) {
		size_t n = strlen(statusbar[i]);

		if (n == 0)
			continue;
		if (len + n >= STATUSLENGTH - 1)
			break;
		strcat(str, statusbar[i]);
		len += n;
	}
	return strcmp(str, last);
}

void
setroot(void)
{
	if (!getstatus(statusstr[0], statusstr[1]))
		return;

	if (!dpy) {
		int screen;

		dpy = XOpenDisplay(NULL);
		if (!dpy)
			return;
		xdisplay_open = 1;
		screen = DefaultScreen(dpy);
		root = RootWindow(dpy, screen);
	}
	if (!XStoreName(dpy, root, statusstr[0])) {
		XCloseDisplay(dpy);
		dpy = NULL;
		xdisplay_open = 0;
		return;
	}
	XFlush(dpy);
}

void
pstdout(void)
{
	if (!getstatus(statusstr[0], statusstr[1]))
		return;
	printf("%s\n", statusstr[0]);
	fflush(stdout);
}

void
chldhandler(int signum)
{
	(void)signum;

	while (waitpid(-1, NULL, WNOHANG) > 0)
		;
#ifndef __OpenBSD__
	if (pending_click_mask) {
		pending_mask |= pending_click_mask;
		pending_click_mask = 0;
	}
	processpending();
#endif
}

void
statusloop(void)
{
#ifndef __OpenBSD__
	sigset_t old;

	setupsignals();
#endif
	int sec = 0;

	getcmds(-1);
	writestatus();

	while (statusContinue) {
		for (int t = 0; t < TICKS_PER_SEC && statusContinue; t++) {
#ifndef __OpenBSD__
			processpending();
#endif
			usleep(TICK_US);
		}
#ifndef __OpenBSD__
		sigprocmask(SIG_BLOCK, &blocksigs, &old);
#endif
		getcmds(sec);
		writestatus();
#ifndef __OpenBSD__
		sigprocmask(SIG_SETMASK, &old, NULL);
		processpending();
#endif
		sec++;
	}
}

void
termhandler(int signum)
{
	(void)signum;
	statusContinue = 0;
	if (xdisplay_open && dpy) {
		XCloseDisplay(dpy);
		dpy = NULL;
	}
	exit(0);
}

int
main(int argc, char **argv)
{
	for (int i = 0; i < argc; i++) {
		if (!strcmp("-d", argv[i]) && i + 1 < argc)
			delim = argv[++i];
		else if (!strcmp("-p", argv[i]))
			writestatus = pstdout;
	}

	signal(SIGTERM, termhandler);
	signal(SIGINT, termhandler);
	statusloop();
	return 0;
}
