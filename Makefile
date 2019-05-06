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
TESTS		=	run_tests

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
EXTERN_FLAGS		=
CXXFLAGS	=	-Wall -Werror -Wextra -std=c++17 -fPIC $(EXTERN_FLAGS) -Wno-ignored-qualifiers
CPPFLAGS	=	-I $(F_INCLUDES)
LDFLAGS		=
FLAGS		=	$(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS)

# Compilation sources
MAIN		=	$(F_SOURCES)/Main.cpp

CORE_SRC	=	$(F_SOURCES)/Core/Log.cpp

APP_SRC		=	$(F_SOURCES)/App/Item.cpp \
				$(F_SOURCES)/App/Variant.cpp

TSRC		=	$(F_TESTS)/tests_Variant.cpp \
				$(F_TESTS)/tests_Chrono.cpp

SRC			=	$(CORE_SRC) $(APP_SRC)

OBJ			=	$(SRC:.cpp=.o)

TOBJ		=	$(TSRC:.cpp=.o)

# Compilation rules
all: compile

compile: $(OBJ) static dynamic

static:
	$(CSTATIC) -o $(OA_STATIC) $(OBJ)

dynamic:
	$(CC) -o $(OA_DYNAMIC) -shared $(OBJ) $(FLAGS)

bin: $(OBJ)
	$(CC) -o $(BINARY) $(MAIN) $(OBJ) $(FLAGS)

debug:
	make EXTERN_FLAGS="-g3" bin

tests_run:
	make EXTERN_FLAGS="-lcriterion --coverage" compile_tests

compile_tests: $(OBJ) $(TOBJ)
	$(CC) -o $(TESTS) $(OBJ) $(TOBJ) $(FLAGS)
	./$(TESTS)

clean:
	$(RM) $(OBJ) $(TOBJ)
	find . -type f -name '*.gcno' -delete
	find . -type f -name '*.gcda' -delete
	find . -type f -name 'vgcore.*' -delete

fclean: clean
	$(RM) $(OA_DYNAMIC) $(OA_STATIC) $(BINARY) $(TESTS)

re: fclean all

.PHONY: all compile static dynamic bin debug clean fclean re