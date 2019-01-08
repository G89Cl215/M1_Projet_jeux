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
		  piece_dame.cpp\
		  piece_dame_angl.cpp\

SRCDIR	= .
SRC		= $(addprefix $(SRCDIR)/,$(SRCFILE))
HDR 	= .
OBJDIR	= obj
OBJFILE	= $(SRCFILE:.cpp=.o)
OBJ		= $(addprefix $(OBJDIR)/,$(OBJFILE))

HISTDIR	= Historique

NAME	= Game_factory

all : $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

$(OBJDIR)/%.o : %.cpp | $(HISTDIR) $(OBJDIR)
		$(CC) $(CFLAGS) -o $@ -c $< -I $(HDR)

$(OBJDIR) :
	@/bin/mkdir $(OBJDIR) 2>/dev/null

$(HISTDIR) :
	@/bin/mkdir $(HISTDIR) 2>/dev/null

clean :
	@/bin/rm $(OBJ) 2>/dev/null || true
	@/bin/rm -R $(OBJDIR) 2>/dev/null || true

fclean : clean
	/bin/rm $(NAME) 2>/dev/null || true

re : fclean all
