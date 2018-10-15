# ---------------------------------------------------------------------------
VERSION = BCB.01
# ---------------------------------------------------------------------------
!ifndef BCB
BCB = $(MAKEDIR)\..
!endif
# ---------------------------------------------------------------------------
PROJECT = SDIAPP.exe
OBJFILES = SDIAPP.obj SDIMain.obj About.obj Error.obj Prefs.obj Decode.obj \
   "\Documenti\Builder Projects\MyClass\WaveFile.obj"
RESFILES = SDIAPP.res
RESDEPEN = $(RESFILES) SDIMain.dfm About.dfm Error.dfm Prefs.dfm
LIBFILES = 
# ---------------------------------------------------------------------------
CFLAG1 = -O2 -Hc -w -k- -r -vi -c -a4 -b- -w-par -w-inl -Vx -Ve -x 
CFLAG2 = -I"d:\documenti\builder projects\myclass";"d:\builder projects\myclass";"d:\programmi\borland\cbuilder\projects\builder projects\myclass";"$(BCB)\projects\builder projects\myclass";$(BCB)\projects;$(BCB)\include;$(BCB)\include\vcl \
   -H=$(BCB)\lib\vcl.csm 
PFLAGS = -U"d:\documenti\builder projects\myclass";"d:\builder projects\myclass";"d:\programmi\borland\cbuilder\projects\builder projects\myclass";"$(BCB)\projects\builder projects\myclass";$(BCB)\projects;$(BCB)\lib\obj;$(BCB)\lib \
   -I"d:\documenti\builder projects\myclass";"d:\builder projects\myclass";"d:\programmi\borland\cbuilder\projects\builder projects\myclass";"$(BCB)\projects\builder projects\myclass";$(BCB)\projects;$(BCB)\include;$(BCB)\include\vcl \
   -AWinTypes=Windows;WinProcs=Windows;DbiTypes=BDE;DbiProcs=BDE;DbiErrs=BDE -$L- \
   -$D- -JPHNV -M  
RFLAGS = -i"d:\documenti\builder projects\myclass";"d:\builder projects\myclass";"d:\programmi\borland\cbuilder\projects\builder projects\myclass";"$(BCB)\projects\builder projects\myclass";$(BCB)\projects;$(BCB)\include;$(BCB)\include\vcl 
LFLAGS = -L"d:\documenti\builder projects\myclass";"d:\builder projects\myclass";"d:\programmi\borland\cbuilder\projects\builder projects\myclass";"$(BCB)\projects\builder projects\myclass";$(BCB)\projects;$(BCB)\lib\obj;$(BCB)\lib \
   -aa -Tpe -x -V4.0
IFLAGS = 
LINKER = ilink32
# ---------------------------------------------------------------------------
ALLOBJ = c0w32.obj $(OBJFILES)
ALLRES = $(RESFILES)
ALLLIB = $(LIBFILES) vcl.lib import32.lib cp32mt.lib 
# ---------------------------------------------------------------------------
.autodepend

$(PROJECT): $(OBJFILES) $(RESDEPEN)
    $(BCB)\BIN\$(LINKER) @&&!
    $(LFLAGS) +
    $(ALLOBJ), +
    $(PROJECT),, +
    $(ALLLIB),, +
    $(ALLRES) 
!

.pas.hpp:
    $(BCB)\BIN\dcc32 $(PFLAGS) { $** }

.pas.obj:
    $(BCB)\BIN\dcc32 $(PFLAGS) { $** }

.cpp.obj:
    $(BCB)\BIN\bcc32 $(CFLAG1) $(CFLAG2) -o$* $* 

.c.obj:
    $(BCB)\BIN\bcc32 $(CFLAG1) $(CFLAG2) -o$* $**

.rc.res:
    $(BCB)\BIN\brcc32 $(RFLAGS) $<
#-----------------------------------------------------------------------------
