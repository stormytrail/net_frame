#config
CONFIG_FILE := makefile.config
ifneq ($(wildcard $(CONFIG_FILE)),$(CONFIG_FILE))
$(error $(CONFIG_FILE) not found)
endif
include $(CONFIG_FILE)

TARGET_LIB_SRC:=./lib/$(TARGET_LIB_SRC)
TARGET_LIB_SRC_DEBUG=$(TARGET_LIB_SRC:%.a=%_debug.a)

CFLAGS += -std=c++11 -c

BASIC_DIRS = ./src ./sdk ./inc ./lib ./build ./bin ./third_party
BUILD_DIRS = $(BASIC_DIRS)

INCLUDE_SRC=-I./inc
INCLUDE_ALL=$(INCLUDE_SRC) $(addprefix -I,$(INCLUDE_DIRS))

LIBRARY_SRC=./lib
LIB_ALL = -L$(LIBRARY_SRC) $(addprefix -L,$(LIBRARY_DIRS))

L_SRC = $(notdir $(TARGET_LIB_SRC))
L_SRC := $(L_SRC:lib%.a=-l%)
L_SRC_DEBUG = $(L_SRC)_debug
L_ALL = $(addprefix -l,$(LIBS))

SRC_CODE = $(shell find src -name "*.cpp")
BUILD_DIRS += $(addprefix build/,$(sort $(dir $(SRC_CODE))))
SRC_OBJS_RELEASE = $(addprefix build/,$(SRC_CODE:%.cpp=%_release.o))
SRC_OBJS_DEBUG = $(addprefix build/,$(SRC_CODE:%.cpp=%_debug.o))

SDK_CODE = $(shell find sdk -name "*.cpp")
BUILD_DIRS += $(addprefix build/,$(sort $(dir $(SDK_CODE))))
SDK_OBJS_RELEASE = $(addprefix build/,$(SDK_CODE:%.cpp=%_release.o))
SDK_OBJS_DEBUG = $(addprefix build/,$(SDK_CODE:%.cpp=%_debug.o))
SDK_RELEASE = $(addprefix build/,$(SDK_CODE:%.cpp=%_release))
SDK_DEBUG = $(addprefix build/,$(SDK_CODE:%.cpp=%_debug))

LDFLAGS = $(foreach dir,$(LIBRARY_SRC) $(LIBRARY_DIRS),-Wl,-rpath=$(dir))
LDFLAGS += -Wl,--start-group

#LDFLAGS = $(addprefix -Wl\,rpath=,$(LIBRARY_SRC) $(LIBRARY_DIRS)) -Wl,--start-group
LDFLAGS_END = -Wl,--end-group

.PHONY:all

all:lib_src examples

get_start:$(BASIC_DIRS)
	@echo hehe

#lib
lib_src:$(TARGET_LIB_SRC) $(TARGET_LIB_SRC_DEBUG)
$(TARGET_LIB_SRC):$(SRC_OBJS_RELEASE)
	ar cr $@ $^
$(TARGET_LIB_SRC_DEBUG):$(SRC_OBJS_DEBUG)
	ar cr $@ $^

$(SRC_OBJS_RELEASE):build/%_release.o:%.cpp | $(BUILD_DIRS)
	g++ $(CFLAGS) $< -o $@ $(INCLUDE_ALL)

$(SRC_OBJS_DEBUG):CFLAGS += -g
$(SRC_OBJS_DEBUG):build/%_debug.o:%.cpp | $(BUILD_DIRS)
	g++ $(CFLAGS) $< -o $@ $(INCLUDE_ALL)

#sdk
#obj
examples:$(SDK_RELEASE) $(SDK_DEBUG)
$(SDK_OBJS_RELEASE):build/%_release.o:%.cpp | $(BUILD_DIRS)
	g++ $(CFLAGS) $< -o $@ $(INCLUDE_ALL)

$(SDK_OBJS_DEBUG):CFLAGS += -g
$(SDK_OBJS_DEBUG):build/%_debug.o:%.cpp | $(BUILD_DIRS)
	g++ $(CFLAGS) $< -o $@ $(INCLUDE_ALL)

#bin
$(SDK_RELEASE):L_ALL += $(L_SRC)
$(SDK_RELEASE):$(SDK_OBJS_RELEASE) | $(BUILD_DIRS) $(TARGET_LIB_SRC)
	g++  $< -o $@ $(INCLUDE_ALL) $(LIB_ALL) $(LDFLAGS) $(L_ALL) $(LDFLAGS_END)
	@cp $@ ./bin

$(SDK_DEBUG):L_ALL += $(L_SRC_DEBUG)
$(SDK_DEBUG):$(SDK_OBJS_DEBUG) | $(BUILD_DIRS) $(TARGET_LIB_SRC_DEBUG)
	g++  $< -o $@ $(INCLUDE_ALL) $(LIB_ALL) $(LDFLAGS) $(L_ALL) $(LDFLAGS_END)
	@cp $@ ./bin

$(BUILD_DIRS):
	@test -d $@ || mkdir -p $@

clean:
	rm lib/*
	rm -rf build/*

doomsday:
	@rm -rf $(BASIC_DIRS)
