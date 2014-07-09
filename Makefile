CXX=g++
CXXFLAGS=-std=c++11 
INCLUDEDIR=./include/
SOURCEDIR=./src
OUTPUTNAME=carbon
BUILDDIR=./builds
DISTDIR=$(BUILDDIR)/dist

all:
	mkdir -p $(DISTDIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDEDIR) $(SOURCEDIR)/main.cpp -o $(DISTDIR)/$(OUTPUTNAME)

clean:
	rm -rf $(BUILDDIR)
