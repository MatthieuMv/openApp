##
## EPITECH PROJECT, 2019
## openApp
## File description:
## Makefile
##

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
CXXFLAGS	=	-Wall -Werror -Wextra -std=c++17 -fPIC $(DEBUG) -Wno-ignored-qualifiers
CPPFLAGS	=	-I $(F_INCLUDES) -I $(F_EXTERN) -I $(F_EXTERN)/sol2 -I $(F_EXTERN)/lua/src
LDFLAGS		=	-L $(F_EXTERN)/lua/src -l lua
FLAGS		=	$(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS)

# Compilation sources
MAIN		=	$(F_SOURCES)/Main.cpp

CORE_SRC	=	$(F_SOURCES)/Core/Log.cpp

APP_SRC		=	$(F_SOURCES)/App/Interpreter.cpp \
				$(F_SOURCES)/App/Register.cpp \
				$(F_SOURCES)/App/Item.cpp

SRC			=	$(CORE_SRC) $(APP_SRC)

OBJ			=	$(SRC:.cpp=.o)

# Compilation rules
all: compile

compile: $(OBJ) static dynamic

static:
	$(CSTATIC) -o $(OA_STATIC) $(OBJ)

dynamic:
	$(CC) -o $(OA_DYNAMIC) -shared $(OBJ) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS)

bin: $(OBJ)
	$(CC) -o $(BINARY) $(MAIN) $(OBJ) $(FLAGS)

debug:
	make DEBUG=-g3 bin

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(OA_DYNAMIC)
	$(RM) $(OA_STATIC)
	$(RM) $(BINARY)

re: fclean all

.PHONY: all compile static dynamic bin debug clean fclean re