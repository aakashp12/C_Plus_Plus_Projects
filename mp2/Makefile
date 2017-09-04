EXENAME1 = testimage
EXENAME2 = testscene

OBJ1 = testimage.o png.o rgbapixel.o image.o 
OBJ2 = testscene.o png.o rgbapixel.o image.o scene.o

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi -lpthread

all: $(EX1) $(EX2)

$(EXENAME1): $(OBJ1)
	$(LD) $(OBJ1) $(LDFLAGS) -o $(EXENAME1)

$(EXENAME2): $(OBJ2)
	$(LD) $(OBJ2) $(LDFLAGS) -o $(EXENAME2)

testscene.o: testscene.cpp png.h rgbapixel.h image.h scene.h
	$(CXX) $(CXXFLAGS) testscene.cpp

testimage.o: testimage.cpp png.h rgbapixel.h image.h
	$(CXX) $(CXXFLAGS) testimage.cpp

image.o: image.cpp image.h png.h rgbapixel.h 
	$(CXX) $(CXXFLAGS) image.cpp

png.o: png.cpp png.h rgbapixel.h
	$(CXX) $(CXXFLAGS) png.cpp

rgbapixel.o: rgbapixel.cpp rgbapixel.h
	$(CXX) $(CXXFLAGS) rgbapixel.cpp

scene.o: scene.cpp scene.h image.h png.h rgbapixel.h
	$(CXX) $(CXXFLAGS) scene.cpp
	
clean:
	-rm -f *.o $(EXENAME1) $(EXENAME2)
