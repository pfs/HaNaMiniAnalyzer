CLIBS		=-L/usr/lib -lstdc++
ROOTINC		=-I$(shell root-config --incdir)
ROOTLIBS	=$(shell root-config --libs)  -lMinuit -lRooFit -lRooFitCore -lRooStats 
ROOTCFLAGS	=$(shell root-config --cflags)
ROOTGLIBS	=$(shell root-config --glibs)  -lMinuit -lRooFit -lRooFitCore -lRooStats 
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

skim: Skim clean;

sim: Sim clean;

clean:
	@echo "Cleaning..."
	@rm -f *.o

hambtree:
	@echo "Compiling the TreeAnalyzer .... \n"
	$(CXX) TreeAnalyzer.C -c -o TreeAnalyzer.o -O0 $(ROOTCFLAGS) -fPIC $(HEADERS) -g
	@echo "Linking ...... \n"
	g++ TreeAnalyzer.o -g -fPIC -O0 -I$(ROOTINC) -m64 -pthread $(HEADERS) -o analyzetree $(LIBS) $(ROOTGLIBS)
Skim:
	@echo "Compiling the Skimmer .... \n"
	$(CXX) Skimmer.C -c -o Skimmer.o -O0 $(ROOTCFLAGS) -fPIC $(HEADERS) -g
	@echo "Linking ...... \n"
	g++ Skimmer.o -g -fPIC -O0 -I$(ROOTINC) -m64 -pthread $(HEADERS) -o skimtree $(LIBS) $(ROOTGLIBS)
	
Sim:
	@echo "Compiling the SimultaneousFit .... \n"
	$(CXX) SimultaneousFit.C -c -o SimultaneousFit.o -O0 $(ROOTCFLAGS) -fPIC $(HEADERS) -g
	@echo "Linking ...... \n"
	g++ SimultaneousFit.o -g -fPIC -O0 -I$(ROOTINC) -m64 -pthread $(HEADERS) -o simfit $(LIBS) $(ROOTGLIBS)    	       
