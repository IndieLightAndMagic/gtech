# $(wildcard *.cpp /xxx/xxx/*.cpp): get all .cpp files from the current directory and dir "/xxx/xxx/"
SRCS := $(wildcard *.cpp)
# $(patsubst %.cpp,%.o,$(SRCS)): substitute all ".cpp" file name strings to ".o" file name strings
OBJS := $(patsubst %.cpp,%.o,$(SRCS))


CC := g++
AR := AR
AFLAGS := rcs
CFLAGS := -Wall -g -I../inc
TARGET := libshdr.a
LFLAGS := -L../../glew-2.0.0/build/lib/  -L../../glfw/build/src/ -framework OpenGL -framework Cocoa -framework IOKit  -framework CoreVideo -lglfw3  -lGLEW  -lpthread



all: $(TARGET)
$(TARGET): $(OBJS)
# $< is for each obj ITS a for loop.
	#[AR].###################################.#
	$(AR) $(AFLAGS) $@ $^  
# $^ is not a for each, rather it uses OBJS as a whole, which is not what we inted for.
# $(CC) -o $@ $^ $(LFLAGS)
	
%.o: %.cpp
	#[CMP].###################################.#
	$(CC) $(CFLAGS) -c $<
clean:
	rm -rf $(TARGET) *.o
	
.PHONY: all clean