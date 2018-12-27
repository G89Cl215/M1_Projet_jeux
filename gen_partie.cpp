#include "piece.hpp"

GAME::GAME(e_variante game_type)
{
	int		i;

	i = 0;
	while (i < NB_GAME && g_setter[i][0] != game_type)
			i++;
	this->board = new BOARD(g_setter[i][2]);
	this->status = white_turn;
	this->in_game = g_setter[i][1];
}

/* Initialisation de la liste chainee des differents types de pieces
 * possibles dans une partie de Dames
 */

void	Dame_type_setup(t_type **list_start)
{
	new t_type	*w_queen;
	new t_type	*b_pawn;
	new t_type	*b_queen;

	(*list_start)->color = 1;
	(*list_start)->move_verif = &pawn_move_legit;
	(*list_start)->piece = 0;
	(*list_start)->status = 0;
	(*list_start)->next = w_queen;

	w_queen->color = 1;
	w_queen->move_verif = &queen_move_legit;
	w_queen->piece = 1;
	w_queen->status = 0;
	w_queen->next = b_pawn;

	b_pawn->color = -1;
	b_pawn->move_verif = &pawn_move_legit;
	b_pawn->piece = 0;
	b_pawn->status = 0;
	b_pawn->next = b_queen;

	b_queen->color = -1;
	b_queen->move_verif = &queen_move_legit;
	b_queen->piece = 1;
	b_queen->status = 0;
	b_queen->next = NULL;
}

/*Attention, la fonction suivante utilise un codage logique des cases
 * (et non un quelconque codage "standard") qui considere que A 1 
 * est la case du pion 1. Il pourrait donc y avoir incompatibilite 
 * avec certains codes.
 * A bon entendeur...
 */


int		*Dame_set_pos(int i)
{
	new int		pos[2];

	pos[0] = i / 5 + 2 * (i / 20);
	pos[1] = 2 * (i % 5) + (i / 10) % 2;
	return (pos);
}

PIECE	*Dame_setup(void)
{
		t_type	*w_pawn;
		PIECE	list[40];
		int		i;

		i = 0;
		Dame_type_setup(&w_pawn);
		while (i < 20)
		{
			list[i] = new PIECE(w_pawn, Dame_set_pos(i));
			i++;
		}
		w_pawn = (w_pawn->next)->next;
		while (i < 40)
		{
			list[i] = new PIECE(w_pawn, Dame_set_pos(i));
			i++;
		}
		return (list);
}
