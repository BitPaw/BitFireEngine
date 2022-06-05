#pragma once

struct Restklasse
{
	private:
	int** restklasse;
	public:
	int(*operation)(int, int);
	bool zyklisch;
	bool hat_generator;
	bool hat_neutralElement;
	int generator;
	int neutralelement;
	int set_Generator(int mod);
	bool Zyklisch();
	int neutralElement();
	int inverse(int number);
	void print();
	Restklasse(int mod, int(*function)(int, int));
	Restklasse();
};