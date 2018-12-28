#ifndef GEN_GAME_HPP
# define GEN_GAME_HPP

# define NB_GAME 1 //definit le nombre possible jeux traites par notre constructeur de partie

# include <string>
# include <iostream>
# include "t_lst.hpp"
# include "type_piece.hpp"

class			BOARD;


//t_lst			**Dame_setup(void);
t_lst			**Echec_setup(void);
t_lst			**Stratego_setup(void);


typedef struct	s_Variante
{
	std::string			jeu;
//	t_lst			**(*game_setup)(void);
//	int				(*end_game)()
	int				board_size;
}				t_V;


t_V				g_setter[] =
{
	{"Dame", 10},
/*	{"Echec", &Echec_setup, 8},
	{"Stratego", &Stratego_setup, 10}*/
};


enum			STATUS
{
	white_turn,
	black_turn,
	white_win,
	black_win,
	draw
};


class			GAME
{
	private :
		BOARD	*board;
		STATUS	status;
	public :
		GAME(std::string game_type);
		BOARD	*get_board(void) const;
		STATUS	get_status(void) const;
		void	display_status(void);
		void	set_status(STATUS status);
		void	change_turn(void);
//		int		ft_parsing(std::sting str);
};

#endif
