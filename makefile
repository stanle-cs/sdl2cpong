#BINPATH specifies the path to the executable
#BINPATH += bin

#OBJSPATH specifies the path to all the object files
OBJPATH +=obj
#SOURCEPATH specifies the path to the source files
SOURCEPATH += src
vpath %.c $(SOURCEPATH)
vpath %.h $(SOURCEPATH)

#INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS = -ID:/c_prog/SDL2/include

#LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS = -LD:/c_prog/SDL2/lib

#DEPS list independent headers used
DEPS += defs.h structs.h

#OBJS specifies which files to compile as part of the project
_OBJS += pong.o
_OBJS += init.o input.o
_OBJS += draw.o stage.o

OBJS = $(patsubst %,$(OBJPATH)/%,$(_OBJS))

#CC specifies which compiler we're using
CC = gcc

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
# -Wl,-subsystem,windows gets rid of the console window
COMPILER_FLAGS = -Wall -Werror=implicit-function-declaration -O2


#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS += -lmingw32 -lSDL2main -lSDL2 -lSDL2_image  -lSDL2_ttf
#LINKER_FLAGS += -mwindows -lm -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lversion -luuid -static-libgcc -lsetupapi -lhid

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = pong

#Compile source files
#CXXFLAGS += `sdl2-config --cflags`
CXXFLAGS += -g -lefence 
#This is the target that compiles our executable
#all: $(OBJ_NAME)

$(OBJPATH)/%.o: %.c %.h $(DEPS)
	$(CC) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(CXXFLAGS) $(LINKER_FLAGS) -c -o $@ $<

$(OBJ_NAME): $(OBJS)
	$(CC) -o $@ $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) 

# cleaning everything that can be automatically recreated with "make".
clean:
	$(RM) -rf $(OBJPATH) $(PROG)