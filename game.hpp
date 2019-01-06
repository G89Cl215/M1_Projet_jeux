#ifndef GEN_GAME_HPP
# define GEN_GAME_HPP

# include <string>
# include <iostream>
# include "status.hpp"

class			BOARD;
class			MAILLON;
class			PIECE;
class			TYPE;

class			GAME
{
	friend class GAME_Echec;
	friend class GAME_Dame;
	friend class GAME_Dame_Angl;
	private :
		BOARD	*board;
		STATUS	status;
		
	public :
		GAME(BOARD *board, STATUS status);
		BOARD			*get_board() const;
		STATUS			get_status() const;
		void			display_status();
		void			set_status(STATUS status);
		void			change_turn();
		virtual int		move(MAILLON *to_move, int *new_position) = 0;
		void			update_moves();
		void			display_moves();
		int				parsing(std::string str);
		virtual			~GAME() = 0;
};

class			GAME_Echec : public GAME
{
	public :
		GAME_Echec();
		int			is_check(int color);
		void		type_setup(TYPE **w_king);
		MAILLON		**set_up();
		int			move(MAILLON *to_move, int *new_position);
		void		end_game();
		~GAME_Echec();
};


class			GAME_Dame : public GAME
{
	public :
		GAME_Dame();
		void		type_setup(TYPE **w_king);
		MAILLON		**set_up();
		int			move(MAILLON *to_move, int *new_position);
		int			must_take();
		int			can_take(PIECE *piece);
		void		end_game();
		~GAME_Dame();
};

class			GAME_Dame_Angl : public GAME
{
	public :
		GAME_Dame_Angl();
		void		type_setup(TYPE **w_king);
		MAILLON		**set_up();
		int			move(MAILLON *to_move, int *new_position);
		int			must_take();
		int			can_take(PIECE *piece);
		void		end_game();
		~GAME_Dame_Angl();
};

#endif
