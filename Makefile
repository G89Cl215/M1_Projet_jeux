CC		= gcc
CFLAGS	= -std=c++11 -Wall -Werror -Wextra

SRC		= piece.cpp\

OBJ		= $(SRC:.cpp=.o)

NAME	= Jeu_de_dames

all : $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean :
	/bin/rm $(OBJ)

fclean : clean
	/bin/rm $(NAME)

re : fclean all
