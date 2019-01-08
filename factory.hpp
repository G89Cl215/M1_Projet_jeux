#ifndef FACTORY_H
# define FACTORY_H

#include <string>
#include <fstream>


class					GAME;

class					FACTORY
{
	public :
		static const int			NB_GAME				{3};
		static const std::string	GAME_NAME[NB_GAME];
		static GAME					*init(std::fstream &hist);
		static GAME					*init(std::ifstream &to_load, std::fstream &hist);
		static GAME					*create(std::string str);
		static GAME					*new_game(GAME *game, std::fstream &hist);
		static void					load_game();
		static void					display_commands();
		static void					display_history(std::fstream &hist);
		static void					possible_moves(GAME *game);
		static int					parsing(GAME *game, std::string str, std::fstream &hist);
		static int					message_fin(GAME *game, std::string str);
};

#endif
