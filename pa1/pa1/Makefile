EXEMAIN = pa1
EXEBlock = testblock
EXEChain = testchain
OBJS  = main.o PNG.o RGBAPixel.o lodepng.o chain.o block.o
OBJS_B = testblock.o PNG.o RGBAPixel.o lodepng.o block.o
OBJS_G = testchain.o PNG.o RGBAPixel.o lodepng.o chain.o block.o

CXX = clang++
CXXFLAGS = -std=c++14 -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++14 -lpthread -lm

all : pa1 testblock testchain

$(EXEMAIN) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXEMAIN)

$(EXEBlock) : $(OBJS_B)
	$(LD) $(OBJS_B) $(LDFLAGS) -o $(EXEBlock)

$(EXEChain) : $(OBJS_G)
	$(LD) $(OBJS_G) $(LDFLAGS) -o $(EXEChain)

main.o : main.cpp chain.h cs221util/PNG.h cs221util/RGBAPixel.h block.h
	$(CXX) $(CXXFLAGS) main.cpp

testblock.o : testblock.cpp cs221util/PNG.h cs221util/RGBAPixel.h block.h
	$(CXX) $(CXXFLAGS) testblock.cpp

testchain.o : testchain.cpp chain.h cs221util/PNG.h cs221util/RGBAPixel.h block.h
	$(CXX) $(CXXFLAGS) testchain.cpp

chain.o : chain_given.cpp chain.cpp chain.h block.h
	$(CXX) $(CXXFLAGS) chain.cpp

block.o : block.cpp block.h cs221util/PNG.h cs221util/RGBAPixel.h cs221util/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) block.cpp

PNG.o : cs221util/PNG.cpp cs221util/PNG.h cs221util/RGBAPixel.h cs221util/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs221util/PNG.cpp

RGBAPixel.o : cs221util/RGBAPixel.cpp cs221util/RGBAPixel.h
	$(CXX) $(CXXFLAGS) cs221util/RGBAPixel.cpp

lodepng.o : cs221util/lodepng/lodepng.cpp cs221util/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs221util/lodepng/lodepng.cpp

clean :
	-rm -f *.o $(EXEMAIN) $(EXEBlock) $(EXEChain)
