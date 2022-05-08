CC=gcc
CXX=g++
CC_FLAGS=-g -Wall 
CXX_FLAGS=-g -std=c++17 -Wall -O2

rm=rm -fr
mkdir=mkdir2 -p

TARGET=main
BUILD_DIR=build
SRC_DIR= .
SRCS = $(foreach dir, $(SRC_DIR), $(wildcard $(dir)/*.cpp))
# $(foreach dir, $(SRC_DIR), $(wildcard $(dir)/*.c*)) 
# $(wildcard $(SRC_DIR)/*.c*) 
# moveonly_test.cpp add.c
# OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
OBJS = $(addprefix $(BUILD_DIR)/, $(addsuffix .o, $(basename $(SRCS))))
DEPS = $(OBJS:.o=.d)

INC_DIR = c:/sfml/include
LIB_DIR = c:/sfml/lib
LIBS    = sfml-audio sfml-graphics sfml-main sfml-network sfml-system sfml-window

INC_FLAGS = $(addprefix -I,$(INC_DIR))
LIB_FLAGS = $(addprefix -L,$(LIB_DIR)) $(addprefix -l,$(LIBS))
LD_FLAGS  = 

all: $(TARGET)
.PHONY: clean

$(TARGET): $(OBJS)
	$(CXX) $(CXX_FLAGS) $(OBJS) -o $@ $(LD_FLAGS) $(LIB_FLAGS)

$(BUILD_DIR)/%.o: %.cpp
	@$(mkdir) $(dir $@)
	$(CXX) $(CXX_FLAGS) $(INC_FLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: %.c
	@$(mkdir) $(dir $@)
	$(CC) $(CC_FLAGS) $(INC_FLAGS) -c $< -o $@

clean:
	@$(rm) $(BUILD_DIR)
	@$(rm) $(TARGET).exe
	@echo $(OBJS)

-include $(DEPS)
