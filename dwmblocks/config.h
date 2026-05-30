/* Modify this file to change what commands output to your statusbar, and recompile using the make command. */

/* NOTE: if dwmblocks does not show anything, please consider doing the following:
 * 1. Copy "bin" to "~/.local/bin", then add the latter to your $PATH
 * 2. Add the absolute path name to the commands
 * (for example, "/home/matteo/.local/bin/capslock")
 * 3. Check that the scripts are executable, and that you have the permission to
 * execute the script
 */

static const Block blocks[] = {
	// Icon  Command    Interval (s)    Update signal
	//{"",    "capslock",           1,     1},
	{"",    "memory",            10,     4},
	{"",    "cpu",                5,     5},
	/* {"", "media", 3, 6}, */ /* needs `media` script in $PATH; see bin/media.example */
	{"",    "fanspeed",           5,     7},
	{"",    "internet",           5,     8},
	{"",    "bluetooth",          5,     6},
	{"",    "battery",           10,     9},
	{"",    "clock",             30,    10},
	{"",    "volume",             0,    11},
	{"",    "brightness",         5,     3},
	{"",    "mic",                0,    12},
};

//Sets delimiter between status commands. NULL character ('\0') means no delimiter.
static char *delim = " │ ";
