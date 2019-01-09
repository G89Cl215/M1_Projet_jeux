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
}

	
void		GAME_Echec::transform(PIECE *piece)
{
	std::string		str;

	std::cout << "Votre pion peut etre promu" << std::endl;
	std::cout << "Choisissez parmis les pieces suivantes :" << std::endl;
	std::cout << "Fou" << std::endl;
	std::cout << "Cavalier" << std::endl;
	std::cout << "Tour" << std::endl;
	std::cout << "Dame" << std::endl;
	std::cin >> str;
	while (1)
	{
		if (!(str.compare("Fou")))
		{
			piece->transform(1);
			break ;
		}
		else if (!(str.compare("Cavalier")))
		{
			piece->transform(2);
			break ;
		}
		else if (!(str.compare("Tour")))
		{
			piece->transform(3);
			break ;
		}
		else if (!(str.compare("Dame")))
		{
			piece->transform(4);
			break ;
		}
		else
			std::cin >> str;
	}
}

int		GAME_Echec::get_move(int c, int l, int color)
{
	MAILLON										*voyager	{*this->board->get_listePieces()};
	PIECE										*piece;
	std::vector<std::vector<int>>				moves;
	std::vector<std::vector<int>>::iterator		it;

	while (voyager)
	{
		piece = voyager->get_piece();
		if (piece->get_color() == color)
		{
			moves = piece->get_moves();
			it = moves.begin();
			while (it < moves.end())
			{
				if ((*it)[0] == c && (*it)[1] == l)
					return (1);
				it++;
			}
		}
		voyager = voyager->get_next();
	}
	return (0);
}

PIECE		*GAME_Echec::get_king(int color)
{
	MAILLON			*voyager	{*(this->board->get_listePieces())};
	PIECE			*piece;

	while (voyager)
	{
		piece = voyager->get_piece();
		if (piece->get_color() == color && !(piece->get_type()->get_piece().compare("W")))
			return (piece);
		voyager = voyager->get_next();
	}
	return (0);
}

void		GAME_Echec::is_check(int flag)
{
	PIECE	*b_king	{this->get_king(-1)};
	PIECE	*w_king	{this->get_king(1)};
	int		*w_pos	{w_king->get_position()};
	int		*b_pos	{b_king->get_position()};
	
	if (this->get_move(w_pos[0], w_pos[1], 1))
	{
		w_king->set_status(w_king->get_status() + 2);
		if (flag)
			std::cout << "	*  White king is in check" <<std::endl;
	}
	else if (w_king->get_status() > 1)
		w_king->set_status(w_king->get_status() - 2);

	if (this->get_move(b_pos[0], b_pos[1], 1))
	{
		b_king->set_status(b_king->get_status() + 2);
		if (flag)
			std::cout << "	*  Black king is in check" <<std::endl;
	}
	else if (b_king->get_status() > 1)
		b_king->set_status(b_king->get_status() - 2);
}

int			GAME_Echec::move(MAILLON *to_move, int *new_position)
{
	int		color		{this->status == STATUS::white_turn ? 1 : -1};
	PIECE	*king		{this->get_king(color)};
	PIECE	*piece		{to_move->get_piece()};
	PIECE	*rook;
	TYPE	*to_remove;
	MAILLON	*put_back;
	int		j			{piece->is_legit(new_position)};
	int		pos[2];
			
	pos[0] = piece->get_position()[0];
	pos[1] = piece->get_position()[1];
	if (j)
	{
		
		if (!(piece->get_status()))
			piece->set_status(1);
		if (!(j % 2))
		{
			to_remove = this->board->case_occupee(new_position[0], new_position[1])->get_piece()->get_type();
			this->board->remove(new_position);
		}
		piece->set_position(new_position);
		this->update_moves();
		this->is_check(1);
		if (king->get_status() > 1)
		{
			piece->set_position(pos);
			if (!(j % 2))
			{
				put_back = new MAILLON(new PIECE(to_remove, new_position));
				MAILLON::pushback(this->board->get_listePieces(), put_back);
			}
			this->update_moves();
			this->is_check(0);
			this->board->affiche();
			
			return(0);
		}
		if (j > 2)
		{
			this->transform(piece);
			this->update_moves();
			this->is_check(1);
		}
		return (1);
	}
	else if (!(piece->get_type()->get_piece().compare("W")) && !(piece->get_status())
				&& new_position[0] == pos[0])
	{
		j = pos[1] - new_position[1];
		if (j == 2 && (put_back = this->board->case_occupee(pos[0], 0))
						&& !(this->board->case_occupee(pos[0], 1))
						&& !(this->board->case_occupee(pos[0], 2))
						&& !(this->board->case_occupee(pos[0], 3)))
		{
			rook = put_back->get_piece();
			if (!(rook->get_status()) && !(rook->get_type()->get_piece().compare("T")))
			{
				piece->set_position(pos[0], 3);
				this->update_moves();
				this->is_check(1);
				if (king->get_status() < 1)
				{
					piece->set_position(new_position);
					this->update_moves();
					this->is_check(1);
					if (king->get_status() < 1)
					{	
						rook->set_position(pos[0], 3);
						return (1);
					}
				}
				piece->set_position(pos);
			}
		}
		if (j == -2 && (put_back = this->board->case_occupee(pos[0], 7))
						&& !(this->board->case_occupee(pos[0], 6))
						&& !(this->board->case_occupee(pos[0], 5)))
		{
			rook = put_back->get_piece();
			if (!(rook->get_status()) && !(rook->get_type()->get_piece().compare("T")))
			{
				piece->set_position(pos[0], 5);
				this->update_moves();
				this->is_check(1);
				if (king->get_status() < 1)
				{
					piece->set_position(new_position);
					this->update_moves();
					this->is_check(1);
					if (king->get_status() < 1)
					{	
						rook->set_position(pos[0], 5);
						return (1);
					}
				}
				piece->set_position(pos);
			}
		}
	}	
	return (0);
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

GAME_Echec::~GAME_Echec()
{
	delete this->board;
}
