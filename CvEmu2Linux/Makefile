# Project: cvemu2
# Makefile created by Dev-C++ 4.9.8.3
# Modified (manually!) by Giovanni Ortu A.D. 11 November 2003

VERSION = 0
PATCHLEVEL = 5
SUBLEVEL = 0
EXTRAVERSION = -beta

PROGRAMRELEASE=$(VERSION).$(PATCHLEVEL).$(SUBLEVEL)$(EXTRAVERSION)
SDLDIR = libsdl
#CINCS =  -I"/usr/include/c++/3.2.2"
BINDIR = /usr/local/bin

CPP  = g++
OBJ  = video/tms9918.o mem/cvmemory.o cpu/cpu6502.o pia/6821pia.o video/drv9918.o font/font.o main.o audio/sn76496.o menu/menu.o savestate/savestate.o keyboard/keyboard.o
LINKOBJ  = $(OBJ) $(SDLDIR)/libSDL.so
#LIBS =  -L"/usr/lib"
BIN  = ../cvemu2
CFLAGS =   -w -O3


.PHONY: all all-before all-after clean clean-custom

all: all-before $(BIN) all-after

clean: clean-custom
	rm -f $(OBJ) $(BIN)

install: 
	cp $(BIN) $(BINDIR)

$(BIN): $(LINKOBJ)
	$(CPP) $(LINKOBJ) -o $(BIN) $(LIBS)


video/tms9918.o: video/tms9918.c video/tms9918.h
	$(CPP) -c video/tms9918.c -o video/tms9918.o $(CFLAGS)

mem/cvmemory.o: mem/cvmemory.c mem/cvmemory.h mem/../include/defs.h
	$(CPP) -c mem/cvmemory.c -o mem/cvmemory.o $(CFLAGS)

cpu/cpu6502.o: cpu/cpu6502.c cpu/cpu6502.h cpu/../include/defs.h    cpu/../video/tms9918.h cpu/../pia/6821pia.h cpu/../pia/../include/memory.h
	$(CPP) -c cpu/cpu6502.c -o cpu/cpu6502.o $(CFLAGS)

pia/6821pia.o: pia/6821pia.c pia/6821pia.h pia/../include/memory.h    pia/../audio/sn76496.h
	$(CPP) -c pia/6821pia.c -o pia/6821pia.o $(CFLAGS)

video/drv9918.o: video/drv9918.c video/tms9918.h
	$(CPP) -c video/drv9918.c -o video/drv9918.o $(CFLAGS)

font/font.o: font/font.cpp include/../font/font.h
	$(CPP) -c font/font.cpp -o font/font.o $(CFLAGS)

main.o: main.cpp include/defs.h include/memory.h font/font.h  cpu/cpu6502.h  cpu/../video/tms9918.h video/tms9918.h mem/cvmemory.h    mem/../include/defs.h pia/6821pia.h pia/../include/memory.h    audio/sn76496.h main.h
	$(CPP)  -c main.cpp -o main.o $(CFLAGS)

audio/sn76496.o: audio/sn76496.c audio/sn76496.h
	$(CPP) -c audio/sn76496.c -o audio/sn76496.o  $(CFLAGS)

menu/menu.o: menu/menu.c menu/../include/defs.h menu/menu.h
	$(CPP) -c menu/menu.c -o menu/menu.o  $(CFLAGS)

savestate/savestate.o: savestate/savestate.c savestate/savestate.h
	$(CPP) -c savestate/savestate.c -o savestate/savestate.o  $(CFLAGS)

keyboard/keyboard.o: keyboard/keyboard.c keyboard/keyboard.h
	$(CPP) -c keyboard/keyboard.c -o keyboard/keyboard.o  $(CFLAGS)
