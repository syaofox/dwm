/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const unsigned int systrayiconsize = 16;   /* icon size (0 = bar height) */
static const unsigned int systrayiconpaddingh = 0; /* icon horizontal padding */
static const unsigned int systrayiconpaddingv = 2; /* icon vertical padding */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const unsigned int gappih    = 6;        /* horizontal inner gap */
static const unsigned int gappiv    = 4;        /* vertical inner gap */
static const unsigned int gappoh    = 4;        /* horizontal outer gap */
static const unsigned int gappov    = 4;        /* vertical outer gap */
static const int smartgaps          = 0;        /* 1 means no outer gap when 1 client */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const unsigned int barheight = 0;        /* bar height (0 = auto) */
static const int focusonhover       = 0;        /* 1: focus on hover, 0: don't focus */
static const Bool viewontag         = True;     /* Switch view on tag switch */
static const char *fonts[]          = { "JetBrainsMono Nerd Font Propo:style=Bold:size=10" };
static const char dmenufont[]       = "JetBrainsMono Nerd Font Propo:style=Bold:size=10";
static char col_gray1[]       = "#2E3440";
static char col_gray2[]       = "#4C566A";
static char col_gray3[]       = "#D8DEE9";
static char col_gray4[]       = "#ECEFF4";
static char col_cyan[]        = "#88C0D0";
static char col_white[]       = "#ECEFF4";
static char col_red[]         = "#BF616A";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm]   = { col_gray2, col_gray1, col_gray2 }, /* 未选中，无客户端 */
	[SchemeSel]    = { col_gray4, col_cyan,  col_cyan  }, /* 选中，无客户端 */
	[SchemeOcc]    = { col_white, col_gray1, col_gray2 }, /* 未选中，有客户端 */
	[SchemeSelOcc] = { col_white, col_cyan,  col_cyan  }, /* 选中，有客户端 */
	[SchemeStatus] = { col_gray3, col_gray1, col_gray1 }, /* 状态栏 */
	[SchemeTitle]  = { col_white, col_gray1, col_gray2 }, /* 窗口标题区 */
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   iscentered   isalwaysontop   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           0,            0,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           0,            0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const int refreshrate = 120;  /* refresh rate (per second) for client move/resize */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "rofi", "-show", "drun", "-theme", "theme", "-show-icons", NULL };
static const char *termcmd[]  = { "gnome-terminal", NULL };
static const char *filecmd[]  = { "nemo",  NULL };
static const char *clipmancmd[] = { "/bin/sh", "-c", "xfce4-clipman-history", NULL };
static const char *lockcmd[] = { "/bin/sh", "-c", "slock -m \"Single is simple, double is double.\"", NULL };
static const char *showkeyscmd[] = { "/bin/sh", "-c", "~/.config/dwm/show-keys.sh", NULL };
static const char *bravecmd[] = { "/bin/sh", "-c", "~/.config/dwm/run-brave.sh", NULL };
static const char *sysactcmd[] = { "/bin/sh", "-c", "~/.config/dwm/sysact.sh", NULL };
static const char *shotclipcmd[] = { "/bin/sh", "-c", "maim -s | xclip -selection clipboard -t image/png", NULL };
static const char *shotsavecmd[] = { "/bin/sh", "-c", "mkdir -p $HOME/Pictures/Screenshots && maim -s $HOME/Pictures/Screenshots/screenshot_$(date +%Y%m%d_%H%M%S).png", NULL };


/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {		
		{ "col_gray1",          STRING,  &col_gray1 },
		{ "col_gray2",          STRING,  &col_gray2 },
		{ "col_gray3",          STRING,  &col_gray3 },
		{ "col_gray4",          STRING,  &col_gray4 },
		{ "col_cyan",           STRING,  &col_cyan },
		{ "col_white",          STRING,  &col_white },
		{ "col_red",            STRING,  &col_red },
};


static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_space,  spawn,          {.v = dmenucmd } },
	{ MODKEY,             			XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_comma,  setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_period, setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    viewnexttag,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Tab,    viewnexttag,    {.i = -1 } },
	{ MODKEY,             			XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	// { MODKEY,                       XK_space,  setlayout,      {0} },
	// { MODKEY,                       XK_space,  cyclelayout,    {.i = +1} },
	// { MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglealwaysontop, {0} },
	// { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	// { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	// { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	// { MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	// { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	// { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_equal,  incrgaps,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  incrgaps,       {.i = -1 } },
	{ MODKEY,                       XK_g,      togglegaps,     {0} },
	{ MODKEY|ShiftMask,             XK_g,      defaultgaps,    {0} },
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

	{ MODKEY,                       XK_e,      spawn,          {.v = filecmd } },
	{ MODKEY,                       XK_v,      spawn,          {.v = clipmancmd } },
	{ MODKEY|ShiftMask,             XK_l,      spawn,          {.v = lockcmd } },
	{ MODKEY|ShiftMask,             XK_slash,  spawn,          {.v = showkeyscmd } },
	{ MODKEY,                       XK_w,      spawn,          {.v = bravecmd } },
	{ MODKEY,                       XK_s,      spawn,          {.v = shotclipcmd } },
	{ MODKEY|ShiftMask,             XK_s,      spawn,          {.v = shotsavecmd } },
	{ ControlMask|Mod1Mask,         XK_Delete, spawn,          {.v = sysactcmd } },


};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {.i = 0} },
	{ ClkClientWin,         MODKEY|ShiftMask, Button1,     movemouse,      {.i = 1} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkLtSymbol,          0,              Button1,        cyclelayout,    {.i = +1} },
	{ ClkLtSymbol,          0,              Button3,        cyclelayout,    {.i = -1} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

