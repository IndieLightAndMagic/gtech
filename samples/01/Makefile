CC := g++
CFLAGS := -Wall -g -I../../inc
TARGET := hello
LFLAGS := -L../../../glew-2.0.0/build/lib/  -L../../../glfw/build/src/ -framework OpenGL -framework Cocoa -framework IOKit  -framework CoreVideo -lglfw3  -lGLEW  -lpthread


# $(wildcard *.cpp /xxx/xxx/*.cpp): get all .cpp files from the current directory and dir "/xxx/xxx/"
SRCS := $(wildcard *.cpp)
# $(patsubst %.cpp,%.o,$(SRCS)): substitute all ".cpp" file name strings to ".o" file name strings
OBJS := $(patsubst %.cpp,%.o,$(SRCS))

all: $(TARGET)
$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LFLAGS)
%.o: %.cpp
	$(CC) $(CFLAGS) -c $<
clean:
	rm -rf $(TARGET) *.o
	
.PHONY: all clean