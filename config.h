/* See LICENSE file for copyright and license details. */

#ifndef CONFIG_H_
#define CONFIG_H_

#include <stddef.h>
#include <X11/keysym.h>
#include <X11/XF86keysym.h>

#include "dwm.h"
#include "layouts.h"
#include "ipc.h"

/* appearance */
static const unsigned int borderpx  = 5;        /* border pixel of windows */
static const unsigned int snap      = 10;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static const int showbar            = 0;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
    /*               fg         bg         border   */
    [SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
    [SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10" };

static const Rule rules[] = {
    /* xprop(1):
     *  WM_CLASS(STRING) = instance, class
     *  WM_NAME(STRING) = title
     */
    /* class     instance  title           tags mask          isfloating  isterminal  noswallow  monitor */
    { "ft",      NULL,     NULL,           0,                 1,          1,           0,        -1 },
    { "sp",      NULL,     NULL,           (unsigned int)~0,  1,          1,           0,        -1 },
    { NULL,      NULL,     "Event Tester", 0,                 0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
    /* symbol     arrange function */
    { "[]=",      tile                   },  /* first entry is default */
    { "[M]",      monocle                },
    { "[@]",      spiral                 },
    { "[\\]",     dwindle                },
    { "H[]",      deck                   },
    { "TTT",      bstack                 },
    { "===",      bstackhoriz            },
    { "HHH",      grid                   },
    { "###",      nrowgrid               },
    { "---",      horizgrid              },
    { ":::",      gaplessgrid            },
    { "|M|",      centeredmaster         },
    { ">M>",      centeredfloatingmaster },
    { "><>",      NULL                   },  /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod4Mask  /* SUPER */
#define TAGKEYS(KEY,TAG) \
    { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
    { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

#define CMD(cmd) { .v = cmd }

static const Key keys[] = {
    /* modifier                     key        function          argument */
    { MODKEY,                       XK_r,      spawn,            CMD("~/bin/rofi-launcher") },
    { ControlMask|Mod1Mask,         XK_t,      spawn,            CMD("alacritty") },
    { MODKEY,                       XK_Return, spawn,            CMD("alacritty --class=ft") },
    { ControlMask|Mod1Mask,         XK_Return, spawn,            CMD("alacritty --class=sp") },
    { MODKEY,                       XK_e,      spawn,            CMD("nemo") },
    { MODKEY,                       XK_g,      spawn,            CMD("microsoft-edge-stable") },
    { MODKEY,                       XK_Down,   focusstack,       {.i = +1 } },
    { MODKEY,                       XK_Up,     focusstack,       {.i = -1 } },
    { MODKEY,                       XK_i,      incnmaster,       {.i = +1 } },
    { MODKEY,                       XK_d,      incnmaster,       {.i = -1 } },
    { MODKEY,                       XK_Left,   setmfact,         {.f = -0.05} },
    { MODKEY,                       XK_Right,  setmfact,         {.f = +0.05} },
    { MODKEY|ShiftMask,             XK_Return, zoom,             {0} },
    { MODKEY,                       XK_Tab,    view,             {0} },
    { MODKEY,                       XK_q,      killclient,       {0} },
    { MODKEY,                       XK_t,      setlayout,        {.v = &layouts[0]} },
    { MODKEY,                       XK_m,      togglefullscreen, {0} },
    { MODKEY,                       XK_f,      togglefloating,   {0} },
    { MODKEY,                       XK_Tab,    view,             {.ui = (unsigned) ~0 } },
    { MODKEY|ShiftMask,             XK_Tab,    tag,              {.ui = (unsigned) ~0 } },
    { MODKEY,                       XK_comma,  focusmon,         {.i = -1 } },
    { MODKEY,                       XK_period, focusmon,         {.i = +1 } },
    { MODKEY|ShiftMask,             XK_comma,  tagmon,           {.i = -1 } },
    { MODKEY|ShiftMask,             XK_period, tagmon,           {.i = +1 } },
    { MODKEY|ShiftMask,             XK_r,      restart,          {0} },
    { MODKEY,                       XK_Escape, spawn,            CMD("~/bin/power-menu/powermenu.sh") },
    TAGKEYS(                        XK_1,                        0)
    TAGKEYS(                        XK_2,                        1)
    TAGKEYS(                        XK_3,                        2)
    TAGKEYS(                        XK_4,                        3)
    TAGKEYS(                        XK_5,                        4)
    TAGKEYS(                        XK_6,                        5)
    TAGKEYS(                        XK_7,                        6)
    TAGKEYS(                        XK_8,                        7)
    TAGKEYS(                        XK_9,                        8)
    TAGKEYS(                        XK_0,                        9)
};

/* auto execs definition */

#define HOME "/home/imxyy"
#define EXECUTER HOME"/bin/executer"
#define EXECWRAP(cmd) CMD(EXECUTER " " cmd)

static const Exec execs[] = {
    /* cmd                                                                      once */
    { EXECWRAP("picom --experimental-backends"),                                0 },
    { EXECWRAP("fcitx5"),                                                       0 },
    { EXECWRAP("cfw"),                                                          0 },
    { EXECWRAP("blueman-applet"),                                               0 },
    { EXECWRAP("nm-applet"),                                                    0 },
    { EXECWRAP("/usr/lib/polkit-gnome/polkit-gnome-authentication-agent-1"),    0 },
    { CMD("bluetoothreset"),                                                    1 },
    { CMD("echo 'Xft.dpi:125' | xrdb -merge"),                                  1 },
    { CMD("sleep 1; feh --bg-fill ~/Pictures/wallpaper/simple.png"),            1 },
};

#undef TAGKEYS
#undef CMD
#undef EXECUTER
#undef EXECWRAP

static const Env envs[] = {
    /* name                     value              replace */
    {  "DESKTOP_SESSION",       "dwm",             1 },
    {  "XDG_CURRENT_DESKTOP",   "dwm",             1 },
    {  "GTK_IM_MODULE",         "fcitx",           1 },
    {  "QT_IM_MODULE",          "fcitx",           1 },
    {  "XMODIFIERS",            "@im=fcitx",       1 },
};

static const char *ipcsockpath = "/tmp/dwm.sock";
static IPCCommand ipccommands[] = {
    IPCCOMMAND( view,                1,      {ARG_TYPE_UINT}  ),
    IPCCOMMAND( toggleview,          1,      {ARG_TYPE_UINT}  ),
    IPCCOMMAND( tag,                 1,      {ARG_TYPE_UINT}  ),
    IPCCOMMAND( toggletag,           1,      {ARG_TYPE_UINT}  ),
    IPCCOMMAND( tagmon,              1,      {ARG_TYPE_UINT}  ),
    IPCCOMMAND( focusmon,            1,      {ARG_TYPE_SINT}  ),
    IPCCOMMAND( focusstack,          1,      {ARG_TYPE_SINT}  ),
    IPCCOMMAND( zoom,                1,      {ARG_TYPE_NONE}  ),
    IPCCOMMAND( incnmaster,          1,      {ARG_TYPE_SINT}  ),
    IPCCOMMAND( killclient,          1,      {ARG_TYPE_SINT}  ),
    IPCCOMMAND( togglefloating,      1,      {ARG_TYPE_NONE}  ),
    IPCCOMMAND( setmfact,            1,      {ARG_TYPE_FLOAT} ),
    IPCCOMMAND( setlayoutsafe,       1,      {ARG_TYPE_PTR}   ),
    IPCCOMMAND( quit,                1,      {ARG_TYPE_NONE}  )
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
    /* click                event mask      button          function        argument */
    { ClkLtSymbol,          0,              Button1,        setlayout,      {0}                },
    { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
    { ClkWinTitle,          0,              Button2,        zoom,           {0}                },
    { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0}                },
    { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0}                },
    { ClkTagBar,            0,              Button1,        view,           {0}                },
    { ClkTagBar,            0,              Button3,        toggleview,     {0}                },
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0}                },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0}                },
};

#endif /* CONFIG_H_ */
