#include "maillon.hpp"
#include "piece.hpp"

MAILLON::MAILLON(PIECE *piece) : piece(piece), next(0)
{
}


MAILLON		*MAILLON::get_next(void)
{
	return (this->next);
}

PIECE			*MAILLON::get_piece(void)
{
		return (this->piece);
}

void		MAILLON::pushback(MAILLON **list_begin, MAILLON *new_back)
{
	MAILLON *voyager;

	if (!list_begin)
		return ;
	if (!(*list_begin))
		*list_begin = new_back;
	else
	{
		voyager = *list_begin;
		while (voyager->get_next())
			voyager = voyager->get_next();
		voyager->set_next(new_back);
	}
}

void		MAILLON::list_del(MAILLON **list_begin)
{
	MAILLON	*to_del;

	if (!(list_begin))
		return ;
	while (*list_begin)
	{
		to_del = *list_begin;
		*list_begin = (*list_begin)->get_next();
		delete to_del;
	}
}

void		MAILLON::set_next(MAILLON *new_next)
{
	this->next = new_next;
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


MAILLON::~MAILLON()
{
	delete this->piece;
}
