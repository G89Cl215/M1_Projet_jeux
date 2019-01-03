#include <iostream>
#include "gen_partie.hpp"
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

void		BOARD::retirePiece(int l, int c)
{
	MAILLON	*a_retirer;

	if ((a_retirer = (*(this->get_listePieces()))-> search(l, c)))
	{
		delete(a_retirer->get_piece());
		a_retirer = a_retirer->get_next();
	}
}


int			BOARD::move(int *square, int *position_new)
{
		int		j;
		PIECE	*to_move;

		to_move = ((*(this->in_game))->search(*square, square[1]))->get_piece();
		j = (to_move->get_type())->move_verif(this, to_move, position_new);
		if (j != 0)
				to_move->set_position(position_new);
		if (j == 2)
				//demander a lutilisateur la transfo. 1 pour les dames.
				to_move->transform(1);
		return (j);
}


int			BOARD::case_occupee(int l, int c, int color)
{
	MAILLON *found;

	if (((found = (*(this->get_listePieces()))->search(l, c))) 
					&& (((found)->get_piece())->get_color() == (-1) * color))
		return (1);
	return (0);
}

// Affiche le plateau avec les pieces présentes dessus
// - correspond à une case blanche et . à une case noire


static void	affiche_ligne_bord(int taille) 
{
	int i;

	i = 0;
   	while (i++ < taille)
		cout << "+---";
	cout << "+" << endl;
}


void		BOARD::affiche()
{
	int		c;
	int		l;
	MAILLON	*to_display;

	l = 0;
	affiche_ligne_bord(this->get_taille());
	while (l < this->get_taille())
	{
		c = 0;
		while (c < this->get_taille())
		{
			cout << "| ";
			if ((to_display = (*(this->get_listePieces()))->search(l, c)))
				cout << (to_display->get_piece())->display_piece() << " ";
			else if (((l + c) % 2) == 0)
				cout << "- ";
			else
				cout << "  ";
			c++;
		}
		cout << "|" << endl;
		l++;
		affiche_ligne_bord(this->get_taille());
	}
}
