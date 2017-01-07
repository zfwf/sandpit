SOURCES=main.cpp
EXECUTABLE=main

# Set directories
OBJDIR = obj
DEBUGDIR = debug
RELEASEDIR = release

# CC specifies which compiler we're using
CC = g++

# INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS = -I/usr/local/include -I/opt/X11/include

# LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS = -L/usr/local/lib -I/opt/X11/lib

# COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -c -Wall

# LINKER_FLAGS specifies the libraries we're linking against
# Cocoa, IOKit, and CoreVideo are needed for GLFW3.
LINKER_FLAGS = -framework Cocoa -framework IOKit -framework CoreVideo -framework OpenGL -lglfw3 -lglew




MKDIR_P = mkdir -p

ifeq ($(DEBUG),1)
	CUROBJDIR = $(CURDIR)/$(OBJDIR)/$(DEBUGDIR)
	CUREXEDIR = $(CURDIR)/$(DEBUGDIR)
	EXE = $(CUREXEDIR)/$(EXECUTABLE)
else
	CUROBJDIR = $(CURDIR)/$(OBJDIR)/$(RELEASEDIR)
	CUREXEDIR = $(CURDIR)/$(RELEASEDIR)
	
endif

OBJDIRS = $(addprefix $(CUROBJDIR)/, $(dir $(SOURCES)))
OBJECTS = $(join $(OBJDIRS),$(notdir $(SOURCES:.cpp=.o)))
EXE = $(CUREXEDIR)/$(EXECUTABLE)

all: $(SOURCES) $(EXE)

.PHONY = clean
clean:
	rm -rf $(CURDIR)/$(OBJDIR)
	rm -rf $(CURDIR)/$(DEBUGDIR)
	rm -rf $(CURDIR)/$(RELEASEDIR)
    
$(EXE): $(CUREXEDIR) $(CUROBJDIR) $(OBJECTS) 
	$(CC) $(LINKER_FLAGS) $(OBJECTS) -o $@

$(CUROBJDIR)/%.o: %.cpp
	$(CC) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $< -o $@


$(CUREXEDIR) $(CUROBJDIR):
	mkdir -p $@

