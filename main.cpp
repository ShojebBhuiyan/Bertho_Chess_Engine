#include "definitions.hpp"

int main()
{
	
	init_engine();
	
	//U64 occupancy = 0ULL;

	//set_bit(occupancy, c5);
	//set_bit(occupancy, f2);
	//set_bit(occupancy, g7);
	//set_bit(occupancy, b2);
	//set_bit(occupancy, g5);
	//set_bit(occupancy, e2);
	//set_bit(occupancy, e7);
	
	//print_bitBoard(get_bishop_attacks(a1, occupancy));

	//print_bitBoard(generate_bishop_attacks(a1, occupancy));

	char fen[] = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/Pp2P3/2N2Q1p/1PPBBPpP/R3K2R b KQkq a3 0 1"; //Testing FEN


	

	parse_FEN(fen);

	print_board();

	//print_bitBoard(piece_boards[bK]);

	//print_bitBoard(pawn_attacks[Black][e6] & occupancies[White]);
	


	generate_moves();

	//print_attacks(White);

	//print_attacks(Black);

	
	
	return 0;
}