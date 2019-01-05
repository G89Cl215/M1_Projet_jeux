#ifndef G_SETTER_H
# define G_SETTER_H

constexpr int NB_GAME = 2; //definit le nombre possible jeux traites par notre constructeur de partie

class			MAILLON;

MAILLON			**Dame_setup(void);
MAILLON			**Echec_setup(void);
MAILLON			**Stratego_setup(void);

typedef struct	s_Variante
{
	std::string	jeu;
	MAILLON		**(*game_setup)(void);
//	int			(*end_game)();
	int			board_size;
}				t_V;

extern t_V		g_setter[];

#endif
