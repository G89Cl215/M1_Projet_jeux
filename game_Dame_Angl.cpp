#include "piece.hpp"
#include "type.hpp"
#include "maillon.hpp"
#include "Board.hpp"
#include "game.hpp"

#include <iostream>
#include <vector>

/* Initialisation de la liste chainee des differents types de pieces
 * possibles dans une partie de Dames
 */


GAME_Dame_Angl::GAME_Dame_Angl() : GAME((new BOARD(8, this->set_up())), STATUS::white_turn)
{
	this->update_moves();
	this->display_status();
}

void		GAME_Dame_Angl::type_setup(TYPE **list_start)
{
	TYPE	*w_queen;
	TYPE	*b_pawn;
	TYPE	*b_queen;

	b_queen = new TYPE(&Dame_Angl_queen_move, -1, "Q", 0);
	b_pawn = new TYPE(&Dame_Angl_pawn_move, -1, "o", b_queen);
	w_queen = new TYPE(&Dame_Angl_queen_move, 1, "Q", b_pawn);
	*list_start = new TYPE(&Dame_Angl_pawn_move, 1, "o", w_queen);
}

/*Attention, la fonction suivante utilise un codage logique des cases
 * (et non un quelconque codage "standard") qui considere que A 1 
 * est la case du pion 1. Il pourrait donc y avoir incompatibilite 
 * avec certains codes.
 * A bon entendeur...
 */


static int	*Dame_Angl_set_pos(int i)
{
	int		*pos = new int[2];

	pos[0] = i / 4 + 2 * (i / 12);
	pos[1] = 2 * (i % 4) + (i / 4) % 2;
	return (pos);
}

MAILLON		**GAME_Dame_Angl::set_up()
{
	TYPE	*w_pawn;
	MAILLON	**list;
	MAILLON	*cur_piece;
	PIECE	*piece;
	int		i		{1};

	this->type_setup(&w_pawn);
	piece = new PIECE(w_pawn, Dame_Angl_set_pos(0));
	list = new MAILLON*;
	*list = new MAILLON(piece);
	while (i < 24) 
	{
		piece = new PIECE(w_pawn, Dame_Angl_set_pos(i));
		cur_piece = new MAILLON(piece);
		MAILLON::pushback(list, cur_piece);
		i++;
		if (i == 12)
			w_pawn = (w_pawn->get_next())->get_next();
	}
	return (list);
}

