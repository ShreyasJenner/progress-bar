# Compiler and flags
CC=gcc
CFLAGS=-Wall -Iinclude

# Directories
SRCDIR=src
OBJDIR=obj
LIBDIR=lib

# Files
SRC=$(wildcard $(SRCDIR)/*.c)
OBJ=$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))
LIB=$(LIBDIR)/libprogressbar.a

# Rules
all: $(LIB)

$(LIB): $(OBJ) | $(LIBDIR)
	ar -rcs $@ $<

$(LIBDIR):
	mkdir -p $(LIBDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR)/*.o
	rm $(LIB)

.PHONY: all clean

