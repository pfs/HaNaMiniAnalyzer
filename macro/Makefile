CLIBS		=-L/usr/lib -lstdc++
ROOTINC		=-I$(shell root-config --incdir)
ROOTLIBS	=$(shell root-config --libs) 
ROOTCFLAGS	=$(shell root-config --cflags)
ROOTGLIBS	=$(shell root-config --glibs) 
HOMELIB =$(HOME)/lib

ORSOINCLUDES = -I../interface
ORSOSOURCES = ../src

CXX=g++
CXXFLAGS	= -O -Wall -fPIC
LD		= g++
LDFLAGS 	= -g
SOFLAGS 	= -shared

HEADERS 	=$(ORSOINCLUDES)

HAMBLIB	=-L$(HOMELIB) -lHambTree.2016 
# Linux with egcs

CXXFLAGS	+= $(ROOTCFLAGS)
GLIBS		=$(ROOTGLIBS) 
LIBS		= $(ROOTLIBS) 
#LIBS		+= $(HAMBLIB)

#------------------------------------------------------------------------------



all: hambtree clean; 

clean:
	@echo "Cleaning..."
	@rm -f *.o

hambtree:
	@echo "Compiling the TreeAnalyzer .... \n"
	$(CXX) TreeAnalyzer.C -c -o TreeAnalyzer.o -O0 $(ROOTCFLAGS) -fPIC $(HEADERS) -g
	@echo "Linking ...... \n"
#	g++ TreeAnalyzer.o -o analyzetree $(ROOTGLIBS) $(LIBS) -g -fPIC -O0 -I$(ROOTINC) -m64 -pthread $(HEADERS)
	g++ TreeAnalyzer.o -g -fPIC -O0 -I$(ROOTINC) -m64 -pthread $(HEADERS) -o analyzetree $(LIBS) $(ROOTGLIBS)
       
