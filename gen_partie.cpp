#include "piece.hpp"
#include "Board.hpp"
#include "gen_partie.hpp"

GAME::GAME(char *game_type)
{
	int		i;

	i = 0;
	while (i < NB_GAME && ft_strcmp(g_setter[i].jeu, game_type))
			i++;
	this->board = new BOARD(g_setter[i].board_size, g_setter[i].game_setup());
	this->status = white_turn;
	this->display_status();
}


void		GAME::display_status(void)
{
	std::cout << endl << "	*  " << this->status << endl;
}


void		GAME::change_turn(void)
{
	//en pseudo-code
	if (this->status == white_turn)
		this->status++;
	if (this->status == black_turn)
		this->status--;
	this->display_status();
}

/* Initialisation de la liste chainee des differents types de pieces
 * possibles dans une partie de Dames
 */

void		Dame_type_setup(t_type **list_start)
{
	t_type	*w_queen;
	t_type	*b_pawn;
	t_type	*b_queen;

	*w_queen = new t_type;
	*b_pawn = new t_type;
	*b_queen = new t_type;
	
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


int			*Dame_set_pos(int i)
{
	new int		pos[2];

	pos[0] = i / 5 + 2 * (i / 20);
	pos[1] = 2 * (i % 5) + (i / 10) % 2;
	return (pos);
}
//a revoir avec le nouveau systeme
t_lst		**Dame_setup(void)
{
	new t_type	*w_pawn;
	t_lst		**list;
	int			i;

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
