# name of the program (Minix service)
PROG=proj

.PATH: ${.CURDIR}
.PATH: ${.CURDIR}/devices/
.PATH: ${.CURDIR}/devices/timer/
.PATH: ${.CURDIR}/devices/keyboard/
.PATH: ${.CURDIR}/devices/mouse/
.PATH: ${.CURDIR}/devices/video/
.PATH: ${.CURDIR}/devices/serial_port/
.PATH: ${.CURDIR}/devices/rtc/
.PATH: ${.CURDIR}/game/
.PATH: ${.CURDIR}/sprites/

# source code files to be compiled
SRCS = proj.c utils.c kbc.c timer.c keyboard.c mouse.c video.c serial_port.c rtc.c dispatcher.c sprite.c game.c menu.c chess.c

# additional compilation flags
# "-Wall -Wextra -Werror -I . -std=c11 -Wno-unused-parameter" are already set
CFLAGS += -pedantic -D D_LCOM_OPTIMIZED_

# list of library dependencies (for Lab 2, only LCF library)
DPADD += ${LIBLCF}
LDADD += -llcf

# include LCOM's makefile that does all the "heavy lifting"
.include <minix.lcom.mk>