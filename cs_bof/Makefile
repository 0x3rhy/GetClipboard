BOFNAME := clipboard
CC_x64 := x86_64-w64-mingw32-gcc
CC_x86 := i686-w64-mingw32-gcc
STRIP_x64 := x86_64-w64-mingw32-strip
STRIP_x86 := i686-w64-mingw32-strip
STRIP := strip
OPTIONS := -s -w -Os -ffunction-sections -fmerge-all-constants -Wno-write-strings

.PHONY: all bin bof

all: bof bin

bin:
	$(CC_x64) $(BOFNAME).c -o $(BOFNAME).x64.exe $(OPTIONS)
	$(STRIP) --strip-all $(BOFNAME).x64.exe

bof:
	$(CC_x64) -o $(BOFNAME).x64.o -DBOF -c $(BOFNAME).c
	$(STRIP_x64) --strip-unneeded $(BOFNAME).x64.o
	$(CC_x86) -o $(BOFNAME).x86.o -DBOF -c $(BOFNAME).c
	$(STRIP_x86) --strip-unneeded $(BOFNAME).x86.o

clean:
	rm -f $(BOFNAME).*.exe
	rm -f $(BOFNAME).*.o

