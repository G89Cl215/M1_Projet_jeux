#ifndef GEN_GAME_HPP
# define GEN_GAME_HPP

# include <string>
# include <iostream>
# include "status.hpp"

class			BOARD;
class			MAILLON;
class			TYPE;

class			GAME
{
	private :
		BOARD	*board;
		STATUS	status;
		
	public :
		GAME(BOARD *board, STATUS status);
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

class			GAME_Echec : public GAME
{
	public :
		GAME_Echec();
		int		is_check(int color);
		void	end_game();
		void	type_setup(TYPE **w_king);
		MAILLON **set_up();
};


class			GAME_Dame : public GAME
{
	public :
		GAME_Dame();
		void	end_game();
		void	type_setup(TYPE **w_king);
		MAILLON **set_up();
};

class			GAME_Dame_Angl : public GAME
{
	public :
		GAME_Dame_Angl();
		void	end_game();
		void	type_setup(TYPE **w_king);
		MAILLON **set_up();
};

#endif
