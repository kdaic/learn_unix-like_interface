#
# Makefile
#
##################################################################################
OS:=$(shell uname -s)
UNAME := $(shell uname)

##################################################################################
# library file name
APP_NAME = termios_raw_input

##################################################################################
# library file name
TOP_DIR_NAME = templete_build

##################################################################################
# compiler
# OS dependency
ifeq ($(OS),Linux)
	CXX:=g++ -std=c++03
else ifeq ($(OS),QNX)
  CXX:=QCC -Vgcc_ntox86_cpp
else
  $(error unknown OS $(OS))
endif

##################################################################################
# local directory
LIB_DIR = .
BIN_DIR = .
SRC_DIR = .

##################################################################################
# test directory
TEST_SRC_DIR = ./test

##################################################################################
# include directory
INCLUDE_DIR = .
INCLUDE_PLOG_DIR = ./include/$(TOP_DIR_NAME)/util/plog/include
INCLUDE_USRLOCAL_DIR = /usr/local/include
INCLUDE_GTEST_INTERNAL_DIR = /usr/local/include/gtest/internal
INCLUDES = . $(INCLUDE_DIR)
INCLUDES += $(INCLUDE_PLOG_DIR)
INCLUDES += $(INCLUDE_USRLOCAL_DIR)
INCLUDES += $(INCLUDE_GTEST_INTERNAL_DIR)
#
# OS dependency
ifeq ($(OS),QNX)
	INCLUDES += /usr/pkg/include
endif
#
# INCLUDES_PATH(add prefix -I)
INCLUDES_PATH = $(addprefix -I, $(INCLUDES))

##################################################################################
# library directoxry
LOCAL_LINK_DIR = -L/usr/local/lib
LINK_DIRS = -L. -L/usr/lib
LINK_DIRS += $(LOCAL_LINK_DIRS)
#
# link (pay attension to linking-order)
LINK  = $(LINK_DIRS)
LINK += -lm
#
# OS dependency
ifeq ($(OS),Linux)
	LINK_GTEST = -lgtest_main -lgtest
  LINK+=-lpthread -ldl $(LINK_GTEST)
endif

##################################################################################
# option
CFLAGS = -g3 -Wall -D$(UNAME) -D_REENTRANT
# CFLAGS += -Wextra -fPIC -Wl,-rpath=.  -DUSE_PIO -DUSE_DUMMYDEV

##################################################################################
# library & application
SLIB_APP = $(LIB_DIR)/lib$(APP_NAME).a
# LIB_APP = $(LIB_DIR)/lib$(APP_NAME).so
EXE_APP  = $(BIN_DIR)/$(APP_NAME)
TEST_APP = $(BIN_DIR)/unit_test
#
EXE_SRC :=$(SRC_DIR)/main.cpp
SLIB_SRC:=$(wildcard $(filter-out $(SRC_DIR)/*.cpp, $(EXE_SRC)))
SLIB_SRC+=$(wildcard $(SRC_UTIL_DIR)/*.cpp)
TEST_SRC:=$(wildcard $(TEST_SRC_DIR)/*.cpp) $(wildcard $(TEST_SRC_UTIL_DIR)/*.cpp)
#
SLIB_OBJS=$(SLIB_SRC:%.cpp=%.o)
EXE_OBJS =$(EXE_SRC:%.cpp=%.o)
TEST_OBJS=$(TEST_SRC:%.cpp=%.o)

##################################################################################
# Target
# COMPILE_TARGETS = $(SLIB_APP) $(LIB_APP) $(EXE_APP) $(TEST_APP)
COMPILE_TARGETS = $(EXE_APP)
all: compile_title $(COMPILE_TARGETS)
compile_title:
	@echo
	@echo "COMPILE_TARGETS="$(COMPILE_TARGETS)"\n"
	@echo ---- $(MAKE) $(COMPILE_TARGETS) "("$(shell basename $(shell pwd))")" ----- "\n"


# separate compile -- make staic library
$(SLIB_APP): $(SLIB_OBJS)
	@echo "\n  "$^" --> "$@"\n"
	@if [ ! -d $(LIB_DIR) ]; then \
		mkdir -p $(LIB_DIR); \
	fi
	ar rcs $@ $^
# @rm $(SLIB_OBJS)

# separate compile -- make shared library
$(LIB_APP): $(LIB_OBJS)
	@echo "\n  "$^" --> "$@"\n"
	@if [ ! -d $(LIB_DIR) ]; then \
		mkdir -p $(LIB_DIR); \
	fi
	$(eval LIB_CFLAGS = $(CFLAGS) -fPIC)
	$(CXX) -shared -o $@ $^ $(LIB_CFLAGS) $(LINK)
# @rm $(LIB_OBJS)

# separated compile -- make executing application
# $(EXE_APP): $(EXE_OBJS) $(SLIB_APP)
$(EXE_APP): $(EXE_OBJS)
	@echo "\n  "$^" --> "$@"\n"
	@if [ ! -d $(BIN_DIR) ]; then \
		mkdir -p $(BIN_DIR); \
	fi
	$(CXX) -o $@ $^ $(CFLAGS) $(LINK)
# @rm $(EXE_OBJS)

# separated compile -- make unit_test application
$(TEST_APP): $(TEST_OBJS) $(SLIB_APP)
	@echo "\n  "$^" --> "$@"\n"
	@if [ ! -d $(BIN_DIR) ]; then \
		mkdir -p $(BIN_DIR); \
	fi
	$(CXX) -o $@ $^ $(CFLAGS) $(LINK)
# @rm $(TEST_OBJS)

### common compile -- make object file
%.o: %.cpp
	@echo "\n  "$<" --> "$@"\n"
	@if [ "$(LIB_APP)" != "" ]; then \
		echo "$(CXX) -c $(CFLAGS) -fPIC $(INCLUDES_PATH) -o $@ $<"; \
		$(CXX) -c $(CFLAGS) -fPIC $(INCLUDES_PATH) -o $@ $<;\
	else \
		echo "$(CXX) -c $(CFLAGS) $(INCLUDES_PATH) -o $@ $<"; \
		$(CXX) -c $(CFLAGS) $(INCLUDES_PATH) -o $@ $<; \
	fi

# make clean
clean:
	rm -f $(EXE_OBJS)
	rm -f *~ core
	rm -f $(INCLUDE_DIR)/*~
	rm -f $(SRC_DIR)/*~
#	rm -f $(SLIB_OBJS)
#	rm -f $(LIB_OBJS)
#	rm -f $(TEST_OBJS)

# 全消しするときは make cleanall
cleanall: clean
	rm -f $(EXE_APP)
#	rm -f $(SLIB_APP)
#	rm -f $(TEST_APP)
