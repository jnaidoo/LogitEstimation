# Makefile to build Logit_test application
# this version: 5/30/2012

#-------------------#
# set useful macros #
#-------------------#

TGT=Logit_test

# compiler
CXX=g++-mp-4.7
 
# compiler flags
CPPFLAGS=-Wall -Wextra -O2 -m64 \
-I/Users/jesse/Tools/boost-1.4.9/boost_1_49_0/ \
-I/Users/jesse/Tools/eigen-3.0.5/eigen-eigen-6e7488e20373/

# debugger flags
CPP_DEBUG_FLAGS=-g -Wall -Wextra -m64 -O0 -fno-inline \
-I/Users/jesse/Tools/boost-1.4.9/boost_1_49_0/ \
-I/Users/jesse/Tools/eigen-3.0.5/eigen-eigen-6e7488e20373/

# system commands
RM=rm

# Logit_test is executable
# Logit.hpp, Logit.cpp are interface and implementation of Logit class
# which need to be linked? which only compiled into object code?

# list of object files
OBJS=Logit_test.o Logit.o
# compiled with debug symbols
DBGS=Logit_test.d Logit.d

#---------#
# targets #
#---------#

default : exe

# exe's only dependency is Logit_test executable
exe : $(TGT) 

# Logit_test executable consists of Logit.o linked with Logit_test.o
# hence its dependencies are the $(OBJS)
# note the compiler flags are for the optimized version of the code
# see below for an explanation of the $^, $@ etc
$(TGT) : $(OBJS) Logit.hpp
	$(CXX) $(CPPFLAGS) $^ -o $@

# rule to build debugger version of the code
dbg : $(DBGS)
	$(CXX) $(CPP_DEBUG_FLAGS) $^ -o $(TGT).dbg

# remove all
clean :
	rm -f $(OBJS) $(DBGS) $(TGT) $(TGT).dbg

# recall -c is "compile, don't link" option
# $< = first dependency
# $@ = file name of the target
# $^ = all dependencies, duplicates removed
# $? = all dependencies newer than the target

#-------------------------------------------#
# pattern rules to compile individual files #
#-------------------------------------------#

# the below pattern rules only specify dependence of .o's on
# the .cpp's, not explicitly on the header (.hpp) files
# so when we invoke make after editing Logit.hpp but not Logit.cpp
# make does not rebuild the target Logit_test

$(OBJS) : %.o : %.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@

# to make the debug files
$(DBGS) : %.d : %.cpp
	$(CC) $(CPP_DEBUG_FLAGS) -c $< -o $@



