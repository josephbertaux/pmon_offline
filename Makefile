SHELL=/bin/bash

CXX = g++

ROOTFLGS = $(shell root-config --cflags)
ROOTLIBS = $(shell root-config --glibs)

FLGS = -I. $(ROOTFLGS) -I$(ONLINE_MAIN)/include -I$(OFFLINE_MAIN)/include
LIBS = -Wl,--no-as-needed  -L$(ONLINE_MAIN)/lib -L$(OFFLINE_MAIN)/lib -lpmonitor -lEvent -lNoRootEvent -lmessage      $(ROOTLIBS) -fPIC

OBJS = main.o pmon.o

main : $(OBJS) $(S_OBJS)
	$(CXX) $(FLGS) -o $@ $^ $(LIBS)

#lib%.so : %.cc
#	$(CXX) $(FLGS) -o $@ -shared $< $(LIBS)

%.o : %.cc
	$(CXX) $(FLGS) -c $< -o $@ $(LIBS)

.PHONY: clean
clean:
	rm -rf main $(OBJS) $(S_OBJS)
