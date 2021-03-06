# include "piece.hpp"
# include "Board.hpp"

# include <vector>

void		Dame_Angl_queen_move(BOARD *board, PIECE *piece)
{
	std::vector<std::vector<int>>	list;
	int								*pos	{piece->get_position()};
	int								color	{piece->get_color()};

	for (int i : {-1, 1})
	{
		for (int j : {-1, 1})
		{
			if (board->in_board(pos[0] + j, pos[1] + i)
					&& !(board->case_occupee(pos[0] + j, pos[1] + i)))
				list.push_back({pos[0] + j, pos[1] + i, 1});
		}
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

void	Dame_Angl_pawn_move(BOARD *board, PIECE *piece)
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
		if (board->in_board(pos[0] + 2 * color, pos[1] + 2 * i)
					&& !(board->case_occupee(pos[0] + 2 * color, pos[1] + 2 * i))
					&& (board->can_take(pos[0] + color, pos[1] + i, color)))
			list.push_back({pos[0] + 2 * color, pos[1] + 2 * i, 2});
	}
	piece->set_legit(list);
}
