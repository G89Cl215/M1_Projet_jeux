#ifndef TYPE_H
#define TYPE_H

#include <string>

class		PIECE;

class		TYPE
{
	private :
		int			(*move_verif)(const PIECE *piece, const int *position);
		int			color;
		std::string	piece;
		int			status;
		TYPE		*next;
	public :
		TYPE(int (*move_verif)(const PIECE *piece, const int *pos),
					   int color, std::string piece, TYPE *next);
		TYPE		*get_next(void);
		std::string	get_piece(void);
		int			get_status(void);
		int			get_color(void);
		~TYPE();
		
};

#endif
