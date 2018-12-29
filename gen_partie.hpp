#ifndef GEN_GAME_HPP
# define GEN_GAME_HPP

# define NB_GAME 1 //definit le nombre possible jeux traites par notre constructeur de partie

# include <string>
# include <iostream>

class			MAILLON;
class			BOARD;

MAILLON			**Dame_setup(void);
MAILLON			**Echec_setup(void);
MAILLON			**Stratego_setup(void);

typedef struct	s_Variante
{
	std::string	jeu;
	MAILLON		**(*game_setup)(void);
//	int			(*end_game)();
	int			board_size;
}				t_V;


t_V				g_setter[] =
{
	{"Dame", &Dame_setup, 10},
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
		int		(move_parsing)(std::string str);
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
