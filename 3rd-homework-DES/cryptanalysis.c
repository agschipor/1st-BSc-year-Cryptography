#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char P[] = {16, 7, 20, 21,
			29, 12, 28, 17,
			1, 15, 23, 26,
			5, 18, 31, 10, 
			2, 8, 24, 14,
			32, 27, 3, 9,
			19, 13, 30, 6,
			22, 11, 4, 25};

unsigned char E[] = {32, 1, 2, 3, 4, 5, 
			4, 5, 6, 7, 8, 9, 
			8, 9, 10, 11, 12, 13, 
			12, 13, 14, 15, 16, 17, 
			16, 17, 18, 19, 20, 21, 
			20, 21, 22, 23, 24, 25, 
			24, 25, 26, 27, 28, 29, 
			28, 29, 30, 31, 32, 1};

unsigned char PC1[] = {57, 49, 41, 33, 25, 17, 9, 
			1, 58, 50, 42, 34, 26, 18, 
			10, 2, 59, 51, 43, 35, 27, 
			19, 11, 3, 60, 52, 44, 36, 
			63, 55, 47, 39, 31, 23, 15, 
			7, 62, 54, 46, 38, 30, 22, 
			14, 6, 61, 53, 45, 37, 29, 
			21, 13, 5, 28, 20, 12, 4};

unsigned char PC2[] = {14, 17, 11, 24, 1, 5, 
			3, 28, 15, 6, 21, 10, 
			23, 19, 12, 4, 26, 8, 
			16, 7, 27, 20, 13, 2, 
			41, 52, 31, 37, 47, 55, 
			30, 40, 51, 45, 33, 48, 
			44, 49, 39, 56, 34, 53, 
			46, 42, 50, 36, 29, 32};

unsigned char S[8][4][16] = {
						{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
						 0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
						 4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
						15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13},

						{15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
						 3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
						 0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
						13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9},

						{10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
						13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
						13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
						 1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12},

						 {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
						13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
						10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
						 3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14},

						{2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
						14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
						 4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
						11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3},

						{12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
						10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
						 9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
						 4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13},

						{4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
						13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
						 1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
						 6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12},

						{13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
						 1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
						 7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
						 2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}
					};

unsigned char P_1[32];
unsigned char PC2_1[56];
unsigned char PC1_1[64];

/*int ReadPairs(unsigned char LR0[3][8], unsigned char LR0S[3][8], unsigned char LR3[3][8], unsigned char LR3S[3][8])
{
	FILE *reader;
	int index, element;
	char character;

	reader = fopen("pairs.txt", "r");

	if(reader == NULL)
		return 0;

	for(index = 0; index < 8; index++)
		fscanf(reader, "%c", &LR0[0][index]);

	fscanf(reader, "%c", &character);

	for(index = 0; index < 8; index++)
		fscanf(reader, "%c", &LR0[1][index]);

	fscanf(reader, "%c", &character);

	for(index = 0; index < 8; index++)
		fscanf(reader, "%c", &LR0[2][index]);

	fscanf(reader, "%c", &character);

	for(index = 0; index < 8; index++)
		fscanf(reader, "%c", &LR0S[0][index]);

	fscanf(reader, "%c", &character);

	for(index = 0; index < 8; index++)
		fscanf(reader, "%c", &LR0S[1][index]);

	fscanf(reader, "%c", &character);

	for(index = 0; index < 8; index++)
		fscanf(reader, "%c", &LR0S[2][index]);

	fscanf(reader, "%c", &character);

	for(index = 0; index < 8; index++)
	{
		fscanf(reader, "%02X", &element);
		LR3[0][index] = element;
	}

	fscanf(reader, "%c", &character);

	for(index = 0; index < 8; index++)
	{
		fscanf(reader, "%02X", &element);
		LR3[1][index] = element;
	}

	fscanf(reader, "%c", &character);

	for(index = 0; index < 8; index++)
	{
		fscanf(reader, "%02X", &element);
		LR3[2][index] = element;
	}

	fscanf(reader, "%c", &character);

	for(index = 0; index < 8; index++)
	{
		fscanf(reader, "%02X", &element);
		LR3S[0][index] = element;
	}

	fscanf(reader, "%c", &character);

	for(index = 0; index < 8; index++)
	{
		fscanf(reader, "%02X", &element);
		LR3S[1][index] = element;
	}

	fscanf(reader, "%c", &character);

	for(index = 0; index < 8; index++)
	{
		fscanf(reader, "%02X", &element);
		LR3S[2][index] = element;
	}

	fclose(reader);

	return 1;
}*/

int ReadPairs(unsigned char LR0[3][8], unsigned char LR0S[3][8], unsigned char LR3[3][8], unsigned char LR3S[3][8])
{
	FILE *reader;
	int index, element;
	char character;

	reader = fopen("pairs.txt", "r");

	if(reader == NULL)
		return 0;

	for(index = 0; index < 8; index++)
	{	
		fscanf(reader, "%02X", &element);
		LR0[0][index] = element;
	}

	fscanf(reader, "%c", &character);

	for(index = 0; index < 8; index++)
	{	
		fscanf(reader, "%02X", &element);
		LR0[1][index] = element;
	}

	fscanf(reader, "%c", &character);

	for(index = 0; index < 8; index++)
	{	
		fscanf(reader, "%02X", &element);
		LR0[2][index] = element;
	}

	fscanf(reader, "%c", &character);

	for(index = 0; index < 8; index++)
	{	
		fscanf(reader, "%02X", &element);
		LR0S[0][index] = element;
	}	

	fscanf(reader, "%c", &character);

	for(index = 0; index < 8; index++)
	{	
		fscanf(reader, "%02X", &element);
		LR0S[1][index] = element;
	}

	fscanf(reader, "%c", &character);

	for(index = 0; index < 8; index++)
	{	
		fscanf(reader, "%02X", &element);
		LR0S[2][index] = element;
	}

	fscanf(reader, "%c", &character);

	for(index = 0; index < 8; index++)
	{
		fscanf(reader, "%02X", &element);
		LR3[0][index] = element;
	}

	fscanf(reader, "%c", &character);

	for(index = 0; index < 8; index++)
	{
		fscanf(reader, "%02X", &element);
		LR3[1][index] = element;
	}

	fscanf(reader, "%c", &character);

	for(index = 0; index < 8; index++)
	{
		fscanf(reader, "%02X", &element);
		LR3[2][index] = element;
	}

	fscanf(reader, "%c", &character);

	for(index = 0; index < 8; index++)
	{
		fscanf(reader, "%02X", &element);
		LR3S[0][index] = element;
	}

	fscanf(reader, "%c", &character);

	for(index = 0; index < 8; index++)
	{
		fscanf(reader, "%02X", &element);
		LR3S[1][index] = element;
	}

	fscanf(reader, "%c", &character);

	for(index = 0; index < 8; index++)
	{
		fscanf(reader, "%02X", &element);
		LR3S[2][index] = element;
	}

	fclose(reader);

	return 1;
}


unsigned char* MakePermutation(unsigned char* bitstring, char *PC, int length)
{
	int index, permuted_bitstring_length = length / 8, offset = permuted_bitstring_length - 1;
	unsigned char* permuted_bitstring;

	if((permuted_bitstring = (char*)calloc(permuted_bitstring_length, sizeof(char))) == NULL)
		return NULL;

	for(index = 0; index < permuted_bitstring_length; index++)
		permuted_bitstring[index] = 0;

	for(index = 0; index < length; index++)
		if(PC[index] != 0)
			permuted_bitstring[(index / 8)] = permuted_bitstring[(index / 8)] | (((bitstring[(PC[index] - 1) / 8] >> (7 - ((PC[index] - 1) % 8))) & 1) << (7 - (index % 8)));

	return permuted_bitstring;
}


unsigned char* Calculate_F_Output(unsigned char LR0[], unsigned char LR3[], unsigned char LR0S[], unsigned char LR3S[])
{
	int index;
	unsigned char RLXOR[4];

	for(index = 0; index < 4; index++)
		RLXOR[index] = (LR3[index + 4] ^ LR3S[index + 4]) ^ (LR0[index] ^ LR0S[index]);

	return MakePermutation(RLXOR, P_1, 32);
}

unsigned char* Transform_F_Output(unsigned char f_output[4])
{
	int index, aux_index = 0;
	unsigned char *expanded_output;

	if((expanded_output = (char*)calloc(8, sizeof(char))) == NULL)
		return NULL;

	for(index = 0; index < 8; index++)
		expanded_output[index] = 0;

	for(index = 0; index < 4; index++)
	{
		expanded_output[aux_index] = expanded_output[aux_index++] | f_output[index] >> 4;
		expanded_output[aux_index] = expanded_output[aux_index++] | (f_output[index] & 15);
	}

	return expanded_output;
}


unsigned char* Transform_Expansion(unsigned char *expansion)
{
	int index, index1, index2;
	unsigned char *expanded_expension, aux;

	if((expanded_expension = (char*)calloc(8, sizeof(char))) == NULL)
		return NULL;
	
	expanded_expension[0] = expansion[0] >> 2;
	expanded_expension[1] = ((expansion[0] & 3) << 4) | (expansion[1] >> 4);
	expanded_expension[2] = ((expansion[1] & 15) << 2) | (expansion[2] >> 6);
	expanded_expension[3] = expansion[2]  & 63;
	expanded_expension[4] = expansion[3] >> 2;
	expanded_expension[5] = ((expansion[3] & 3) << 4) | (expansion[4] >> 4);
	expanded_expension[6] = ((expansion[4] & 15) << 2) | (expansion[5] >> 6);
	expanded_expension[7] = expansion[5] & 63;

	return expanded_expension;
}


unsigned char ReturnSBoxValue(unsigned char input, int round)
{
	return S[round][(((input >> 5) & 1) << 1) | (input & 1)][(input >> 1) & 15];
}


int Attack(unsigned char LR0[][8], unsigned char LR0S[][8], unsigned char LR3[][8], unsigned char LR3S[][8], unsigned char counters[8][64], int pair)
{
	int index1, index2, counter;
	unsigned char IN[8][64], bs, R3[4], R3S[4], *expandedR3, *expandedR3S, *fOutput, *aux, outS1, outS2;

	for(index1 = 0; index1 < 4; index1++)
	{
		R3[index1] = LR3[pair][index1];
		R3S[index1] = LR3S[pair][index1];
	}

	if((aux = MakePermutation(R3, E, 48)) == NULL)
		return 0;

	expandedR3 = Transform_Expansion(aux);

	free(aux);

	if((aux = MakePermutation(R3S, E, 48)) == NULL)
		return 0;

	expandedR3S = Transform_Expansion(aux);

	free(aux);

	aux = Calculate_F_Output(LR0[pair], LR3[pair], LR0S[pair], LR3S[pair]);
	
	fOutput = Transform_F_Output(aux);

	free(aux);

	for(index1 = 0; index1 < 8; index1++)
		for(index2 = 0; index2 < 64; index2++)
			IN[index1][index2] = 64;

	for(index1 = 0; index1 < 8; index1++)
	{
		counter = 0;
		for(bs = 0; bs < 64; bs++)
		{
			outS1 = ReturnSBoxValue((expandedR3[index1] ^ expandedR3S[index1]) ^ bs, index1);
			outS2 = ReturnSBoxValue(bs, index1);
			if((outS1 ^ outS2) == fOutput[index1])
				IN[index1][counter++] = bs;
		}

		for(index2 = 0; index2 < 64 && IN[index1][index2] != 64; index2++)
			counters[index1][IN[index1][index2] ^ expandedR3[index1]]++;
	}

	return 1;
}


unsigned char* MakeK3(unsigned char *expanded_key3)
{
	int index1, index2;
	unsigned char *key3;

	if((key3 = (char*)calloc(6, sizeof(char))) == NULL)
		return NULL;

	key3[0] = (expanded_key3[0] << 2) | ((expanded_key3[1] >> 4) & 3);
	key3[1] = ((expanded_key3[1] & 15) << 4) | ((expanded_key3[2] >> 2) & 15);
	key3[2] = ((expanded_key3[2] & 3) << 6) | expanded_key3[3];
	key3[3] = (expanded_key3[4] << 2) | ((expanded_key3[5] >> 4) & 3);
	key3[4] = ((expanded_key3[5] & 15) << 4) | ((expanded_key3[6] >> 2) & 15);
	key3[5] = ((expanded_key3[6] & 3) << 6) | expanded_key3[7];

	return key3;
}


void ShiftBits(unsigned char* key)
{
	char aux;

	aux = (key[3] >> 4) & 15;
	key[3] = (key[3] & 15) | ((key[2] & 15) << 4);
	key[2] = (key[2] >> 4) | ((key[1] & 15) << 4);
	key[1] = (key[1] >> 4) | ((key[0] & 15) << 4);
	key[0] = (key[0] >> 4) | (aux << 4);

	aux = key[6] & 15;
	key[6] = (key[6] >> 4) | ((key[5] & 15) << 4);
	key[5] = (key[5] >> 4) | ((key[4] & 15) << 4);
	key[4] = (key[4] >> 4) | ((key[3] & 15) << 4);
	key[3] = (key[3] & (15 << 4)) | aux;	
}

int IsOddNumberOfBits(unsigned char character)
{	
	int bits_number = 0;
	while(character != 0)
	{
		if(character & 1)
			bits_number++;
		int index;

		character = character >> 1;
	}

	if(bits_number & 1)
		return 1;
	else
		return 0;
}


void MakeLS(unsigned char* key, int round)
{
	switch(round)
	{
		case 1:
		case 2:
		case 9:
		case 16:
		{
			char aux1, aux2, aux3;

			aux1 = (key[0] >> 7) & 1;
			aux2 = (key[3] >> 7) & 1;
			aux3 = (key[3] >> 3) & 1;

			key[3] = key[3] << 1;
			key[3] = key[3] & ((7 << 5) | 15);
			key[3] = key[3] | aux1 << 4;

			aux1 = (key[2] >> 7) & 1;

			key[2] = key[2] << 1;
			key[2] = key[2] | aux2;
			
			aux2 = (key[1] >> 7) & 1;

			key[1] = key[1] << 1;
			key[1] = key[1] | aux1;

			key[0] = key[0] << 1;
			key[0] = key[0] | aux2;

			aux1 = (key[6] >> 7) & 1;

			key[6] = key[6] << 1;
			key[6] = key[6] | aux3;


			aux2 = (key[5] >> 7) & 1;

			key[5] = key[5] << 1;
			key[5] = key[5] | aux1;

			aux1 = (key[4] >> 7) & 1;

			key[4] = key[4] << 1;
			key[4] = key[4] | aux2;

			key[3] = key[3] | aux1;

			break;
		}
		default:
		{
			char aux1, aux2, aux3;

			aux1 = (key[0] >> 6) & 3;
			aux2 = (key[3] >> 6) & 3;
			aux3 = (key[3] >> 2) & 3;
			
			key[3] = key[3] << 2;
			key[3] = key[3] & ((3 << 6) | 15);
			key[3] = key[3] | aux1 << 4;

			aux1 = (key[2] >> 6) & 3;

			key[2] = key[2] << 2;
			key[2] = key[2] | aux2;
			
			aux2 = (key[1] >> 6) & 3;

			key[1] = key[1] << 2;
			key[1] = key[1] | aux1;

			key[0] = key[0] << 2;
			key[0] = key[0] | aux2;

			aux1 = (key[6] >> 6) & 3;

			key[6] = key[6] << 2;
			key[6] = key[6] | aux3;


			aux2 = (key[5] >> 6) & 3;

			key[5] = key[5] << 2;
			key[5] = key[5] | aux1;

			aux1 = (key[4] >> 6) & 3;

			key[4] = key[4] << 2;
			key[4] = key[4] | aux2;

			key[3] = key[3] | aux1;
		}
	} 
}


unsigned char* f(unsigned char first_half[4], unsigned char key[6])
{
	int index, i = 0;
	unsigned char *expanded_half;

	if((expanded_half = MakePermutation(first_half, E, 48)) == NULL)
		return NULL;

	for(index = 0; index < 6; index++)
		expanded_half[index] = expanded_half[index] ^ key[index];

	first_half[0] = (S[0][(((expanded_half[0] >> 7) & 1) << 1) | ((expanded_half[0] >> 2) & 1)][(expanded_half[0] >> 3) & 15] << 4) | (S[1][(((expanded_half[0] >> 1) & 1) << 1) | ((expanded_half[1] >> 4) & 1)][((expanded_half[0] & 1) << 3) | ((expanded_half[1] >> 5) & 7)]);
	first_half[1] = (S[2][(((expanded_half[1] >> 3) & 1) << 1) | ((expanded_half[2] >> 6) & 1)][((expanded_half[1] & 7) << 1) | ((expanded_half[2] >> 7) & 1)] << 4) | (S[3][(((expanded_half[2] >> 5) & 1) << 1) | (expanded_half[2] & 1)][(expanded_half[2] >> 1) & 15]);
	first_half[2] = (S[4][(((expanded_half[3] >> 7) & 1) << 1) | ((expanded_half[3] >> 2) & 1)][(expanded_half[3] >> 3) & 15] << 4) | (S[5][(((expanded_half[3] >> 1) & 1) << 1) | ((expanded_half[4] >> 4) & 1)][((expanded_half[3] & 1) << 3) | ((expanded_half[4] >> 5) & 7)]);
	first_half[3] = (S[6][(((expanded_half[4] >> 3) & 1) << 1) | ((expanded_half[5] >> 6) & 1)][((expanded_half[4] & 7) << 1) | ((expanded_half[5] >> 7) & 1)] << 4) | (S[7][(((expanded_half[5] >> 5) & 1) << 1) | (expanded_half[5] & 1)][(expanded_half[5] >> 1) & 15]);

	free(expanded_half);

	return MakePermutation(first_half, P, 32);
}


unsigned char* Encrypt(unsigned char bitstring[8], unsigned char key[8])
{
	int index, aux_index;
	unsigned char* permuted_key;
	unsigned char* round_key;
	unsigned char* partial_encrypted_bitstring;
	unsigned char* permuted_partial_encrypted_bitstring;
	unsigned char right_half[4], aux, bitstring_copy[8];

	for(index = 0; index < 8; index++)
		bitstring_copy[index] = bitstring[index];

	if((partial_encrypted_bitstring = (char*)calloc(8, sizeof(char))) == NULL)
		return NULL;

	if((permuted_key = MakePermutation(key, PC1, 56)) == NULL)
		return NULL;

	for(index = 1; index < 4; index++)
	{
		MakeLS(permuted_key, index);

		if((round_key = MakePermutation(permuted_key, PC2, 48)) == NULL)
			return NULL;

		for(aux_index = 4; aux_index < 8; aux_index++)
			right_half[aux_index - 4] = bitstring_copy[aux_index];

		if((permuted_partial_encrypted_bitstring = f(right_half, round_key)) == NULL)
			return NULL;

		for(aux_index = 0; aux_index < 4; aux_index++)
			permuted_partial_encrypted_bitstring[aux_index] = bitstring_copy[aux_index] ^ permuted_partial_encrypted_bitstring[aux_index];

		for(aux_index = 4; aux_index < 8; aux_index++)
		{
			partial_encrypted_bitstring[aux_index - 4] = bitstring_copy[aux_index];
			partial_encrypted_bitstring[aux_index] = permuted_partial_encrypted_bitstring[aux_index -  4];
		}

		for(aux_index = 0; aux_index < 8; aux_index++)
			bitstring_copy[aux_index] = partial_encrypted_bitstring[aux_index];

		free(permuted_partial_encrypted_bitstring);
		free(round_key);
	}

	free(permuted_key);

	return partial_encrypted_bitstring;
}


int main()
{
	int index1, index2;
	unsigned char LR0[3][8], LR0S[3][8], LR3[3][8], LR3S[3][8], counters[8][64];
	unsigned char expanded_key3[8], possible_values;
	unsigned char *key3, *key3beforePC2, *key3beforePC1, unknown_positions[8];

	if(ReadPairs(LR0, LR0S, LR3, LR3S) == 0)
	{
		printf("A I/O problem has occured!\n");
		exit(0);
	}

	for(index1 = 0; index1 < 32; index1++)
		for(index2 = 0; index2 < 32; index2++)
			if(P[index2] == index1 + 1)
				P_1[index1] = index2 + 1;

	for(index1 = 0; index1 < 56; index1++)
		for(index2 = 0; index2 < 48; index2++)
			if(PC2[index2] == index1 + 1)
				PC2_1[index1] = index2 + 1;

	for(index1 = 0; index1 < 64; index1++)
		for(index2 = 0; index2 < 56; index2++)
			if(PC1[index2] == index1 + 1)
				PC1_1[index1] = index2 + 1;

	for(index1 = 0; index1 < 8; index1++)
		for(index2 = 0; index2 < 64; index2++)
			counters[index1][index2] = 0;

	for(index1 = 0; index1 < 3; index1++)
		Attack(LR0, LR0S, LR3, LR3S, counters, index1);

	for(index1 = 0; index1 < 8; index1++)
		for(index2 = 0; index2 < 64; index2++)
			if(counters[index1][index2] == 3)
			{
				expanded_key3[index1] = index2;
				break;
			}

	/*for(index1 = 0; index1 < 8; index1++)
	{
		printf(" ");
		for(index2 = 0; index2 < 8; index2++)
			printf("%d", (expanded_key3[index1] >> (7 - index2)) & 1);
	}*/

	if((key3 = MakeK3(expanded_key3)) == NULL)
	{
		printf("A problem has occured!\n");
		exit(1);
	}

	for(index1 = 0; index1 < 56; index1++)
	{
		if(index1 %8 == 0)
			printf("\n");	
		printf("%d ", PC2_1[index1]);
	}

	printf("\n\n");

	for(index1 = 0; index1 < 64; index1++)
	{
		if(index1 %8 == 0)
			printf("\n");	
		printf("%d ", PC1_1[index1]);
	}

	if((key3beforePC2 = MakePermutation(key3, PC2_1, 56)) == NULL)
	{
		printf("A problem has occured!\n");
		exit(2);
	}

	ShiftBits(key3beforePC2);

	if((key3beforePC1 = MakePermutation(key3beforePC2, PC1_1, 64)) == NULL)
	{
		printf("A problem has occured!\n");
		exit(3);
	}

	printf("\n");
	for(index1 = 0; index1 < 8; index1++)
	{
		for(index2 = 0; index2 < 8; index2++)
			printf("%d", (key3beforePC1[index1] >> (7 - index2)) & 1);
		printf(" ");
	}

	index2 = 0;
	for(index1 = 0; index1 < 56; index1++)
		if(PC2_1[index1] == 0)
			unknown_positions[index2++] = index1 + 1;

	for(index1 = 0; index1 < 8; index1++)
		if(unknown_positions[index1] <= 28)
			unknown_positions[index1] = (unknown_positions[index1] + 4) % 28;
		else
			unknown_positions[index1] = (unknown_positions[index1] + 4) % 28 + 28;

	for(index1 = 0; index1 < 8; index1++)
		for(index2 = 0; index2 < 64; index2++)
			if(PC1_1[index2] == unknown_positions[index1])
			{
				unknown_positions[index1] = index2 + 1;
				break;
			}

	for(index1 = 0; index1 < 7; index1++)
		for(index2 = index1 + 1; index2 < 8; index2++)
			if(unknown_positions[index2] < unknown_positions[index1])
			{
				unsigned char a = unknown_positions[index2];
				unknown_positions[index2] = unknown_positions[index1];
				unknown_positions[index1] = a;
			}

	printf("\n");
	for(index1 = 0; index1 < 8; index1++)
		printf("%d ", unknown_positions[index1] - 1);

	unsigned char copy[8], *en = NULL;
	possible_values = 0;
	int ok = 0;
	do
	{
		ok = 1;

		if(en != NULL)
			free(en);

		unsigned char aux = possible_values;

		for(index1 = 0; index1 < 8; index1++)
			copy[index1] = key3beforePC1[index1];		

		for(index1 = 0; index1 < 8; index1++)
		{
			copy[(unknown_positions[index1] - 1) / 8] = copy[(unknown_positions[index1] - 1) / 8] | ((aux & 1) << (7 - ((unknown_positions[index1] - 1) % 8)));
			aux = aux >> 1;
		}
		
		for(index1 = 0; index1 < 8; index1++)
			if(!IsOddNumberOfBits(copy[index1]))
				copy[index1] = copy[index1] | 1;

		en = Encrypt(LR0[0], copy);
		
		possible_values++;

		for(index1 = 0; index1 < 8; index1++)
			if(en[index1] != LR3[0][index1])
				ok =0;

	}
	while(ok == 0 && possible_values < 255);


	printf("\n");
	for(index1 = 0; index1 < 8; index1++)
		printf("%02X", copy[index1]);

	return 1;
}