#pragma once
#pragma warning (disable : 4146) //To bypass a compiler error flag for the get_LS1B_index function
//Headers

#include <iostream>

//Definitions

#define U64 unsigned long long
#define not_A_file 18374403900871474942ULL
#define not_H_file 9187201950435737471ULL
#define not_HG_file 4557430888798830399ULL
#define not_AB_file 18229723555195321596ULL

//Macros

#define get_bit(bitboard, square) (bitboard & (1ULL << square))
#define set_bit(bitboard, square) (bitboard |= (1ULL << square))
#define pop_bit(bitboard, square) (get_bit(bitboard, square) ? bitboard ^= (1ULL << square) : 0)

//Globals

extern U64 pawn_attacks[2][64];
extern U64 knight_attacks[64];
extern U64 king_attacks[64];
extern const char* coordinates[];
extern const int bishop_relevant_bits[64];
extern const int rook_relevant_bits[64];
//Enums

enum {
	a8, b8, c8, d8, e8, f8, g8, h8,
	a7, b7, c7, d7, e7, f7, g7, h7,
	a6, b6, c6, d6, e6, f6, g6, h6,
	a5, b5, c5, d5, e5, f5, g5, h5,
	a4, b4, c4, d4, e4, f4, g4, h4,
	a3, b3, c3, d3, e3, f3, g3, h3,
	a2, b2, c2, d2, e2, f2, g2, h2,
	a1, b1, c1, d1, e1, f1, g1, h1
};

enum { White, Black };

//Function prototypes

void print_bitBoard(U64 bitboard);
U64 mask_pawn_attacks(int side, int square);
U64 mask_knight_attacks(int square);
U64 mask_king_attacks(int square);
U64 mask_bishop_occupancies(int square);
U64 mask_rook_occupancies(int square);
U64 generate_bishop_attacks(int square, U64 block);
U64 generate_rook_attacks(int square, U64 block);
int count_bits(U64 Board);
int get_LS1B_index(U64 board);
U64 generate_occupancy(int index, int num_bits, U64 attack);
void init_attack_tables();
