/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "ibm plex mono:size=10", "emojione:size=9", "font awesome:size=9" };
// defualt colors
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
// molokai colors
static const char col_gray[]        = "#121212";
static const char col_magenta[]     = "#e71d36";
static const char col_orange[]      = "#ff8700";
static const char col_red[]         = "#8b0000";
static const char col_geniva_blue[]  = "#68adb3";
static const char col_brown[]        = "#5c431c";
static const char col_blonde[]        = "#F0E2B6";
static const char *colors[][4]      = {
	/*               fg         bg           border      float */

	/* [SchemeNorm]  = { col_geniva_blue, col_brown, col_brown },
	[SchemeSel] = { col_brown, col_blonde, col_blonde }, */

	[SchemeNorm] = { col_gray2, col_gray3, col_cyan },
	[SchemeSel]  = { col_gray4, col_brown, col_geniva_blue },

	/* [SchemeNorm] = { col_gray4, col_gray,    col_gray,   col_gray },
	[SchemeSel] =  { col_gray4, col_magenta, col_orange, col_red }, */
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {"st", "-n", "spterm", "-g", "144x41", NULL };
const char *spcmd2[] = {"st", "-n", "splf", "-g", "144x41", "-e", "lf", NULL };
const char *spcmd3[] = {"st", "-n", "sppm", "-g", "144x41", "-e", "pulsemixer", NULL };
const char *spcmd4[] = {"st", "-n", "sppu", "-g", "144x41", "-e", "popupgrade", NULL };
const char *spcmd5[] = {"st", "-n", "spcalc", "-f", "monospace:size=16", "-g", "50x20", "-e", "bc", "-lq", NULL };
const char *spcmd6[] = {"tabbed", "-n", "spsurf", "-g", "1200x900", "-c", "surf", "-e", NULL };
const char *spcmd7[] = {"st", "-n", "spcal", "-g", "144x41", "-e", "st -e calcurse -D ~/.config/calcurse", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
	{"splf",	spcmd2},
	{"sppm",	spcmd3},
	{"sppu",	spcmd4},
	{"spclac",	spcmd5},
	{"spsurf",	spcmd6},
	{"spcal",	spcmd7},
};

/* tagging */
/* static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" }; */
static const char *tags[] = { "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating    swollow    monitor */

	/* Rule to make st swallow programs started in the terminal to be swollowed */
	{ "st",	      NULL,	  NULL,	      0,	    0,	          1,         -1 },

	/* Rules to make certain windows automatically float */
	{ "Gimp",     NULL,       NULL,       0,            1,            1,         -1 },
	{ "st",       NULL,      "lfmpv",     0,            1,            1,         -1 },
	{ "st",       NULL,    "/bin/sh",     0,            1,            1,         -1 },
	{ "st",       NULL,   "popupgrade",   0 << 8,       1,            1,         -1 },

	/* All the scratch pads */
	{ NULL,	      "spterm",	  NULL,	    SPTAG(0),	    1,	          0,          -1 },
	{ NULL,	      "splf",	  NULL,	    SPTAG(1),	    1,	          0,          -1 },
	{ NULL,	      "sppm",	  NULL,	    SPTAG(2),	    1,	          0,          -1 },
	{ NULL,	      "sppu",	  NULL,	    SPTAG(3),	    1,	          0,          -1 },
	{ NULL,	      "spcalc",	  NULL,	    SPTAG(4),	    1,	          0,          -1 },
	{ NULL,	      "spsurf",	  NULL,	    SPTAG(5),	    1,	          0,          -1 },
	{ NULL,	      "spcal",	  NULL,	    SPTAG(6),	    1,	          0,          -1 },
};

/* layout(s) */
static const float mfact     = 0.6; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int decorhints  = 1;    /* 1 means respect decoration hints */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "TTT",      bstack },
	{ "[M]",      monocle },
	{ "><>",      NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/dash", "-c", cmd, NULL } }

/* commands */
/* static const char *termcmd[]  = { "st", NULL }; */

#include <X11/XF86keysym.h>
#include "focusurgent.c"
static Key keys[] = {
	/* modifier                     key        function        argument */

	/* dwm control keys */
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_u,      focusurgent,    {0} },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_k,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ControlMask,           XK_f,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_f,      togglefullscr,  {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefloating, {0} },
	{ MODKEY,                       XK_s,      togglesticky,   {0} },
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
	{ MODKEY|ShiftMask,             XK_e,      quit,           {0} },
	{ MODKEY|ControlMask,           XK_e,      quit,           {1} },

	/* spawn Keys */
	{ MODKEY|ShiftMask,             XK_Return, spawn,          SHCMD("st") },
	{ MODKEY,			XK_o,		spawn,		SHCMD("dmenu_run -l 20") },
	{ MODKEY|ShiftMask,		XK_b,		spawn,		SHCMD("st -e bmon -p w*,*") },
	{ MODKEY|ShiftMask,		XK_d,		spawn,		SHCMD("geodoppler") },
	{ MODKEY|ShiftMask,		XK_m,		spawn,		SHCMD("st -e lf") },
	{ MODKEY,			XK_e,		spawn,		SHCMD("st -e neomutt; kill -$((34+12)) $(pidof zara)") },
	{ MODKEY|ControlMask,		XK_t,		spawn,		SHCMD("torwrap; kill -$((34+7)) $(pidof zara)") },
	{ MODKEY|ShiftMask,		XK_h,		spawn,		SHCMD("selectionhandler dmenuhandler") },
	{ MODKEY|ControlMask,		XK_h,		spawn,		SHCMD("selectionhandler linkhandler") },
	{ MODKEY|ShiftMask|ControlMask, XK_h,		spawn,		SHCMD("st -e htop") },
	{ MODKEY,			XK_g,		spawn,		SHCMD("st -e gotop") },
	{ MODKEY,			XK_n,		spawn,		SHCMD("st -e newsboat; kill -$((34+6)) $(pidof zara)") },
	{ MODKEY|ControlMask,		XK_c,		spawn,		SHCMD("camtoggle") },
	{ MODKEY,			XK_w,		spawn,		SHCMD("firefox") },
	{ MODKEY|ShiftMask,		XK_w,		spawn,		SHCMD("st -e nmtui; kill -$((34+2)) $(pidof zara) && kill -$((34+4)) $(pifof zara)") },

	/* scratch pads */
	{ MODKEY,            		XK_y,  	   togglescratch,  {.ui = 0 } },
	{ MODKEY|ShiftMask,   		XK_u,	   togglescratch,  {.ui = 1 } },
	{ MODKEY|ShiftMask,             XK_p,	   togglescratch,  {.ui = 2 } },
	{ MODKEY|ControlMask,           XK_p,	   togglescratch,  {.ui = 3 } },
	{ MODKEY,		     	XK_c, 	   togglescratch,  {.ui = 6 } },
	{ MODKEY|ShiftMask,            	XK_c, 	   togglescratch,  {.ui = 4 } },
	{ MODKEY|ControlMask,     	XK_b, 	   togglescratch,  {.ui = 5 } },

	/* control keys */
	{ MODKEY,			XK_grave,	spawn,		SHCMD("dmenuunicode") },
	{ MODKEY,			XK_Insert,	spawn,		SHCMD("showclip") },
	{ MODKEY|ShiftMask,		XK_Insert,	spawn,		SHCMD("switchclip") },
	{ MODKEY|ShiftMask,		XK_s,		spawn,		SHCMD("selectionswitch") },
	{ MODKEY|ShiftMask,		XK_i,		spawn,		SHCMD("speedtest-notify") },
	{ MODKEY|ShiftMask,		XK_r,		spawn,		SHCMD("dmenuresp") },
	{ MODKEY|ControlMask,		XK_r,		spawn,		SHCMD("dmenurefbar") },
	{ MODKEY|ShiftMask,		XK_l,		spawn,		SHCMD("$LOCKER") },
	{ MODKEY|ControlMask,		XK_l,		spawn,		SHCMD("$LOCKER & sleep 1 && sysact hibernate") },

	/* recording keys */
	{ MODKEY,			XK_F12,		spawn,		SHCMD("maim pic-full-$(date '+%y%m%d-%H%M-%S').png") },
	{ MODKEY|ShiftMask,		XK_F12,		spawn,		SHCMD("maimpick") },
	{ MODKEY,			XK_r,		spawn,		SHCMD("dmenurecord; kill -$((34+9)) $(pidof zara)") },
	{ MODKEY,			XK_Delete,	spawn,		SHCMD("dmenurecord kill; kill -$((34+9)) $(pidof zara)") },

	/* power keys */
	{ MODKEY|ShiftMask,		XK_Escape,	spawn,		SHCMD("sysact") },

	/* XF86 keys */
	{ 0, XF86XK_AudioMute,		spawn,		SHCMD("pamixer -t; kill -44 $(pidof zara)") },
	{ 0, XF86XK_AudioRaiseVolume,	spawn,		SHCMD("pamixer --allow-boost -i 3; kill -44 $(pidof zara)") },
	{ 0, XF86XK_AudioLowerVolume,	spawn,		SHCMD("pamixer --allow-boost -d 3; kill -44 $(pidof zara)") },
	{ 0, XF86XK_PowerOff,		spawn,		SHCMD("sysact") },
	{ 0, XF86XK_Calculator,		spawn,		SHCMD("st -e bc -l") },
	{ 0, XF86XK_Sleep,		spawn,		SHCMD("sudo -A zzz") },
	{ 0, XF86XK_WWW,		spawn,		SHCMD("tabbed -c surf -e") },
	{ 0, XF86XK_DOS,		spawn,		SHCMD("st") },
	{ 0, XF86XK_ScreenSaver,	spawn,		SHCMD("$LOCKER") },
	{ 0, XF86XK_TaskPane,		spawn,		SHCMD("st -e gotop") },
	{ 0, XF86XK_Mail,		spawn,		SHCMD("st -e neomutt ; kill -$((34+12)) $(pidof zara)") },
	{ 0, XF86XK_MyComputer,		spawn,		SHCMD("st -e lf") },
	{ 0, XF86XK_Launch1,		spawn,		SHCMD("xset dpms force off") },
	{ 0, XF86XK_TouchpadToggle,	spawn,		SHCMD("(synclient | grep 'TouchpadOff.*1' && synclient TouchpadOff=0) || synclient TouchpadOff=1") },
	{ 0, XF86XK_TouchpadOff,	spawn,		SHCMD("synclient TouchpadOff=1") },
	{ 0, XF86XK_TouchpadOn,		spawn,		SHCMD("synclient TouchpadOff=0") },
	{ 0, XF86XK_MonBrightnessUp,	spawn,		SHCMD("xbacklight -inc 15") },
	{ 0, XF86XK_MonBrightnessDown,	spawn,		SHCMD("xbacklight -dec 15") },

	/* function Keys */
	{ MODKEY,			XK_F1,		spawn,		SHCMD("groff -mom \"${READMEFILE:-${XDG_DATA_HOME:-$HOME/.local/share}/help.mom}\" -Tpdf | zathura -") },
	{ MODKEY,			XK_F3,		spawn,		SHCMD("displayselect") },
	{ MODKEY,			XK_F4,		spawn,		SHCMD("prompt 'Would You Like To Put The Computer To Sleep?' 'sudo -A zzz'") },
	{ MODKEY,			XK_F7,		spawn,		SHCMD("td-toggle") },
	{ MODKEY,			XK_F8,		spawn,		SHCMD("notify-send '📧 Syncing Mail'; mailsync && notify-send '📧 Mail Synced'; kill -$((34+12)) $(pidof zara)") },
	{ MODKEY,			XK_F9,		spawn,		SHCMD("dmenumount") },
	{ MODKEY|ShiftMask,		XK_F9,		spawn,		SHCMD("dmenuumount") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
