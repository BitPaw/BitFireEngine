#pragma once

#include "Restklassen.h"

class Koerper
{
	private:
	Restklasse rk1;
	Restklasse rk2;
	const char* Typ;
	public:
	bool Endlich;
	bool Kommutativ;
	bool mit_Eins;
	bool Null_frei;
	Koerper();
	Koerper(Restklasse rk);
	Koerper(Restklasse rk1, Restklasse rk2);
	void addRestklasse(Restklasse rk);
	void endlich();
	void kommutativ();
	void mit_eins();
	void null_frei();
};
