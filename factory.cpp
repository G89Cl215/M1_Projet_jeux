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

GAME		*FACTORY::init(std::fstream &hist)
{
	std::string		str;
	int				i	{0};

	std::cout << "	===           BIENVENUE             ===" << std::endl;
	std::cout << "	*  Auteurs :  Thomas MORNARD,         *" << std::endl;
	std::cout << "	*             Thomas GOUEDARD         *" << std::endl;
	std::cout << "	*  La fabrique de jeu est prete,      *" << std::endl;
	std::cout << "	*  Ce programme vous fera jouer       *" << std::endl;
	std::cout << "	*  Les variantes supportees sont :    *" << std::endl;
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
	hist << str << std::endl;
	return (FACTORY::create(str));
}

GAME		*FACTORY::init(std::ifstream &to_load, std::fstream &hist)
{
	std::string		str;
	GAME			*game;

	std::cout << "	===           BIENVENUE             ===" << std::endl;
	std::cout << "	*  Auteurs :  Thomas MORNARD,         *" << std::endl;
	std::cout << "	*             Thomas GOUEDARD         *" << std::endl;
	std::cout << "	*  La fabrique de jeu est prete,      *" << std::endl;
	std::cout << "	*  Vous avez choisi de charger        *" << std::endl;
	std::cout << "	*       une partie via un historique  *" << std::endl;
	std::cout << "	===                                 ===" << std::endl;

	to_load >> str;
	if (!(ft_isgame(str)))
	{
		std::cout << "	*  Le fichier charge est non conforme *" << std::endl;
		std::cout << "	*  Il ne debute pas par un jeu connu  *"<< std::endl;
		std::cout << "	*          Reprise Manuelle           *" << std::endl << std::endl <<std::endl;
		return (0);
	}
	game = FACTORY::create(str);
	hist << str << std::endl;
	std::cout << "Vous jouez a une partie de " << std::endl;
	std::cout << "	" << str << std::endl;
	to_load >> str;
	while (!(to_load.eof()))
	{
		if (!(FACTORY::parsing(game, str, hist)))
			break ;
		to_load >> str;
	}
	return (game);
}

GAME		*FACTORY::create(std::string str)
{
	if (!(str.compare("Echec")))
		return (new GAME_Echec());
	if (!(str.compare("Dame_v.Anglaise")))
		return (new GAME_Dame_Angl());
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
		std::cout << "	*		Affiche" << std::endl;
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

GAME	*FACTORY::new_game(GAME *game, std::fstream &hist)
{
	std::string		str;
	
	if (game)
	{
		std::cout << "	*  Abandon de la partie" << std::endl;
		std::cout << "	*  Etes-vous sur ? (O/N)" << std::endl;
		std::cin >> str ;
		if (!(str.compare("O")))
		{
			delete game ;
			return (FACTORY::init(hist));
		}
		return (game);
	}
	// ici : Gestion de l'historique sinon les deux vont s'additionner
	return (FACTORY::init(hist));
}

void	FACTORY::load_game()
{
	std::string		str;
	
	std::cout << "	*  Veuillez taper le chemin du fichier historique" << std::endl;
	std::cout << "	*  le chemin peut etre absolu ou relatif" << std::endl;
	std::cin >> str;
}

void	FACTORY::display_history(std::fstream &hist)
{
	std::string		str;
	int				i	{1};

	std::cout << "	*  Historique :" << std::endl;
	hist.clear();
	hist.seekg(0, std::ios::beg);
	hist >> str;
	std::cout << "Vous jouez a une partie de " << std::endl;
	while (!(hist.eof()))
	{
		if (!(i % 2))
			std::cout << i / 2 << ".  ";
		else
			std::cout << "	";
		std::cout << str;
		if (i++ % 2)
			std::cout << std::endl;
		hist >> str;
	}
	std::cout << std::endl << std::endl;
	hist.clear();
}

int		FACTORY::parsing(GAME *game, std::string str, std::fstream &hist)
{
	if (!(str.compare("Status")))
		game->display_status();
	else if (!(str.compare("New_game")))
		game = FACTORY::new_game(game, hist);
	else if (!(str.compare("Historique")))
		FACTORY::display_history(hist);
	else if (!(str.compare("Affiche")))
		game->get_board()->affiche();
	else if (!(str.compare("Coups_possibles")))
		FACTORY::possible_moves(game);
	else if (!(str.compare("Charge_partie")))
		FACTORY::load_game();
	else if (!(str.compare("Help")) || !(str.compare("help")))
		FACTORY::display_commands();
	else if (game->parsing(str, hist))
		game->change_turn();
	else
		return (0);
	return (1);
}

int		FACTORY::message_fin(GAME *game, std::string str)
{
	if (!(str.compare("resign")))
		game->set_status(game->get_status() == STATUS::white_turn ?
						STATUS::black_win : STATUS::white_win);
	if (!(str.compare("quit")))
		return (1);
	else if (game->get_status() != STATUS::white_turn
					&& game->get_status() != STATUS::black_turn)
	{
		game->display_status();
		return (1);
	}
	return (0);
}
