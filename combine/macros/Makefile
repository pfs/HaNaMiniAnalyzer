HOMELIB		= $(HOME)/lib
ROOFITLIB	=$(ROOFITSYS)/lib
ROOTINC		=-I$(shell root-config --incdir)
ROOTLIBS	=$(shell root-config --libs) -lMinuit #-lRooFit -lRooFitCore -lRooStats 
ROOTCFLAGS	=$(shell root-config --cflags)
ROOTGLIBS	=$(shell root-config --glibs) -lMinuit #-lRooFit -lRooFitCore -lRooStats
ROOFITLIBS       =-L$(ROOFITLIB) -lRooFit -lRooFitCore -lRooStats 
COMBLIB		=-L$(HOMELIB) -lHiggsAnalysisCombinedLimit
ROOFITINC	=-I$(ROOFITSYS)/include
MYHEADERS=-I../interface
CXX=g++

GLIBS		=$(ROOTGLIBS) 
LIBS		= $(ROOTLIBS)
LIBS		+= $(ROOFITLIBS)
LIBS		+= $(COMBLIB)
HEADERS 	+= $(MYHEADERS)
HEADERS 	+= $(ROOFITINC)


all:  dlps clean

t: Ttest clean

ws: WS clean

ws1: WS1 clean

ws2: WS2 clean

ws3: WS3 clean

ws4: WS4 clean

ws5: WS5 clean

ws7: WS7 clean
md: med clean

dlps:
	@echo "Compiling the mytest .... \n"
	$(CXX) mytest.C -c -o mytest.o -O0 $(ROOTCFLAGS) -fPIC $(HEADERS) -g
	@echo "Linking ...... \n"
	g++ mytest.o -o doTest $(ROOTGLIBS) $(LIBS) -g -fPIC -O0 -I/opt/root/include -m64 -pthread $(HEADERS)
WS:
	@echo "Compiling the WSProvider.C .... \n"
	$(CXX) WSProvider.C -c -o WSProvider.o -O0 $(ROOTCFLAGS) -fPIC $(HEADERS) -g
	@echo "Linking ...... \n"
	g++ WSProvider.o -o provideWS $(ROOTGLIBS) $(LIBS) -g -fPIC -O0 -I/opt/root/include -m64 -pthread $(HEADERS)
	
Ttest:
	@echo "Compiling the myT_test .... \n"
	$(CXX) myT_test.C -c -o myT_test.o -O0 $(ROOTCFLAGS) -fPIC $(HEADERS) -g
	@echo "Linking ...... \n"
	g++ myT_test.o -o doTtest $(ROOTGLIBS) $(LIBS) -g -fPIC -O0 -I/opt/root/include -m64 -pthread $(HEADERS)
WS1:
	@echo "Compiling the WSProvider_1.C .... \n"
	$(CXX) WSProvider_1.C -c -o WSProvider_1.o -O0 $(ROOTCFLAGS) -fPIC $(HEADERS) -g
	@echo "Linking ...... \n"
	g++ WSProvider_1.o -o provideWS1 $(ROOTGLIBS) $(LIBS) -g -fPIC -O0 -I/opt/root/include -m64 -pthread $(HEADERS)
WS2:
	@echo "Compiling the WSProvider_2.C .... \n"
	$(CXX) WSProvider_2.C -c -o WSProvider_2.o -O0 $(ROOTCFLAGS) -fPIC $(HEADERS) -g
	@echo "Linking ...... \n"
	g++ WSProvider_2.o -o provideWS2 $(ROOTGLIBS) $(LIBS) -g -fPIC -O0 -I/opt/root/include -m64 -pthread $(HEADERS)
WS3:
	@echo "Compiling the WSProvider_3.C .... \n"
	$(CXX) WSProvider_3.C -c -o WSProvider_3.o -O0 $(ROOTCFLAGS) -fPIC $(HEADERS) -g
	@echo "Linking ...... \n"
	g++ WSProvider_3.o -o provideWS3 $(ROOTGLIBS) $(LIBS) -g -fPIC -O0 -I/opt/root/include -m64 -pthread $(HEADERS)
WS4:
	@echo "Compiling the WSProvider_4.C .... \n"
	$(CXX) WSProvider_4.C -c -o WSProvider_4.o -O0 $(ROOTCFLAGS) -fPIC $(HEADERS) -g
	@echo "Linking ...... \n"
	g++ WSProvider_4.o -o provideWS4 $(ROOTGLIBS) $(LIBS) -g -fPIC -O0 -I/opt/root/include -m64 -pthread $(HEADERS)
WS5:
	@echo "Compiling the WSProvider_5.C .... \n"
	$(CXX) WSProvider_5.C -c -o WSProvider_5.o -O0 $(ROOTCFLAGS) -fPIC $(HEADERS) -g
	@echo "Linking ...... \n"
	g++ WSProvider_5.o -o provideWS5 $(ROOTGLIBS) $(LIBS) -g -fPIC -O0 -I/opt/root/include -m64 -pthread $(HEADERS)

WS7:
	@echo "Compiling the WSProvider_5.C .... \n"
	$(CXX) WSProvider_7.C -c -o WSProvider_7.o -O0 $(ROOTCFLAGS) -fPIC $(HEADERS) -g
	@echo "Linking ...... \n"
	g++ WSProvider_7.o -o provideWS7 $(ROOTGLIBS) $(LIBS) -g -fPIC -O0 -I/opt/root/include -m64 -pthread $(HEADERS)

med:
	@echo "Compiling the IntermediateProvider.C .... \n"
	$(CXX) IntermediateProvider.C -c -o IntermediateProvider.o -O0 $(ROOTCFLAGS) -fPIC $(HEADERS) -g
	@echo "Linking ...... \n"
	g++ IntermediateProvider.o -o provideIntermediate $(ROOTGLIBS) $(LIBS) -g -fPIC -O0 -I/opt/root/include -m64 -pthread $(HEADERS)
clean:
	@echo "Cleaning..."
	@rm -f *.o
