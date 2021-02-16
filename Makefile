##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile
##

CFLAGS	=	-I./include -Wall -Wextra -Werror -Wno-deprecated -fPIC
LDFLAGS	=	-shared

NAME	=	libmy_malloc.so


FILES	=	calloc.c		\
			free.c			\
			malloc.c		\
			realloc.c		\
			reallocarray.c	\
			mputnbr.c		\
			utils.c

SRC		= 	$(addprefix src/, $(FILES))

OBJ	=	$(SRC:.c=.o)

all:	$(NAME)

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	rm -f $(OBJ) $(OBJ2)

fclean:	clean
	rm -f $(NAME)
	rm -f tests/*.o
	rm -f unit_test
	rm -f *.gc*

re:	fclean all

.PHONY: all fclean clean re  $(NAME)