#ifndef TYPE_H
#define TYPE_H

#include <string>

class		PIECE;
class		BOARD;

class		TYPE
{
	private :
		int			color;
		std::string	piece;
		TYPE		*next;
	public :
		TYPE(void (*moves)(BOARD *board, PIECE *piece),
					   int color, std::string piece, TYPE *next);
		void		(*moves)(BOARD *board, PIECE *piece);
		TYPE		*get_next();
		std::string	get_piece();
		int			get_color();
		~TYPE();
		
};

#endif
