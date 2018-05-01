#directory
PBERRDIR=../PBErr
GTREEDIR=../GTree
GSETDIR=../GSet
PBJSONDIR=../PBJson

# Build mode
# 0: development (max safety, no optimisation)
# 1: release (min safety, optimisation)
# 2: fast and furious (no safety, optimisation)
BUILDMODE=1

include $(PBERRDIR)/Makefile.inc

INCPATH=-I./ -I$(PBERRDIR)/ -I$(PBJSONDIR)/ -I$(GSETDIR)/ -I$(GTREEDIR)/
BUILDOPTIONS=$(BUILDPARAM) $(INCPATH)

# compiler
COMPILER=gcc

#rules
all : main

main: main.o pberr.o pbjson.o gtree.o gset.o pbmath.o Makefile 
	$(COMPILER) main.o pberr.o pbjson.o gtree.o gset.o pbmath.o $(LINKOPTIONS) -o main

main.o : main.c $(PBERRDIR)/pberr.h pbmath.h pbmath-inline.c Makefile
	$(COMPILER) $(BUILDOPTIONS) -c main.c

pbmath.o : pbmath.c pbmath.h pbmath-inline.c Makefile
	$(COMPILER) $(BUILDOPTIONS) -c pbmath.c

pberr.o : $(PBERRDIR)/pberr.c $(PBERRDIR)/pberr.h Makefile
	$(COMPILER) $(BUILDOPTIONS) -c $(PBERRDIR)/pberr.c

pbjson.o : $(PBJSONDIR)/pbjson.c $(PBJSONDIR)/pbjson-inline.c $(PBJSONDIR)/pbjson.h Makefile
	$(COMPILER) $(BUILDOPTIONS) -c $(PBJSONDIR)/pbjson.c

gtree.o : $(GTREEDIR)/gtree.c $(GTREEDIR)/gtree.h $(GTREEDIR)/gtree-inline.c Makefile $(GSETDIR)/gset-inline.c $(GSETDIR)/gset.h $(PBERRDIR)/pberr.c $(PBERRDIR)/pberr.h
	$(COMPILER) $(BUILDOPTIONS) -c $(GTREEDIR)/gtree.c

gset.o : $(GSETDIR)/gset.c $(GSETDIR)/gset.h $(GSETDIR)/gset-inline.c Makefile $(PBERRDIR)/pberr.c $(PBERRDIR)/pberr.h
	$(COMPILER) $(BUILDOPTIONS) -c $(GSETDIR)/gset.c

clean : 
	rm -rf *.o main

valgrind :
	valgrind -v --track-origins=yes --leak-check=full --gen-suppressions=yes --show-leak-kinds=all ./main
	
unitTest :
	main > unitTest.txt; diff unitTest.txt unitTestRef.txt
