#ifndef STATUS_H
# define STATUS_H

# include <iostream>
# include <string>

enum class		STATUS
{
	white_turn = 0,
	black_turn,
	white_win,
	black_win,
	draw
};

std::ostream &operator <<(std::ostream &out , STATUS &d);

#endif
