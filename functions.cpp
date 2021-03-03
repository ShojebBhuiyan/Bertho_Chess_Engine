#include "definitions.hpp"

U64 pawn_attacks[2][64];
U64 knight_attacks[64];

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
	std::cout << "\nBitboard ID: " << bitboard;
}

U64 mask_pawn_attacks(int side, int square)
{
	U64 attacks = 0ULL;
	U64 bitboard = 0ULL;

	set_bit(bitboard, square);

	//White Pawns

	if (!side)
	{
		if ((bitboard >> 7) & not_A_file) attacks |= (bitboard >> 7);
		if ((bitboard >> 9) & not_H_file) attacks |= (bitboard >> 9);
	}
	//Black Pawns
	else
	{
		if ((bitboard << 7) & not_H_file) attacks |= (bitboard << 7);
		if ((bitboard << 9) & not_A_file) attacks |= (bitboard << 9);
	}
	return attacks;
}

U64 mask_knight_attacks(int square)
{
	U64 attacks = 0ULL;
	U64 bitboard = 0ULL;

	set_bit(bitboard, square);

	if ((bitboard >> 17) & not_H_file) attacks |= (bitboard >> 17);
	if ((bitboard << 17) & not_A_file) attacks |= (bitboard << 17);
	if ((bitboard >> 15) & not_A_file)attacks |= (bitboard >> 15);
	if ((bitboard << 15) & not_H_file) attacks |= (bitboard << 15);
	if ((bitboard >> 10) & not_HG_file) attacks |= (bitboard >> 10);
	if ((bitboard << 10) & not_AB_file) attacks |= (bitboard << 10);
	if ((bitboard >> 6) & not_AB_file) attacks |= (bitboard >> 6);
	if ((bitboard << 6) & not_HG_file) attacks |= (bitboard << 6);

	return attacks;
}

void init_attack_tables()
{
	for (int square = 0; square < 64; square++)
	{
		//Pawn Attack Tables
		
		pawn_attacks[White][square] = mask_pawn_attacks(White, square);
		pawn_attacks[Black][square] = mask_pawn_attacks(Black, square);

		//Knight Attack Tables

		knight_attacks[square] = mask_knight_attacks(square);
	}
}