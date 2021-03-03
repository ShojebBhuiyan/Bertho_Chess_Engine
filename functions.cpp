#include "definitions.hpp"

void print_bitBoard(U64 bitboard)
{
	for (int rank = 0; rank < 8; rank++)
	{
		for (int file = 0; file < 8; file++)
		{
			int square = rank * 8 + file;

			if (!file)
				std::cout << " " << 8 - rank << "  ";

			std::cout << (get_bit(bitboard, square) ? 1 : 0) << " ";
		}
		std::cout << "\n";
	}

	std::cout << "\n    A B C D E F G H\n";
	//std::cout << "\nBitboard: " << bitboard;
}