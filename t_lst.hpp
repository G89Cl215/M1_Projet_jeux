#ifndef T_LST_H
# define T_LST_H

class					PIECE;

typedef struct			s_piecelst
{
	PIECE				*piece;
	struct s_piecelst	*next;
}						t_lst;

#endif
