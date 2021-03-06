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

#define get_bit(bitboard, square) ((bitboard) & (1ULL << square))
#define set_bit(bitboard, square) ((bitboard) |= (1ULL << square))
#define pop_bit(bitboard, square) ((bitboard) &=  ~(1ULL << square))

//Globals

//extern U64 pawn_attacks[2][64];
//extern U64 knight_attacks[64];
//extern U64 king_attacks[64];
//extern const char* coordinates[];
//extern const int bishop_relevant_bits[64];
//extern const int rook_relevant_bits[64];
//extern unsigned int state;
//extern const U64 bishop_magics[64];
//extern const U64 rook_magics[64];
//extern U64 bishop_masks[64];
//extern U64 rook_masks[64];
//extern U64 bishop_attacks[64][512];
//extern U64 rook_attacks[64][4096];
//extern U64 piece_boards[12];

//Enums

enum 
{
	a8, b8, c8, d8, e8, f8, g8, h8,
	a7, b7, c7, d7, e7, f7, g7, h7,
	a6, b6, c6, d6, e6, f6, g6, h6,
	a5, b5, c5, d5, e5, f5, g5, h5,
	a4, b4, c4, d4, e4, f4, g4, h4,
	a3, b3, c3, d3, e3, f3, g3, h3,
	a2, b2, c2, d2, e2, f2, g2, h2,
	a1, b1, c1, d1, e1, f1, g1, h1, nil
};

enum { White, Black, Both };

enum { Rook, Bishop }; 

enum { wKCast = 1, wQCast = 2, bKCast = 4, bQCast = 8 };

enum { wP, wN, wB, wR, wQ, wK, bP, bN, bB, bR, bQ, bK };

//Function prototypes

void print_bitBoard(U64 bitboard);
U64 mask_pawn_attacks(int side, int square);
U64 mask_knight_attacks(int square);
U64 mask_king_attacks(int square);
U64 mask_bishop_occupancies(int square);
U64 mask_rook_occupancies(int square);
U64 generate_bishop_attacks(int square, U64 block);
U64 generate_rook_attacks(int square, U64 block);
static inline int count_bits(U64 Board);
static inline int get_LS1B_index(U64 board);
U64 generate_occupancy(int index, int num_bits, U64 attack);
unsigned int generate_random_u32();
U64 generate_random_u64();
U64 generate_candidate();
U64 generate_magic_number(int square, int relevant_bits, bool bishop);
void init_attack_tables();
void init_magic_numbers();
void init_sliders(bool bishop);
U64 get_bishop_attacks(int square, U64 occupancy);
U64 get_rook_attacks(int square, U64 occupancy);
U64 get_queen_attacks(int square, U64 occupancy);
void init_engine();
void init_pieces();
void print_board();