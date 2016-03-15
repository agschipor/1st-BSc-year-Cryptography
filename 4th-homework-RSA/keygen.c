#include <iostream>
#include <NTL/ZZ.h>
#include <fstream>

NTL_CLIENT

using namespace std;


void GeneratePandQ(ZZ &p, ZZ &q)
{
	GenGermainPrime(p, 512, 80);
	GenGermainPrime(q, 512, 80);
}


void GenerateEandCalculateD(ZZ &e, ZZ &d, ZZ p, ZZ q)
{
	ZZ seed, e_aux;
	long min_Hamming_weight, min_Hamming_weight_aux;

	srand((unsigned)time(NULL));

	seed = rand();

	SetSeed(seed);

	ZZ phi_n = (p - 1) * (q - 1);

	for(int i = 0; i < 100; i++)
	{
		GenGermainPrime(e_aux, 16, 80);

		min_Hamming_weight_aux = weight(e_aux);

		if(i == 1)
		{
			min_Hamming_weight = weight(e_aux);
			e = e_aux;
		}
		else
			if(min_Hamming_weight > min_Hamming_weight_aux)
			{
				min_Hamming_weight = min_Hamming_weight_aux;
				e = e_aux;
			}
	}

	InvMod(d, e, phi_n);	
}


void WriteKeysInFile(ZZ p, ZZ q, ZZ e, ZZ d)
{
	fstream writer;

	writer.open("public_key.txt", ios::out);

	writer << (p * q) << endl;
	writer << e;

	writer.close();

	writer.open("private_key.txt", ios::out);

	writer << p << endl;
	writer << q << endl;
	writer << d;

	writer.close();
}


int main()
{
	ZZ p, q, e, d;

	GeneratePandQ(p, q);
	GenerateEandCalculateD(e, d, p, q);
	WriteKeysInFile(p, q, e, d);

	return 0;
}