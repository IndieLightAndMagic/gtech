# $(wildcard *.cpp /xxx/xxx/*.cpp): get all .cpp files from the current directory and dir "/xxx/xxx/"
SRCS := $(wildcard *.cpp)
# $(patsubst %.cpp,%.o,$(SRCS)): substitute all ".cpp" file name strings to ".o" file name strings
OBJS := $(patsubst %.cpp,%.o,$(SRCS))

#Lib and Header directory
RUTDIR := ../../..
LIBDIR := $(RUTDIR)/lib
INCDIR := $(RUTDIR)/inc

#Static Dependencies
STATIC_LIBRARIES = GLEW glfw3 util 
APPLE_FRAMEWORKS = OpenGL Cocoa IOKit CoreVideo

#Tools
CC := g++
AR := ar
MV := mv

#Flags
CFLAGS := -Wall -g -I$(INCDIR)
LFLAGS := -L$(LIBDIR)  $(addprefix -framework , $(APPLE_FRAMEWORKS)) $(addprefix -l,$(STATIC_LIBRARIES)) 


################################################
TARGET := $(patsubst %.cpp,%,$(SRCS))
all: $(TARGET)
$(TARGET): $(OBJS)
# $< is for each obj ITS a for loop.
	#[LNK].###################################.#
	$(CC) -o $@ $@.o  $(LFLAGS)
# $^ is not a for each, rather it uses OBJS as a whole, which is not what we inted for.
# $(CC) -o $@ $^ $(LFLAGS)
	
%.o: %.cpp
	#[CMP].###################################.#
	$(CC) $(CFLAGS) -c $<
clean:
	rm -rf $(TARGET) *.o
	
.PHONY: all clean