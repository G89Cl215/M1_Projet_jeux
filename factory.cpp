#include "factory.hpp"
#include "game.hpp"
#include "Board.hpp"

static int		ft_isgame(std::string str)
{
	int		i;

	i = 0;
	while (i < FACTORY::NB_GAME && str.compare(FACTORY::GAME_NAME[i]))
		i++;
	if (i == FACTORY::NB_GAME)
		return (0);
	return (1);
}

GAME		*FACTORY::init()
{
	std::string		str;
	int				i	{0};

	std::cout << "	===          BIENVENUE            ===" << std::endl;
	std::cout << "	*  Auteurs :  Thomas MORNARD,       *" << std::endl;
	std::cout << "	*             Thomas GOUEDARD       *" << std::endl;
	std::cout << "	*  La fabrique de jeu est prete,    *" << std::endl;
	std::cout << "	*  Ce programme vous fera jouer     *" << std::endl;
	std::cout << "	*  Les variantes supportees sont :  *" << std::endl;
	while (i < FACTORY::NB_GAME)
	{
		std::cout <<"	*       " << FACTORY::GAME_NAME[i] << std::endl;
		i++;
	}
	std::cout << "	*  Veuillez choisir une variante    *" << std::endl;
	std::cout << "	===                               ===" << std::endl;
	std::cin >> str;
	while (!(ft_isgame(str)))
	{
		if (!(str.compare("quit")))
			return (0);
		std::cout << "Ceci n'est pas un nom de jeu" << std::endl;
		std::cin >> str;
	}
	return (FACTORY::create(str));
}

GAME		*FACTORY::create(std::string str)
{
	if (!(str.compare("Echec")))
		return (new GAME_Echec());
	if (!(str.compare("Dame_v.Anglaise")))
		return (new GAME_Dame_Angl);
	return (new GAME_Dame());
}

void		FACTORY::display_commands()
{
		std::cout << std::endl << "Usage :" << std::endl;
		std::cout << "	*  Les mouvements se saisissent de la maniere suivante" << std::endl;
		std::cout << "	*  1) Tapez les coordonnees d'une de vos pieces" << std::endl;
		std::cout << "	*		comme indique sur l'echelle : " << std::endl;
		std::cout << "	*		lettre puis chiffre, sans espace" << std::endl;
		std::cout << "	*  2) Tapez un tiret '-' toujours sans espace" << std::endl;
		std::cout << "	*  3) Tapez les coordonnees d'un deplacement valide" << std::endl;
		std::cout << "	*     de la piece saisie" << std::endl;
		std::cout << "	*  ex) e3-e4" << std::endl;
		std::cout << std::endl << "D'autres commandes sont dsiponibles" << std::endl;
		std::cout << "	*  Les commandes disponibles sont :" << std::endl;
		std::cout << "	*		Status" << std::endl;
		std::cout << "	*		New_game" << std::endl;
		std::cout << "	*		Historique" << std::endl;
		std::cout << "	*		Coups_possibles" << std::endl;
		std::cout << "	*		quit" << std::endl;
		std::cout << "	*		resign" << std::endl;
		std::cout << "	*		Help ou help" << std::endl;
}

void	FACTORY::possible_moves(GAME *game)
{
	std::cout << std::endl << "Liste des coups possibles, piece par piece :" << std::endl;
	game->display_moves();
}

GAME	*FACTORY::new_game(GAME *game)
{
	delete game ;
	return (FACTORY::init());
}

int		FACTORY::parsing(GAME *game, std::string str)
{
	if (!(str.compare("Status")))
		game->display_status();
	else if (!(str.compare("New_game")))
	{
		std::cout << "	*  Abandon de la partie" << std::endl;
		std::cout << "	*  Etes-vous sur ? (O/N)" << std::endl;
		std::cin >> str ;
		if (!(str.compare("O")))
			game = FACTORY::new_game(game);
	}
	else if (!(str.compare("Historique")))
		std::cout << "Historique" << std::endl;
	else if (!(str.compare("Affiche")))
		game->get_board()->affiche();
	else if (!(str.compare("Coups_possibles")))
		FACTORY::possible_moves(game);
	else if (!(str.compare("Help")) || !(str.compare("help")))
		FACTORY::display_commands();
	else if (game->parsing(str))
		game->change_turn();
	else
		return (0);
	return (1);
}

int		FACTORY::message_fin(GAME *game, std::string str)
{
	if (!(str.compare("resign")) || !(str.compare("quit")))
	{

//		game.ft_game_end();
//		liberation de toute memoire allouee
		return (1);
	}
	else if (game->get_status() != STATUS::white_turn
					&& game->get_status() != STATUS::black_turn)
	{
		game->display_status();
		return (1);
	}
	return (0);
}


