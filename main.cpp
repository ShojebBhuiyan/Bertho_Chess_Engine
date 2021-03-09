#include "definitions.hpp"

int main()
{
	//init_pieces();

	///*print_bitBoard(piece_boards[bP] | piece_boards[wP] | piece_boards[wN] | piece_boards[bN] | piece_boards[wB] | piece_boards[bB] | piece_boards[wR] | piece_boards[bR] | piece_boards[wQ] | piece_boards[bQ]
	//	| piece_boards[wK] | piece_boards[bK]);*/

	//print_board();

	//init_engine();
	
	//map_pieces();
	//init_pieces();
	
	char fen[] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

	parse_FEN(fen);

	print_board();

	return 0;
}