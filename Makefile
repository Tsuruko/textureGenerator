CC=g++
CFLAGS=-DUSE_UNIX -I./Includes -Wall -std=c++11
#.SUFFIXES: .cpp

SRCS=Source/Bitmap.cpp Source/Scene.cpp Source/CellTexture.cpp Source/CloudTexture.cpp Source/Color.cpp Source/main.cpp Source/MarbleTexture.cpp Source/PerlinNoise.cpp Source/Vector3.cpp Source/WoodTexture.cpp Source/WorleyNoise.cpp

OBJS=$(SRCS:.cpp=.o)

texture: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) -lm

Source/%.o: Source/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	-rm -f texture
	-rm -f core*
	-rm -f Source/*.o
	-rm -f *~
	-rm -f \#*


