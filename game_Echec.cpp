#include "piece.hpp"
#include "type.hpp"
#include "maillon.hpp"
#include "Board.hpp"
#include "game.hpp"

#include <iostream>
#include <vector>

GAME_Echec::GAME_Echec() : GAME(new BOARD(8, this->set_up()), STATUS::white_turn)
{
	this->update_moves();
	this->display_status();
}


void		GAME_Echec::type_setup(TYPE **w_king)
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


MAILLON		**GAME_Echec::set_up()
{
	TYPE				*w_king;
	MAILLON				**list;
	MAILLON				*cur_piece;
	PIECE				*piece;
	std::vector<int>	pos = {0, 4};
	int					i {0};

	this->type_setup(&w_king);
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
