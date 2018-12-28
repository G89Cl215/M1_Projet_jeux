#ifndef PIECE_H
# define PIECE_H

# include "type_piece.hpp" 

class				PIECE;

typedef struct		s_type
{
	int				move_verif(const PIECE *piece, const int *position);
	int				color;
	TYPE			piece;
	int				status;
	struct s_type	*next;
}					t_type;

class				PIECE
{
	private :
		t_type	*type;
		int		*position;
	public :
		PIECE(t_type *type, int *position);
		int		*get_position(void) const;
		int		get_color(void) const;
		TYPE	get_type(void) const;
		char	*display_type(void);
		int		move(int *position);
		void	transform(int n);
		~PIECE();
};

int					pawn_move_legit(PIECE *piece, const int *position_new);
int					queen_move_legit(PIECE *piece, const int *position_new);

#endif
