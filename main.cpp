#include "definitions.hpp"

int main()
{
	
	init_engine();
	
	char fen[] = "rnbqkb1r/pp1p1pPp/8/2p1pP2/1P1P4/3P3P/P1P1P3/RNBQKBNR w KQkq e6 0 1"; //Testing FEN

	parse_FEN(fen);

	print_board();

	print_attacks(White);

	print_attacks(Black);

	return 0;
}