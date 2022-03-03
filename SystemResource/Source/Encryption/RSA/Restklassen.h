#pragma once

class Restklasse
{
	private:
	int** restklasse;
	public:
	const char* Operation;
	bool zyklisch;
	bool hat_generator;
	bool hat_neutralElement;
	int generator;
	int neutralelement;
	void Restring_plus(int mod);
	void Restring_minus(int mod);
	void Restring_mal(int mod);
	void Restring_durch(int mod);
	int set_Generator(int mod);
	bool Zyklisch();
	int neutralElement();
	int inverse(int number);
	void print();
	Restklasse(int mod, char op);
	Restklasse();
	static unsigned int chineseRemainder(unsigned int* remainderset, unsigned int* moduloset);
};