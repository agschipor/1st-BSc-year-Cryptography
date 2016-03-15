#include <iostream>
#include <fstream>
#include <NTL/ZZ.h>

NTL_CLIENT

using namespace std;


void ReadPrivateKeyFromFile(ZZ &p, ZZ &q, ZZ &d)
{
	fstream reader;

	reader.open("private_key.txt", ios::in);

	reader >> p;
	reader >> q;
	reader >> d;

	reader.close();
}


void Decrypt(ZZ p, ZZ q, ZZ d)
{
	ZZ character_ascii, n = p * q;
	fstream reader, writer;
	unsigned char converted_ascii;

	reader.open("encrypted_text.txt", ios::in);
	writer.open("decrypted_text.txt", ios::out);

	while(!reader.eof())
	{
		reader >> character_ascii;
		
		if(reader.eof())
			break;
		
		cout << character_ascii;
		BytesFromZZ(&converted_ascii, PowerMod(character_ascii, d, n), 1);

		writer << converted_ascii;
	}

	reader.close();
	writer.close();
}


int main()
{
	ZZ p, q, d;

	ReadPrivateKeyFromFile(p, q, d);
	Decrypt(p, q, d);

	return 0;
}