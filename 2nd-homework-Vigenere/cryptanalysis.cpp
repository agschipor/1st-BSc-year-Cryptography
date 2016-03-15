#include <stdio.h>
#include <stdlib.h>


char* ReadText(char* path, long *length)
{		
	FILE *reader;
	int index = -1;
	char *text;

	reader = fopen(path, "r");

	if(reader == NULL)
		return NULL;

	if(fseek(reader, 0, SEEK_END) == -1)
		return NULL;

	if((*length = ftell(reader)) == -1)
		return NULL;

	text = (char*)malloc(sizeof(char) * (*length));

	if(text == NULL)
		return NULL;

	if(fseek(reader, 0, SEEK_SET) == -1)
		return NULL;

	while(!feof(reader))
		fscanf(reader, "%c", &text[++index]);

	fclose(reader);

	return text;		
}


double CalculateCoincidenceIndex(char* encrypted_text, long length, int key_length, int offset)
{
	int index;
	int frequency[26];
	double text_length = 0;
	double coincidence_index = 0;

	for(index = 0; index < 26; ++index)
		frequency[index] = 0;

	for(index = offset; index < length; index += key_length)
	{
		frequency[encrypted_text[index] - 65]++;
		text_length++;
	}

	for(index = 0; index < 26; ++index)
		coincidence_index += ((frequency[index] / text_length) * ((frequency[index] - 1) / (text_length - 1)));

	return coincidence_index;
}


int CalculateKeyLength(char* encrypted_text, long length)
{
	double coincidence_index;
	int key_length = 0, index, is_good;

	do
	{
		is_good = 1;

		key_length += 1;

		coincidence_index = 0;

		for(index = 0; index < key_length; ++index)
			coincidence_index += CalculateCoincidenceIndex(encrypted_text, length, key_length, index);
	}
	while(coincidence_index / key_length > 0.071 || coincidence_index / key_length < 0.059);

	return key_length;
}


double CalculateMutualIndexOfCoincidence(char *encrypted_text, long en_length, double *nm_probability, int offset, int shift, int key_length)
{
	int index;
	int en_frequency[26], nm_frequency[26];
	double entext_length =0;
	double mutual_index_of_coincidence = 0;

	for(index = 0; index < 26; ++index)
		en_frequency[index] = nm_frequency[index] = 0;

	for(index = offset; index < en_length; index += key_length)
	{
		en_frequency[((encrypted_text[index] % 65 + shift) % 26)]++;
		entext_length++;
	}

	for(index = 0; index < 26; ++index)
		mutual_index_of_coincidence += ((en_frequency[index] / entext_length) * nm_probability[index]);

	return mutual_index_of_coincidence;
}


int* CalculateKey(char* encrypted_text, long en_length, char *normal_text, long nm_length)
{
	int *key, index, key_length = CalculateKeyLength(encrypted_text, en_length), shift = -1;
	double mutual_index_of_coincidence, nm_probability[26];;

	for(index = 0; index < 26; ++index)
		nm_probability[index] = 0;

	for(index = 0; index < nm_length; ++index)
		nm_probability[normal_text[index] - 65]++;

	for(index = 0; index < 26; ++index)
		nm_probability[index] /= nm_length;

	key = (int*)malloc(sizeof(int) * key_length);

	if(key == NULL)
		return NULL;


	for(index = 0; index < key_length; ++index)
	{
		shift = -1;

		do
		{
			shift += 1;
			mutual_index_of_coincidence = CalculateMutualIndexOfCoincidence(encrypted_text, en_length, nm_probability, index, shift, key_length);
		}
		while(mutual_index_of_coincidence < 0.055 || mutual_index_of_coincidence > 0.075);

		key[index] = ((26 - shift) > 0) ? (26 - shift) % 26 : (26 - shift);
	}	

	return key;
}


char* Decrypt(int *key, int key_length, char* encrypted_text, long length)
{
	int index;
	char *decrypted_text;

	decrypted_text = (char*)malloc(sizeof(char) * length);

	if(decrypted_text == NULL)
		return NULL;

	for(index = 0; index < length; ++index)
		if((encrypted_text[index] - 65 - key[index % key_length]) < 0)
			decrypted_text[index] = (char)(((encrypted_text[index] - 65 - key[index % key_length]) + 26) + 65);		
		else
			decrypted_text[index] = (char)(((encrypted_text[index] - 65 - key[index % key_length]) % 26) + 65);		

	return decrypted_text;
}


int main()
{
	FILE *writter;
	int *key, key_length, index;
	long en_length, *enlength_address = &en_length, nm_length, *nm_length_address = &nm_length;
	char* encrypted_text, *normal_text, *decrypted_text;

	if((encrypted_text = ReadText("encrypted_text.txt", enlength_address)) == NULL)
	{
		printf("\nA problem has occured!");
		exit(1);
	}

	if((normal_text = ReadText("normal_text.txt", nm_length_address)) == NULL)
	{
		printf("\nA problem has occured");
		exit(2);
	}

	if((key = CalculateKey(encrypted_text, en_length, normal_text, nm_length)) == NULL)
	{
		printf("\nA memory problem has occured!");
		exit(3);
	}

	writter = fopen("found_key.txt", "w");

	if(writter == NULL)
	{
		printf("\nA I/O problem has occured!");
		exit(4);
	}

	key_length = CalculateKeyLength(encrypted_text, en_length);

	for(index = 0; index < key_length; ++index)
		fprintf(writter, "%d\n", key[index]);

	fclose(writter);

	writter = fopen("decrypted_text_with_found_key.txt", "w");

	if((decrypted_text = Decrypt(key, key_length, encrypted_text, en_length)) == NULL)
	{
		printf("A problme has occured!");
		exit(5);
	}

	for(index = 0; index < en_length; ++index)
		fprintf(writter, "%c", decrypted_text[index]);

	free(encrypted_text);
	free(decrypted_text);
	free(normal_text);
	free(key);

	return 0;
}