#include <string>
#include <iostream>

#include "libft/libft.h"
#include "gen_partie.hpp"

#define BUFFER_SIZE 50


void	ft_init(void)
{
	int	i;

	i = 0;
	std::cout << "	===          BIENVENUE            ===" << std::endl;
	std::cout << "	*  Auteurs :  Thomas MORNARD,       *" << std::endl;
	std::cout << "	*             Thomas GOUEDARD       *" << std::endl;
	std::cout << "	*  Ce programme vous fera jouer     *" << std::endl;
	std::cout << "	*  Les variantes supportees sont :  *" << std::endl;
	while (i < NB_GAME)
	{
	std::cout <<"	*       " << g_setter[i].jeu << std::endl;
	i++;
	}
	std::cout << "	===                               ===" << std::endl;
}


int		ft_isgame(std::string str)
{
	int		i;

	i = 0;
	while (i < NB_GAME && str.compare(g_setter[i].jeu))
		i++;
	if (i == NB_GAME)
		return (0);
	std::cout << "taille du plateau" << g_setter[i].board_size << std::endl;
	return (1);
}

/*void	ft_usage()
{
}*/

int		ft_parsing(std::string str)
{
	if (!(str.compare("Status")))
		;
	else if (!(str.compare("Help")) || !(str.compare("help")))
		std::cout << "Les commandes disponibles sont :";
	else
	{
		
	}
		
	return (1);
}

int		ft_message_fin(std::string str)
{
	if (!(str.compare("resign")))
	{

//		g_game.ft_game_end();
		return (1);
	}
	if (!(str.compare("quit")))
	{
		//liberation de toute memoire allouee
		return (1);
	}

	return (0);
}

int		main(void)
{
	std::string		str;
//	GAME		*game;
	
	ft_init();
	std::cin >> str;
	while (!(ft_isgame(str)))
	{
		if (ft_message_fin(str))
			return (0);
		std::cout << "Ceci n'est pas un nom de jeu" << std::endl;
		std::cin >> str;
	}
//	*game = new GAME(str);
	std::cin >> str;
	while (!(ft_message_fin(str)))
   	{
		if (!(ft_parsing(str)))
			std::cout << "Ce n'est pas un coup valide" <<std:: endl;
		std::cin >> str;
		
	
	
	}
	return (0);
}
