# $(wildcard *.cpp /xxx/xxx/*.cpp): get all .cpp files from the current directory and dir "/xxx/xxx/"
SRCS := $(wildcard *.cpp)
# $(patsubst %.cpp,%.o,$(SRCS)): substitute all ".cpp" file name strings to ".o" file name strings
OBJS := $(patsubst %.cpp,%.o,$(SRCS))

LIBDIR := ../../lib
INCDIR := ../../inc 

CC := g++
AR := ar
MV := mv
AFLAGS := rcs
CFLAGS := -Wall -g -I../../inc 
TEST_TARGET := stbtest


TARGET := libstb.a 
TARGET_NAKED_NAME := stb 



#INFO:



###################################################
all: PFX = App
all: CFLAGS += -DSTB_IMAGE_IMPLEMENTATION	
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
	rm -Rf $(LIBDIR)/$(TARGET) *.o $(TEST_TARGET)
###################################################
install: $(TARGET)
	$(MV) $(TARGET) $(LIBDIR)/
###################################################
.PHONY: all clean test test_o install


###################################################
test: CFLAGS =  -Wall -I../../inc -DTEST_BENCH
test: PFX = Tst
test: 
	$(CC) $(CFLAGS) -o $(TEST_TARGET) $(SRCS) -L$(LIBDIR) -l$(TARGET_NAKED_NAME)






