#include "status.hpp"

std::ostream &operator <<(std::ostream &out , STATUS &d)
{
	switch (d)
	{
			case (STATUS::white_turn) :
				out << " C'est a Blanc de jouer ";
			case (STATUS::black_turn) :
				out << " C'est a Noir de jouer ";
			case (STATUS::white_win) :
				out << " Blanc remporte la partie ";
			case (STATUS::black_win) :
				out << " Noir remporte la partie "; 
			case (STATUS::draw) :
				out << " La partie se solde par un status-quo ";
	}
	return (out);
}
