CC		= gcc
CFLAGS	= -std=c++11 -Wall -Werror -Wextra

SRCFILE	= piece.cpp\

SRCDIR	= .
SRC		= $(addprefix $(SRCDIR)/,$(SRCFILE))
HDR 	= .
OBJDIR	= obj
OBJFILE	= $(SRCFILE:.cpp=.o)
OBJ		= $(addprefix $(OBJDIR)/,$(OBJFILE))


NAME	= Jeu_de_dames

all : $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

$(OBJDIR)/%.o : %.c
		@/bin/mkdir $(OBJDIR) 2>/dev/null || true
		$(CC) $(CFLAGS) -o $@ -c $< -I $(HDR)

clean :
	/bin/rm $(OBJ)

fclean : clean
	/bin/rm $(NAME)

re : fclean all
