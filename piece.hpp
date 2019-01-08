#ifndef PIECE_H
# define PIECE_H

# include <string>
# include <vector>

class	TYPE;
class	BOARD;

class	PIECE
{
	private :
		TYPE							*type;
		int								*position;
		int								status;
		std::vector<std::vector<int>>	possible_moves;
	public :
		PIECE(TYPE *type, int *position);
		PIECE(TYPE *type, std::vector<int> position); 
		int								*get_position() const;
		int								get_status() const;
		int								get_color() const;
		TYPE							*get_type() const;
		std::string						color_code() const;
		std::string						display_piece() const;
		std::vector<std::vector<int>>	get_moves() const;
		void							display_moves(int i);
		void							set_legit(std::vector<std::vector<int>> list);
		int								is_legit(int *new_pos);
		void							set_position(int *position_new);
		void							set_status(int new_status);
		void							transform(int n);
		~PIECE();
};

void	Dame_pawn_move(BOARD *board, PIECE *piece);
void	Dame_queen_move(BOARD *board, PIECE *piece);

void	Dame_Angl_pawn_move(BOARD *board, PIECE *piece);
void	Dame_Angl_queen_move(BOARD *board, PIECE *piece);

void	Echec_pawn_move(BOARD *board, PIECE *piece);
void	Echec_queen_move(BOARD *board, PIECE *piece);
void	Echec_king_move(BOARD *board, PIECE *piece);
void	rook_move(BOARD *board, PIECE *piece);
void	bishop_move(BOARD *board, PIECE *piece);
void	knight_move(BOARD *board, PIECE *piece);


#endif
