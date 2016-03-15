#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char IP[] = {58, 50, 42, 34, 26, 18, 10, 2, 
			60, 52, 44, 36, 28, 20, 12, 4, 
			62, 54, 46, 38, 30, 22, 14, 6, 
			64, 56, 48, 40, 32, 24, 16, 8, 
			57, 49, 41, 33, 25, 17, 9, 1, 
			59, 51, 43, 35, 27, 19, 11, 3, 
			61, 53, 45, 37, 29, 21, 13, 5, 
			63, 55, 47, 39, 31, 23, 15, 7};

unsigned char IP_1[64];

unsigned char E[] = {32, 1, 2, 3, 4, 5, 
			4, 5, 6, 7, 8, 9, 
			8, 9, 10, 11, 12, 13, 
			12, 13, 14, 15, 16, 17, 
			16, 17, 18, 19, 20, 21, 
			20, 21, 22, 23, 24, 25, 
			24, 25, 26, 27, 28, 29, 
			28, 29, 30, 31, 32, 1};

unsigned char S[8][4][16] = {	{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
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

unsigned char P[] = {16, 7, 20, 21,
			29, 12, 28, 17,
			1, 15, 23, 26,
			5, 18, 31, 10, 
			2, 8, 24, 14,
			32, 27, 3, 9,
			19, 13, 30, 6,
			22, 11, 4, 25};

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

unsigned char* MakePermutation(unsigned char* bitstring, char *PC, int length)
{
	int index, permuted_bitstring_length = length / 8, offset = permuted_bitstring_length - 1;
	unsigned char* permuted_bitstring;

	if((permuted_bitstring = (char*)calloc(permuted_bitstring_length, sizeof(char))) == NULL)
		return NULL;

	for(index = 0; index < permuted_bitstring_length; index++)
		permuted_bitstring[index] = 0;

	for(index = 0; index < length; index++)
		permuted_bitstring[(index / 8)] = permuted_bitstring[(index / 8)] | (((bitstring[(PC[index] - 1) / 8] >> (7 - ((PC[index] - 1) % 8))) & 1) << (7 - (index % 8)));

	return permuted_bitstring;
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

int ReadKey(unsigned char key[8])
{
	int index, element;
	FILE *reader;

	reader = fopen("key.txt", "r");

	if(reader == NULL)
		return 0;

	for(index = 0; index < 8; index++)
	{
		fscanf(reader, "%02X", &element);
		key[index] = element;
	}

	fclose(reader);

	return 1;
}

int CreateRoundKeys(unsigned char key[8], unsigned char *round_keys[16])
{
	int index;
	unsigned char *permuted_key;

	if((permuted_key = MakePermutation(key, PC1, 56)) == NULL)
		return 0;

	for(index = 1; index < 17; index++)
	{
		MakeLS(permuted_key, index);

		if((round_keys[index -1] = MakePermutation(permuted_key, PC2, 48)) == NULL)
			return 0;
	}

	free(permuted_key);

	return 1;
}

unsigned char* Decrypt(unsigned char *encrypted_bitstring, unsigned char *round_keys[16])
{
	int index1, index2, index3;
	unsigned char aux, left_half[4];
	unsigned char *permuted_encrypted_bitstring;
	unsigned char *partial_decrypted_bitstring;
	unsigned char *permuted_partial_decrypted_bitstring;

	for(index1 = 0; index1 < 64; index1++)
		for(index2 = 0; index2 < 64; index2++)
			if(IP[index2] == index1 + 1)
				IP_1[index1] = index2 + 1;
	
	if((permuted_encrypted_bitstring = MakePermutation(encrypted_bitstring, IP, 64)) == NULL)
		return NULL;

	if((partial_decrypted_bitstring = (char*)calloc(8, sizeof(char))) == NULL)
		return NULL;

	for(index1 = 0; index1 < 4; index1++)
	{
		aux = permuted_encrypted_bitstring[index1];
		permuted_encrypted_bitstring[index1] = permuted_encrypted_bitstring[index1 + 4];
		permuted_encrypted_bitstring[index1 + 4] = aux;
	}

	for(index1 = 16; index1 > 0; index1--)
	{
		for(index2 = 0; index2 < 4; index2++)
			left_half[index2] = permuted_encrypted_bitstring[index2];

		if((permuted_partial_decrypted_bitstring = f(left_half, round_keys[index1 - 1])) == NULL)
			return NULL;

		for(index2 = 4; index2 < 8; index2++)
			permuted_partial_decrypted_bitstring[index2 - 4] = permuted_encrypted_bitstring[index2] ^ permuted_partial_decrypted_bitstring[index2 - 4];

		for(index2 = 4; index2 < 8; index2++)
		{
			partial_decrypted_bitstring[index2 - 4] = permuted_partial_decrypted_bitstring[index2 - 4];
			partial_decrypted_bitstring[index2] = permuted_encrypted_bitstring[index2 - 4];
		}

		for(index2 = 0; index2 < 8; index2++)
			permuted_encrypted_bitstring[index2] = partial_decrypted_bitstring[index2];

		free(permuted_partial_decrypted_bitstring);
	}

	free(permuted_encrypted_bitstring);

	return MakePermutation(partial_decrypted_bitstring, IP_1, 64);
}

unsigned char* ReadEncryptedText(long *length)
{
	FILE *reader;
	int index, element;
	unsigned char *encrypted_text;

	reader = fopen("encrypted_text.txt", "r");

	if(reader == NULL)
		return NULL;

	if(fseek(reader, 0, SEEK_END) == -1)
		return NULL;

	if((*length = ftell(reader)) == -1)
		return NULL;

	*length /= 2;

	encrypted_text = (char*)calloc((*length), sizeof(char));

	if(encrypted_text == NULL)
		return NULL;

	if(fseek(reader, 0, SEEK_SET) == -1)
		return NULL;

	for(index = 0; index < *length; index++)
	{
		fscanf(reader, "%02X", &element);
		encrypted_text[index] = element;
	}
	
	fclose(reader);

	return encrypted_text;		
}

int main()
{
	int index1, index2;
	long length, *length_address = &length;
	unsigned char  key[8], encrypted_bitstring[8], *round_keys[16];
	unsigned char *encrypted_text, *decrypted_bitstring;
	FILE *writer;

	if(ReadKey(key) == 0)
	{
		printf("\nA problem has occured!");
		exit(0);
	}

	if(CreateRoundKeys(key, round_keys) == 0)
	{
		printf("\nA problem has occured!");
		exit(0);
	}

	if((encrypted_text = ReadEncryptedText(length_address)) == NULL)
	{
		printf("\nA problem has occured!");
		exit(1);
	}

	writer = fopen("decrypted_text.txt", "w");

	if(writer == NULL)
	{
		printf("\nA problem has occured!");
		exit(2);
	}

	for(index1 = 0; index1 < length; index1++)
	{
		encrypted_bitstring[index1 % 8] = encrypted_text[index1];

		if((index1 + 1) % 8 == 0)
		{
			if((decrypted_bitstring = Decrypt(encrypted_bitstring, round_keys)) == NULL)
			{
				printf("\nA problem has occured!");
				exit(9);
			}

			for(index2 = 0; index2 < 8; index2++)
				fprintf(writer, "%c", decrypted_bitstring[index2]);

			free(decrypted_bitstring);
		}
	}

	fclose(writer);

	return 0;
}