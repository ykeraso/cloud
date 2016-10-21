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

# Sourc file of Lib
SOURCES = \
	../src/List.c 
	
BASESRC = $(foreach file, $(SOURCES), $(notdir $(file) ) )
OBJECT := $(BASESRC:.c=.o)

all: obj $(TARGET)

obj:
	$(foreach file, $(SOURCES), ($(GCC) $(CFLO) $(file) $(CINLIB) $(CIN)) )

$(TARGET):
	$(GCC) $(CFLSO) $(TARGET) $(OBJECT)
	
clean:
	rm -f $(TARGET) $(wildcard *.o)