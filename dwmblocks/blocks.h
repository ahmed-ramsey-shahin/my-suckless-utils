//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/	/*Command*/		/*Update Interval*/	/*Update Signal*/
	{ "", "/home/graph_seeker/.my_scripts/memory_block", 30,  0 },
	{ "", "/home/graph_seeker/.my_scripts/volume_block", 0,   2 },
	{ "", "/home/graph_seeker/.my_scripts/battery_block", 30,  0 },
	{ "", "/home/graph_seeker/.my_scripts/date_block",   5,   0 },
};

//sets delimiter between status commands. NULL character ('\0') means no delimiter.
static char delim[] = "\0";
static unsigned int delimLen = 5;
