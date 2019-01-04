#ifndef GEN_GAME_HPP
# define GEN_GAME_HPP

# include <string>
# include <iostream>
# include "status.hpp"

class			BOARD;

class			GAME
{
	private :
		BOARD	*board;
		STATUS	status;
//		int		(move_parsing)(std::string str);
	public :
		GAME(std::string game_type);
		~GAME();
		BOARD	*get_board(void) const;
		STATUS	get_status(void) const;
		void	display_status(void);
		void	set_status(STATUS status);
		void	change_turn(void);
		int		parsing(std::string str);
};

#endif
