#ifndef PIECE_H
# define PIECE_H

# include <string>

class	TYPE;
class	BOARD;

class	PIECE
{
	private :
		TYPE	*type;
		int		*position;
	public :
		PIECE(TYPE *type, int *position);
		int			*get_position(void) const;
		int			get_color(void) const;
		TYPE		*get_type(void) const;
		std::string	color_code(void) const;
		std::string	display_piece(void) const;
		void		set_position(int *position_new);
		void		transform(int n);
		~PIECE();
};

int		pawn_move_legit(BOARD *board, PIECE *piece, int *position_new);
int		queen_move_legit(BOARD *board, PIECE *piece, int *position_new);

#endif
