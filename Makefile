CC		= g++
CFLAGS	= -std=c++11 -Wall -Werror -Wextra

SRCFILE	= status.cpp\
		  type.cpp\
		  maillon.cpp\
		  main.cpp\
		  Board.cpp\
		  gen_partie.cpp\
		  piece.cpp\
		  piece_echec.cpp\

SRCDIR	= .
SRC		= $(addprefix $(SRCDIR)/,$(SRCFILE))
HDR 	= .
OBJDIR	= obj
OBJFILE	= $(SRCFILE:.cpp=.o)
OBJ		= $(addprefix $(OBJDIR)/,$(OBJFILE))

NAME	= Jeu_de_dames

all : $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

$(OBJDIR)/%.o : %.cpp | $(OBJDIR)
		$(CC) $(CFLAGS) -o $@ -c $< -I $(HDR)

$(OBJDIR) :
	@/bin/mkdir $(OBJDIR) 2>/dev/null

clean :
	@/bin/rm $(OBJ) || true
	@/bin/rm -R $(OBJDIR) || true

fclean : clean
	/bin/rm $(NAME) || true

re : fclean all
