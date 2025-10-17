/* See LICENSE file for copyright and license details. */
/* Default settings; can be overriden by command line. */

static int topbar = 0;                      /* -b  option; if 0, dmenu appears at bottom     */
static int center = 0;
static int lineheight = 0;
static int min_lineheight = 30;
static int width = 0;
static unsigned int border_width = 2;

// vi mode settings
static int vi_mode = 1;
static int start_mode = 0;
static Key global_esc = { XK_Escape };
static Key quit_keys[] = {
	{ XK_q, 0 },
};
/* -fn option overrides fonts[0]; default X11 font or font set */
static const char *fonts[] = {
	"JetBrainsMono Nerd Font:size=10"
};
static const char *prompt      = NULL;      /* -p  option; prompt to the left of input field */
static const char *colors[SchemeLast][2] = {
	/*     fg         bg       */
	[SchemeNorm] = { "#10b1fe", "#282c34" },
	[SchemeSel] = { "#3fc46b", "#282c34" },
	[SchemeOut] = { "#000000", "#00ffff" },
    [SchemeCursor] = { "#3fc46b", "#282c34" },
};
/* -l option; if nonzero, dmenu uses vertical list with given number of lines */
static unsigned int lines      = 0;

/*
 * Characters not considered part of a word while deleting words
 * for example: " /?\"&[]"
 */
static const char worddelimiters[] = " ";
