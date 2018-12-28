#include "piece.hpp"
#include "gen_partie.hpp"
#include "libft/libft.h"

PIECE::PIECE(t_type *type, int *position)
{
	this->type = type;
	this->position = position;
}


int		*PIECE::get_position(void) const
{
	return (this->position);
}


int		PIECE::get_color(void) const
{
	return ((this->type)->color);
}


TYPE	PIECE::get_type(void) const
{
	return ((this->type)->piece);
}	


int		PIECE::move(int *position_new)
{
		int	j;

		j = (this->type)->move_verif(this, position_new);
		if (j != 0)
				this->position = position_new;
		if (j == 2)
				this->transform(1);
		return (j);
}


void	PIECE::transform(int i)
{
	while (i--)
		this->type = (this->type)->next;
}


/*
int		queen_verif(const PIECE *piece, int new_i, int new_j, int flag, int i)
{
	if (new_i == piece->position[0])
	{
		if (new_j == piece->position[1])
			return (1);
		else
			return (0);
	}
	if (!ft_btw(new_i, 0, 9) || !ft_btw(new_j, 0, 9))
			return (0);
	if (flag ^ case_occupee(new_i, new_j, piece->type->couleur))
		return (0);
	if (flag)
		return (pawn_verif(piece, new_i + x, new_j + i, 0, 0));
	return (pawn_verif(piece, new_i + 1, new_j - 1, 1, - 1) || pawn_verif(piece, new_i + , new_j + 1, 1, 1));
}

int		queen_move_legit(PIECE *piece, int *position_new)
{
		int	i;
		int	j;


		


		return (0);
}*/


int		pawn_verif(const PIECE *piece, int new_i, int new_j, int flag, int i)
{
	int	*pos;

	pos = piece->get_position();
	if (new_i == pos[0])
	{
		if (new_j == pos[1])
			return (1);
		else
			return (0);
	}
	if (!ft_btw(new_j, 0, 9) || flag ^ case_occupee(new_i, new_j, piece->get_color()))
		return (0);
	new_i -= piece->get_color();
	if (flag)
		return (pawn_verif(piece, new_i, new_j + i, 0, 0));
	return (pawn_verif(piece, new_i, new_j - 1, 1, - 1) || pawn_verif(piece, new_i, new_j + 1, 1, 1));
}


int		pawn_move_legit(const PIECE *piece, const int *position_new)
{
	int		*pos;

	pos = piece->get_position();
	if (((position_new[0] - pos[0]) * piece->get_color()) <= 0) 	
		return (0);
	if (pawn_verif(piece, position_new[0], position_new[1], 0, 0))
			return ((position_new[0] == 0 || position_new[1] == 9) ? 2 : 1);
	return (0);
}
