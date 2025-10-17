/* See LICENSE file for copyright and license details. */
#include "layouts.c"

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappx     = 25;       /* gaps between windows */
static const int focusonwheel       = 0;        /* 0 means focus when scrolling */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int user_bh            = 20;       /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const char *fonts[]          = { "JetBrainsMono Nerd Font:size=12" };
static const char dmenufont[]       = "JetBrainsMono Nerd Font:size=10";
static const char col_gray1[]       = "#282c34";  // background (dark base)  
static const char col_gray2[]       = "#3E4451";  // inactive border / background variant  
static const char col_gray3[]       = "#10b1fe";  // normal text / foreground  
static const char col_gray4[]       = "#3fc56b";  // selected text / brighter foreground  
static const char col_cyan[]        = "#10b1fe";  // accent / highlight  
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_gray1, col_cyan  },
};

/*
#282c34
#abb2bf
#636d83
#10b1fe
#3fc56b
#ce9887
#f9c859
#ff78f8
#9f7efe
#3691ff
#ff936a
#ff6480
#7a82da
*/

/* tagging */
static const char *tags[] = { "", "", "", "", "", "󰎁", "", "", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   isterminal   noswallow    monitor */
	{ "Brave",    NULL,       NULL,       1 << 0,       0,           0,           1,           -1 },
	{ "Vsim",     NULL,       NULL,       1 << 2,       0,           0,           1,           -1 },
	{ "kitty",    NULL,       NULL,       0,            0,           1,           0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.8; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const int refreshrate = 120;  /* refresh rate (per second) for client move/resize */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
    { "HHH",      grid}
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|Mod1Mask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]          = { "dmenu_run", "-b", "-m", dmenumon, "-p", "cmd", "-bw", "0", NULL };
static const char *termcmd[]           = { "kitty", NULL };
static const char *bravecmd[]          = { "brave", NULL };
static const char *backgroundcmd[]     = { "feh", "--bg-scale", "/home/graph_seeker/Pictures/SFW/Picture_31.jpg", NULL };
static const char *nvimcmd[]           = { "kitty", "tmux", "new-session", "-A", "-s", "nvim", NULL };
static const char *superfilecmd[]      = { "kitty", "tmux", "new-session", "-A", "-s", "spf", NULL };
static const char *makenvimcmd[]       = { "tmux", "new-session", "-d", "-s", "nvim", "-n", "main", "nvim", NULL };
static const char *makespfcmd[]        = { "tmux", "new-session", "-d", "-s", "spf", "-n", "main", "spf", NULL };
static const char *picomcmd[]          = { "picom", NULL };
static const char *keyboardlayoutcmd[] = { "setxkbmap", "-layout", "us,ara", "-option", "grp:alt_shift_toggle", NULL };
static const char *dwmblockscmd[]      = { "dwmblocks", NULL };
static const char *dunstcmd[]          = { "dunst", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_w,      spawn,          {.v = bravecmd } },
	{ MODKEY,                       XK_z,      spawn,          {.v = nvimcmd } },
	{ MODKEY,                       XK_y,      spawn,          {.v = superfilecmd } },
	{ MODKEY,                       XK_Print,  spawn,          SHCMD("scrot -s /tmp/screen.png && xclip -selection clipboard -t image/png -i /tmp/screen.png") },
	{ MODKEY|ControlMask|Mod1Mask,  XK_j,      spawn,          SHCMD("pactl set-sink-volume @DEFAULT_SINK@ -5%; pkill -RTMIN+2 dwmblocks") },
	{ MODKEY|ControlMask|Mod1Mask,  XK_k,      spawn,          SHCMD("pactl set-sink-volume @DEFAULT_SINK@ +5%; pkill -RTMIN+2 dwmblocks") },
	{ MODKEY|ShiftMask,             XK_k,      spawn,          SHCMD("playerctl play-pause") },
	{ MODKEY,                       XK_m,      spawn,          SHCMD("/home/graph_seeker/.my_scripts/music_menu") },
	{ MODKEY,                       XK_x,      spawn,          SHCMD("/home/graph_seeker/.my_scripts/power_menu") },
	{ MODKEY,                       XK_c,      spawn,          SHCMD("dmenu -C -c -l 1 -mw 500 -p calc") },
	{ MODKEY|ShiftMask,             XK_z,      zoom,           {0} },
	{ MODKEY,                       XK_f,      fullscreen,     {0} },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_o,      winview,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_g,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* auto start apps */
Autostarttag autostarttaglist[] = {
    { .cmd = backgroundcmd,     .tags = 0 },
    { .cmd = makenvimcmd,       .tags = 0 },
    { .cmd = makespfcmd,        .tags = 0 },
    { .cmd = picomcmd,          .tags = 0 },
    { .cmd = keyboardlayoutcmd, .tags = 0 },
    { .cmd = dwmblockscmd,      .tags = 0 },
    { .cmd = dunstcmd,          .tags = 0 },
    { .cmd = bravecmd,          .tags = 1 << 0},
    { .cmd = nvimcmd,           .tags = 1 << 1},
	{ .cmd = NULL,              .tags = 0 },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

