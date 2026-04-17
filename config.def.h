/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const unsigned int systrayiconsize = 12;   /* icon size (0 = bar height) */
static const unsigned int systrayiconpaddingh = 2; /* icon horizontal padding */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const unsigned int gappih    = 6;        /* horizontal inner gap */
static const unsigned int gappiv    = 4;        /* vertical inner gap */
static const unsigned int gappoh    = 4;        /* horizontal outer gap */
static const unsigned int gappov    = 4;        /* vertical outer gap */
static const int smartgaps          = 0;        /* 1 means no outer gap when 1 client */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const unsigned int barheight = 26;        /* bar height (0 = auto) */
static const int focusonhover       = 0;        /* 1: focus on hover, 0: don't focus */
static const Bool viewontag         = True;     /* Switch view on tag switch */
static const char *fonts[]          = { "JetBrainsMono Nerd Font Propo:style=Bold:size=10" };
static const char *tagfonts[]        = { "JetBrainsMono Nerd Font Propo:style=Bold:size=11" };
static const char *titlefonts[]      = { 
	"Noto Sans CJK SC:style=Regular:size=10",
	"JetBrainsMono Nerd Font Propo:style=Regular:size=10"
 };
static const char *systrayfonts[]    = { "JetBrainsMono Nerd Font Propo:style=Regular:size=9" };
static const char dmenufont[]       = "JetBrainsMono Nerd Font Propo:style=Bold:size=10";

static char col_norm_fg[]       		= "#444444";
static char col_norm_bg[]       		= "#222222";
static char col_norm_border[]      		= "#444444";

static char col_sel_fg[]       			= "#eeeeee";
static char col_sel_bg[]       			= "#005577";
static char col_sel_border[]        	= "#005577";

static char col_occ_fg[]       			= "#ECEFF4";
static char col_occ_bg[]       			= "#222222";
static char col_occ_border[]       		= "#444444";

static char col_selocc_fg[]       		= "#FFFFFF";
static char col_selocc_bg[]       		= "#005577";
static char col_selocc_border[]   		= "#005577";

static char col_status_fg[]      		= "#bbbbbb";
static char col_status_bg[]      		= "#222222";
static char col_status_border[]  		= "#222222";

static char col_title_fg[]       		= "#ECEFF4";
static char col_title_bg[]       		= "#222222";
static char col_title_border[]   		= "#444444";

static char col_titlesel_fg[]    		= "#FFFFFF";
static char col_titlesel_bg[]    		= "#005577";
static char col_titlesel_border[] 		= "#222222";

static int enabletagunderline 			= 1;
static char col_tagunderline[]   		= "#d488d6";

static const unsigned int tagunderlinepadding = 4;
static const unsigned int tagunderlineheight = 2;

static char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm]   = { col_norm_fg, col_norm_bg, col_norm_border }, /* 未选中，无客户端 */
	[SchemeSel]    = { col_sel_fg, col_sel_bg, col_sel_border }, /* 选中，无客户端 */
	[SchemeOcc]    = { col_occ_fg, col_occ_bg, col_occ_border }, /* 未选中，有客户端 */
	[SchemeSelOcc] = { col_selocc_fg, col_selocc_bg, col_selocc_border }, /* 选中，有客户端 */
	[SchemeStatus] = { col_status_fg, col_status_bg, col_status_border }, /* 状态栏 */
	[SchemeTitleNorm]  = { col_title_fg, col_title_bg, col_title_border }, /* 窗口标题区*/
	[SchemeTitleSel]  = { col_titlesel_fg, col_titlesel_bg, col_titlesel_border }, /* 窗口标题区选中*/
	[SchemeTagUnderline] = { col_tagunderline, col_tagunderline, col_tagunderline }, /* tag下划线 */
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      									instance    								title				tags mask     isfloating   iscentered   isalwaysontop   monitor */
	{ "FreeFileSync",               				NULL,                   					NULL,				1 << 8, 	  0,           0,            0,           -1 },
	{ "Localsend",                  				"localsend",            					NULL,				1 << 8, 	  0,           0,            0,           -1 },
	{ "mpv",                        				NULL,       								NULL,				0,            1,           1,            1,           -1 },
	{ "Io.github.celluloid_player.Celluloid",       "io.github.celluloid_player.Celluloid",     NULL,				0,            1,           1,            1,           -1 },
	{ "Xviewer",                    				NULL,       								NULL,				0,            1,           1,            1,           -1 },
	
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
static const char *termcmd[]  = { "/bin/bash" , "-c", "~/.config/dwm/run-term.sh", NULL };
static const char *filecmd[]  = { "nemo",  NULL };
static const char *clipmancmd[] = { "/bin/sh", "-c", "xfce4-clipman-history", NULL };
static const char *lockcmd[] = { "/bin/sh", "-c", "slock -m \"Single is simple, double is double.\"", NULL };
static const char *showkeyscmd[] = { "/bin/sh", "-c", "~/.config/dwm/show-keys.sh", NULL };
static const char *bravecmd[] = { "/bin/sh", "-c", "~/.config/dwm/run-browser.sh", NULL };
static const char *rofiwebcmd[] = { "/bin/sh", "-c", "~/.config/dwm/rofi-websites.sh", NULL };
static const char *sysactcmd[] = { "/bin/sh", "-c", "~/.config/dwm/sysact.sh", NULL };
static const char *shotclipcmd[] = { "/bin/sh", "-c", "maim -s | xclip -selection clipboard -t image/png", NULL };
static const char *shotsavecmd[] = { "/bin/sh", "-c", "mkdir -p $HOME/Pictures/Screenshots && maim -s $HOME/Pictures/Screenshots/screenshot_$(date +%Y%m%d_%H%M%S).png", NULL };
static const char *chgwallscmd[] = { "/bin/sh", "-c", "~/.config/dwm/change-wallpaper.sh", NULL };
static const char *volupcmd[] = { "/bin/sh", "-c", "pactl set-sink-volume @DEFAULT_SINK@ +5% && pactl get-sink-volume @DEFAULT_SINK@ | head -n1 | awk '{print $5}' | sed 's/%//' | xargs -I{} dunstify -r 9988 -t 1000 'Volume {}%'", NULL };
static const char *voldncmd[] = { "/bin/sh", "-c", "pactl set-sink-volume @DEFAULT_SINK@ -5% && pactl get-sink-volume @DEFAULT_SINK@ | head -n1 | awk '{print $5}' | sed 's/%//' | xargs -I{} dunstify -r 9988 -t 1000 'Volume {}%'", NULL };
static const char *volmutecmd[] = { "/bin/sh", "-c", "pactl set-sink-mute @DEFAULT_SINK@ toggle && (pactl get-sink-mute @DEFAULT_SINK@ | grep -q yes && dunstify -r 9988 -t 1000 'Muted' || pactl get-sink-volume @DEFAULT_SINK@ | head -n1 | awk '{print $5}' | sed 's/%//' | xargs -I{} dunstify -r 9988 -t 1000 'Volume {}%')", NULL };


/*
 * Xresources preferences to load at startup
 */
ResourcePref resources[] = {		
		{ "col_norm_fg",        STRING,  &col_norm_fg },
		{ "col_norm_bg",        STRING,  &col_norm_bg },
		{ "col_norm_border",    STRING,  &col_norm_border },
		{ "col_sel_fg",         STRING,  &col_sel_fg },
		{ "col_sel_bg",         STRING,  &col_sel_bg },
		{ "col_sel_border",     STRING,  &col_sel_border },
		{ "col_occ_fg",         STRING,  &col_occ_fg },
		{ "col_occ_bg",         STRING,  &col_occ_bg },
		{ "col_occ_border",     STRING,  &col_occ_border },
		{ "col_selocc_fg",      STRING,  &col_selocc_fg },
		{ "col_selocc_bg",     STRING,  &col_selocc_bg },
		{ "col_selocc_border",  STRING,  &col_selocc_border },
		{ "col_status_fg",     STRING,  &col_status_fg },
		{ "col_status_bg",     STRING,  &col_status_bg },
		{ "col_status_border", STRING,  &col_status_border },
		{ "col_title_fg",      STRING,  &col_title_fg },
		{ "col_title_bg",      STRING,  &col_title_bg },
		{ "col_title_border",  STRING,  &col_title_border },
		{ "col_titlesel_fg",   STRING,  &col_titlesel_fg },
		{ "col_titlesel_bg",   STRING,  &col_titlesel_bg },
		{ "col_titlesel_border", STRING, &col_titlesel_border },
		{ "col_tagunderline",  STRING,  &col_tagunderline },
		{ "tagunderline",  STRING,  &enabletagunderline },

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
	{ MODKEY,                       XK_grave,  swapstack,      {0} },
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
	{ MODKEY|ShiftMask,             XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ControlMask|ShiftMask, XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ControlMask|ShiftMask, XK_period, tagmon,         {.i = +1 } },
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
	{ MODKEY,                       XK_s,      spawn,          {.v = rofiwebcmd } },
	{ MODKEY,                       XK_a,      spawn,          {.v = shotclipcmd } },
	{ MODKEY|ShiftMask,             XK_a,      spawn,          {.v = shotsavecmd } },
	{ ControlMask|Mod1Mask,         XK_Delete, spawn,          {.v = sysactcmd } },
	{ MODKEY|ShiftMask,             XK_w,      spawn,          {.v = chgwallscmd } },

	{ 0,                       XF86XK_AudioRaiseVolume, spawn, {.v = volupcmd } },
	{ 0,                       XF86XK_AudioLowerVolume, spawn, {.v = voldncmd } },
	{ 0,                       XF86XK_AudioMute,        spawn, {.v = volmutecmd } },
};

/* AppKey: application-specific key bindings */
static const AppKey appkeys[] = {
    /* class                                    instance                  				title                 modifier 		key			function           argument */
    { "Io.github.celluloid_player.Celluloid", 	"io.github.celluloid_player.Celluloid", NULL,                 0,         	XK_q,       killclient,        {0} },
    { "Xviewer",                                "xviewer",                      		NULL,                 0,          	XK_q,       killclient,        {0} },
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

