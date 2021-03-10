#include "definitions.hpp"

U64 pawn_attacks[2][64];
U64 knight_attacks[64];
U64 king_attacks[64];

U64 piece_boards[12];
U64 occupancies[3];

char piece_initials[] = "PNBRQKpnbrqk";

//std::map <char, int> piece_initials;
//
//void map_pieces()
//{
//	piece_initials.insert({ 'P', wP });
//	piece_initials.insert({ 'N', wN });
//	piece_initials.insert({ 'B', wB });
//	piece_initials.insert({ 'R', wR });
//	piece_initials.insert({ 'Q', wQ });
//	piece_initials.insert({ 'K', wK });
//	piece_initials.insert({ 'p', bP });
//	piece_initials.insert({ 'n', bN });
//	piece_initials.insert({ 'b', bB });
//	piece_initials.insert({ 'r', bR });
//	piece_initials.insert({ 'q', bQ });
//	piece_initials.insert({ 'k', bK });
//}

bool side = White;

int enpassant = nil;

int castle;

unsigned int state = 1804289383; //Placeholder pseudo random number generated beforehand using rand()

//struct BlackMagic
//{
//	U64* ptr;
//	U64 notmask;
//	U64 blackmagic;
//};
//
//BlackMagic mask_bishop[64];
//BlackMagic mask_rook[64];
//
//U64 slider_attack[88316];

U64 bishop_masks[64];
U64 rook_masks[64];

U64 bishop_attacks[64][512];
U64 rook_attacks[64][4096];

const char* coordinates[]
{
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

const U64 bishop_magics[64] =
{
	0x40040844404084ULL,
	0x2004208a004208ULL,
	0x10190041080202ULL,
	0x108060845042010ULL,
	0x581104180800210ULL,
	0x2112080446200010ULL,
	0x1080820820060210ULL,
	0x3c0808410220200ULL,
	0x4050404440404ULL,
	0x21001420088ULL,
	0x24d0080801082102ULL,
	0x1020a0a020400ULL,
	0x40308200402ULL,
	0x4011002100800ULL,
	0x401484104104005ULL,
	0x801010402020200ULL,
	0x400210c3880100ULL,
	0x404022024108200ULL,
	0x810018200204102ULL,
	0x4002801a02003ULL,
	0x85040820080400ULL,
	0x810102c808880400ULL,
	0xe900410884800ULL,
	0x8002020480840102ULL,
	0x220200865090201ULL,
	0x2010100a02021202ULL,
	0x152048408022401ULL,
	0x20080002081110ULL,
	0x4001001021004000ULL,
	0x800040400a011002ULL,
	0xe4004081011002ULL,
	0x1c004001012080ULL,
	0x8004200962a00220ULL,
	0x8422100208500202ULL,
	0x2000402200300c08ULL,
	0x8646020080080080ULL,
	0x80020a0200100808ULL,
	0x2010004880111000ULL,
	0x623000a080011400ULL,
	0x42008c0340209202ULL,
	0x209188240001000ULL,
	0x400408a884001800ULL,
	0x110400a6080400ULL,
	0x1840060a44020800ULL,
	0x90080104000041ULL,
	0x201011000808101ULL,
	0x1a2208080504f080ULL,
	0x8012020600211212ULL,
	0x500861011240000ULL,
	0x180806108200800ULL,
	0x4000020e01040044ULL,
	0x300000261044000aULL,
	0x802241102020002ULL,
	0x20906061210001ULL,
	0x5a84841004010310ULL,
	0x4010801011c04ULL,
	0xa010109502200ULL,
	0x4a02012000ULL,
	0x500201010098b028ULL,
	0x8040002811040900ULL,
	0x28000010020204ULL,
	0x6000020202d0240ULL,
	0x8918844842082200ULL,
	0x4010011029020020ULL
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

const U64 rook_magics[64] =
{
	0x8a80104000800020ULL,
	0x140002000100040ULL,
	0x2801880a0017001ULL,
	0x100081001000420ULL,
	0x200020010080420ULL,
	0x3001c0002010008ULL,
	0x8480008002000100ULL,
	0x2080088004402900ULL,
	0x800098204000ULL,
	0x2024401000200040ULL,
	0x100802000801000ULL,
	0x120800800801000ULL,
	0x208808088000400ULL,
	0x2802200800400ULL,
	0x2200800100020080ULL,
	0x801000060821100ULL,
	0x80044006422000ULL,
	0x100808020004000ULL,
	0x12108a0010204200ULL,
	0x140848010000802ULL,
	0x481828014002800ULL,
	0x8094004002004100ULL,
	0x4010040010010802ULL,
	0x20008806104ULL,
	0x100400080208000ULL,
	0x2040002120081000ULL,
	0x21200680100081ULL,
	0x20100080080080ULL,
	0x2000a00200410ULL,
	0x20080800400ULL,
	0x80088400100102ULL,
	0x80004600042881ULL,
	0x4040008040800020ULL,
	0x440003000200801ULL,
	0x4200011004500ULL,
	0x188020010100100ULL,
	0x14800401802800ULL,
	0x2080040080800200ULL,
	0x124080204001001ULL,
	0x200046502000484ULL,
	0x480400080088020ULL,
	0x1000422010034000ULL,
	0x30200100110040ULL,
	0x100021010009ULL,
	0x2002080100110004ULL,
	0x202008004008002ULL,
	0x20020004010100ULL,
	0x2048440040820001ULL,
	0x101002200408200ULL,
	0x40802000401080ULL,
	0x4008142004410100ULL,
	0x2060820c0120200ULL,
	0x1001004080100ULL,
	0x20c020080040080ULL,
	0x2935610830022400ULL,
	0x44440041009200ULL,
	0x280001040802101ULL,
	0x2100190040002085ULL,
	0x80c0084100102001ULL,
	0x4024081001000421ULL,
	0x20030a0244872ULL,
	0x12001008414402ULL,
	0x2006104900a0804ULL,
	0x1004081002402ULL
};

// Print functions

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

void print_board()
{
	std::cout << "\n";

	for (int rank = 0; rank < 8; rank++)
	{
		for (int file = 0; file < 8; file++)
		{
			int square = rank * 8 + file;

			if (!file)
				std::cout << " " << 8 - rank << "  ";

			int piece = -1;

			for (int bit = wP; bit <= bK; bit++)
			{
				if (get_bit(piece_boards[bit], square))
					piece = bit;
			}


			//std::cout << " " << (piece == -1) ? '.' : (char) piece_initials[piece];
			printf(" %c", (piece == -1) ? '.' : piece_initials[piece]);

		}

		std::cout << "\n";
	}

	std::cout << "\n     A B C D E F G H\n";

	printf("\n  Side: %s", (!side) ? "White to move\n" : "Black to move\n");

	//std::cout << "\nSide: " << (!side) ? "White to move\n" : "Black to move\n";

	printf("\n  Enpassant: %s", (enpassant != nil) ? coordinates[enpassant] : "Not eligible\n");

	//std::cout << "\nEnpassant: " << (enpassant != nil) ? coordinates[enpassant] : "Not eligible";

	printf("\n\n  Castling:  %c%c%c%c\n\n", (castle & wK) ? 'K' : '-',
		(castle & wQ) ? 'Q' : '-',
		(castle & bK) ? 'k' : '-',
		(castle & bQ) ? 'q' : '-');
}

void print_attacks(int side)
{
	std::cout << "\n";

	for (int rank = 0; rank < 8; rank++)
	{
		for (int file = 0; file < 8; file++)
		{
			int square = rank * 8 + file;

			if (!file)
				std::cout << " " << 8 - rank << "  ";

			printf(" %d", is_attacked(side, square) ? 1 : 0);
		}

		std::cout << "\n";
	}

	std::cout << "\n     A B C D E F G H\n";
}


// Attack functions

bool is_attacked(int side, int square)
{
	// By White Pawns
	
	if (side == White && (pawn_attacks[Black][square] & piece_boards[wP]))
		return true;

	// By Black Pawns
	
	if (side == Black && (pawn_attacks[White][square] & piece_boards[bP]))
		return true;

	// By Knights

	if (knight_attacks[square] & ((side == White) ? piece_boards[wN] : piece_boards[bN]))
		return true;

	// By Bishops
	
	if (get_bishop_attacks(square, occupancies[Both]) & ((side == White) ? piece_boards[wB] : piece_boards[bB]))
		return true;

	// By Rooks

	if (get_rook_attacks(square, occupancies[Both]) & ((side == White) ? piece_boards[wR] : piece_boards[bR]))
		return true;

	// By Queens

	if (get_queen_attacks(square, occupancies[Both]) & ((side == White) ? piece_boards[wQ] : piece_boards[bQ]))
		return true;
	
	// By Kings

	if (king_attacks[square] & ((side == White) ? piece_boards[wK] : piece_boards[bK]))
		return true;
	
	return false;
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

U64 get_bishop_attacks(int square, U64 occupancy)
{
	//Reference: https://www.chessprogramming.org/Magic_Bitboards#Plain

	occupancy &= bishop_masks[square];
	occupancy *= bishop_magics[square];
	occupancy >>= (U64)(64 - bishop_relevant_bits[square]);

	return bishop_attacks[square][occupancy];
}

U64 get_rook_attacks(int square, U64 occupancy)
{
	//Reference: https://www.chessprogramming.org/Magic_Bitboards#Plain
	occupancy &= rook_masks[square];
	occupancy *= rook_magics[square];
	occupancy >>= (U64)(64 - rook_relevant_bits[square]);

	return rook_attacks[square][occupancy];
}

U64 get_queen_attacks(int square, U64 occupancy)
{
	U64 result = 0ULL;
	U64 bishop_occupancy = occupancy;
	U64 rook_occupancy = occupancy;

	bishop_occupancy &= bishop_masks[square];
	bishop_occupancy *= bishop_magics[square];
	bishop_occupancy >>= (64 - bishop_relevant_bits[square]);

	rook_occupancy &= rook_masks[square];
	rook_occupancy *= rook_magics[square];
	rook_occupancy >>= (64 - rook_relevant_bits[square]);

	result = bishop_attacks[square][bishop_occupancy] | rook_attacks[square][rook_occupancy];

	return result;
}

// Bit manipulation functions

static inline int count_bits(U64 board)
{
	int count = 0;
	while (board)
	{
		count++;
		board &= board - 1;
	}
	
	return count;
}

static inline int get_LS1B_index(U64 board)
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

unsigned int generate_random_u32()
{
	unsigned int number = state; //Random placeholder value

	//XORshift32 algorithm

	number ^= number << 13;
	number ^= number >> 17;
	number ^= number << 5; 
	
	state = number;

	return number;
}

U64 generate_random_u64()
{
	U64 a, b, c, d; //Randoms

	a = (U64)(generate_random_u32()) & 0xFFFF; //Slicing 16 bits from the MS1B
	b = (U64)(generate_random_u32()) & 0xFFFF;
	c = (U64)(generate_random_u32()) & 0xFFFF;
	d = (U64)(generate_random_u32()) & 0xFFFF;

	return a | (b << 16) | (c << 32) | (d << 48);
}

// Magic number functions

U64 generate_candidate()
{
	return generate_random_u64() & generate_random_u64() & generate_random_u64();
}

U64 generate_magic_number(int square, int relevant_bits, bool bishop)
{
	//Reference: https://www.chessprogramming.org/Looking_for_Magics

	U64 occupancies[4096]; //max limit of rook and bishop occupancies
	U64 attacks[4096];
	U64 used_attacks[4096];

	U64 attack_mask = bishop ? mask_bishop_occupancies(square) : mask_rook_occupancies(square);

	int occupancy_indices = 1 << relevant_bits;

	for (int index = 0; index < occupancy_indices; index++)
	{
		occupancies[index] = generate_occupancy(index, relevant_bits, attack_mask);
		attacks[index] = bishop ? generate_bishop_attacks(square, occupancies[index]) :
			generate_rook_attacks(square, occupancies[index]);
	}

	//std::cout << "Passed checkpoint 1\n";
	//int cont_count = 0;

	for (int count = 0; count < 10000000; count++)
	{
		U64 magic_number = generate_candidate();
		//print_bitBoard(magic_number);
		//getchar();
		//int cont_count = 0;
		int bit_count = count_bits((attack_mask * magic_number) & 0xFF00000000000000);
		//print_bitBoard((U64)bit_count);
		//print_bitBoard(0xFF00000000000000);
		//std::cout << bit_count << "\n";
		//getchar();
		if (bit_count < 6)
		{
			//std::cout << "Continue\n";
			//cont_count++;
			continue;
		}
			

		memset(used_attacks, 0ULL, sizeof(used_attacks));

		bool fail = false;

		//std::cout << "Passed checkpoint 2\nContinued: " << cont_count << " times\n";

		for (int index = 0; !fail && index < occupancy_indices; index++)
		{
			//3rd key step listed here : https://www.chessprogramming.org/Magic_Bitboards#How_it_works

			int magic_index = (int)((occupancies[index] * magic_number) >> (64 - relevant_bits));
			//std::cout << "Magic Index: " << magic_index << "\n";
			//getchar();
			//If magic number works

			if (used_attacks[magic_index] == 0ULL)
				used_attacks[magic_index] = attacks[index];

			//If magic number fails

			else if (used_attacks[magic_index] != attacks[index])
				fail = true;

		}
		//std::cout << "Reached checkpoint 3\n";
		if (!fail)
		{
			//std::cout << "Found magic number\n";

			return magic_number;
		}
	}

	//If magic number fails

	std::cout << "Magic number failed\n";
	return 0ULL;
}

// Initializers

void init_magic_numbers()
{
	for (int square = 0; square < 64; square++)
	{
		printf("0x%llxULL,\n", generate_magic_number(square, rook_relevant_bits[square], Rook));
	}

	printf("\n\n\n");
	for (int square = 0; square < 64; square++)
		printf("0x%llxULL,\n", generate_magic_number(square, bishop_relevant_bits[square], Bishop));
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

void init_sliders(bool bishop)
{
	for (int square = 0; square < 64; square++)
	{
		bishop_masks[square] = mask_bishop_occupancies(square);
		rook_masks[square] = mask_rook_occupancies(square);

		U64 attack_mask = bishop ? bishop_masks[square] : rook_masks[square];

		int relevant_bits = count_bits(attack_mask); 

		int occupancy_indices = (1 << relevant_bits);

		for (int index = 0; index < occupancy_indices; index++)
		{
			if (bishop)
			{ 
				U64 occupancy = generate_occupancy(index, relevant_bits, attack_mask);

				int magic_index = (int)((occupancy * bishop_magics[square]) >> (64 - bishop_relevant_bits[square]));

				bishop_attacks[square][magic_index] = generate_bishop_attacks(square, occupancy);
			}

			else //Rook
			{
				U64 occupancy = generate_occupancy(index, relevant_bits, attack_mask);

				int magic_index = (int)((occupancy * rook_magics[square]) >> (64 - rook_relevant_bits[square]));

				rook_attacks[square][magic_index] = generate_rook_attacks(square, occupancy);
			}
		}
	}
}



void init_pieces()
{
	//White Pawns
	
	for (int index = a2; index <= h2; index++)
		set_bit(piece_boards[wP], index);
	
	//Black Pawns

	for (int index = a7; index <= h7; index++)
		set_bit(piece_boards[bP], index);

	//White Knights
		
	set_bit(piece_boards[wN], b1);
	set_bit(piece_boards[wN], g1);

	//Black Knights

	set_bit(piece_boards[bN], b8);
	set_bit(piece_boards[bN], g8);

	//White Bishops

	set_bit(piece_boards[wB], c1);
	set_bit(piece_boards[wB], f1);

	//Black Bishops

	set_bit(piece_boards[bB], c8);
	set_bit(piece_boards[bB], f8);

	//White Rooks

	set_bit(piece_boards[wR], a1);
	set_bit(piece_boards[wR], h1);

	//Black Rooks

	set_bit(piece_boards[bR], a8);
	set_bit(piece_boards[bR], h8);

	//White Queen

	set_bit(piece_boards[wQ], d1);

	//Black Queen 

	set_bit(piece_boards[bQ], d8);

	//White King

	set_bit(piece_boards[wK], e1);

	//Black King 

	set_bit(piece_boards[bK], e8);
}

void init_engine()
{
	init_attack_tables();
	//init_magic_numbers();
	init_sliders(Bishop);
	init_sliders(Rook);
	//init_pieces();
	//print_board();
}

// Parsers

void parse_FEN(char* fen)
{
	memset(piece_boards, 0ULL, sizeof(piece_boards));

	memset(occupancies, 0ULL, sizeof(occupancies));

	side = White;
	enpassant = nil;
	castle = 0;

	for (int rank = 0; rank < 8; rank++)
	{
		for (int file = 0; file < 8; file++)
		{
			int square = rank * 8 + file;

			if ((*fen >= 'A' && *fen <= 'z') || (*fen >= 'a' && 'fen' <= 'z'))
			{
			
				int piece;

				switch (*fen)
				{
					case 'P': piece = 0; break;
					case 'N': piece = 1; break;
					case 'B': piece = 2; break;
					case 'R': piece = 3; break;
					case 'Q': piece = 4; break;
					case 'K': piece = 5; break;
					case 'p': piece = 6; break;
					case 'n': piece = 7; break;
					case 'b': piece = 8; break;
					case 'r': piece = 9; break;
					case 'q': piece = 10; break;
					case 'k': piece = 11; break;
				}

				set_bit(piece_boards[piece], square);
				
				fen++;
			}

			if (*fen >= '0' && *fen <= '9')
			{
				//std::cout << "FEN: " << *fen << "\n";

				int move = (*fen++) - '0';

				int piece = -1;

				for (int bit = wP; bit <= bK; bit++)
				{
					if (get_bit(piece_boards[bit], square))
						piece = bit;
				}

				if (piece == -1)
					file--;

				file += move;
			}
		
			if (*fen == '/')
				fen++;
		}
	}

	fen++; //To go to side to move

	((*fen++) == 'w') ? (side = White) : (side = Black);

	fen += 2; //To go to castling rights

	while (*fen != ' ')
	{
		switch (*fen)
		{
			case 'K': castle |= wK; break;
			case 'Q': castle |= wQ; break;
			case 'k': castle |= bK; break;
			case 'q': castle |= bQ; break;
			case '-': break;
		}
		
		fen++;
	}

	fen++; //To go to enpassant eligibility
	
	if (*fen != '-')
	{
		int file = fen[0] - 'a';
		int rank = 8 - (fen[1] - '0');

		enpassant = rank * 8 + file;
	}
	else
		enpassant = nil;

	//Update White occupancies

	for (int piece = wP; piece <= wK; piece++)
		occupancies[White] |= piece_boards[piece];
		
	//Update Black occupancies

	for (int piece = bP; piece <= bK; piece++)
		occupancies[Black] |= piece_boards[piece];
		
	//Update all occupancies

	occupancies[Both] |= occupancies[White];
	occupancies[Both] |= occupancies[Black];
}
