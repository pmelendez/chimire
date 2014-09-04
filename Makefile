CXX=g++
CXXFLAGS=-std=c++11 -Wall -Werror
INC=./include ./submodules/picojson ./submodules/cppformat ./submodules/libevents/libevents
INCLUDEDIR=$(foreach d, $(INC), -I$d)
SOURCEDIR=./src
OUTPUTNAME=carbon
BUILDDIR=./builds
DISTDIR=$(BUILDDIR)/dist
OBJDIR=$(BUILDDIR)/objs
LIBDIR=libraries
EXECNAME=carbon
CXXFILES= test.o  main.o
LIBS= -lformat #-ljson
CURRDIR=$(shell pwd)
LD_LIBRARY_PATH=$(CURRDIR)/$(LIBDIR)
SUBMODULES_DIR=$(CURRDIR)/submodules
SUBMOD_INCLUDES=libev/ c-ares/
SUBMOD_INC_PATH=$(foreach d, $(SUBMOD_INCLUDES),$(SUBMODULES_DIR)/$d)
CPLUS_INCLUDE_PATH=$(SUBMOD_INC_PATH)
C_INCLUDE_PATH=$(CPLUS_INCLUDE_PATH)

sep:=:
empty:=
space:=$(empty) $(empty)
LIB_INC_PATH:= $(subst $(space),$(sep),$(CPLUS_INCLUDE_PATH))

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

$(DISTDIR)/carbon: $(DISTDIR) $(OBJS) $(LIBDIR)/libformat.a $(LIBDIR)/libreactcpp.a
	@echo "$(ACTIVEC) Making Executable $(YELLOW) $(DISTDIR)/$(EXECNAME)  $(WHITE)" 
	@cd $(OBJDIR) && $(CXX) $(OBJS) -L../../$(LIBDIR)  -pthread $(LIBS)  -o ../dist/$(EXECNAME)

$(DISTDIR):
	@mkdir -p $(DISTDIR)
	@mkdir -p $(OBJDIR)

%.o: $(SOURCEDIR)/%.cpp
	@echo "$(ACTIVEC) Compiling $(GREEN)$(SOURCEDIR)/$*.cpp $(WHITE)"
	@$(CXX) $(INCLUDEDIR) $(CXXFLAGS) -c $(SOURCEDIR)/$*.cpp -o $(OBJDIR)/$*.o #2>&1 | grep error  

$(LIBDIR)/libformat.a:
	@echo "$(ACTIVEC) Compiling $(GREEN)libformat $(WHITE)"
	@cd submodules/cppformat/ && cmake .
	@cd submodules/cppformat/ && make -s 
	@cp submodules/cppformat/libformat.a $(LIBDIR)

$(LIBDIR)/libreactcpp.a: $(LIBDIR)/libcares.a $(LIBDIR)/libev.a
	@echo "$(ACTIVEC) Compiling $(GREEN)libreactcpp $(WHITE)"
	@cd submodules/REACT-CPP/ && CPLUS_INCLUDE_PATH=$(LIB_INC_PATH) LIBRARY_PATH=$(LD_LIBRARY_PATH) make -s
	@cp ./submodules/REACT-CPP/src/libreactcpp.a $(LIBDIR)

$(LIBDIR)/libcares.a:
	@echo "$(ACTIVEC) Compiling $(GREEN)libares $(WHITE)"
	@cd submodules/c-ares/ && ./buildconf && ./configure && make -s
	@cp submodules/c-ares/.libs/libcares.a $(LIBDIR)


$(LIBDIR)/libev.a:
	@echo "$(ACTIVEC) Compiling $(GREEN)libev $(WHITE)"
	@cd submodules/libev/ && ./configure && make -s
	@cp submodules/libev/.libs/libev.so* $(LIBDIR)

clean:
	rm -rf $(BUILDDIR)

clean-libs:
	rm -rf $(LIBDIR)/*
