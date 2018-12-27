#ifndef BOARD_H
# define BOARD_H

# include <vector>

class					PIECE;

typedef struct			s_piecelst
{
	PIECE				*piece;
	struct s_piecelst	*next;
}						t_lst;


class					BOARD
{
	private:
		int				taille;
		t_lst			**in_game;
	public:
		BOARD(int taille, t_lst **in_game);
		virtual	~BOARD();
		t_lst			**get_listePieces(void);
		int				get_taille(void);
		void			retirePiece(int l, int c);
		int				case_occupee(int l, int c, int color);
		void			affiche();
};

#endif
