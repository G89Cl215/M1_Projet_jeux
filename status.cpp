#include "status.hpp"

std::ostream &operator <<(std::ostream &out , STATUS &d)
{
	switch (d)
	{
			case (STATUS::white_turn) :
				out << " C'est a Blanc de jouer ";
				break ;
			case (STATUS::black_turn) :
				out << " C'est a Noir de jouer ";
				break ;
			case (STATUS::white_win) :
				out << " Blanc remporte la partie ";
				break ;
			case (STATUS::black_win) :
				out << " Noir remporte la partie "; 
				break ;
			case (STATUS::draw) :
				out << " La partie se solde par un status-quo ";
				break ;
	}
	return (out);
}
