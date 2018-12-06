#ifndef PIECE_H
# define PIECE_H

# include <stdlib.h>



typedef struct		s_type
{
	int				*move_verif(const PIECE *piece, const int *position);
	int				couleur;
	TYPE			piece;
	struct s_type	*next;
}					t_type;


class	PIECE
{
	private :
			t_type	*type;
			int		*position;
	public :
			PIECE(TYPE type, int *position);
			int		*get_position();
			int		move(int *position);
			void	transform(int n);
			~PIECE();
};

int		move_legit(const PIECE *piece, const int *position_new);

#endif
