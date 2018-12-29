#ifndef PIECE_H
# define PIECE_H

# include <string>

class	TYPE;

class	PIECE
{
	private :
		TYPE	*type;
		int		*position;
	public :
		PIECE(TYPE *type, int *position);
		int			*get_position(void) const;
		int			get_color(void) const;
		std::string	get_type(void) const;
		int			move(int *position);
		void		transform(int n);
		~PIECE();
};

int		pawn_move_legit(const PIECE *piece, const int *position_new);
int		queen_move_legit(const PIECE *piece, const int *position_new);

#endif
