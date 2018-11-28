#include "piece.hpp"

PIECE::PIECE(TYPE type, int *position, int couleur)
{
	this->type = type;
	this->position = (int*)malloc(sizeof(*position) * 2);
	this->position[1] = position[1];
	this->position[0] = position[0];
	this->couleur = couleur;
}

int		*PIECE::get_position(void)
{
		return (this->position);
}

int		PIECE::move(int *position_new)
{
	int	j;

	if (j = move_legit(this, position_new))
			this->position = position_new;
	return (j);
}
/*
int		move_legit(PIECE *piece, int *position_new)
{
	int	i;

	i = 0;

	
	return (0);
}*/
