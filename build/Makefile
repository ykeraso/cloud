#######################################
#
#   Makefile for K23-a:Part1
#

EXE=run-d
EXETEST=test.$(EXE)
TESTOUTFILE=test.out

BASEDIR := $(shell pwd)
ROOTSRC=../src/
ROOTTEST=../test/
ROOTUNIT=../utest/

MKDIR_P=mkdir -p
OUTDIR=../obj/

GCC=gcc
GCCFLAGS=-Wall -O3 -o

CIN=-I ../include

#Test parameters
CINUNIT=-I $(ROOTUNIT)
TEST_C := $(wildcard $(ROOTTEST)*.c)
TEST_O := $(patsubst $(ROOTTEST)%.c, %.o,$(TEST_C))
UNI_C= $(ROOTUNIT)uni.c
UNI_O= $(OUTDIR)uni.o

#Libraries
LIBS = \
	../Libs/ServDiscLib
	
LIBLINK := $(foreach lib, $(LIBS), -L$(BASEDIR)/$(lib)/build -l$(notdir $(lib)) ) 
 

#Files for executable
MAIN_C=$(ROOTSRC)main/main.c
MAIN_O=$(OUTDIR)main.o

SRC_C=$(ROOTSRC)my_src/src.c
SRC_O=$(OUTDIR)src.o

OBJS=$(MAIN_O) $(SRC_O) $(TEST_O)

# Targets 

ifeq ($(SKIP_TEST),true)
all: directories libs default
else
all: directories libs default test_all
endif

directories: $(OUTDIR)

libs:
	$(foreach lib,$(LIBS),$(MAKE) -C $(lib)/build )
	

default: $(EXE)

run: $(EXE)
	./$(EXE)

memtest: directories test $(EXE) $(EXETEST)
	rm -f $(TEST_O)
	valgrind --leak-check=yes ./$(EXE)
	valgrind --leak-check=yes ./$(EXETEST) reg


test_all: test $(EXETEST)
	rm -f $(TEST_O)
	./$(EXETEST) reg > $(TESTOUTFILE)
	
test:
	$(foreach file,$(TEST_C),($(GCC) -c $(file) $(CINUNIT) $(CIN));)

$(OUTDIR):
	$(MKDIR_P) $(OUTDIR)

$(EXE): $(MAIN_O)
	$(GCC) $(GCCFLAGS) $(EXE) $(MAIN_O) $(LIBLINK)

$(EXETEST): $(TEST_O) $(UNI_O)
	$(GCC) $(GCCFLAGS) $(EXETEST) $(TEST_O) $(UNI_O)
	

$(MAIN_O): $(MAIN_C)
	$(GCC) -c $(MAIN_C) -o $(MAIN_O) $(CIN)

$(SRC_O): $(SRC_C)
	$(GCC) -c $(SRC_C) -o $(SRC_O) $(CIN)

$(UNI_O): $(UNI_C)
	$(GCC) -c $(UNI_C) -o $(UNI_O) $(CIN)
	

clean:
	rm -rf ${OUTDIR}
	$(foreach file,$(TEST_O),(rm -f $(file) );)
	$(foreach lib, $(LIBS), $(MAKE) -C $(lib)/build/ clean)	
	rm -f $(EXE) $(EXETEST) $(TESTOUTFILE)
	





