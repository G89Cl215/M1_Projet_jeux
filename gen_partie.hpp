#ifndef GEN_GAME_HPP
# define GEN_GAME_HPP

# include <string>
# include <iostream>
# include "status.hpp"

class			BOARD;
class			MAILLON;

class			GAME
{
	private :
		BOARD	*board;
		STATUS	status;
	public :
		GAME(std::string game_type);
		~GAME();
		BOARD	*get_board() const;
		STATUS	get_status() const;
		void	display_status();
		void	set_status(STATUS status);
		void	change_turn();
		int		move(MAILLON *to_move, int *new_position);
		void	update_moves();
		void	display_moves();
		int		parsing(std::string str);
};

#endif
