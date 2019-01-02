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
		int			status;
		TYPE		*next;
	public :
		TYPE(int (*move_verif)(BOARD *board, PIECE *piece, int *pos),
					   int color, std::string piece, TYPE *next);
		int			(*move_verif)(BOARD *board, PIECE *piece, int *position);
		TYPE		*get_next(void);
		std::string	get_piece(void);
		int			get_status(void);
		int			get_color(void);
		~TYPE();
		
};

#endif
