/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 20;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 20;       /* vert inner gap between windows */
static const unsigned int gappoh    = 20;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 20;       /* vert outer gap between windows and screen edge */
static const int swallowfloating    = 1;        /* 1 means swallow floating windows by default */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10", "JoyPixels:size=10" };
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_white[] 	    = "#ffffff";
static const char col_cyan[]        = "#005577";
static const char col_red[] 	    = "#D22021";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_white, col_gray1, col_gray2 },
	[SchemeSel]  = { col_white, col_gray2,  col_red  },
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {"st", "-n", "spterm", "-g", "144x41", NULL };
const char *spcmd2[] = {"st", "-n", "splf", "-g", "144x41", "-e", "startlf", NULL };
const char *spcmd3[] = {"st", "-n", "sppm", "-g", "144x41", "-e", "pulsemixer", NULL };
const char *spcmd4[] = {"st", "-n", "spcalc", "-f", "monospace:size=16", "-g", "50x20", "-e", "bc", "-lq", NULL };
const char *spcmd5[] = {"tabbed", "-n", "spsurf", "-g", "1200x900", "-c", "surf", "-e", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
	{"splf",	spcmd2},
	{"sppm",	spcmd3},
	{"spclac",	spcmd4},
	{"spsurf",	spcmd5},
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask	    iscentered  isfloating  isterminal  swallow	  monitor */

	/* Rule to make all windows centered when floating */
	{ NULL,	      NULL,	  NULL,	      0,	    1,		0,	    0,		0,        -1 },

	/* Rule to make st swallow programs started in the terminal that would make it inoperable */
	{ "st",	      NULL,	  NULL,	      0,	    1,	        0,	    1,		1,        -1 },

	/* Rules to make certain windows automatically float */
	{ "Gimp",     NULL,       NULL,       0,            1,          1,          0,          1,        -1 },
	{ "st",       NULL,      "lfmpv",     0,            1,		1,          1,		0,        -1 },
	{ "st",       NULL,    "/bin/sh",     0,            1,		1,          1,		1,        -1 },
	{ "st",       NULL,   "popupgrade",   0 << 8,       1,		1,          1,		1,        -1 },

	/* All the scratch pads */
	{ NULL,	      "spterm",	  NULL,	    SPTAG(0),	    1,		1,	    1,		0,        -1 },
	{ NULL,	      "splf",	  NULL,	    SPTAG(1),	    1,		1,	    1,		0,        -1 },
	{ NULL,	      "sppm",	  NULL,	    SPTAG(2),	    1,		1,	    1,		0,        -1 },
	{ NULL,	      "spcalc",	  NULL,	    SPTAG(3),	    1,		1,	    1,		0,        -1 },
	{ NULL,	      "spsurf",	  NULL,	    SPTAG(4),	    1,		1,	    0,		0,        -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#include "vanitygaps.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[@]",	spiral },		/* Fibonacci spiral */
	{ "[\\]",	dwindle },		/* Decreasing in size right and leftward */


	{ "[]=",	tile },			/* Master on left, slaves on right */
	{ "TTT",	bstack },		/* Master on top, slaves on bottom */


	{ "H[]",	deck },			/* Master on left, slaves in monocle-like mode on right */
 	{ "[M]",	monocle },		/* All windows on top of eachother */

	{ "|M|",	centeredmaster },		/* Master in middle, slaves on sides */
	{ ">M>",	centeredfloatingmaster },	/* Same but master floats */

	{ "><>",	NULL },			/* no layout function means floating behavior */
	{ NULL,		NULL },
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
static const char *termcmd[]  = { "st", NULL };

#include <X11/XF86keysym.h>
#include "push.c"
#include "focusurgent.c"
static Key keys[] = {
	/* modifier                     key        	function        argument */

	/* dwm control keys */
	{ MODKEY,                       XK_b,     	togglebar,      {0} },
	{ MODKEY,			XK_z,	  	incrgaps,	{.i = +3 } },
	{ MODKEY,			XK_x,	  	incrgaps,	{.i = -3 } },
	{ MODKEY,			XK_a,	  	togglegaps, 	{0} },
	{ MODKEY|ShiftMask,		XK_a,	  	defaultgaps,	{0} },
	{ MODKEY,                       XK_j,     	focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,     	focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_u,     	focusurgent,    {0} },
	{ MODKEY|ShiftMask,             XK_j,     	pushdown,       {0} },
	{ MODKEY|ShiftMask,             XK_k,     	pushup,         {0} },
	{ MODKEY,                       XK_o,     	incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_p,     	incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,     	setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,     	setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return,	zoom,           {0} },
	{ MODKEY,                       XK_Tab,   	view,           {0} },
	{ MODKEY|ControlMask,		XK_comma, 	cyclelayout,    {.i = -1 } },
	{ MODKEY|ControlMask,           XK_period,	cyclelayout,    {.i = +1 } },
 	{ MODKEY|ShiftMask,             XK_f,     	togglefloating, {0} },
	{ MODKEY,	                XK_f,     	togglefullscr,  {0} },
	{ MODKEY|ControlMask,           XK_s,     	togglesticky,   {0} },
	{ MODKEY,                       XK_0,     	view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,     	tag,            {.ui = ~0 } },
	{ MODKEY|ControlMask,           XK_comma, 	focusmon,       {.i = -1 } },
	{ MODKEY|ControlMask,           XK_period,	focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma, 	tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,	tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                    	0)
	TAGKEYS(                        XK_2,                    	1)
	TAGKEYS(                        XK_3,                    	2)
	TAGKEYS(                        XK_4,                    	3)
	TAGKEYS(                        XK_5,                    	4)
	TAGKEYS(                        XK_6,                    	5)
	TAGKEYS(                        XK_7,                    	6)
	TAGKEYS(                        XK_8,                    	7)
	TAGKEYS(                        XK_9,                    	8)
	{ MODKEY|ShiftMask,             XK_q,     	killclient,   	{0} },
	{ MODKEY|ControlMask,           XK_q,     	spawn,        	SHCMD("xdo kill") },
	{ MODKEY|ShiftMask,             XK_e,     	quit,         	{0} },

	/* spawn Keys */
	{ MODKEY|ShiftMask,             XK_Return,	spawn,          {.v = termcmd } },
	{ MODKEY,			XK_d,		spawn,		SHCMD("dmenu_run -l 20") },
	{ MODKEY,			XK_v,		spawn,		SHCMD("$TERMINAL -e startlf") },
	{ MODKEY,			XK_e,		spawn,		SHCMD("$TERMINAL -e neomutt; pkill -RTMIN+12 $STATUSBAR") },
	{ MODKEY,			XK_t,		spawn,		SHCMD("torwrap; pkill -RTMIN+7 $STATUSBAR") },
	{ MODKEY|ShiftMask,		XK_t,		spawn,		SHCMD("$TERMINAL -e toxic") },
	{ MODKEY|ShiftMask,		XK_h,		spawn,		SHCMD("selectionhandler dmenuhandler") },
	{ MODKEY|ControlMask,		XK_h,		spawn,		SHCMD("selectionhandler linkhandler") },
	{ MODKEY|ShiftMask|ControlMask, XK_h,		spawn,		SHCMD("$TERMINAL -e htop") },
	{ MODKEY,			XK_g,		spawn,		SHCMD("$TERMINAL -e gotop") },
	{ MODKEY,			XK_n,		spawn,		SHCMD("$TERMINAL -e newsboat") },
	{ MODKEY,			XK_c,		spawn,		SHCMD("$TERMINAL -e calcurse -D ~/.config/calcurse") },
	{ MODKEY|ControlMask,		XK_c,		spawn,		SHCMD("mpv --no-osc --no-input-default-bindings --input-conf=/dev/null --title='mpvfloat' /dev/video0") },
	{ MODKEY,			XK_w,		spawn,		SHCMD("$BROWSER") },
	{ MODKEY|ShiftMask,		XK_w,		spawn,		SHCMD("$TERMINAL -e nmtui") },

	/* scratch pads */
	{ MODKEY,            		XK_y,  	   togglescratch,  {.ui = 0 } },
	{ MODKEY,            		XK_u,	   togglescratch,  {.ui = 1 } },
	{ MODKEY|ShiftMask,             XK_p,	   togglescratch,  {.ui = 2 } },
	{ MODKEY|ShiftMask,            	XK_c, 	   togglescratch,  {.ui = 3 } },
	{ MODKEY,            		XK_i, 	   togglescratch,  {.ui = 4 } },

	/* control keys */
	{ MODKEY,			XK_grave,	spawn,		SHCMD("dmenuunicode") },
	{ MODKEY,			XK_Insert,	spawn,		SHCMD("showclip") },
	{ MODKEY|ShiftMask,		XK_Insert,	spawn,		SHCMD("switchclip") },
	{ MODKEY|ShiftMask,		XK_s,		spawn,		SHCMD("selectionswitch") },
	{ MODKEY|ShiftMask,		XK_i,		spawn,		SHCMD("speedtest-notify") },
	{ MODKEY|ShiftMask,		XK_r,		spawn,		SHCMD("restart") },
	{ MODKEY|ControlMask,		XK_r,		spawn,		SHCMD("dmenurefbar") },
	{ MODKEY|ShiftMask,		XK_l,		spawn,		SHCMD("$LOCKER") },

	/* recording keys */
	{ MODKEY,			XK_F12,		spawn,		SHCMD("maim pic-full-$(date '+%y%m%d-%H%M-%S').png") },
	{ MODKEY|ShiftMask,		XK_F12,		spawn,		SHCMD("maimpick") },
	{ MODKEY,			XK_r,		spawn,		SHCMD("dmenurecord; pkill -RTMIN+9 $STATUSBAR") },
	{ MODKEY,			XK_Delete,		spawn,		SHCMD("dmenurecord kill; pkill -RTMIN+9 $STATUSBAR") },

	/* power keys */
	{ MODKEY|ShiftMask,		XK_x,		spawn,		SHCMD("prompt 'Shutdown Computer?' 'sudo -A shutdown -h now'") },
	{ MODKEY|ShiftMask,		XK_BackSpace,	spawn,		SHCMD("prompt 'Reboot Computer?' 'sudo -A reboot'") },
	{ MODKEY|ShiftMask,		XK_Escape,	spawn,		SHCMD("prompt 'Exit Xorg?' 'sudo killall Xorg'") },

	/* XF86 keys */


	{ 0, XF86XK_AudioMute,		spawn,		SHCMD("pamixer -t; kill -$((34+10)) $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioRaiseVolume,	spawn,		SHCMD("pamixer --allow-boost -i 3; kill -$((34+10)) $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioLowerVolume,	spawn,		SHCMD("pamixer --allow-boost -d 3; kill -$((34+10)) $(pidof dwmblocks)") },
	{ 0, XF86XK_PowerOff,		spawn,		SHCMD("sysact") },
	{ 0, XF86XK_Calculator,		spawn,		SHCMD("$TERMINAL -e bc -l") },
	{ 0, XF86XK_Sleep,		spawn,		SHCMD("sudo -A zzz") },
	{ 0, XF86XK_WWW,		spawn,		SHCMD("$BROWSER") },
	{ 0, XF86XK_DOS,		spawn,		SHCMD("$TERMINAL") },
	{ 0, XF86XK_ScreenSaver,	spawn,		SHCMD("$LOCKER") },
	{ 0, XF86XK_TaskPane,		spawn,		SHCMD("$TERMINAL -e gotop") },
	{ 0, XF86XK_Mail,		spawn,		SHCMD("$TERMINAL -e neomutt ; pkill -RTMIN+12 dwmblocks") },
	{ 0, XF86XK_MyComputer,		spawn,		SHCMD("$TERMINAL -e startlf") },
	{ 0, XF86XK_Launch1,		spawn,		SHCMD("xset dpms force off") },
	{ 0, XF86XK_TouchpadToggle,	spawn,		SHCMD("(synclient | grep 'TouchpadOff.*1' && synclient TouchpadOff=0) || synclient TouchpadOff=1") },
	{ 0, XF86XK_TouchpadOff,	spawn,		SHCMD("synclient TouchpadOff=1") },
	{ 0, XF86XK_TouchpadOn,		spawn,		SHCMD("synclient TouchpadOff=0") },
	{ 0, XF86XK_MonBrightnessUp,	spawn,		SHCMD("xbacklight -inc 15") },
	{ 0, XF86XK_MonBrightnessDown,	spawn,		SHCMD("xbacklight -dec 15") },

	/* function Keys */
	{ MODKEY,			XK_F3,		spawn,		SHCMD("displayselect") },
	{ MODKEY,			XK_F4,		spawn,		SHCMD("prompt 'Would You Like To Put The Computer To Sleep?' 'sudo -A zzz'") },
	{ MODKEY,			XK_F7,		spawn,		SHCMD("td-toggle") },
	{ MODKEY,			XK_F8,		spawn,		SHCMD("notify-send '📧 Syncing Mail'; mailsync && notify-send '📧 Mail Synced'; pkill -RTMIN+12 $STATUSB") },
	{ MODKEY,			XK_F9,		spawn,		SHCMD("dmenumount") },
	{ MODKEY,			XK_F10,		spawn,		SHCMD("dmenuumount") },

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigdwmblocks,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigdwmblocks,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigdwmblocks,   {.i = 3} },
	{ ClkStatusText,        0,              Button4,        sigdwmblocks,   {.i = 4} },
	{ ClkStatusText,        0,              Button5,        sigdwmblocks,   {.i = 5} },
	{ ClkStatusText,        ShiftMask,      Button1,        sigdwmblocks,   {.i = 6} },
	{ ClkStatusText,        ShiftMask,      Button3,        spawn,          SHCMD("st -e nvim ~/.local/src/dwmblocks/config.h") },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

/* dwmc stuff */
void
setlayoutex(const Arg *arg)
{
	setlayout(&((Arg) { .v = &layouts[arg->i] }));
}

//void
//cyclelayout(const Arg *arg)
//{
//	cyclelayout(&((Arg) ( .i = 1 << arg->i }));

void
viewex(const Arg *arg)
{
	view(&((Arg) { .ui = 1 << arg->ui }));
}

void
viewall(const Arg *arg)
{
	view(&((Arg){.ui = ~0}));
}

void
toggleviewex(const Arg *arg)
{
	toggleview(&((Arg) { .ui = 1 << arg->ui }));
}

void
tagex(const Arg *arg)
{
	tag(&((Arg) { .ui = 1 << arg->ui }));
}

void
toggletagex(const Arg *arg)
{
	toggletag(&((Arg) { .ui = 1 << arg->ui }));
}

void
tagall(const Arg *arg)
{
	tag(&((Arg){.ui = ~0}));
}

/* signal definitions */
/* signum must be greater than 0 */
/* trigger signals using `xsetroot -name "fsignal:<signame> [<type> <value>]"` */
static Signal signals[] = {
	/* signum           function */
	{ "focusstack",     focusstack },
	{ "setmfact",       setmfact },
	{ "togglebar",      togglebar },
	{ "incnmaster",     incnmaster },
	{ "togglefloating", togglefloating },
	{ "togglefullscr",  togglefullscr },
	{ "togglesticky",   togglesticky },
	{ "focusmon",       focusmon },
	{ "tagmon",         tagmon },
	{ "zoom",           zoom },
	{ "view",           view },
	{ "viewall",        viewall },
	{ "viewex",         viewex },
	{ "toggleview",     view },
	{ "toggleviewex",   toggleviewex },
	{ "tag",            tag },
	{ "tagall",         tagall },
	{ "tagex",          tagex },
	{ "toggletag",      tag },
	{ "toggletagex",    toggletagex },
	{ "killclient",     killclient },
	{ "quit",           quit },
	{ "setlayout",      setlayout },
	{ "setlayoutex",    setlayoutex },
	{ "cyclelayout",    cyclelayout },
	{ "pushup",         pushup },
	{ "pushdown",       pushdown },
	{ "togglescratch",  togglescratch },
};
