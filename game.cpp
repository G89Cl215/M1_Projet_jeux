#include "piece.hpp"
#include "type.hpp"
#include "maillon.hpp"
#include "Board.hpp"
#include "game.hpp"

#include <iostream>
#include <vector>


GAME::GAME(BOARD *board, STATUS status) : board(board), status(status)
{};


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
	int				new_pos[2];
	std::size_t		i			{0};
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

GAME::~GAME()
{
}
