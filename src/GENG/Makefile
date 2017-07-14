# $(wildcard *.cpp /xxx/xxx/*.cpp): get all .cpp files from the current directory and dir "/xxx/xxx/"
SRCS := $(wildcard *.cpp)
# $(patsubst %.cpp,%.o,$(SRCS)): substitute all ".cpp" file name strings to ".o" file name strings
OBJS := $(patsubst %.cpp,%.o,$(SRCS))

LIBDIR := ../../lib

CC := g++
AR := ar
MV := mv
AFLAGS := rcs
CFLAGS := -Wall -g -I../../inc
TARGET := libgeng.a 




#INFO:


###################################################
all: PFX = App

all: install 

$(TARGET): $(OBJS)
# $< is for each obj ITS a for loop.
	#[AR].###################################.#
	$(AR) $(AFLAGS) $@ $^  
	
# $^ is not a for each, rather it uses OBJS as a whole, which is not what we inted for.
# $(CC) -o $@ $^ $(LFLAGS)
%.o : %.cpp
	#[$(PFX)_CMP].###################################.#
	$(CC) $(CFLAGS) -c $< 
###################################################
clean:
	rm -Rf $(LIBDIR)/$(TARGET) *.o
###################################################
install: $(TARGET)
	$(MV) $(TARGET) $(LIBDIR)/
###################################################
.PHONY: all clean test test_o install







