#include "piece.hpp"
#include "type.hpp"
#include "maillon.hpp"
#include "Board.hpp"
#include "gen_partie.hpp"
#include "g_setter.hpp"

#include <iostream>
#include <vector>


t_V				g_setter[] =
{
	{"Dame", &Dame_setup, 10},
	{"Echec", &Echec_setup, 8},
	/*{"Stratego", &Stratego_setup, 10}*/
};


GAME::GAME(std::string game_type) : status(STATUS::white_turn) 
{
	int		i {0};

	while (i < NB_GAME && game_type.compare(g_setter[i].jeu))
		i++;
	this->board = new BOARD(g_setter[i].board_size, g_setter[i].game_setup());
	this->update_moves();
	this->display_status();
}


BOARD		*GAME::get_board(void) const
{
	return (this->board);
}


STATUS		GAME::get_status() const
{
	return (this->status);
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


int			GAME::parsing(std::string str)
{
	MAILLON			*to_move;
	std::size_t		i			{0};
	int				new_pos[2];
	int				color		{this->status == STATUS::white_turn ? 1 : -1};

	new_pos[1] = str[i++] - 'a';
	new_pos[0] = atoi(str.substr(i).c_str()) - 1;
	i += (new_pos[0] > 9 ? 2 : 1);
	if (this->board->in_board(new_pos[0], new_pos[1])
			&& (to_move = this->board->case_occupee(new_pos[0], new_pos[1]))
			&& (to_move->get_piece()->get_color() == color))
	{
		if (str[i++] != '-')
			return (0);
		new_pos[1]  = str[i++] - 'a';
		new_pos[0] = atoi(str.substr(i++).c_str()) - 1;
		if (this->board->in_board(new_pos[0], new_pos[1])
			&& this->move(to_move, new_pos))
			return (1);
	}
	return (0);
}


int			GAME::move(MAILLON *to_move, int *new_position)
{
	int		j;
	PIECE	*piece {to_move->get_piece()};

	j = piece->is_legit(new_position);
	if (j != 0)
	{
		if (!(piece->get_status()))
			piece->set_status(1);
		if (!(j % 2))
			this->get_board()->remove(new_position);
		piece->set_position(new_position);
		if (j > 2)	
			piece->transform(1);
		std::cout << "how" << std::endl;
		this->update_moves();
	}
	return (j);
}


void		GAME::update_moves()
{
	MAILLON		*voyager	{*this->board->get_listePieces()};
	PIECE		*piece;

	while (voyager)
	{
		piece = voyager->get_piece();
		piece->get_type()->moves(this->board, piece);
		voyager = voyager->get_next();
	}
}


void		GAME::display_moves()
{
	MAILLON		*voyager	{*this->board->get_listePieces()};
	PIECE		*piece;
	int			color		{this->status == STATUS::white_turn ? 1 : -1};

	while (voyager)
	{
		piece = voyager->get_piece();
		if (piece->get_color() == color)
			piece->display_moves();
		voyager = voyager->get_next();
	}
}



/* Initialisation de la liste chainee des differents types de pieces
 * possibles dans une partie de Dames
 */

static void	Dame_type_setup(TYPE **list_start)
{
	TYPE	*w_queen;
	TYPE	*b_pawn;
	TYPE	*b_queen;

	b_queen = new TYPE(&Dame_queen_move, -1, "Q", 0);
	b_pawn = new TYPE(&Dame_pawn_move, -1, "O", b_queen);
	w_queen = new TYPE(&Dame_queen_move, 1, "Q", b_pawn);
	*list_start = new TYPE(&Dame_pawn_move, 1, "O", w_queen);
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



//=======         ECHEC_SETUP

void		Echec_type_setup(TYPE **w_king)
{
	TYPE	*w_pawn;
	TYPE	*w_bishop;
	TYPE	*w_knight;
	TYPE	*w_rook;
	TYPE	*w_queen;
	TYPE	*b_king;
	TYPE	*b_pawn;
	TYPE	*b_bishop;
	TYPE	*b_knight;
	TYPE	*b_rook;
	TYPE	*b_queen;

	b_queen = new TYPE(&Echec_queen_move, -1, "Q", 0);
	b_rook = new TYPE(&rook_move, -1, "T", b_queen);
	b_knight = new TYPE(&knight_move, -1, "C", b_rook);
	b_bishop = new TYPE(&bishop_move, -1, "F", b_knight);
	b_pawn = new TYPE(&Echec_pawn_move, -1, "o", b_bishop);
	b_king = new TYPE(&Echec_king_move, -1, "W", b_pawn);
	w_queen = new TYPE(&Echec_queen_move, 1, "Q", b_king);
	w_rook = new TYPE(&rook_move, 1, "T", w_queen);
	w_knight = new TYPE(&knight_move, 1, "C", w_rook);
	w_bishop = new TYPE(&bishop_move, 1, "F", w_knight);
	w_pawn = new TYPE(&Echec_pawn_move, 1, "o", w_bishop);
	*w_king = new TYPE(&Echec_king_move, 1, "W", w_pawn);
}


MAILLON		**Echec_setup(void)
{
	TYPE				*w_king;
	MAILLON				**list;
	MAILLON				*cur_piece;
	PIECE				*piece;
	std::vector<int>	pos = {0, 4};
	int					i {0};

	Echec_type_setup(&w_king);
	piece = new PIECE(w_king, pos);
	list = new MAILLON*;
	*list = new MAILLON(piece);
	w_king = w_king->get_next();

//	PLACE les poins blancs
	while (i < 8)
	{
		pos = {1, i};
		piece = new PIECE(w_king, pos);
		cur_piece = new MAILLON(piece);
		MAILLON::pushback(list, cur_piece);
		i++;
	}
//	PLACE les fous blancs
	w_king = w_king->get_next();
	pos = {0, 2};
	piece = new PIECE(w_king, pos);
	cur_piece = new MAILLON(piece);
	MAILLON::pushback(list, cur_piece);
	pos = {0, 5};
	piece = new PIECE(w_king, pos);
	cur_piece = new MAILLON(piece);
	MAILLON::pushback(list, cur_piece);


//	PLACE les cavaliers blancs
	w_king = w_king->get_next();
	pos = {0, 1};
	piece = new PIECE(w_king, pos);
	cur_piece = new MAILLON(piece);
	MAILLON::pushback(list, cur_piece);
	pos = {0, 6};
	piece = new PIECE(w_king, pos);
	cur_piece = new MAILLON(piece);
	MAILLON::pushback(list, cur_piece);


//	PLACE les tours blanches
	w_king = w_king->get_next();
	pos = {0, 0};
	piece = new PIECE(w_king, pos);
	cur_piece = new MAILLON(piece);
	MAILLON::pushback(list, cur_piece);
	pos = {0, 7};
	piece = new PIECE(w_king, pos);
	cur_piece = new MAILLON(piece);
	MAILLON::pushback(list, cur_piece);


//	PLACE la dame blanche
	w_king = w_king->get_next();
	pos = {0, 3};
	piece = new PIECE(w_king, pos);
	cur_piece = new MAILLON(piece);
	MAILLON::pushback(list, cur_piece);

	w_king = w_king->get_next();
	pos = {7, 4};
	piece = new PIECE(w_king, pos);
	cur_piece = new MAILLON(piece);
	MAILLON::pushback(list, cur_piece);

	i = 0;
	w_king = w_king->get_next();
	while (i < 8)
	{
		pos = {6, i};
		piece = new PIECE(w_king, pos);
		cur_piece = new MAILLON(piece);
		MAILLON::pushback(list, cur_piece);
		i++;
	}

	w_king = w_king->get_next();
	pos = {7, 2};
	piece = new PIECE(w_king, pos);
	cur_piece = new MAILLON(piece);
	MAILLON::pushback(list, cur_piece);
	pos = {7, 5};
	piece = new PIECE(w_king, pos);
	cur_piece = new MAILLON(piece);
	MAILLON::pushback(list, cur_piece);
	

	w_king = w_king->get_next();
	pos = {7, 1};
	piece = new PIECE(w_king, pos);
	cur_piece = new MAILLON(piece);
	MAILLON::pushback(list, cur_piece);
	pos = {7, 6};
	piece = new PIECE(w_king, pos);
	cur_piece = new MAILLON(piece);
	MAILLON::pushback(list, cur_piece);
		

	w_king = w_king->get_next();
	pos = {7, 0};
	piece = new PIECE(w_king, pos);
	cur_piece = new MAILLON(piece);
	MAILLON::pushback(list, cur_piece);
	pos = {7, 7};
	piece = new PIECE(w_king, pos);
	cur_piece = new MAILLON(piece);
	MAILLON::pushback(list, cur_piece);
	
	w_king = w_king->get_next();
	pos = {7, 3};
	piece = new PIECE(w_king, pos);
	cur_piece = new MAILLON(piece);
	MAILLON::pushback(list, cur_piece);
	return (list);
}
