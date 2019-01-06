#ifndef FACTORY_H
# define FACTORY_H

#include <string>


class					GAME;

class					FACTORY
{
	public :
		static const int			NB_GAME				{3};
		static const std::string	GAME_NAME[NB_GAME];
		static GAME					*init();
		static GAME					*create(std::string str);
		static void					display_commands();
		static void					possible_moves(GAME *game);
		static int					parsing(GAME *game, std::string str);
		static int					message_fin(GAME *game, std::string str);
};

#endif
