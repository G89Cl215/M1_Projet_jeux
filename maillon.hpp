#ifndef MAILLON_H
# define MAILLON_H

class					PIECE;

class					MAILLON
{
	private :
		PIECE		*piece;
		MAILLON		*next;
	public :
		MAILLON(PIECE *piece);
		~MAILLON(); //ca cest important il peut y avoir des leaks
		MAILLON			*get_next(void);
		PIECE			*get_piece(void);
		void			set_next(MAILLON *next);
//		static void		list_del(MAILLON **list_begin);
		static void		pushback(MAILLON **list_begin, MAILLON *new_back);
		MAILLON			*search(int line, int column);
		
};

#endif
