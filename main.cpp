#include "definitions.hpp"

int main()
{
	//print_bitBoard(mask_pawn_attacks(Black, c4));	
	//U64 not_AB_file = 0ULL;
	//for (int rank = 0; rank < 8; rank++)
	//{
		//for (int file = 0; file < 8; file++)
		//{
		//	int square = rank * 8 + file;
			//if (file > 1 )
				//set_bit(not_AB_file, square);
		//}
	//}
	//print_bitBoard(not_AB_file);
	init_pawn_table();
	for (int square = 0; square < 64; square++)
		print_bitBoard(pawn_attacks[White][square]);
	return 0;
}