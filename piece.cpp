#include "piece.hpp"
#include "type.hpp"
#include "Board.hpp"
#include "gen_partie.hpp"

PIECE::PIECE(TYPE *type, int *position) : type(type), position(position)
{}


int			*PIECE::get_position(void) const
{
	return (this->position);
}


int			PIECE::get_color(void) const
{
	return ((this->type)->get_color());
}


TYPE		*PIECE::get_type(void) const
{
	return (this->type);
}

std::string	PIECE::color_code(void) const
{
	return (this->get_color() == 1 ? "33" : "31");
}

std::string	PIECE::display_piece(void) const
{
	std::string		str {"\033["};
			
	str.append(this->color_code());
	str.append("m");
	str.append((this->type)->get_piece());
	str.append("\033[0m");
	return (str);
}


void		PIECE::set_position(int *position_new)
{
	this->position[0] = position_new[0];
	this->position[1] = position_new[1];
}

PIECE::~PIECE()
{
	delete [] this->position;
}

void		PIECE::transform(int i)
{
	while (i--)
		this->type = (this->type)->get_next();
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
*/
int		queen_move_legit(BOARD *board, PIECE *piece, int *position_new)
{
		(void)board;
		(void)piece;
		(void)position_new;
		return (0);
}

static int	ft_btw(int a, int b, int c)
{
	return ((!(a < b) || !(a > c)));
}

static int	pawn_verif(BOARD *board, PIECE *piece, int new_i, int new_j, int flag, int i)
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
	if (!ft_btw(new_j, 0, board->get_taille() - 1)
					|| flag ^ board->can_take(new_i, new_j, piece->get_color())
					|| (!(flag) && (board->case_occupee(new_i, new_j))))
		return (0);
	new_i -= piece->get_color();
	if (flag)
		return (pawn_verif(board, piece, new_i, new_j + i, 0, 0));
	return (pawn_verif(board, piece, new_i, new_j - 1, 1, -1)
					|| pawn_verif(board, piece, new_i, new_j + 1, 1, 1));
}


int		pawn_move_legit(BOARD *board, PIECE *piece, int *position_new)
{
	int		*pos;

	pos = piece->get_position();
	if (((position_new[0] - pos[0]) * piece->get_color()) <= 0) 	
		return (0);
	if (pawn_verif(board, piece, position_new[0], position_new[1], 0, 0))
			return ((position_new[0] == 0 || position_new[1] == 9) ? 2 : 1);
	return (0);
}
