#include "type.hpp"

TYPE::TYPE(void (*moves)(BOARD *board, PIECE *piece),
					   int color, std::string piece, TYPE *next) :
		color(color), piece(piece), next(next), moves(moves)
{}

TYPE		*TYPE::get_next()
{
	return (this->next);
}

std::string	TYPE::get_piece()
{
	return (this->piece);
}

int			TYPE::get_color()
{
	return (this->color);
}
