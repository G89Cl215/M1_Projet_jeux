//Voici les fonctions permettant de determiner les mouvements possibles
//des differentes pieces d'un jeu d'echec

# include "piece.hpp"
# include "Board.hpp"
# include <vector>

void	knight_move(BOARD *board, PIECE *piece) 
{
	std::vector<std::vector<int>>	moves;
	std::vector<int>				tab		{-2, -1, 1, 2};
	int								color	{piece->get_color()};
	int								*pos	{piece->get_position()};

	for (int c : tab)
	{
		for (int l : tab)
		{
			if ((c + l) % 2 != 0)
			{
				if (board->in_board(pos[0] + c, pos[1] + l)
					&& board->can_play(pos[0] + c, pos[1] + l, color))
					moves.push_back({pos[0] + c, pos[1] + l, 1 + board->can_take(pos[0] + c, pos[1] + l, color)});
			}
		}
	}
	piece->set_legit(moves);
}


void	bishop_move(BOARD *board, PIECE *piece)
{
	std::vector<std::vector<int>>	moves;
	int								distance;
	int								color	{piece->get_color()};
	int								*pos	{piece->get_position()};

	for (int i : {-1, 1})
	{
		for (int j : {-1, 1})
		{
			distance = 1;
			while (board->in_board(pos[0] + i * distance, pos[1] + j * distance)
					&& board->can_play(pos[0] + i * distance, pos[1] + j * distance, color))
			{
				if (board->can_take(pos[0] + i * distance, pos[1] + j * distance, color))
				{
					moves.push_back({pos[0] + i * distance, pos[1] + j * distance, 2});
					break;
				}
				moves.push_back({pos[0] + i * distance, pos[1] + j * distance, 1});
				distance++;
			}
		}
	}
	piece->set_legit(moves);
}


void	Echec_pawn_move(BOARD *board, PIECE *piece)
{
	std::vector<std::vector<int>>	moves;
	int								color	{piece->get_color()};
	int								*pos	{piece->get_position()};
	
	if (!(piece->get_status()) && !(board->case_occupee(pos[0] + 2 * color, pos[1])))
		moves.push_back({pos[0] + 2 * color, pos[1], 1});
	if (!(board->case_occupee(pos[0] + color, pos[1])))
		moves.push_back({pos[0] + color, pos[1], (pos[0] + color == board->get_taille() - 1) ? 3 : 1});
	for (int i : {-1, 1})
	{
		if (board->in_board(pos[0] + color, pos[1] + i)
			&& board->can_take(pos[0] + color, pos[1] + i, color))
			moves.push_back({pos[0] + color, pos[1] + i, (pos[0] + color == board->get_taille() - 1) ? 4 : 2});
	}
	piece->set_legit(moves);
}


void	rook_move(BOARD *board, PIECE *piece)
{
	std::vector<std::vector<int>>	moves;
	int								distance = 1;
	int								color	{piece->get_color()};
	int								*pos	{piece->get_position()};

	for (int i : {-1, 0, 1})
	{
		for (int j : {-1, 0, 1})
		{
			if ((i + j) % 2 != 0 && !(i == 0 && j == 0))
			{
				distance = 1;
				while (board->in_board(pos[0] + i * distance, pos[1] + j * distance)
						&& board->can_play(pos[0] + i * distance, pos[1] + j * distance, color))
				{
					if (board->can_take(pos[0] + i * distance, pos[1] + j * distance, color))
					{
						moves.push_back({pos[0] + i * distance, pos[1] + j * distance, 2});
						break ;
					}
					moves.push_back({pos[0] + i * distance, pos[1] + j * distance, 1});
					distance++;
				}
			}
		}
	}
	piece->set_legit(moves);
}


void	Echec_queen_move(BOARD *board, PIECE *piece)
{
	std::vector<std::vector<int>>	moves;
	int								distance;
	int								color	{piece->get_color()};
	int								*pos	{piece->get_position()};
	
	for (int i : {-1, 0, 1})
	{
		for (int j : {-1, 0, 1})
		{
			if (i != 0 || j != 0)
			{
				distance = 1;
				while (board->in_board(pos[0] + i * distance, pos[1] + j * distance)
						&& board->can_play(pos[0] + i * distance, pos[1] + j * distance, color))
				{
					if (board->can_take(pos[0] + i * distance, pos[1] + j * distance, color))
					{
						moves.push_back({pos[0] + i * distance, pos[1] + j * distance, 2});
						break;
					}
					moves.push_back({pos[0] + i * distance, pos[1] + j * distance, 1});
					distance++;
				}
			}
		}
	}
	piece->set_legit(moves);
}


void	Echec_king_move(BOARD *board, PIECE	*piece)
{
	std::vector<std::vector<int>>	moves;
	int								color	{piece->get_color()};
	int								*pos	{piece->get_position()};
	
	for (int i : {-1, 0, 1})
	{
		for (int j : {-1, 0, 1})
		{
			if (!(i == 0 && j == 0) && board->in_board(pos[0] + i, pos[1] + j)
				&& board->can_play(pos[0] + i, pos[1] + j, color))
			{
				if (board->can_take(pos[0] + i, pos[1] + j, color))
					moves.push_back({pos[0] + i, pos[1] + j, 2});
				else
					moves.push_back({pos[0] + i, pos[1] + j, 1});
			}
		}
	}
	piece->set_legit(moves);
}
