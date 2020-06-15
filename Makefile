CXX      := g++

CXXFLAGS := -pedantic-errors -Wall -Wextra -Werror -std=c++11

LDFLAGS  := -L/usr/lib -lstdc++ -lm \
	    -L$(HOME)/lib  -lmicrohttpd\

BUILD    := ./build

OBJ_DIR  := $(BUILD)/objects

APP_DIR  := $(BUILD)/apps

TARGET   := httpd_server

INCLUDE  :=-I$(HOME)/include/\
	-I src/Server/\
	-I src/Tools/ \
	-I src/Database/\
	-I src/WebPage_Creator/

SRC      := $(wildcard src/Database/*.cpp) \
	    $(wildcard src/WebPage_Creator/*.cpp) \
	    $(wildcard src/Server/*.cpp)\
	    $(wildcard src/Tools/*.cpp)	\
	    $(wildcard src/*.cpp)

OBJECTS  := $(SRC:%.cpp=$(OBJ_DIR)/%.o)

all: build $(APP_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@ $(LDFLAGS)

$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -o $(APP_DIR)/$(TARGET) $^ $(LDFLAGS)

.PHONY: all build clean debug release

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)

debug: CXXFLAGS += -DDEBUG -g
debug: all

release: CXXFLAGS += -O2
release: all

clean:
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -rvf $(APP_DIR)/*
