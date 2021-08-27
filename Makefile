##
## EPITECH PROJECT, 2021
## Puissance4
## File description:
## Makefile
##

NAME	=	EuroLoto
CC	=	@gcc
SRC	=	$(wildcard src/*.c) 						\
		$(wildcard src/cli/*.c)						\
		$(wildcard src/filemanager/*.c)				\
		$(wildcard src/tools/*.c)					\
		$(wildcard src/search_proposition/*.c)		\
		$(wildcard src/datamanager/*.c)

INCLUDE	=	-I./include 					\
			-I./include/file				\
			-I./include/cli					\
			-I./include/tools				\
			-I./include/search_proposition	\
			-I./include/datamanager

OBJ	=	${SRC:.c=.o}
CFLAGS	=	-Wall -Wextra -pedantic -g3 -O0
LIB	= -lcurl

.c.o:
	@echo "\e[1;91m[\e[1;92mOK\e[1;91m]\e[0m" "\e[1;91m Compile\e[1;93m" $< "\e[1;91mto\e[1;92m" $@ "\e[0m"
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

all: $(OBJ)
	@echo "\e[1;91m[\e[1;92mOK\e[1;91m]\e[0m" "\e[1;91m LINK\e[1;93m" $< "\e[1;91mto\e[1;92m" $(NAME) "\e[0m"
	$(CC) -o $(NAME) $(OBJ) $(LIB)

clean:
	@rm -f $(OBJ)

fclean:	clean
	@rm -f $(NAME)

re:	fclean all




