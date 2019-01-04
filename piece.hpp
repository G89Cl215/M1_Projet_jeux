#ifndef PIECE_H
# define PIECE_H

# include <string>
# include <vector>

class	TYPE;
class	BOARD;

class	PIECE
{
	private :
		TYPE							*type;
		int								*position;
		std::vector<std::vector<int>>	possible_moves;
	public :
		PIECE(TYPE *type, int *position);
		PIECE(TYPE *type, std::vector<int> position); 
		int			*get_position(void) const;
		int			get_color(void) const;
		TYPE		*get_type(void) const;
		std::string	color_code(void) const;
		std::string	display_piece(void) const;
		void		set_legit(std::vector<std::vector<int>> list);
		int			is_legit(int *new_pos);
		void		set_position(int *position_new);
		void		transform(int n);
		~PIECE();
};

int		pawn_move_legit(BOARD *board, PIECE *piece, int *position_new);
int		queen_move_legit(BOARD *board, PIECE *piece, int *position_new);

#endif


