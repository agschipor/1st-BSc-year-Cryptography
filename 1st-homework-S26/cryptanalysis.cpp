#include "SubstitutionCipher.h"
#include <fstream>
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

struct MonogramFrequency
{
	char monogram;
	double frequency;
};


int partition(MonogramFrequency *input, int l, int r)
{
	MonogramFrequency pivot = input[r];

    while ( l < r )
    {
		while ( (input[l].frequency) > pivot.frequency)
			l++;

		while ( input[r].frequency < pivot.frequency )
            r--;

		if ( input[l].frequency == input[r].frequency )
            l++;
        else if ( l < r )
        {
            MonogramFrequency tmp = input[l];
            input[l] = input[r];
            input[r] = tmp;
        }
    }

    return r;
}


void quicksort(MonogramFrequency *input, int l, int r)
{
    if ( l < r )
    {
        int j = partition(input, l, r);        
        quicksort(input, l, j-1);
        quicksort(input, j+1, r);
    }
}

int main()
{
	SubstitutionCipher *cipher = new SubstitutionCipher();
	Key *key_obj = new Key();

	MonogramFrequency *official1_statistics = new MonogramFrequency[26];
	MonogramFrequency *personal1_statistics = new MonogramFrequency[26];

	string encrypted_text, decrypted_text;
	fstream reader;

	int index, indexc, encrypted_text_length;
	double frequency, best_score = 0;

	char child_key[26], key[26];

	reader.open("D:\\Facultate\\Coduri si Criptografie\\Tema1\\encrypted_text.txt", ios::in);

	if(std::getline(reader, encrypted_text) == 0)
		return 0;

	encrypted_text_length = encrypted_text.length();

	reader.close();
	
	reader.open("D:\\Facultate\\Coduri si Criptografie\\Tema1\\official_statistics1.txt", ios::in);

	for(index = 0; index < 26; index++)
	{
		reader >> official1_statistics[index].frequency;
		official1_statistics[index].monogram = (char)(index + 65);
	}

	reader.close();

	for(index = 0; index < 26; index++)
	{
		personal1_statistics[index].monogram = (char)(index + 65);
		personal1_statistics[index].frequency = 0;
	}

	for(index = 0; index < encrypted_text_length; index++)
		personal1_statistics[encrypted_text[index] - 65].frequency++;

	for(index = 0; index < 26; index++) 
		personal1_statistics[index].frequency /= encrypted_text_length;

	quicksort(official1_statistics, 0, 25);
	quicksort(personal1_statistics, 0, 25);

	//////////////////////////////////////////

	for(index = 0; index < 26; index++)
	{
		char a = official1_statistics[index].monogram;
		char b = personal1_statistics[index].monogram;
		child_key[official1_statistics[index].monogram - 65] = personal1_statistics[index].monogram;
	}

	double bigrams[26][26];
	double bigrams_sum = 0;
	double bigram_existance[26][26];


	for(index = 0; index < 26; index++)
		for(indexc = 0; indexc < 26; indexc++)
			bigrams[index][indexc] = 0;

	reader.open("D:\\Facultate\\Coduri si Criptografie\\Tema1\\bigrams.txt", ios::in);

	while(reader.eof() != true)
	{
		string bigram_and_freq;
		char x, y;
		double freq;

		reader >> x;
		reader >> y;
		reader >> freq;

		bigrams[x - 65][y - 65] = freq;
		bigrams_sum += freq;
	}

	for(index = 0; index < 26; index++)
		for(indexc = 0; indexc < 26; indexc++)
			if(bigrams[index][indexc] != 0)
				bigrams[index][indexc] = log10(bigrams[index][indexc] / bigrams_sum);
			else
				bigrams[index][indexc] = log10(0.01 / bigrams_sum);

	key_obj->SetKey(child_key);
	decrypted_text = cipher->Decrypt(encrypted_text, key_obj);

	for(index = 0; index < 26; index++)
		for(indexc = 0; indexc < 26; indexc++)
			bigram_existance[index][indexc] = 0;

	double decrypted_text_length = decrypted_text.length();
	for(index = 0; index < decrypted_text_length - 1; index++)
                if (bigram_existance[decrypted_text[index] - 65][decrypted_text[index + 1] - 65] == 0)
                    bigram_existance[decrypted_text[index] - 65][decrypted_text[index + 1] - 65] = 1;

	for(index = 0; index < 26; index++)
		for(indexc = 0; indexc < 26; indexc++)
			if (bigram_existance[index][indexc] != 0)
				best_score += bigrams[index][indexc];

	for(index = 0; index < 26; index++)
		key[index] = child_key[index];

	int iterations_no = 0;

	srand((unsigned)time(NULL));
	while(iterations_no < 1000)
	{
		double score = 0;
		int first_rindex, second_rindex;
		char aux;

		first_rindex = rand() % 26;
		second_rindex = rand() % 26;

		aux = child_key[first_rindex];
        child_key[first_rindex] = child_key[second_rindex];
        child_key[second_rindex] = aux;

		key_obj->SetKey(child_key);
		decrypted_text = cipher->Decrypt(encrypted_text, key_obj);

		for(index = 0; index < 26; index++)
			for(indexc = 0; indexc < 26; indexc++)
				bigram_existance[index][indexc] = 0;

		decrypted_text_length = decrypted_text.length();
		for(index = 0; index < decrypted_text_length - 1; index++)
			if (bigram_existance[decrypted_text[index] - 65][decrypted_text[index + 1] - 65] == 0)
				bigram_existance[decrypted_text[index] - 65][decrypted_text[index + 1] - 65] = 1;

		for(index = 0; index < 26; index++)
			for(indexc = 0; indexc < 26; indexc++)
				if (bigram_existance[index][indexc] != 0)
					score += bigrams[index][indexc];

		if (score > best_score)
        {
            best_score = score;

            for (index = 0; index < 26; index++)
                key[index] = child_key[index];

            iterations_no = 0;
        }
        else
        {
            aux = child_key[first_rindex];
            child_key[first_rindex] = child_key[second_rindex];
            child_key[second_rindex] = aux;
            iterations_no++;
        }
	}

	key_obj->SetKey(key);

	for(index = 0; index < 26; index++)
		cout << key[index] << " = " << (char)(index + 65) << endl;;

	return 1;
}