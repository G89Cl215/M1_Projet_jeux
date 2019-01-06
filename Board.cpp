#include <iostream>
#include "game.hpp"
#include "type.hpp"
#include "piece.hpp"
#include "maillon.hpp"
#include "Board.hpp"

using namespace std;

// CONSTRUCTEUR

BOARD::BOARD(int taille, MAILLON **in_game) : taille(taille), in_game(in_game)
{}


// DESTRUCTEUR

BOARD::~BOARD()
{
	MAILLON::list_del(in_game);
}

MAILLON		**BOARD::get_listePieces(void)
{
	return (this->in_game);
}


int			BOARD::get_taille(void)
{
	return (this->taille);
}

// AUTRES METHODES
// Retire une piece située aux coordonnées en paramètre de la liste de pièces

void		BOARD::remove(int *pos)
{
	MAILLON	*a_retirer;

	std::cout << "hello" << std::endl;
	if ((a_retirer = (*(this->in_game))->search(pos[0], pos[1])))
	{
		std::cout << "world" << std::endl;
		delete (a_retirer->get_piece());
		*a_retirer = *(a_retirer->get_next());
	}
}


MAILLON		*BOARD::case_occupee(int l, int c)
{
	return ((*(this->in_game))->search(l, c));
}


int			BOARD::can_take(int l, int c, int color)
{
	MAILLON *found;

	if ((found = this->case_occupee(l, c))
				&& (((found)->get_piece())->get_color() == (-1) * color))
		return (1);
	return (0);
}


int			BOARD::can_play(int l, int c, int color)
{
	MAILLON *found;

	if ((found = this->case_occupee(l, c))
				&& (((found)->get_piece())->get_color() == color))
		return (0);
	return (1);
}

int			BOARD::in_board(int l, int c)
{
	return ((l < this->taille && l >= 0) && (c < this->taille && c >= 0));
}


//	=>	AFFICHAGE  <=
//
// Affiche le plateau avec les pieces présentes dessus
// - correspond à une case blanche et . à une case noire


static void	affiche_ligne_bord(int taille) 
{
	int i;

	i = 0;
	cout << "  --	";	
   	while (i++ < taille)
		cout << "+---";
	cout << "+" << endl;
}

static void	affiche_echelle(int taille) 
{
	char	i;

	i = 'a';
	cout << endl;
	cout << "	| ";
	while (i < 'a' + taille)
		cout << i++ << " | ";
	cout << endl << endl;
}

void		BOARD::affiche()
{
	int		c;
	int		l {this ->get_taille()};
	MAILLON	*to_display;

	affiche_echelle(this->get_taille());
	affiche_ligne_bord(this->get_taille());
	while (l-- > 0)
	{
		c = 0;
		cout <<"  " << l + 1 << "	"; 
		while (c < this->get_taille())
		{
			cout<< "| ";
			if ((to_display = (*(this->get_listePieces()))->search(l, c)))
				cout << (to_display->get_piece())->display_piece() << " ";
			else if (((l + c) % 2) == 0)
				cout << "- ";
			else
				cout << "  ";
			c++;
		}
		cout << "|" << endl;
		affiche_ligne_bord(this->get_taille());
	}
	cout << endl;
}
