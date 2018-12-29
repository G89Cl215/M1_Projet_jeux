#include "type.hpp"

TYPE::TYPE(int (*move_verif)(const PIECE *piece, const int *pos),
					   int color, std::string piece, TYPE *next) :
		move_verif(move_verif), color(color), piece(piece), status(0), next(next)
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
