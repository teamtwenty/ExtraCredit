#!/bin/bash
# What goes above this line? Do you know why?

#---------------------------------------------------------------------------------------------------------------
# FILE:    Makefile
# DESCR:   Make file for Lab Projecr 5 (pthreads).
# AUTHORS: Kevin R. Burger (burgerk@asu.edu)
#---------------------------------------------------------------------------------------------------------------

# Define a macro named CPPFLAGS which contains these flags for the GNU g++ compiler.
# -c         : Compile a .c file only to produce the .o file.
# -O3        : Maximum optimization.
# -Wall      : Turn on all warnings. Your code should compile with no errors or warnings.
CPPFLAGS = -c -g -O0 -Wall

# Define a macro named SOURCES which contains the list of the .cpp files.
SOURCES = Amicable.cpp \
          Keith.cpp    \
          Main.cpp     \
          Prime.cpp    \
          Thread.cpp
          
# Define a macro named OBJECT which is equivalent to SOURCES with all occurrences of .cpp replaced by .o       
OBJECTS = $(SOURCES:.cpp=.o)

# Define the make target which is a binary named 'thread'. Name this macro TARGET.
TARGET = thread

# Define a rule which states that $(OBJECTS) is a prereq for $(TARGET). The command line option should
# invoke the GNU g++ compiler on $(OBJECTS) sending the output to $(TARGET) and linking with the pthread
# library, i.e., "-lpthread".
$(TARGET): $(OBJECTS) 
	g++ $(OBJECTS) -o $(TARGET) -lpthread

# A rule stating that a .cpp file is a prereq for a .o file.
%.o: %.cpp
	g++ $(CPPFLAGS) $< -o $@

# A rule stating that a .cpp file is a prereq for a .d file.
%.d: %.cpp
	rm -f $@; gcc -MM $< > $@

# Include all of the .d files. Why?
include $(SOURCES:.cpp=.d)

# A (phony) target to clean the directory of all of the .o files, all of the .d files, and the target.
.PHONY: clean
clean:
	rm -f $(OBJECTS)
	rm -f *.d
	rm -f $(TARGET)
