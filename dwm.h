/* See LICENSE file for copyright and license details. */

#ifndef DWM_H_
#define DWM_H_

#include <bits/types/FILE.h>
#include <sys/epoll.h>
#include <X11/Xlib.h>

/* macros */
#define BUTTONMASK              (ButtonPressMask|ButtonReleaseMask)
#define CLEANMASK(mask)         (mask & ~(numlockmask|LockMask) & (ShiftMask|ControlMask|Mod1Mask|Mod2Mask|Mod3Mask|Mod4Mask|Mod5Mask))
#define INTERSECT(x,y,w,h,m)    (MAX(0, MIN((x)+(w),(m)->wx+(m)->ww) - MAX((x),(m)->wx)) \
    * MAX(0, MIN((y)+(h),(m)->wy+(m)->wh) - MAX((y),(m)->wy)))
#define ISVISIBLE(C)            ((C->tags & C->mon->tagset[C->mon->seltags]))
#define LENGTH(X)               (sizeof X / sizeof X[0])
#define MOUSEMASK               (BUTTONMASK|PointerMotionMask)
#define WIDTH(X)                ((X)->w + 2 * (X)->bw)
#define HEIGHT(X)               ((X)->h + 2 * (X)->bw)
#define TAGMASK                 ((1 << LENGTH(tags)) - 1)
#define TEXTW(X)                (drw_fontset_getwidth(drw, (X)) + lrpad)

/* enums */
enum { CurNormal, CurResizeTL, CurResizeTR, CurResizeBL, CurResizeBR, CurMove, CurLast }; /* cursor */
enum { SchemeNorm, SchemeSel }; /* color schemes */
enum { NetSupported, NetWMName, NetWMState, NetWMCheck,
       NetWMFullscreen, NetActiveWindow, NetWMWindowType,
       NetWMWindowTypeDialog, NetClientList, NetLast }; /* EWMH atoms */
enum { WMProtocols, WMDelete, WMState, WMTakeFocus, WMLast }; /* default atoms */
enum { ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
       ClkClientWin, ClkRootWin, ClkLast }; /* clicks */

typedef struct{
	int selected;
	int occupied;
	int urgent;
} TagState;

typedef struct {
	int isfixed, isfloating, isurgent, neverfocus, oldstate, isfullscreen;
} ClientState;

typedef union {
    long i;
    unsigned long ui;
    float f;
    const void *v;
} Arg;

typedef struct {
    unsigned int click;
    unsigned int mask;
    unsigned int button;
    void (*func)(const Arg *arg);
    const Arg arg;
} Button;

typedef struct Monitor Monitor;
typedef struct Client Client;
struct Client {
    char name[256];
    float mina, maxa;
    int x, y, w, h;
    int oldx, oldy, oldw, oldh;
    int floatx, floaty, floatw, floath;
    int basew, baseh, incw, inch, maxw, maxh, minw, minh, hintsvalid;
    int bw, oldbw;
    unsigned int tags;
    int isfixed, isfloating, isurgent, neverfocus, oldstate, isfullscreen, isterminal, noswallow;
    pid_t pid;
    Client *next;
    Client *snext;
    Client *swallowing;
    Monitor *mon;
    Window win;
    ClientState prevstate;
};

typedef struct {
    unsigned int mod;
    KeySym keysym;
    void (*func)(const Arg *);
    const Arg arg;
} Key;

typedef struct {
    const Arg arg;
    int once;
} Exec;

typedef struct {
    const char *name, *value;
    int replace;
} Env;

typedef struct {
    const char *symbol;
    void (*arrange)(Monitor *);
} Layout;

struct Monitor {
    char ltsymbol[16];
    char lastltsymbol[16];
    float mfact;
    int nmaster;
    int num;
    int by;               /* bar geometry */
    int mx, my, mw, mh;   /* screen size */
    int wx, wy, ww, wh;   /* window area  */
    int gappih;           /* horizontal gap between windows */
    int gappiv;           /* vertical gap between windows */
    int gappoh;           /* horizontal outer gaps */
    int gappov;           /* vertical outer gaps */
    unsigned int seltags;
    unsigned int sellt;
    unsigned int tagset[2];
    TagState tagstate;
    int showbar;
    int topbar;
    Client *clients;
    Client *sel;
    Client *lastsel;
    Client *stack;
    Monitor *next;
    Window barwin;
    const Layout *lt[2];
    const Layout *lastlt;
};

typedef struct {
    const char *cls;
    const char *instance;
    const char *title;
    unsigned int tags;
    int isfloating;
    int isterminal;
    int noswallow;
    int monitor;
} Rule;

/* variables */
extern int bh;
extern FILE *_log;

/* function declarations */
void applyexecs(void);
void applyrules(Client *c);
int applysizehints(Client *c, int *x, int *y, int *w, int *h, int interact);
void arrange(Monitor *m);
void arrangemon(Monitor *m);
void attach(Client *c);
void attachstack(Client *c);
void buttonpress(XEvent *e);
void checkotherwm(void);
void cleanup(void);
void cleanupmon(Monitor *mon);
void clientmessage(XEvent *e);
void configure(Client *c);
void configurenotify(XEvent *e);
void configurerequest(XEvent *e);
Monitor *createmon(void);
void destroynotify(XEvent *e);
void detach(Client *c);
void detachstack(Client *c);
Monitor *dirtomon(int dir);
void drawbar(Monitor *m);
void drawbars(void);
void enternotify(XEvent *e);
void expose(XEvent *e);
void focus(Client *c);
void focusin(XEvent *e);
void focusmon(const Arg *arg);
void focusstack(const Arg *arg);
Atom getatomprop(Client *c, Atom prop);
pid_t getparentprocess(pid_t p);
int getrootptr(int *x, int *y);
long getstate(Window w);
int gettextprop(Window w, Atom atom, char *text, unsigned int size);
void grabbuttons(Client *c, int focused);
void grabkeys(void);
int handlexevnet(struct epoll_event *ev);
void incnmaster(const Arg *arg);
int isdescprocess(pid_t p, pid_t c);
void keypress(XEvent *e);
void killclient(const Arg *arg);
void manage(Window w, XWindowAttributes *wa);
void mappingnotify(XEvent *e);
void maprequest(XEvent *e);
void monocle(Monitor *m);
void motionnotify(XEvent *e);
void movemouse(const Arg *arg);
Client *nexttiled(Client *c);
void pop(Client *c);
void propertynotify(XEvent *e);
void quit(const Arg *arg);
Monitor *recttomon(int x, int y, int w, int h);
void resize(Client *c, int x, int y, int w, int h, int interact);
void resizeclient(Client *c, int x, int y, int w, int h);
void resizemouse(const Arg *arg);
void restack(Monitor *m);
void restart(const Arg *arg);
void run(void);
void scan(void);
int sendevent(Client *c, Atom proto);
void sendmon(Client *c, Monitor *m);
void setclientstate(Client *c, long state);
void setfocus(Client *c);
void setfullscreen(Client *c, int fullscreen);
void setlayout(const Arg *arg);
void setlayoutsafe(const Arg *arg);
void setmfact(const Arg *arg);
void setup(void);
void setupepoll(void);
void seturgent(Client *c, int urg);
void showhide(Client *c);
void spawn(const Arg *arg);
void swallow(Client *p, Client *c);
Client *swallowingclient(Window w);
void tag(const Arg *arg);
void tagmon(const Arg *arg);
Client *termforwin(const Client *c);
void togglebar(const Arg *arg);
void togglefloating(const Arg *arg);
void togglefullscreen(const Arg *arg);
void toggletag(const Arg *arg);
void toggleview(const Arg *arg);
void unfocus(Client *c, int setfocus);
void unmanage(Client *c, int destroyed);
void unmapnotify(XEvent *e);
void unswallow(Client *c);
void updatebarpos(Monitor *m);
void updatebars(void);
void updateclientlist(void);
int updategeom(void);
void updatenumlockmask(void);
void updatesizehints(Client *c);
void updatestatus(void);
void updatetitle(Client *c);
void updatewindowtype(Client *c);
void updatewmhints(Client *c);
void view(const Arg *arg);
pid_t winpid(Window w);
Client *wintoclient(Window w);
Monitor *wintomon(Window w);
int xerror(Display *dpy, XErrorEvent *ee);
int xerrordummy(Display *dpy, XErrorEvent *ee);
int xerrorstart(Display *dpy, XErrorEvent *ee);
void zoom(const Arg *arg);

#endif /* DWM_H_ */
