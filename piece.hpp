#ifndef PIECE_H
# define PIECE_H

# include <stdlib.h>
# include "gen_partie.hpp"

class				PIECE;

typedef struct		s_type
{
	int				move_verif(const PIECE *piece, const int *position);
	int				color;
	TYPE			piece;
	struct s_type	*next;
}					t_type;

class	PIECE
{
	private :
			t_type	*type;
			int		*position;
	public :
			PIECE(t_type *type, int *position);
			int		*get_position(void);
			int		get_color(void);
			TYPE	get_type(void);
			char	*display_type(void);
			int		move(int *position);
			void	transform(int n);
			~PIECE();
};

int					pawn_move_legit(const PIECE *piece, const int *position_new);

#endif
