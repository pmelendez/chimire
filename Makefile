CXX=g++
CXXFLAGS=-std=c++11 
INCLUDEDIR=./include/
SOURCEDIR=./src
OUTPUTNAME=carbon
BUILDDIR=./builds
DISTDIR=$(BUILDDIR)/dist
OBJDIR=$(BUILDDIR)/objs
EXECNAME=carbon
CXXFILES= test.o  main.o

YELLOW=\033[93m
RED=\033[91m
WHITE=\033[0m
GREEN=\033[92m
GREY=\033[90m
BLUE=\033[94m
BBLUE=\033[1;94m
ACTIVEC=$(WHITE)

OBJS := test.o main.o

vpath %.o $(OBJDIR)
#vpath carbon $(DISTDIR)

.PHONY: all test dir
all: $(DISTDIR)/carbon

$(DISTDIR)/carbon: $(DISTDIR) $(OBJS) 
	@echo "$(ACTIVEC) Making Executable  $(WHITE)" 
	@cd $(OBJDIR) && $(CXX) $(OBJS) -o ../dist/$(EXECNAME)

$(DISTDIR):
	@mkdir -p $(DISTDIR)
	@mkdir -p $(OBJDIR)

%.o: $(SOURCEDIR)/%.cpp
	@echo "$(ACTIVEC) Compiling $(GREEN)$(SOURCEDIR)/$*.cpp $(WHITE)"
	@$(CXX) $(CXXFLAGS) -I$(INCLUDEDIR) -c $(CXXFLAGS) $(SOURCEDIR)/$*.cpp -o $(OBJDIR)/$*.o
	
clean:
	rm -rf $(BUILDDIR)

