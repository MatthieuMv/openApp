##
## EPITECH PROJECT, 2019
## openApp
## File description:
## Makefile
##

# File names
NAME		=	bin

# Dir names
OA_ROOT		=	../..
F_SOURCES	=	.
F_INCLUDES	=	$(OA_ROOT)/Includes

# Command aliases
CC			=	g++
CSTATIC		=	ar -cvq
RM			=	rm -f

# Compilation flags
OPTFLAGS	=
CXXFLAGS	=	-Wall -Werror -Wextra -std=c++17 $(OPTFLAGS)
CPPFLAGS	=	-I $(F_INCLUDES)
LDFLAGS		=	-L $(OA_ROOT) -lopenApp
FLAGS		=	$(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS)

# Compilation sources
SRC			=	$(F_SOURCES)/HelloWorld.cpp

OBJ			=	$(SRC:.cpp=.o)

# Compilation rules
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(FLAGS)

debug:
	$(MAKE) OPTFLAGS="-g3"

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all debug clean fclean re