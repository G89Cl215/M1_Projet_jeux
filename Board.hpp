#ifndef BOARD_H
# define BOARD_H

class					MAILLON;

class					BOARD
{
	private:
		int				taille;
		MAILLON			**in_game;
	public:
		BOARD(int taille, MAILLON **in_game);
		MAILLON			**get_listePieces(void);
		int				get_taille(void);
		void			retirePiece(int l, int c);
		int				move(MAILLON *to_move, int *new_position);
		int				can_take(int l, int c, int color);
		int				can_play(int l, int c, int color);
		MAILLON			*case_occupee(int l, int c);
		void			affiche();
		~BOARD();
};

#endif
