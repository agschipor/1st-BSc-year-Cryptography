#include <iostream>
#include <fstream>
#include <NTL/ZZ.h>

NTL_CLIENT

using namespace std;


void ReadPublicKeyFromFile(ZZ &n, ZZ &e)
{
	fstream reader;

	reader.open("public_key.txt", ios::in);

	reader >> n;
	reader >> e;

	reader.close();
}


void Encrypt(ZZ n, ZZ e)
{
	ZZ character_ascii;
	char character;
	fstream reader, writer;

	reader.open("text.txt", ios::in);
	writer.open("encrypted_text.txt", ios::out);

	while(!reader.eof())
	{
		reader >> character;

		if(reader.eof())
			break;

		character_ascii = to_ZZ(character);
		writer << PowerMod(character_ascii, e, n) << " ";
	}

	reader.close();
	writer.close();
}


int main()
{
	ZZ n, e;

	ReadPublicKeyFromFile(n, e);
	Encrypt(n, e);

	return 0;
}