CC		= gcc
CFLAGS	= -std=c++11 -Wall -Werror -Wextra

SRCFILE	= Board.cpp\
		  piece.cpp\
		  gen_partie.cpp

SRCDIR	= .
SRC		= $(addprefix $(SRCDIR)/,$(SRCFILE))
HDR 	= .
OBJDIR	= obj
OBJFILE	= $(SRCFILE:.cpp=.o)
OBJ		= $(addprefix $(OBJDIR)/,$(OBJFILE))

LIBFILE	= libft.a
LIBDIR	= libft
LIB		= $(addprefix $(LIBDIR)/,$(LIBFILE))

NAME	= Jeu_de_dames

all : $(OBJ) $(LIB)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIB)

$(OBJDIR)/%.o : %.cpp | $(OBJDIR)
		$(CC) $(CFLAGS) -o $@ -c $< -I $(HDR)

$(OBJDIR) :
		@/bin/mkdir $(OBJDIR) 2>/dev/null

$(LIB) :
	make -C $(LIBDIR)

clean :
	/bin/rm $(OBJ)
	/bin/rm $(OBJDIR)

fclean : clean
	/bin/rm $(NAME)

re : fclean all
