#include <string>
#include <iostream>
#include <fstream>

#include "factory.hpp"
#include "game.hpp"
#include "Board.hpp"

const std::string	FACTORY::GAME_NAME[NB_GAME] {"Dame", "Dame_v.Anglaise", "Echec"};

int					main(int ac, char **av)
{
	std::string		str;
	GAME			*game	{0};
	std::fstream	hist;
	
	hist.open("Historique/hist.txt", std::fstream::in | std::fstream::out | std::ios::trunc);

	if (ac == 2)
	{
		str = av[1];
		std::ifstream to_load(str, std::ios::in);
		if (to_load)
		{
			game = FACTORY::init(to_load, hist);
			to_load.close();
		}
	}
	else if (ac >= 3)
	{
		std::cout << "Vous avez rentre trop d'arguments" << std::endl;
		return (0);
	}
	else if (!(game = FACTORY::init(hist)))
		return (0);
	game->display_status();
	std::cin >> str;
	while (!(FACTORY::message_fin(game, str)))
   	{
		if (!(FACTORY::parsing(game, str, hist)))
			std::cout << "Ce n'est pas un coup valide" << std::endl;
		else
			game->display_status();
		std::cin >> str;
	}
	hist.close();
	return (0);
}
