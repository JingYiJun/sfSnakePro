CC=gcc
CXX=g++
CC_FLAGS=-g -static -Wall -DSFML_STATIC #-Wl,--stack=268435456
CXX_FLAGS=-g -static -std=c++17 -Wall -O2 -DSFML_STATIC #-Wl,--stack=268435456

rm=rm -fr
mkdir=mkdir2 -p

TARGET=sfSnakePro
BUILD_DIR=build
SRC_DIR= src src/screen src/element
SRCS = $(foreach dir, $(SRC_DIR), $(wildcard $(dir)/*.cpp))
# $(foreach dir, $(SRC_DIR), $(wildcard $(dir)/*.c*)) 
# $(wildcard $(SRC_DIR)/*.c*) 
# moveonly_test.cpp add.c
# OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
OBJS = $(addprefix $(BUILD_DIR)/, $(addsuffix .o, $(basename $(SRCS))))
DEPS = $(OBJS:.o=.d)

INC_DIR = ./src c:/sfml-static/include
LIB_DIR = c:/sfml-static/lib
LIBS    = sfml-main sfml-audio-s sfml-graphics-s sfml-network-s sfml-window-s sfml-system-s freetype openal32 flac vorbisenc vorbisfile vorbis ogg winmm gdi32 opengl32 ws2_32

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
