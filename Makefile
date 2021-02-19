##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile
##

CXXFLAGS += -std=c++11

CFLAGS	=	-I./include -Wall -Wextra  -Wno-deprecated -fPIC
LDFLAGS	=	-shared

NAME	=	libmy_malloc.so


FILES	=	calloc.c		\
			free.c			\
			malloc.c		\
			realloc.c		\
			reallocarray.c	\
			utils.c

SRC		= 	$(addprefix src/, $(FILES))

TESTS	= 	tests/tests_malloc.c		\
			tests/tests_free.c			\
			tests/tests_realloc.c		\
			tests/tests_calloc.c		\
			tests/tests_reallocarray.c

OBJ		=	$(SRC:.c=.o)

TESTS_OBJ		=	$(TESTS:.c=.o)

all:	$(NAME)

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(OBJ) $(LDFLAGS)

tests_run::	$(TESTS_OBJ)
tests_run:: all
	@rm -rf *.gc*
	gcc -o unit_test $(TESTS_OBJ) -I./include --coverage -lcriterion
	LD_PRELOAD=./$(NAME) ./unit_test

clean:
	rm -f $(OBJ) $(OBJ2)

fclean:	clean
	rm -f $(NAME)
	rm -f tests/*.o
	rm -f unit_test
	rm -f *.gc*

re:	fclean all

.PHONY: all $(NAME) tests_run clean fclean re