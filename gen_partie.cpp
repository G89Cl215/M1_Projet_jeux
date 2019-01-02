#include "piece.hpp"
#include "type.hpp"
#include "maillon.hpp"
#include "Board.hpp"
#include "gen_partie.hpp"
#include "g_setter.hpp"

#include <iostream>

t_V				g_setter[] =
{
	{"Dame", &Dame_setup, 10},
/*	{"Echec", &Echec_setup, 8},
	{"Stratego", &Stratego_setup, 10}*/
};


GAME::GAME(std::string game_type) : status(STATUS::white_turn) 
{
	int		i;

	i = 0;
	while (i < NB_GAME && game_type.compare(g_setter[i].jeu))
			i++;
	this->board = new BOARD(g_setter[i].board_size, g_setter[i].game_setup());
	this->display_status();
}


BOARD		*GAME::get_board(void) const
{
	return (this->board);
}

void		GAME::display_status(void)
{
	std::cout << std::endl << "	*  " << this->status << std::endl;
}


void		GAME::set_status(STATUS status)
{
	this->status = status;
}


void		GAME::change_turn(void)
{
	if (this->status == STATUS::white_turn)
		this->set_status(STATUS::black_turn);
	else if (this->status == STATUS::black_turn)
		this->set_status(STATUS::white_turn);
	this->display_status();
}

/* Initialisation de la liste chainee des differents types de pieces
 * possibles dans une partie de Dames
 */

static void	Dame_type_setup(TYPE **list_start)
{
	TYPE	*w_queen;
	TYPE	*b_pawn;
	TYPE	*b_queen;

	b_queen = new TYPE(&queen_move_legit, -1, "Q", 0);
	b_pawn = new TYPE(&pawn_move_legit, -1, "O", b_queen);
	w_queen = new TYPE(&queen_move_legit, 1, "Q", b_pawn);
	*list_start = new TYPE(&pawn_move_legit, 1, "O", w_queen);
}

/*Attention, la fonction suivante utilise un codage logique des cases
 * (et non un quelconque codage "standard") qui considere que A 1 
 * est la case du pion 1. Il pourrait donc y avoir incompatibilite 
 * avec certains codes.
 * A bon entendeur...
 */


static int	*Dame_set_pos(int i)
{
	int		*pos = new int[2];

	pos[0] = i / 5 + 2 * (i / 20);
	pos[1] = 2 * (i % 5) + (i / 5) % 2;
	return (pos);
}

MAILLON		**Dame_setup(void)
{
	TYPE	*w_pawn;
	MAILLON	**list;
	MAILLON	*cur_piece;
	PIECE	*piece;
	int		i;

	i = 1;
	Dame_type_setup(&w_pawn);
	piece = new PIECE(w_pawn, Dame_set_pos(0));
	list = new MAILLON*;
	*list = new MAILLON(piece);
	while (i < 40)
	{
		piece = new PIECE(w_pawn, Dame_set_pos(i));
		cur_piece = new MAILLON(piece);
		MAILLON::pushback(list, cur_piece);
		i++;
		if (i == 20)
			w_pawn = (w_pawn->get_next())->get_next();
	}
	return (list);
}
/*
int			Dame_parsing()
{
	
}*/
