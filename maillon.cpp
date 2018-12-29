#include "maillon.hpp"
#include "piece.hpp"

MAILLON::MAILLON(PIECE *piece) : piece(piece), next(0)
{
}


MAILLON			*MAILLON::get_next(void)
{
	return (this->next);
}

PIECE			*MAILLON::get_piece(void)
{
		return (this->piece);
}

MAILLON			*MAILLON::search(int l, int c)
{
	int				*pos;
	MAILLON			*voyager;
	
	voyager = this;
	while (voyager != 0)
	{
		pos = (voyager->get_piece())->get_position();
		if (pos[0] == l && pos[1] == c)
			return (voyager);
		voyager = voyager->get_next();
	}
	return (0);
}
