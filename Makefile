# dwm - dynamic window manager
# See LICENSE file for copyright and license details.

include config.mk

SRC = drw.c dwm.c util.c layouts.c IPCClient.c yajl_dumps.c ipc.c
OBJ = ${SRC:.c=.o}

all: options dwm dwm-msg

check: options dwm clean

options:
	@echo dwm build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"

.c.o:
	@${CC} -c ${CFLAGS} $<

${OBJ}: config.h config.mk

dwm: ${OBJ}
	@${CC} -s -o $@ ${OBJ} ${LDFLAGS}

dwm-msg: dwm-msg.o
	@${CC} -s -o $@ $< ${LDFLAGS}

clean:
	@rm -f dwm dwm-msg dwm-msg.o ${OBJ} dwm-${VERSION}.tar.gz

dist: clean
	@mkdir -p dwm-${VERSION}
	@cp -R LICENSE Makefile README config.def.h config.mk\
		dwm.1 drw.h util.h ${SRC} dwm.png transient.c dwm-${VERSION}
	@tar -cf dwm-${VERSION}.tar dwm-${VERSION}
	@gzip dwm-${VERSION}.tar
	@rm -rf dwm-${VERSION}

install: all
	@mkdir -p ${DESTDIR}${PREFIX}/bin
	@cp -f dwm dwm-msg ${DESTDIR}${PREFIX}/bin
	@chmod 755 ${DESTDIR}${PREFIX}/bin/dwm
	@chmod 755 ${DESTDIR}${PREFIX}/bin/dwm-msg
	@mkdir -p ${DESTDIR}${MANPREFIX}/man1
	@sed "s/VERSION/${VERSION}/g" < dwm.1 > ${DESTDIR}${MANPREFIX}/man1/dwm.1
	@chmod 644 ${DESTDIR}${MANPREFIX}/man1/dwm.1
	@rm -f dwm dwm-msg dwm-msg.o ${OBJ} dwm-${VERSION}.tar.gz

uninstall:
	@rm -f ${DESTDIR}${PREFIX}/bin/dwm\
		${DESTDIR}${MANPREFIX}/man1/dwm.1

.PHONY: all options clean dist install uninstall
