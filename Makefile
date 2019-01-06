CC		= g++
CFLAGS	= -std=c++11 -Wall -Werror -Wextra

SRCFILE	= status.cpp\
		  type.cpp\
		  maillon.cpp\
		  main.cpp\
		  Board.cpp\
		  game.cpp\
		  game_Dame.cpp\
		  game_Dame_Angl.cpp\
		  game_Echec.cpp\
		  factory.cpp\
		  piece.cpp\
		  piece_echec.cpp\
		  piece_dame_angl.cpp\

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
	@/bin/rm $(OBJ) || true 2>/dev/null
	@/bin/rm -R $(OBJDIR) || true 2>/dev/null

fclean : clean
	/bin/rm $(NAME) || true 2>/dev/null

re : fclean all
