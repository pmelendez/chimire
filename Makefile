CXX=g++
CXXFLAGS=-std=c++11 -Wall -Werror 
INCLUDEDIR=./include/
SOURCEDIR=./src
OUTPUTNAME=carbon
BUILDDIR=./builds
DISTDIR=$(BUILDDIR)/dist
OBJDIR=$(BUILDDIR)/objs
LIBDIR=../../libraries
EXECNAME=carbon
CXXFILES= test.o  main.o
LIBS= -ljson

YELLOW=\033[93m
RED=\033[91m
WHITE=\033[0m
GREEN=\033[92m
GREY=\033[90m
BLUE=\033[94m
BBLUE=\033[1;94m
ACTIVEC=$(WHITE)

OBJS := Socket.o SocketServer.o LogSystem.o main.o

vpath %.o $(OBJDIR)
vpath %.a $(OBJDIR)
#vpath carbon $(DISTDIR)

.PHONY: all test dir
all: $(DISTDIR)/carbon

$(DISTDIR)/carbon: $(DISTDIR) $(OBJS)
	@echo "$(ACTIVEC) Making Executable $(YELLOW) $(DISTDIR)/$(EXECNAME)  $(WHITE)" 
	@cd $(OBJDIR) && $(CXX) $(OBJS) -L$(LIBDIR)  -pthread $(LIBS)  -o ../dist/$(EXECNAME)

$(DISTDIR):
	@mkdir -p $(DISTDIR)
	@mkdir -p $(OBJDIR)

%.o: $(SOURCEDIR)/%.cpp
	@echo "$(ACTIVEC) Compiling $(GREEN)$(SOURCEDIR)/$*.cpp $(WHITE)"
	@$(CXX) -I$(INCLUDEDIR) $(CXXFLAGS) -c $(SOURCEDIR)/$*.cpp -o $(OBJDIR)/$*.o #2>&1 | grep error  
	
clean:
	rm -rf $(BUILDDIR)

