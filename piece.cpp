#include "piece.hpp"
#include "type.hpp"
#include "Board.hpp"
#include "game.hpp"

#include <iostream>

PIECE::PIECE(TYPE *type, int *position) : type(type), position(position), status(0)
{
}


PIECE::PIECE(TYPE *type, std::vector<int> position) : type(type), status(0)
{
	int	*pos = new int[2];

	pos[0] = position[0];
	pos[1] = position[1];
	this->position = pos;
}


int								*PIECE::get_position() const
{
	return (this->position);
}


int								PIECE::get_color() const
{
	return ((this->type)->get_color());
}


TYPE							*PIECE::get_type() const
{
	return (this->type);
}


int								PIECE::get_status() const
{
	return (this->status);
}


std::string						PIECE::color_code() const
{
	return (this->get_color() == 1 ? "33" : "31");
}


std::string						PIECE::display_piece() const
{
	std::string		str {"\033["};
			
	str.append(this->color_code());
	str.append("m");
	str.append((this->type)->get_piece());
	str.append("\033[0m");
	return (str);
}


std::vector<std::vector<int>>	PIECE::get_moves() const
{
	return (this->possible_moves);
}


void							PIECE::display_moves(int i)
{
	std::vector<std::vector<int>>			moves	{this->possible_moves};
	std::vector<std::vector<int>>::iterator	it		{moves.begin()};

	if (moves.begin() != moves.end())
	{
		std::cout << "La piece en " << (char)(this->position[1] + 'a') << " " << this->position[0] + 1 << " peut bouger en : " << std::endl;
		while (it < moves.end())
		{
			if ((*it)[2] >= i)
				std::cout << (char)((*it)[1] + 'a') << " " << (*it)[0] + 1 << "	";
			it++;
		}
		std::cout << std::endl;
		std::cout << std::endl;
	}
}
void							PIECE::set_legit(std::vector<std::vector<int>> list)
{
	(this->possible_moves).clear();
	this->possible_moves = list;
}


int								PIECE::is_legit(int *pos)
{
	std::vector<std::vector<int>>			moves	{this->possible_moves};
	std::vector<std::vector<int>>::iterator	it		{moves.begin()};

	while (it < moves.end())
	{
		if (pos[0] == (*it)[0] && pos[1] == (*it)[1])
			return ((*it)[2]);
		it++;
	}
	return (0);
}


void							PIECE::set_status(int new_status)
{
	this->status = new_status;
}


void							PIECE::set_position(int *position_new)
{
	this->position[0] = position_new[0];
	this->position[1] = position_new[1];
}


void							PIECE::transform(int i)
{
	while (i--)
		this->type = (this->type)->get_next();
}


PIECE::~PIECE()
{
	this->possible_moves.clear();
	delete [] this->position;
}
