#include "definitions.hpp"

U64 pawn_attacks[2][64];
U64 knight_attacks[64];
U64 king_attacks[64];

const char* coordinates[]{
	"a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8",
	"a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7",
	"a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6",
	"a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5",
	"a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4",
	"a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3",
	"a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2",
	"a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1"
};

const int bishop_relevant_bits[64] =
{
	6, 5, 5, 5, 5, 5, 5, 6,
	5, 5, 5, 5, 5, 5, 5, 5,
	5, 5, 7, 7, 7, 7, 5, 5,
	5, 5, 7, 9, 9, 7, 5, 5,
	5, 5, 7, 9, 9, 7, 5, 5,
	5, 5, 7, 7, 7, 7, 5, 5,
	5, 5, 5, 5, 5, 5, 5, 5,
	6, 5, 5, 5, 5, 5, 5, 6
};

const int rook_relevant_bits[64] =
{
	12, 11, 11, 11, 11, 11, 11, 12,
	11, 10, 10, 10, 10, 10, 10, 11,
	11, 10, 10, 10, 10, 10, 10, 11,
	11, 10, 10, 10, 10, 10, 10, 11,
	11, 10, 10, 10, 10, 10, 10, 11,
	11, 10, 10, 10, 10, 10, 10, 11,
	11, 10, 10, 10, 10, 10, 10, 11,
	12, 11, 11, 11, 11, 11, 11, 12
};

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
	std::cout << "\nBitboard ID: " << bitboard << "\n";
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

U64 mask_king_attacks(int square)
{
	U64 attacks = 0ULL;
	U64 bitboard = 0ULL;

	set_bit(bitboard, square);

	if (bitboard >> 8) attacks |= (bitboard >> 8);
	if (bitboard << 8) attacks |= (bitboard << 8);
	if ((bitboard >> 1) & not_H_file) attacks |= (bitboard >> 1);
	if ((bitboard << 1) & not_A_file) attacks |= (bitboard << 1);
	if ((bitboard >> 9) & not_H_file) attacks |= (bitboard >> 9);
	if ((bitboard << 9) & not_A_file) attacks |= (bitboard << 9);
	if ((bitboard >> 7) & not_A_file) attacks |= (bitboard >> 7);
	if ((bitboard << 7) & not_H_file) attacks |= (bitboard << 7);

	return attacks;
}

U64 mask_bishop_occupancies(int square)
{
	U64 attacks = 0ULL;
	int rank, file;
	int t_rank = square / 8;
	int t_file = square % 8;

	for (rank = t_rank + 1, file = t_file + 1; rank <= 6 && file <= 6; rank++, file++)
		attacks |= (1ULL << (rank * 8 + file));
	for (rank = t_rank - 1, file = t_file - 1; rank >= 1 && file >= 1; rank--, file--)
		attacks |= (1ULL << (rank * 8 + file));
	for (rank = t_rank + 1, file = t_file - 1; rank <= 6 && file >= 1; rank++, file--)
		attacks |= (1ULL << (rank * 8 + file));
	for (rank = t_rank - 1, file = t_file + 1; rank >= 1 && file <= 6; rank--, file++)
		attacks |= (1ULL << (rank * 8 + file));

	return attacks;
}

U64 mask_rook_occupancies(int square)
{
	U64 attacks = 0ULL;
	int rank, file;
	int t_rank = square / 8;
	int t_file = square % 8;

	for (rank = t_rank + 1; rank <= 6; rank++)
		attacks |= (1ULL << (rank * 8 + t_file));
	for (rank = t_rank - 1; rank >= 1; rank--)
		attacks |= (1ULL << (rank * 8 + t_file));
	for (file = t_file + 1; file <= 6; file++)
		attacks |= (1ULL << (t_rank * 8 + file));
	for (file = t_file - 1; file >= 1; file--)
		attacks |= (1ULL << (t_rank * 8 + file));

	return attacks;
}

U64 generate_bishop_attacks(int square, U64 block)
{
	U64 attacks = 0ULL;
	int rank, file;
	int t_rank = square / 8;
	int t_file = square % 8;

	for (rank = t_rank + 1, file = t_file + 1; rank <= 7; rank++, file++)
	{
		attacks |= (1ULL << (rank * 8 + file));

		if ((1ULL << (rank * 8 + file)) & block)
			break;
	}
	for (rank = t_rank - 1, file = t_file - 1; rank >= 0; rank--, file--)
	{
		attacks |= (1ULL << (rank * 8 + file));

		if ((1ULL << (rank * 8 + file)) & block)
			break;
	}
	for (rank = t_rank + 1, file = t_file - 1; rank <= 7 && file >= 0; rank++, file--)
	{
		attacks |= (1ULL << (rank * 8 + file));

		if ((1ULL << (rank * 8 + file)) & block)
			break;
	}
	for (rank = t_rank - 1, file = t_file + 1; rank >= 0 && file <= 7; rank--, file++)
	{
		attacks |= (1ULL << (rank * 8 + file));

		if ((1ULL << (rank * 8 + file)) & block)
			break;
	}

	return attacks;
}

U64 generate_rook_attacks(int square, U64 block)
{
	U64 attacks = 0ULL;
	int rank, file;
	int t_rank = square / 8;
	int t_file = square % 8;

	for (rank = t_rank + 1; rank <= 7; rank++)
	{
		attacks |= (1ULL << (rank * 8 + t_file));

		if ((1ULL << (rank * 8 + t_file)) & block)
			break;
	}
	for (rank = t_rank - 1; rank >= 0; rank--)
	{
		attacks |= (1ULL << (rank * 8 + t_file));

		if ((1ULL << (rank * 8 + t_file)) & block)
			break;
	}
	for (file = t_file + 1; file <= 7; file++)
	{
		attacks |= (1ULL << (t_rank * 8 + file));

		if ((1ULL << (t_rank * 8 + file)) & block)
			break;
	}
	for (file = t_file - 1; file >= 0; file--)
	{
		attacks |= (1ULL << (t_rank * 8 + file));
		
		if ((1ULL << (t_rank * 8 + file)) & block)
			break;
	}

	return attacks;
}

int count_bits(U64 board)
{
	int count = 0;
	while (board)
	{
		count++;
		board &= board - 1;
	}
	
	return count;
}

int get_LS1B_index(U64 board)
{
	if (board)
	{
		return count_bits((board & -board) - 1);
	}
	else
		return -1;
}

U64 generate_occupancy(int index, int num_bits, U64 attack)
{
	U64 occupancy = 0ULL;

	for (int count = 0; count < num_bits; count++)
	{
		int square = get_LS1B_index(attack);
		pop_bit(attack, square);

		if (index & (1 << count))
			occupancy |= (1ULL << square);
	}
	
	return occupancy;
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

		//King Attack Tables

		king_attacks[square] = mask_king_attacks(square);
	}
}

