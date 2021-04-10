CC=gcc  -g -O2
SRC1 = $(wildcard src/*.c)
SRC2 = $(wildcard rstats/*.c)
OEXT = .o
EEXT = 
RAINSRC = $(wildcard rain/*.c)
RMOBJ = obj/*.o obj/*.obj
RAINOBJS = obj/functions.o
CPPFLAGS = -Isrc -Irain
LDFLAGS = -Llib -lm -lgsl -lblas
STARGET = functions
TARGET0 = 2Darrays
TARGET1 = gsl1
TARGET2 = monthlyrain
TARGET3 = rainstats
TARGET4 = yearlyrain
TARGETS = yearlyrain rainstats monthlyrain gsl1 2Darrays
all: $(TARGETS)
obj/$(STARGET)$(OEXT): rain/$(STARGET).c
	$(CC) -c  $< -o obj/$(STARGET)$(OEXT) $(CPPFLAGS)
obj/$(TARGET0)$(OEXT): src/2Darrays.c
	$(CC) -c   $< -o obj/2Darrays$(OEXT) $(CPPFLAGS)
$(TARGET0): obj/2Darrays$(OEXT)
	$(CC) -o 2Darrays $< $(LDFLAGS)
obj/$(TARGET1)$(OEXT): src/gsl1.c
	$(CC) -c   $< -o obj/gsl1$(OEXT) $(CPPFLAGS)
$(TARGET1): obj/gsl1$(OEXT)
	$(CC) -o gsl1 $< $(LDFLAGS)
obj/$(TARGET2)$(OEXT): rstats/monthlyrain.c
	$(CC) -c   $< -o obj/monthlyrain$(OEXT) $(CPPFLAGS)
$(TARGET2): obj/monthlyrain$(OEXT) $(RAINOBJS)
	$(CC) -o monthlyrain $? $(LDFLAGS)
obj/$(TARGET3)$(OEXT): rstats/rainstats.c
	$(CC) -c   $< -o obj/rainstats$(OEXT) $(CPPFLAGS)
$(TARGET3): obj/rainstats$(OEXT) $(RAINOBJS)
	$(CC) -o rainstats $? $(LDFLAGS)
obj/$(TARGET4)$(OEXT): rstats/yearlyrain.c
	$(CC) -c   $< -o obj/yearlyrain$(OEXT) $(CPPFLAGS)
$(TARGET4): obj/yearlyrain$(OEXT) $(RAINOBJS)
	$(CC) -o yearlyrain $? $(LDFLAGS)
install: all
	mv $(TARGETS) bin
.PHONY: clean
clean:
	rm -f $(RMOBJ) $(TARGETS)
distclean: clean
	rm -f bin/* Makefile
