#include "piece.hpp"
#include "Board.hpp"

/*
static int	queen_take(BOARD *board, PIECE *piece)
{
	int		*pos	{piece->get_position()};
	int		color	{piece->get_color()};

	for (int i : {-1, 1})
	{
		for (int j : {-1, 1})
		{
			if (board->in_board(pos[0] + 2 * j, pos[1] + 2 * i)
						&& !(board->case_occupee(pos[0] + 2 * j, pos[1] + 2 * i))
						&& (board->can_take(pos[0] + j, pos[1] + i, color)))
				return (1);
		}
	}
	return (0);
}
*/
void		Dame_queen_move(BOARD *board, PIECE *piece)
{
	std::vector<std::vector<int>>	list;
	int								distance;
	int								*pos	{piece->get_position()};
	int								color	{piece->get_color()};

//	if (!(queen_take(board, piece)))
//	{
	for (int i : {-1, 1})
	{
		for (int j : {-1, 1})
		{
			distance = 1;
			while (board->in_board(pos[0] + i * distance, pos[1] + j * distance)
					&& !(board->case_occupee(pos[0] + i * distance, pos[1] + j * distance)))
			{
				list.push_back({pos[0] + i * distance, pos[1] + j * distance, 1});
				distance++;
			}
		}
	}
//	}
//	else
//	{
		for (int i : {-1, 1})
		{
			for (int j : {-1, 1})
			{
				if (board->in_board(pos[0] + 2 * j, pos[1] + 2 * i)
							&& !(board->case_occupee(pos[0] + 2 * j, pos[1] + 2 * i))
							&& (board->can_take(pos[0] + j, pos[1] + i, color)))
					list.push_back({pos[0] + 2 * j, pos[1] + 2 * i, 2});
			}
		}
//	}
	piece->set_legit(list);
}

/*
static int	pawn_take(BOARD *board, int color, std::vector<int> pos, std::vector<int> list)
{
	while 
	for (int i : {-1, 1})
	{
		for (int j : {-1, 1})
		{
			if (board->in_board(pos[0] + 2 * j, pos[1] + 2 * i)
						&&!(board->case_occupee(pos[0] + 2 * j, pos[1] + 2 * i))
						&& (board->can_take(pos[0] + j, pos[1] + i, color)))
				return (1);
		}
	}
	return (0);
}
*/
void	Dame_pawn_move(BOARD *board, PIECE *piece)
{
	std::vector<std::vector<int>>	list;
	int								color		{piece->get_color()};
	int								*pos		{piece->get_position()};

	for (int i : {-1, 1})
	{
		if (board->in_board(pos[0] + color, pos[1] + i)
				&& !(board->case_occupee(pos[0] + color, pos[1] + i)))
			list.push_back({pos[0] + color, pos[1] + i, 1});
	}
	for (int i : {-1, 1})
	{
		for (int j : {-1, 1})
		{
			if (board->in_board(pos[0] + 2 * j, pos[1] + 2 * i)
						&& !(board->case_occupee(pos[0] + 2 * j, pos[1] + 2 * i))
						&& (board->can_take(pos[0] + j, pos[1] + i, color)))
				list.push_back({pos[0] + 2 * j, pos[1] + 2 * i, 2});
		}
	}
	piece->set_legit(list);
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


void	Dame_queen_update_move(MAILLON *BOARD, PIECE *piece, int *new_position)
{
	std::vector<std::vector<int>>	list;
	int					*pos {piece->get_position()};

	queen_verif()
	if (!(prise_dame(pos)))
		while ()








	piece->set_legit(list)
}


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


void	Dame_pawn_update_move(MAILLON *BOARD, PIECE *piece)
{
	std::vector< std::vector<int> >	list;
	int					*pos {piece->get_position()};
	static int			take_power {0};


	if (!(board->pawn_take(pos[0], pos[1])))
	{
		for (int i : {-1, 1})
		{
			if (!(board->case_occupee(pos[0] + piece->get_color(), pos[1] + i)))
				list.push_back({pos[0] + piece->get_color(), pos[1] + i, take_power});
		}
	}

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
}*/
