##
## EPITECH PROJECT, 2019
## openApp
## File description:
## Makefile
##

# File names
OA_STATIC	=	libopenApp.a
OA_DYNAMIC	=	libopenApp.so
OA_WDYNAMIC	=	openApp.dll
BINARY		=	bin
TESTS		=	run_tests

# Dir names
OA_ROOT		=	.
F_SOURCES	=	Sources
F_CORE		=	$(F_SOURCES)/Core
F_APP		=	$(F_SOURCES)/App
F_INCLUDES	=	Includes
F_MEDIAS	=	Medias
F_TESTS		=	Tests
F_RENDERER	=

# Command aliases
CC			=	g++
CSTATIC		=	ar -cvq
RM			=	rm -f

# Compilation flags
OPTFLAGS	=
RFLAGS		=
CXXFLAGS	=	-Wall -Werror -Wextra -std=c++17 -fPIC $(OPTFLAGS) $(RFLAGS)
CPPFLAGS	=	-I $(F_INCLUDES)
LDFLAGS		=
FLAGS		=	$(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS)

# Compilation sources
MAIN		=	$(F_SOURCES)/Main.cpp

CORE_SRC	=	$(F_CORE)/Log.cpp \
				$(F_CORE)/Path.cpp \
				$(F_CORE)/Operators.cpp \
				$(F_CORE)/Colors.cpp \
				$(F_CORE)/String.cpp

APP_SRC		=	$(F_APP)/Item.cpp \
				$(F_APP)/ItemChilds.cpp \
				$(F_APP)/ItemProperty.cpp \
				$(F_APP)/ItemExpression.cpp \
				$(F_APP)/ItemFind.cpp \
				$(F_APP)/Parser.cpp \
				$(F_APP)/Var.cpp \
				$(F_APP)/AppFactory.cpp

TSRC		=	$(F_TESTS)/tests_Var.cpp \
				$(F_TESTS)/tests_Chrono.cpp \
				$(F_TESTS)/tests_ContainerHelper.cpp \
				$(F_TESTS)/tests_Error.cpp \
				$(F_TESTS)/tests_Signal.cpp \
				$(F_TESTS)/tests_Property.cpp \
				$(F_TESTS)/tests_Expression.cpp \
				$(F_TESTS)/tests_Item.cpp \
				$(F_TESTS)/tests_Path.cpp \
				$(F_TESTS)/tests_Factory.cpp \
				$(F_TESTS)/tests_AppFactory.cpp \
				$(F_TESTS)/tests_Parser.cpp \
				$(F_TESTS)/tests_Operators.cpp \
				$(F_TESTS)/tests_STL.cpp \
				$(F_TESTS)/tests_Log.cpp

SRC			=	$(CORE_SRC) $(APP_SRC)

RSRC		=

OBJ			=	$(SRC:.cpp=.o) $(RSRC.cpp=.o)

TOBJ		=	$(TSRC:.cpp=.o)

# Compilation rules
all: compile

win: shared
	mv $(OA_DYNAMIC) $(OA_WDYNAMIC)

irrlicht:
	make compileRenderer F_RENDERER="Renderer/Irrlicht" RFLAGS="-lIrrlicht" RSRC="Renderer/Irrlicht/Irrlicht.cpp Renderer/Irrlicht/EventHandler.cpp"

compile: $(OBJ) static dynamic

compileRenderer: $(OBJ) staticRenderer dynamicRenderer

static:
	$(CSTATIC) -o $(OA_STATIC) $(OBJ)

dynamic:
	$(CC) -o $(OA_DYNAMIC) -shared $(OBJ) $(FLAGS)

staticRenderer:
	$(CSTATIC) -o $(OA_STATIC) $(OBJ) $(RSRC)

dynamicRenderer:
	$(CC) -o $(OA_DYNAMIC) -shared $(OBJ) $(RSRC) $(FLAGS)

bin: $(OBJ)
	$(CC) -o $(BINARY) $(MAIN) $(OBJ) $(FLAGS)

debug:
	$(MAKE) OPTFLAGS="-g3" bin

tests_run:
	$(MAKE) OPTFLAGS="-lcriterion --coverage" compile_tests

compile_tests: $(OBJ) $(TOBJ)
	$(CC) -o $(TESTS) $(OBJ) $(TOBJ) $(FLAGS)
	./$(TESTS)

coverage: tests_run
	gcovr --exclude $(F_TESTS)

clean:
	find . -type f -name '*.gcno' -delete
	find . -type f -name '*.gcda' -delete
	find . -type f -name 'vgcore.*' -delete
	find . -type f -name '*.o' -delete

fclean: clean
	$(RM) $(OA_DYNAMIC) $(OA_STATIC) $(BINARY) $(TESTS)

re: fclean all

.PHONY: all win irrlicht bin debug tests_run clean fclean re