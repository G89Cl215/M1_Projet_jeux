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


GAME_Dame::GAME_Dame() : GAME((new BOARD(10, this->set_up())), STATUS::white_turn)
{
	this->update_moves();
}


void		GAME_Dame::type_setup(TYPE **list_start)
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
	int		*pos	{new int[2]};

	pos[0] = i / 5 + 2 * (i / 20);
	pos[1] = 2 * (i % 5) + (i / 5) % 2;
	return (pos);
}

MAILLON		**GAME_Dame::set_up()
{
	TYPE	*w_pawn;
	MAILLON	**list;
	MAILLON	*cur_piece;
	PIECE	*piece;
	int		i		{1};

	this->type_setup(&w_pawn);
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

int		GAME_Dame::must_take()
{
	int											take_power	{0};
	int											color		{this->status == STATUS::white_turn ? 1 : -1};
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
				if ((*it)[2] > take_power)
					take_power = (*it)[2];
				it++;
			}
		}
		voyager = voyager->get_next();
	}
	return (take_power);
}

int		GAME_Dame::can_take(PIECE *piece)
{
	int											take_power	{0};
	std::vector<std::vector<int>>				moves		{piece->get_moves()};
	std::vector<std::vector<int>>::iterator		it			{moves.begin()};
	
	while (it < moves.end())
	{
		if ((*it)[2] > take_power)
			take_power = (*it)[2];
		it++;
	}
	return (take_power);
}

void		GAME_Dame::display_moves()
{
	MAILLON		*voyager	{*this->board->get_listePieces()};
	PIECE		*piece;
	int			color		{this->status == STATUS::white_turn ? 1 : -1};
	int			take_power	{this->must_take()};

	while (voyager)
	{
		piece = voyager->get_piece();
		if (piece->get_color() == color && this->can_take(piece) == take_power)
			piece->display_moves(take_power);
		voyager = voyager->get_next();
	}
}

int			GAME_Dame::move(MAILLON *to_move, int *new_position)
{
	PIECE			*piece		{to_move->get_piece()};
	int				*pos		{piece->get_position()};
	int				j			{piece->is_legit(new_position)};
	int				to_remove[2];
	int				c;
	int				l;
	int				distance	{0};
	std::string		str;

	if (j)
	{
		if ((j == 1) && (this->must_take() > 1))
		{
			std::cout << "Vous pouvez prendre une piece, la prise est obligatoire" << std::endl;
			return (j);
		}
		while (j > 1)
		{
			if (!(piece->get_type()->get_piece().compare("o")))
			{
				to_remove[0] = (pos[0] + new_position[0]) / 2;
				to_remove[1] = (pos[1] + new_position[1]) / 2;
				this->get_board()->remove(to_remove);
			}
			else
			{
				l = (pos[0] - new_position[0] > 0) ? -1 : 1;
				c = (pos[1] - new_position[1] > 0) ? -1 : 1;
				while (1)
				{
					distance++;
					to_remove[0] = pos[0] + l * distance;
					to_remove[1] = pos[1] + c * distance;
					if (this->get_board()->case_occupee(to_remove[0], to_remove[1]))
					{
						this->get_board()->remove(to_remove);
						break ;
					}
				}
			}
			piece->set_position(new_position);
			piece->get_type()->moves(this->board, piece);
			if ((j = this->can_take(piece)) > 1)
			{
				this->board->affiche();
				std::cout << "	*  Possibilite de prise multiple." << std::endl;
				std::cout << "	*  Entrez une nouvelle case destination prolongeant la prise" << std::endl;
				std::cin >> str;
				new_position[1] = str[0] - 'a';
				new_position[0] = atoi(str.substr(1).c_str()) - 1;
				while (!(this->board->in_board(new_position[0], new_position[1]))
								|| !((j = piece->is_legit(new_position)) > 1))
				{
					std::cout << "Cette coordonnee n'est pas valide, veuillez re-iterer" << std::endl;
					std::cin >> str;
					new_position[1] = str[0] - 'a';
					new_position[0] = atoi(str.substr(1).c_str()) - 1;
				}
			}
		}
		piece->set_position(new_position);
		if (!(piece->get_type()->get_piece().compare("o"))
					&& (new_position[0] == (piece->get_color() == 1 ? 9 : 0)))
			piece->transform(1);
		this->update_moves();
		this->end_game();
		return (1);
	}
	return (0);
}

void		GAME_Dame::end_game()
{
	
	int		color	{this->status == STATUS::white_turn ? 1 : -1};

	if (!(this->must_take()))
	{
		this->set_status(color == 1 ? STATUS::black_win : STATUS::white_win);
		delete this ;
	}
}

GAME_Dame::~GAME_Dame()
{
	delete this->board;
}
