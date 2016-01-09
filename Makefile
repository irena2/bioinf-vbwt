BINDIR = bin/
BUILDDIR = build/
SRCDIR = src/
TESTDIR = test/

CC = g++
CFLAGS = -std=c++11 -I include/

EXEC = all
SOURCES = $(wildcard $(SRCDIR)*.cpp)
OBJECTS = $(addprefix $(BUILDDIR), $(notdir $(SOURCES:.cpp=.o)))

$(EXEC): mkdir $(OBJECTS)
	$(CC) $(OBJECTS) -o $(BINDIR)$(EXEC)

mkdir:
	mkdir -p $(BINDIR) $(BUILDDIR)

$(BUILDDIR)%.o: $(SRCDIR)%.cpp
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS)
	rm -f $(BINDIR)$(EXEC)
	rm -f -r $(BINDIR)
	rm -f -r $(BUILDDIR)

