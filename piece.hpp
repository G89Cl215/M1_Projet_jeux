#ifndef PIECE_H
# define PIECE_H

# include <stdlib.h>

enum class	TYPE
{
	pion,
	dame
};

enum class	COULEUR
{
	noir = -1;
	blanc = 1;
};

class	PIECE
{
	private :
			TYPE	type;
			COULEUR	couleur;
			int		*position;
	public :
			PIECE(TYPE type, int *position, int couleur);
			int		*get_position();
			int		move(int *position);
			~PIECE();
};

int		move_legit(PIECE *piece, int *position_new);

#endif
