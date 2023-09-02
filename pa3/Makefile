EXE = pa3
EXEStats = testStats
EXESqtree = testSQtree
OBJS  = pa3.o PNG.o RGBAPixel.o lodepng.o sqtree.o stats.o
OBJS_S = testStats.o PNG.o RGBAPixel.o lodepng.o stats.o
OBJS_Q = testSQtree.o PNG.o RGBAPixel.o lodepng.o sqtree.o stats.o

CXX = clang++
CXXFLAGS = -std=c++14 -c -g -Og -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++14 -lpthread -lm

all : pa3 testStats testSQtree

$(EXE) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXE)

$(EXEStats) : $(OBJS_S)
	$(LD) $(OBJS_S) $(LDFLAGS) -o $(EXEStats)

$(EXESqtree) : $(OBJS_Q)
	$(LD) $(OBJS_Q) $(LDFLAGS) -o $(EXESqtree)

pa3.o : pa3.cpp sqtree.h cs221util/PNG.h cs221util/RGBAPixel.h stats.h
	$(CXX) $(CXXFLAGS) pa3.cpp -o $@

testStats.o : testStats.cpp cs221util/PNG.h cs221util/RGBAPixel.h stats.h
	$(CXX) $(CXXFLAGS) testStats.cpp -o $@

testSQtree.o : testSQtree.cpp sqtree.h cs221util/PNG.h cs221util/RGBAPixel.h stats.h
	$(CXX) $(CXXFLAGS) testSQtree.cpp -o $@

#sqtree.o : sqtree.cpp sqtree.h stats.h
sqtree.o : sqtree.cpp sqtree.h stats.h cs221util/PNG.h cs221util/RGBAPixel.h
	$(CXX) $(CXXFLAGS) sqtree.cpp -o $@

stats.o : stats.cpp stats.h cs221util/PNG.h cs221util/RGBAPixel.h cs221util/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) stats.cpp -o $@

PNG.o : cs221util/PNG.cpp cs221util/PNG.h cs221util/RGBAPixel.h cs221util/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs221util/PNG.cpp -o $@

RGBAPixel.o : cs221util/RGBAPixel.cpp cs221util/RGBAPixel.h
	$(CXX) $(CXXFLAGS) cs221util/RGBAPixel.cpp -o $@

lodepng.o : cs221util/lodepng/lodepng.cpp cs221util/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs221util/lodepng/lodepng.cpp -o $@

clean :
	-rm -f *.o $(EXE) $(EXEStats) $(EXESqtree)
