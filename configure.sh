#/usr/bin/env bash
echo "generating total makefile ..." >&2
a=0;t=0;TARGETS='';EEXT='';OEXT='.o'
SRC1=$(ls src/*.c )
SRC2=$(ls rstats/*.c)
echo 'CC=gcc  -g -O2'
echo 'SRC1 = $(wildcard src/*.c)'
echo 'SRC2 = $(wildcard rstats/*.c)'
echo 'OEXT = .o'
echo 'EEXT = '
echo 'RAINSRC = $(wildcard rain/*.c)'
echo "RMOBJ = obj/*.o obj/*.obj"
echo "RAINOBJS = obj/functions.o"
echo 'CPPFLAGS = -Isrc -Irain'
echo 'LDFLAGS = -Llib -lm -lgsl -lblas'
echo 'STARGET = functions'

for t in $(echo "$SRC1" "$SRC2")
do
	TARGET=$(basename ${t%.*})
	echo 'TARGET'$a = $TARGET
	TARGETS="$TARGET $TARGETS"
	a=$(($a+1)) 
done
	echo 'TARGETS' = $TARGETS
	echo 'all: $(TARGETS)'
a=0
	echo 'obj/$(STARGET)$(OEXT): rain/$(STARGET).c'
	echo -e "\t"'$(CC) -c  $< -o obj/$(STARGET)$(OEXT) $(CPPFLAGS)'
for s in $(echo "$SRC1")
do
	TARGET=$(basename ${s%.*})
	echo 'obj/$(TARGET'$a')$(OEXT): src/'$TARGET'.c'
	echo -e "\t"'$(CC) -c   $< -o obj/'$TARGET'$(OEXT) $(CPPFLAGS)'
	echo '$(TARGET'$a'): obj/'$TARGET'$(OEXT)'
	echo -e "\t"'$(CC) -o '$TARGET' $< $(LDFLAGS)'
	a=$(($a+1))
done
for s in $(echo "$SRC2")
do
	TARGET=$(basename ${s%.*})
	echo 'obj/$(TARGET'$a')$(OEXT): rstats/'$TARGET'.c'
	echo -e "\t"'$(CC) -c   $< -o obj/'$TARGET'$(OEXT) $(CPPFLAGS)'
	echo '$(TARGET'$a'): obj/'$TARGET'$(OEXT) $(RAINOBJS)'
	echo -e "\t"'$(CC) -o '$TARGET' $? $(LDFLAGS)'
	a=$(($a+1))
done

	echo 'echo created all targets' >&2
	echo 'install: all'
        echo -e '\tmv $(TARGETS) bin'
	echo '.PHONY: clean'
	echo 'clean:'
	echo -e "\t"'rm -f $(RMOBJ) $(TARGETS)'
	echo 'distclean: clean'
        echo -e "\trm -f bin/* Makefile"
echo "generating dirs" >&2
if ! test -d bin; then mkdir  bin; fi
if ! test -d obj; then mkdir  obj; fi
