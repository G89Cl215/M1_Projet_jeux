#include "type.hpp"

TYPE::TYPE(int (*move_verif)(BOARD *board, PIECE *piece, int *pos),
					   int color, std::string piece, TYPE *next) :
		color(color), piece(piece), status(0), next(next), move_verif(move_verif)
{}

TYPE		*TYPE::get_next(void)
{
	return (this->next);
}

std::string	TYPE::get_piece(void)
{
	return (this->piece);
}

int			TYPE::get_status(void)
{
	return (this->status);
}

int			TYPE::get_color(void)
{
	return (this->color);
}
