##
## EPITECH PROJECT, 2019
## openApp
## File description:
## Makefile
##

# Platform (will be lua's one : aix bsd c89 freebsd generic linux macosx mingw posix solaris)
OA_PLATFORM	=	linux

# File names
OA_STATIC	=	openApp.a
OA_DYNAMIC	=	openApp.so
BINARY		=	bin

# Dir names
OA_ROOT		=	.
F_SOURCES	=	Sources
F_INCLUDES	=	Includes
F_MEDIAS	=	Medias
F_TESTS		=	Tests
F_EXTERN	=	Extern

# Command aliases
CC			=	g++
CSTATIC		=	ar -cvq
RM			=	rm -f

# Compilation flags
DEBUG		=
CXXFLAGS	=	-Wall -Werror -Wextra -std=c++17 -fPIC $(DEBUG)
CPPFLAGS	=	-I $(F_INCLUDES) -I $(F_EXTERN)/lua/src
LDFLAGS		=	-L $(F_EXTERN)/lua/src -l lua
FLAGS		=	$(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS)

# Compilation sources
MAIN		=	$(F_SOURCES)/main.cpp

CORE_SRC	=	$(F_SOURCES)/Core/Log.cpp

APP_SRC		=

INTERP_SRC	=	$(F_SOURCES)/Interpreter/Interpreter.cpp

SRC			=	$(CORE_SRC) $(APP_SRC) $(INTERP_SRC)

OBJ			=	$(SRC:.cpp=.o)

# Compilation rules
all: compile

compile: $(OBJ) static dynamic

static:
	$(CSTATIC) -o $(OA_STATIC) $(OBJ)

dynamic:
	$(CC) -o $(OA_DYNAMIC) -shared $(OBJ) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS)

lua_linux:
	make lua OA_PLATFORM=linux

lua_windows:
	make lua OA_PLATFORM=mingw

lua_macosx:
	make lua OA_PLATFORM=macosx

lua:
	make -C $(F_EXTERN)/lua $(OA_PLATFORM)

lua_clean:
	make -C $(F_EXTERN)/lua clean

lua_fclean:
	make -C $(F_EXTERN)/lua fclean

bin: $(OBJ)
	$(CC) -o $(BINARY) $(MAIN) $(OBJ) $(FLAGS)

debug:
	make DEBUG=-g3 bin

clean: lua_clean
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(OA_DYNAMIC)
	$(RM) $(OA_STATIC)
	$(RM) $(BINARY)

re: fclean all

.PHONY: all compile static dynamic bin debug lua_linux lua_windows lua_macosx lua lua_clean lua_fclean clean fclean re