/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx	= 6;  /* border pixel of windows */
static const unsigned int snap		= 32; /* snap pixel */
static const int showbar			= 1;  /* 0 means no bar */
static const int topbar				= 1;  /* 0 means bottom bar */
static const char *fonts[]			= { "Hasklig:bold:size=14" };

char *colors[][3] = {
 	/*               fg         bg         border   */
	[SchemeNorm] = { "#ffffff", "#222222", "#444444" },
	[SchemeSel]  = { "#ffffff", "#005577", "#005577" },
};

static const char *blue[] = {
	"#FFFFFF", "#0E1C4A", "#3E54BD"
};

static const char *red[] = {
	"#FFFFFF", "#340B07", "#73493D"
};

static const char **current_theme = blue;

/*
red - conv_hex "#50241d #240200 #400905 #340b07 #73493d"
green - conv_hex "#1A2C12 #020C02 #193A0D #385C17 #1B331D"
blue - conv_hex "#1E3070 #3E54BD #6C76CB #0E1C4A #282D6E"

static const char *green[] = {
    "#1A2C12", "#020C02", "#193A0D", "#385C17", "#1B331D"
};
*/

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5" };

static const Rule rules[] = {
    // xprop(1):
    // WM_CLASS(STRING) = instance, class
    // WM_NAME(STRING) = title

    // class			instance		title
    // tags mask		isfloating		monitor

    {"neovide",		"neovide",		NULL,
	1 << 0,			0,				-1},
    {"qterminal",	"qterminal",	NULL,
	1 << 0,			0,				-1},

    {"Chromium-browser",	"chromium-browser",	NULL,
	1 << 1,      	0,          	-1},
    {"Chromium-browser",	"crx_adfefoiphefecjmmhmajkgibjadkkjni",   	NULL,
	1 << 1,       	0,          	-1}, // Gemini

    {"Chromium-browser",	"crx_dgommhjhffiieicepokilddfojhkfnag",		NULL,
	1 << 2,       	0,          	-1}, // Discord
    {"Chromium-browser",	"crx_agimnkijcaahngcdmfeangaknmldooml",		NULL,
	1 << 2,       	0,      		-1}, // Youtube
    {"discord",		"discord",	    NULL,
	1 << 2,       	0,             	-1},

    {"dolphin",		"dolphin",	    NULL,
	1 << 3,      	0,             	-1},
    {"gpick",		"gpick",	    NULL,
	~0,      		1,             	-1},
};

/* layout(s) */
static const float mfact	= 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster	= 1;    /* number of clients in master area */
static const int resizehints	= 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; 	/* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol	arrange function */
	{ "[M]",	monocle }, /* first entry is default */
	{ "[T]",	tile },
	{ "[F]",	NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define ALT	Mod1Mask
#define CTRL	ControlMask
#define SHIFT	ShiftMask
#define SUPER	Mod4Mask

#define TAGKEYS(KEY,TAG) \
	{ ALT,				KEY,      view,           {.ui = 1 << TAG} }, \
	{ ALT|CTRL,			KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ ALT|SHIFT,		KEY,      tag,            {.ui = 1 << TAG} }, \
	{ ALT|CTRL|SHIFT, 	KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char rofimon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *roficmd[]	= { "rofi", "-show", "drun", NULL };
static const char *termcmd[]	= { "sh", "/home/nixos/nixos/scripts/qterm.sh", NULL };
static const char *nvcmd[]		= { "neovide", NULL };
static const char *scrshot[]	= { "flameshot", "gui", NULL };
static const char *browser[]	= { "chromium", NULL };
static const char *main_wins[]	= { "/home/nixos/.startup.sh", NULL };
static const char *lockscr[]	= { "slock", NULL };

static const Key keys[] = {

	// modifier		key			function        argument

	// Custom
	{ ALT,			XK_n,		spawn,          {.v = termcmd } },
	{ ALT|SHIFT,	XK_n,		spawn,          {.v = nvcmd } },
	{ ALT,			XK_s,		spawn,          {.v = scrshot } },
	{ SUPER|SHIFT,	XK_b,		spawn,          {.v = browser } },
	{ ALT|SHIFT,  	XK_p,		spawn,          {.v = main_wins } },
	{ SUPER|SHIFT,	XK_l,		spawn,          {.v = lockscr } },
	// { SUPER,		XK_s,		setscheme,      {.i = +1 } },
	
	// Navigation
	{ ALT,			XK_space,	spawn,          {.v = roficmd } },
	{ SUPER,		XK_b,		togglebar,      {0} },
	{ ALT,			XK_Tab,		view,           {0} },
	{ ALT,			XK_a,		focusstack,     {.i = +1 } },
	{ ALT|SHIFT,	XK_a,		focusstack,     {.i = -1 } },
	{ SUPER,		XK_j,		incnmaster,     {.i = +1 } },
	{ SUPER,		XK_k,		incnmaster,     {.i = -1 } },
	{ SUPER,		XK_h,		setmfact,       {.f = -0.05} },
	{ SUPER,		XK_l,		setmfact,       {.f = +0.05} },
	{ SUPER,		XK_Return,	zoom,           {0} },

	// View Manipulation
	{ ALT|SHIFT,	XK_q,		killclient,     {-1} },
	{ SUPER|CTRL,	XK_j,		setlayout,      {.v = &layouts[0]} },
	{ SUPER|CTRL,	XK_k,		setlayout,      {.v = &layouts[1]} },
	{ SUPER|CTRL,	XK_l,		setlayout,      {.v = &layouts[2]} },
	{ SUPER,		XK_space,	setlayout,      {0} },
	{ SUPER|SHIFT,	XK_space,	togglefloating, {0} },
	{ SUPER,		XK_0,		view,           {.ui = ~0 } },
	{ SUPER|SHIFT,	XK_0,		tag,            {.ui = ~0 } },
	{ SUPER,		XK_comma,	focusmon,       {.i = -1 } },
	{ SUPER,		XK_period,	focusmon,       {.i = +1 } },
	{ SUPER|SHIFT,	XK_comma,	tagmon,         {.i = -1 } },
	{ SUPER|SHIFT,	XK_period,	tagmon,         {.i = +1 } },
	{ SUPER|SHIFT,	XK_q,		quit,			{0} },

	// Tag Keys
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         SUPER,          Button1,        movemouse,      {0} },
	{ ClkClientWin,         SUPER,          Button2,        togglefloating, {0} },
	{ ClkClientWin,         SUPER,          Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            SUPER,          Button1,        tag,            {0} },
	{ ClkTagBar,            SUPER,          Button3,        toggletag,      {0} },
};

