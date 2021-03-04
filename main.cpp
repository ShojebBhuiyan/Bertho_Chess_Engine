#include "definitions.hpp"

int main()
{	
	/*init_attack_tables();
	
	for (int square = 0; square < 64; square++)
	{
		print_bitBoard(pawn_attacks[White][square]);
		print_bitBoard(pawn_attacks[Black][square]);
		print_bitBoard(knight_attacks[square]);
		print_bitBoard(king_attacks[square]);
		print_bitBoard(mask_bishop_occupancies(square));
		print_bitBoard(mask_rook_occupancies(square));
	}
	
	U64 block = 0ULL;

	set_bit(block, b6);
	set_bit(block, g7);
	set_bit(block, e2);
	set_bit(block, b2);
	
	std::cout << coordinates[get_LS1B_index(block)];

	print_bitBoard(generate_rook_attacks(c2, block));
	std::cout << count_bits(block);

	U64 attack_mask = mask_rook_occupancies(a1);

	U64 occupancy = generate_occupancy(0, count_bits(attack_mask), attack_mask);

	print_bitBoard(occupancy);

	for (int rank = 0; rank < 8; rank++)
	{
		for (int file = 0; file < 8; file++)
		{
			int square = rank * 8 + file;

			std::cout << count_bits(mask_rook_occupancies(square)) << ", ";
			std::cout << count_bits(mask_rook_occupancies(square)) << ", ";
		}
		std::cout << "\n";
	}*/
	/*
	std::cout << generate_random_u64() << "\n";
	std::cout << generate_random_u64() << "\n";
	std::cout << generate_random_u64() << "\n";
	std::cout << generate_random_u64() << "\n";
	std::cout << generate_random_u64() << "\n";*/
	
	/*print_bitBoard(generate_random_u64());
	print_bitBoard(generate_random_u64());
	print_bitBoard(generate_random_u64());
	print_bitBoard(generate_random_u64());*/

	//init_magic_numbers();


	return 0;
}