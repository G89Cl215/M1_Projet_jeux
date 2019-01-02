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
		int				move(int *square, int *position_new);
		int				case_occupee(int l, int c, int color);
		void			affiche();
		~BOARD();
};

#endif
