#include <iostream>
#include "piece.hpp"
#include "Board.hpp"

using namespace std;

// CONSTRUCTEUR

BOARD::BOARD(int taille, t_lst **in_game)
{
	this->taille = taille;
	this->in_game = in_game;
}

// DESTRUCTEUR

BOARD::~BOARD()
{
}

t_lst	**BOARD::get_listePieces(void)
{
	return (this->in_game);
}

int		BOARD::get_taille(void)
{
	return (this->taille);
}

//
// METHODE DE RECHERCHE DANS UN TABLEAU
//

// Regarde dans la liste des pièces si il existe une pièce aux coordonnées spécifiées
// La fonction renvoie la position de la pièce dans le tableau si une telle pièce existe et -1 sinon

t_lst	*checkTableau(int ligne, int colonne, t_lst **in_game)
{
		int				*pos;
		t_lst			*voyager;
		
		voyager = *in_game;
		while (voyager != NULL)
		{
				pos = (voyager->piece)->get_position();
				if (pos[0] == ligne && pos[1] == colonne)
						return (voyager);
				voyager = voyager->next;
		}
		return (NULL);
}

//
// AUTRES METHODES
//

// Retire une piece située aux coordonnées en paramètre de la liste de pièces

void	BOARD::retirePiece(int ligne, int colonne)
{
		t_lst	*a_retirer;

		if ((a_retirer = checkTableau(ligne, colonne, this->get_listePieces())) != NULL)
		{
				delete(a_retirer->piece);
				a_retirer = a_retirer->next;
		}
}

int		BOARD::case_occupee(int l, int c, int color)
{
		t_lst	**listePieces;

		listePieces = this->get_listePieces();
		checkTableau(l, c, listePieces);
		if (((*listePieces)->piece)->get_color() == (-1) * color)
				return (1);
		return (0);
}

// Affiche le plateau avec les pieces présentes dessus
// - correspond à une case blanche et . à une case noire

void	affiche_ligne_bord(int taille, int flag)
{
		for (int i = 1; i <= taille; i++)
				cout << "____";
		if (flag)
				cout << "|" << endl;
		else
				cout << "_" << endl;
}

void	BOARD::affiche()
{
		t_lst	*to_display;

		affiche_ligne_bord(this->get_taille(), 0);
		for (int ligne = 1; ligne <= this->get_taille(); ligne++)
		{
				for (int colonne = 1; colonne <= this->get_taille(); colonne++)
				{
						cout << "| ";
						if ((to_display = checkTableau(ligne, colonne, this->get_listePieces())))
								cout << (to_display->piece)->display_type() << " ";
						else if (((ligne+colonne) % 2) == 0)
								cout << "- ";
						else
								cout << ". ";
				}
				cout << "|" << endl;

		}
		affiche_ligne_bord(this->get_taille(), 1);
}
