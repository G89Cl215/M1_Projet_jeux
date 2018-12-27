#ifndef GEN_GAME_HPP
# define GEN_GAME_HPP

# include "piece.hpp"
# include "Board.hpp"

# define NB_GAME 1 //definit le nombre possible jeux traite par notre constructeur de partie

class			PIECE;
//class			BOARD;

PIECE			*Dame_setup(void);
PIECE			*Echec_setup(void);
PIECE			*Stratego_setup(void);

PIECE			*Dame_setup(void);

enum			e_variante
{
	Dame,
	Echec,
	Stratego
};

typedef struct	s_Variante
{
	e_variante	jeu;
	PIECE		*(*game_setup)(void);
	int			board_size;
}				t_V;

t_V				g_setter[] =
{
	{Dame, &Dame_setup, 10},
/*	{Echec, &Echec_setup, 8},
	{Stratego, &Stratego_setup, 10}*/
};

enum			TYPE
{
	pawn,
	queen,
	knight,
	bishop,
	rook,
	king
};

class			GAME
{
	private :
			t_lst	*in_game;
			BOARD	board;
			int		status;
	public :
			GAME(e_variante game_type);
			void	retirer_piece();
			
};

#endif
