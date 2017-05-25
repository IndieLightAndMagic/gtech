# $(wildcard *.cpp /xxx/xxx/*.cpp): get all .cpp files from the current directory and dir "/xxx/xxx/"
SRCS := $(wildcard *.cpp)
# $(patsubst %.cpp,%.o,$(SRCS)): substitute all ".cpp" file name strings to ".o" file name strings
OBJS := $(patsubst %.cpp,%.o,$(SRCS))


CC := g++
AR := AR
AFLAGS := rcs
CFLAGS := -Wall -g -I../../inc
TARGET := libshdr.a 
LFLAGS := -L../../../glew-2.0.0/build/lib/  -L../../../glfw/build/src/ -framework OpenGL -framework Cocoa -framework IOKit  -framework CoreVideo -lglfw3  -lGLEW  -lpthread


#INFO:
PFX := App

# Testbench
TARGET_TEST := testbench

#LIBRARYÍ

all: $(TARGET)
$(TARGET): $(OBJS)
# $< is for each obj ITS a for loop.
	#[AR].###################################.#
	$(AR) $(AFLAGS) $@ $^  
	

clean:
	rm -rf $(TARGET_TEST) $(TARGET) *.o


#TEST

test: CFLAGS += -DTEST_BENCH
test: PFX = TST
test: test_o 
	#[$(PFX)_LNK].###################################.#
	$(CC) -o $(TARGET_TEST) $(OBJS) $(LFLAGS)
	./$(TARGET_TEST)
test_o: $(OBJS)
# $^ is not a for each, rather it uses OBJS as a whole, which is not what we inted for.
# $(CC) -o $@ $^ $(LFLAGS)
%.o : %.cpp
	#[$(PFX)_CMP].###################################.#
	$(CC) $(CFLAGS) -c $< 
	
.PHONY: all clean test test_o





