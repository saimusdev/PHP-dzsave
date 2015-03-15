# PHP-DZSAVE Makefile
# Simón Ortego 
# March 2015

# Executable name
EXECUTABLE := test

# Search directory for source code
vpath %.c src

# Dependencies
INCLUDEDIR := include
DEPS := $(wildcard $(INCLUDEDIR)/*.h)

# Compiler object files 
OBJDIR := obj
OBJS := \
	$(OBJDIR)/test.o

# Binaries full path
CC := /usr/local/bin/gcc-4.9
LD := /usr/local/bin/gcc-4.9

# Libraries
#LIBS := -L/usr/local/lib

# Compiler flags
CFLAGS := -g -Wall -O3 #-DDEBUG

# Includes
IFLAGS := \
	#-I/usr/local/Cellar/glib/2.42.1/include/glib-2.0/ \
	-I. \
	-I$(INCLUDEDIR)

# Linker options
#LDFLAGS	:=

# Random stuff
MSG_EMPTYLINE := "" 
MSG_COMPILING := ---COMPILE--- 
MSG_LINKING := ---LINK---
MSG_STRIPING := ---STRIP---
MSG_CLEANING := ---CLEAN--- 
MSG_SUCCESS := ---SUCCESS--- 
RM := rm -f
MKDIR := mkdir -p

##################################################################

all: $(EXECUTABLE)

# Linker call
$(EXECUTABLE): $(OBJS)
	@echo $(MSG_EMPTYLINE)
	@echo $(MSG_LINKING)
	$(LD) -o $@ $^ $(LDFLAGS) $(LIBS)
	@echo $(MSG_EMPTYLINE)
	@echo $(MSG_SUCCESS) $(EXECUTABLE)

# Compiler call
$(OBJS): $(OBJDIR)/%.o: %.c $(DEPS)
	@echo $(MSG_COMPILING) $<
	$(MKDIR) $(OBJDIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(IFLAGS)

# Clean
clean:
	@echo $(MSG_CLEANING)
	$(RM) $(OBJDIR)/*.o
	$(RM) $(EXECUTABLE)