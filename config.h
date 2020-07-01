/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static const int swallowfloating    = 1;        /* 1 means swallow floating windows by default */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10", "JoyPixels:size=10", "Font Awesome:size=10" };
static const char col_black[]       = "#000000";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_white[] 	    = "#ffffff";
static const char col_dblue[] 	    = "#270e68";
static const char col_cyan[]        = "#005577";
static const char col_lblue[] 	    = "#00c6c3";
static const char col_red[] 	    = "#d50000";
static const char col_orng[] 	    = "#fa7a07";
static const char col_pink[] 	    = "#fe44ef";
static const unsigned int transparent = 0;
static const unsigned int translucent = 0xd0;
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_white, col_black, col_dblue },
	[SchemeSel]  = { col_gray1, col_lblue,  col_pink  },
};
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, transparent, OPAQUE },
	[SchemeSel]  = { OPAQUE, OPAQUE, OPAQUE },
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
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
	{"splf",	spcmd2},
	{"sppm",	spcmd3},
	{"sppu",	spcmd4},
	{"spclac",	spcmd5},
	{"spsurf",	spcmd6},
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
/* static const char *tags[] = { "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX" }; */

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
	{ "st",       NULL,      "lfmpv",     0,            1,		1,          1,		1,        -1 },
	{ "st",       NULL,    "/bin/sh",     0,            1,		1,          1,		1,        -1 },
	{ "st",       NULL,   "popupgrade",   0 << 8,       1,		1,          1,		1,        -1 },

	/* All the scratch pads */
	{ NULL,	      "spterm",	  NULL,	    SPTAG(0),	    1,		1,	    1,		0,        -1 },
	{ NULL,	      "splf",	  NULL,	    SPTAG(1),	    1,		1,	    1,		0,        -1 },
	{ NULL,	      "sppm",	  NULL,	    SPTAG(2),	    1,		1,	    1,		0,        -1 },
	{ NULL,	      "sppu",	  NULL,	    SPTAG(3),	    1,		1,	    1,		0,        -1 },
	{ NULL,	      "spcalc",	  NULL,	    SPTAG(4),	    1,		1,	    1,		0,        -1 },
	{ NULL,	      "spsurf",	  NULL,	    SPTAG(5),	    1,		1,	    0,		0,        -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#include "vanitygaps.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",	tile },			/* Master on left, slaves on right */
	{ "TTT",	bstack },		/* Master on top, slaves on bottom */


	{ "[@]",	spiral },		/* Fibonacci spiral */
	{ "[\\]",	dwindle },		/* Decreasing in size right and leftward */


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

#include <X11/XF86keysym.h>
#include "push.c"
#include "focusurgent.c"
static Key keys[] = {
	/* modifier                     key        	function        argument */

	/* dwm control keys */
	{ MODKEY,                       XK_b,     	togglebar,      {0} },
	{ MODKEY,			XK_x,	  	incrgaps,	{.i = +3 } },
	{ MODKEY,			XK_z,	  	incrgaps,	{.i = -3 } },
	{ MODKEY,			XK_a,	  	togglegaps, 	{0} },
	{ MODKEY|ControlMask,		XK_a,	  	defaultgaps,	{0} },
	{ MODKEY|ShiftMask,             XK_x, 		setborderpx,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_z, 		setborderpx,    {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_a,	 	setborderpx,    {.i = 0 } },
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
	{ MODKEY,			XK_q,     	killclient,   	{0} },
	{ MODKEY|ShiftMask,		XK_q,     	spawn,        	SHCMD("xdo kill") },
	{ MODKEY|ShiftMask,             XK_e,     	quit,         	{0} },
	{ MODKEY|ShiftMask|ControlMask, XK_e,     	quit,         	{1} },

	/* spawn Keys */
	{ MODKEY|ShiftMask,             XK_Return,	spawn,          SHCMD("$TERMINAL") },
	{ MODKEY|ShiftMask,		XK_b,		spawn,		SHCMD("$TERMINAL -e bmon -p w*,*") },
	{ MODKEY,			XK_d,		spawn,		SHCMD("dmenu_run -l 20") },
	{ MODKEY|ShiftMask,		XK_d,		spawn,		SHCMD("geodoppler") },
	{ MODKEY,			XK_v,		spawn,		SHCMD("$TERMINAL -e lf") },
	{ MODKEY,			XK_e,		spawn,		SHCMD("$TERMINAL -e neomutt; kill -$((34+12)) $(pidof dwmblocks)") },
	{ MODKEY,			XK_t,		spawn,		SHCMD("torwrap; kill -$((34+7)) $(pidof dwmblocks)") },
	{ MODKEY|ShiftMask,		XK_t,		spawn,		SHCMD("$TERMINAL -e toxic") },
	{ MODKEY|ShiftMask,		XK_h,		spawn,		SHCMD("selectionhandler dmenuhandler") },
	{ MODKEY|ControlMask,		XK_h,		spawn,		SHCMD("selectionhandler linkhandler") },
	{ MODKEY|ShiftMask|ControlMask, XK_h,		spawn,		SHCMD("$TERMINAL -e htop") },
	{ MODKEY,			XK_g,		spawn,		SHCMD("$TERMINAL -e gotop") },
	{ MODKEY,			XK_n,		spawn,		SHCMD("$TERMINAL -e newsboat; kill -$((34+6)) $(pidof dwmblocks)") },
	{ MODKEY,			XK_c,		spawn,		SHCMD("$TERMINAL -e calcurse -D ~/.config/calcurse") },
	{ MODKEY|ControlMask,		XK_c,		spawn,		SHCMD("camtoggle") },
	{ MODKEY,			XK_w,		spawn,		SHCMD("$BROWSER") },
	{ MODKEY|ShiftMask,		XK_w,		spawn,		SHCMD("$TERMINAL -e nmtui; kill -$((34+2)) $(pidof dwmblocks) && kill -$((34+4)) $(pifof dwmblocks)") },

	/* scratch pads */
	{ MODKEY,            		XK_y,  	   togglescratch,  {.ui = 0 } },
	{ MODKEY,            		XK_u,	   togglescratch,  {.ui = 1 } },
	{ MODKEY|ShiftMask,             XK_p,	   togglescratch,  {.ui = 2 } },
	{ MODKEY|ControlMask,           XK_p,	   togglescratch,  {.ui = 3 } },
	{ MODKEY|ShiftMask,            	XK_c, 	   togglescratch,  {.ui = 4 } },
	{ MODKEY,            		XK_i, 	   togglescratch,  {.ui = 5 } },

	/* control keys */
	{ MODKEY,			XK_grave,	spawn,		SHCMD("dmenuunicode") },
	{ MODKEY,			XK_Insert,	spawn,		SHCMD("showclip") },
	{ MODKEY|ShiftMask,		XK_Insert,	spawn,		SHCMD("switchclip") },
	{ MODKEY|ShiftMask,		XK_s,		spawn,		SHCMD("selectionswitch") },
	{ MODKEY|ShiftMask,		XK_i,		spawn,		SHCMD("speedtest-notify") },
	{ MODKEY|ShiftMask,		XK_r,		spawn,		SHCMD("dmenuresp") },
	{ MODKEY|ControlMask,		XK_r,		spawn,		SHCMD("dmenurefbar") },
	{ MODKEY|ShiftMask,		XK_l,		spawn,		SHCMD("$LOCKER & sleep 1 && sysact hibernate") },

	/* recording keys */
	{ MODKEY,			XK_F12,		spawn,		SHCMD("maim pic-full-$(date '+%y%m%d-%H%M-%S').png") },
	{ MODKEY|ShiftMask,		XK_F12,		spawn,		SHCMD("maimpick") },
	{ MODKEY,			XK_r,		spawn,		SHCMD("dmenurecord; kill -$((34+9)) $(pidof dwmblocks)") },
	{ MODKEY,			XK_Delete,	spawn,		SHCMD("dmenurecord kill; kill -$((34+9)) $(pidof dwmblocks)") },

	/* power keys */
	{ MODKEY|ShiftMask,		XK_Escape,	spawn,		SHCMD("sysact") },

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
	{ 0, XF86XK_Mail,		spawn,		SHCMD("$TERMINAL -e neomutt ; kill -$((34+12)) $(pidof dwmblocks)") },
	{ 0, XF86XK_MyComputer,		spawn,		SHCMD("$TERMINAL -e lf") },
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
	{ MODKEY,			XK_F8,		spawn,		SHCMD("notify-send '📧 Syncing Mail'; mailsync && notify-send '📧 Mail Synced'; kill -$((34+12)) $(pidof dwmblocks)") },
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
	{ ClkStatusText,        ShiftMask,      Button2,        sigdwmblocks,   {.i = 7} },
	{ ClkStatusText,        ShiftMask,      Button3,        spawn,          SHCMD("st -e nvim ~/.local/src/dwmblocks/blocks.h") },
	{ ClkStatusText,        ControlMask,    Button1,        sigdwmblocks,   {.i = 8} },
	{ ClkStatusText,        ControlMask,    Button2,        sigdwmblocks,   {.i = 9} },
	{ ClkStatusText,        ControlMask,    Button3,        sigdwmblocks,   {.i = 10} },
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

void
tagall(const Arg *arg)
{
	tag(&((Arg){.ui = ~0}));
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
toggleviewex(const Arg *arg)
{
	toggleview(&((Arg) { .ui = 1 << arg->ui }));
}

void
viewall(const Arg *arg)
{
	view(&((Arg){.ui = ~0}));
}

void
viewex(const Arg *arg)
{
	view(&((Arg) { .ui = 1 << arg->ui }));
}

/* signal definitions */
/* signum must be greater than 0 */
/* trigger signals using `xsetroot -name "fsignal:<signame> [<type> <value>]"` */
static Signal signals[] = {
	/* signum           function */
	{ "cyclelayout",    cyclelayout },
	{ "focusmon",       focusmon },
	{ "focusstack",     focusstack },
	{ "incnmaster",     incnmaster },
	{ "incrgaps",	    incrgaps },
	{ "killclient",     killclient },
	{ "pushdown",       pushdown },
	{ "pushup",         pushup },
	{ "quit",           quit },
	{ "setborderpx",    setborderpx },
	{ "setlayout",      setlayout },
	{ "setlayoutex",    setlayoutex },
	{ "setmfact",       setmfact },
	{ "tag",            tag },
	{ "tagall",         tagall },
	{ "tagex",          tagex },
	{ "tagmon",         tagmon },
	{ "togglebar",      togglebar },
	{ "togglefloating", togglefloating },
	{ "togglefullscr",  togglefullscr },
	{ "togglegaps",	    togglegaps },
	{ "togglescratch",  togglescratch },
	{ "togglesticky",   togglesticky },
	{ "toggletag",      tag },
	{ "toggletagex",    toggletagex },
	{ "toggleview",     view },
	{ "toggleviewex",   toggleviewex },
	{ "view",           view },
	{ "viewall",        viewall },
	{ "viewex",         viewex },
	{ "zoom",           zoom },
};
