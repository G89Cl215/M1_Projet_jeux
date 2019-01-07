#include <iostream>

#include "factory.hpp"
#include "game.hpp"
#include "Board.hpp"

const std::string	FACTORY::GAME_NAME[NB_GAME] {"Dame", "Dame_v.Anglaise", "Echec"};

int				main()
{
	std::string		str;
	GAME			*game;
	
	if (!(game = FACTORY::init()))
		return (0);
	std::cin >> str;
	while (!(FACTORY::message_fin(game, str)))
   	{
		if (!(FACTORY::parsing(game, str)))
			std::cout << "Ce n'est pas un coup valide" << std::endl;
		std::cin >> str;
	}
	return (0);
}
