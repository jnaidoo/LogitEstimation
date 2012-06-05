# Makefile to build Logit_main application
# to interface with Ipopt
# Jesse Naidoo (jnaidoo@uchicago.edu)
# this version: 6/4/2012

#======================================================================
#======================================================================

#-------------------#
# set useful macros #
#-------------------#

TGT=Logit_main  
#Logit_test

#Ipopt Installation Location
IPOPTDIR=/Users/jesse/Tools/Ipopt-3.10.2-x86_64-osx

# Link line for shared libraries
LIBS=-L$(IPOPTDIR)/lib          \
      -lipopt                   \
      -lcoinblas                \
      -lcoinlapack              \
      -lcoinmetis               \
      -lcoinmumps               \
      -lgfortran -ldl -lpthread

# compiler
CXX=g++-mp-4.7
 
# compiler flags
CPPFLAGS=-Wall -Wextra -O2 -m64 \
-I/Users/jesse/Tools/boost-1.4.9/boost_1_49_0/ \
-I/Users/jesse/Tools/eigen-3.0.5/eigen-eigen-6e7488e20373/ \
-DEIGEN_NO_DEBUG \
-I$(IPOPTDIR)/include/coin 

# to speed up Eigen code:
#-DEIGEN_NO_DEBUG

# debugger flags
#CPP_DEBUG_FLAGS=-g -Wall -Wextra -m64 -O0 -fno-inline \
-I/Users/jesse/Tools/boost-1.4.9/boost_1_49_0/ \
-I/Users/jesse/Tools/eigen-3.0.5/eigen-eigen-6e7488e20373/ \
-I$(IPOPTDIR)/include/coin

# system commands
RM=rm

# Logit_test is executable
# Logit.hpp, Logit.cpp are interface and implementation of Logit class
# which need to be linked? which only compiled into object code?

# list of object files
OBJS=Logit_main.o Logit.o LogitNLP.o
# compiled with debug symbols
DBGS=Logit_main.d Logit.d LogitNLP.d

#======================================================================
#======================================================================

#---------#
# targets #
#---------#

default : exe

# exe's only dependency is Logit_main executable
exe : $(TGT) 

# Logit_test executable consists of Logit.o linked with Logit_main.o
# hence its dependencies are the $(OBJS)
# note the compiler flags are for the optimized version of the code
# see below for an explanation of the $^, $@ etc

$(TGT) : $(OBJS) 	
	$(CXX) $(CPPFLAGS) $^ -o $(TGT) $(LIBS)

# rule to build debugger version of the code
dbg : $(DBGS)
	$(CXX) $(CPP_DEBUG_FLAGS) $^ -o $(TGT).dbg $(LIBS)

# remove all
clean :
	rm -f $(OBJS) $(DBGS) $(TGT) $(TGT).dbg

# recall -c is "compile, don't link" option
# $< = first dependency
# $@ = file name of the target
# $^ = all dependencies, duplicates removed
# $? = all dependencies newer than the target

#======================================================================
#======================================================================

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



