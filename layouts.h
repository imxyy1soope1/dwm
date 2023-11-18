#ifndef LAYOUTS_H_
#define LAYOUTS_H_

#include "dwm.h"

void bstack(Monitor *m);
void bstackhoriz(Monitor *m);
void centeredmaster(Monitor *m);
void centeredfloatingmaster(Monitor *m);
void deck(Monitor *m);
void dwindle(Monitor *m);
void spiral(Monitor *m);
void grid(Monitor *m);
void gaplessgrid(Monitor *m);
void horizgrid(Monitor *m);
void nrowgrid(Monitor *m);
void tile(Monitor *m);

#endif /* LAYOUTS_H_ */
