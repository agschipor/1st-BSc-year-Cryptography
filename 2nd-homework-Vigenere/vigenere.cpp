#include <stdio.h>
#include <stdlib.h>


int FilterText()
{
	FILE *reader, *writter;
	char character;

	reader = fopen("ordinary_text.txt", "r");
	writter = fopen("plain_text.txt", "w");

	if(reader == NULL)
		return -1;

	if(writter == NULL)
		return -1;

	while(!feof(reader))
	{
		fscanf(reader, "%c", &character);
		if(character >= 'A' && character <= 'Z')
			fprintf(writter, "%c", character);
		else
			if(character >= 'a' && character <= 'z')
				fprintf(writter, "%c", character - 32);
			
	}

	fclose(reader);
	fclose(writter);

	return 0;
}


char* ReadPlainText(long *length)
{		
	FILE *reader;
	int index = -1;
	char *plain_text;

	reader = fopen("plain_text.txt", "r");

	if(reader == NULL)
		return NULL;

	if(fseek(reader, 0, SEEK_END) == -1)
		return NULL;

	if((*length = ftell(reader)) == -1)
		return NULL;

	plain_text = (char*)malloc(sizeof(char) * (*length));

	if(plain_text == NULL)
		return NULL;

	if(fseek(reader, 0, SEEK_SET) == -1)
		return NULL;

	while(!feof(reader))
		fscanf(reader, "%c", &plain_text[++index]);

	fclose(reader);

	return plain_text;		
}


int* GenerateKey(int *key_length)
{
	FILE *writter;

	writter = fopen("key.txt", "w");

	if(writter == NULL)
		return NULL;

	int *key, index;

	srand((unsigned)time(NULL));

	*key_length = rand() % 20 + 1;

	key = (int*)malloc(sizeof(int) * (*key_length));

	if(key == NULL)
		return NULL;

	for(index = 0; index < *key_length; ++index)
	{
		key[index] = rand() % 26;
		fprintf(writter, "%d\n", key[index]);
	}

	return key;
}


char* Encrypt(int *key, int key_length, char *plain_text, long length)
{
	int index;
	char *encrypted_text;

	encrypted_text = (char*)malloc(sizeof(char) * length);

	if(encrypted_text == NULL)
		return NULL;

	for(index = 0; index < length; ++index)
		encrypted_text[index] = (char)(((plain_text[index] - 65 + key[index % key_length]) % 26) + 65);

	return encrypted_text;
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


int WriteTextToFile(char* path, char* text, long length)
{
	FILE *writter;
	int index;

	writter = fopen(path, "w");

	if(writter == NULL)
		return -1;

	for(index = 0; index < length; ++index)
		fprintf(writter, "%c", text[index]);

	fclose(writter);

	return 0;
}


int main()
{
	char *plain_text, *encrypted_text, *decrypted_text;
	int index, *key, key_length, *key_length_address = &key_length;
	long length;
	long *length_address = &length;

	if(FilterText() == -1)
	{
		printf("\nA file I/O has occured!");
		exit(1);
	}

	if((plain_text = ReadPlainText(length_address)) == NULL)
	{
		printf("A problem has occured!");
		exit(2); 
	}

	if((key = GenerateKey(key_length_address)) == NULL)
	{
		printf("A memory problem has occured!");
		exit(3);
	}

	if((encrypted_text = Encrypt(key, key_length, plain_text, length)) == NULL)
	{
		printf("A memory problem has occured!");
		exit(4);
	}

	if(WriteTextToFile("encrypted_text.txt" ,encrypted_text, length) == -1)
	{
		printf("\nA file I/O has occured!");
		exit(5);
	}

	if((decrypted_text = Decrypt(key, key_length, encrypted_text, length)) == NULL)
	{
		printf("A memory problem has occured!");
		exit(4);
	}

	if(WriteTextToFile("decrypted_text.txt" ,decrypted_text, length) == -1)
	{
		printf("\nA file I/O has occured!");
		exit(5);
	}	

	free(plain_text);
	free(encrypted_text);
	free(decrypted_text);;
	free(key);

	return 0;
}