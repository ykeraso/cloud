###########################################3
#
#    Makefile for ServDiscLib
#

GCC          = gcc
C99          = -std=c99
CFLO         = -c -Wall -Werror -fpic
CFLSO        = -shared -o
CIN          = -I../include/
CINLIB       = -I../../include/
CFLAGS       = -fPIC -shared 

TARGET  = libServDiscLib.so

#debug level
ifeq ($(D),error)
	DEBUG_LEVEL=1
	C99=-std=c99
else 
	ifeq ($(D),trace)
		DEBUG_LEVEL=2
		C99=--std=c99
	else
		ifeq ($(D),all)
			DEBUG_LEVEL=3
			C99=--std=c99
		else
			DEBUG_LEVEL=0
		endif
	endif
endif

#precompile variables
DFLAGS=-DDEBUG_LEVEL=$(DEBUG_LEVEL)


# Sourc file of Lib
SOURCES = \
	../src/List.c 
	
BASESRC = $(foreach file, $(SOURCES), $(notdir $(file) ) )
OBJECT := $(BASESRC:.c=.o)

all: obj $(TARGET)

obj:
	$(foreach file, $(SOURCES), ($(GCC) $(CFLO) $(file) $(CINLIB) $(CIN) $(C99) $(DFLAGS) ))

$(TARGET):
	$(GCC) $(CFLSO) $(TARGET) $(OBJECT)
	
clean:
	rm -f $(TARGET) $(wildcard *.o)