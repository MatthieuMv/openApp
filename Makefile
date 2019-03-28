##
## EPITECH PROJECT, 2019
## openApp
## File description:
## Makefile
##

# File names
OA_DYNAMIC	=	openApp.so
OA_STATIC	=	openApp.a
BINARY		=	bin

# Dir names
OA_ROOT		=	.
F_SOURCES	=	Sources
F_INCLUDES	=	Includes
F_MEDIAS	=	Medias
F_TESTS		=	Tests

# Command aliases
CC			=	g++
RM			=	rm -f

# Compilation flags
DEBUG		=
CXXFLAGS	=	-Wall -Werror -Wextra -std=c++17 -fPIC $(DEBUG)
CPPFLAGS	=	-I $(F_INCLUDES)
LDFLAGS		=
FLAGS		=	$(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS)

# Compilation sources
MAIN		=	$(F_SOURCES)/main.cpp

CORE_SRC	=	$(F_SOURCES)/Core/Log.cpp

APP_SRC		=

INTERP_SRC	=

SRC			=	$(CORE_SRC) $(APP_SRC) $(INTERP_SRC)

OBJ			=	$(SRC:.cpp=.o)

all: compile

compile: static dynamic

static: $(OBJ)

dynamic: $(OBJ)

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