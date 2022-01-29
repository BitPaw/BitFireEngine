#pragma once
#include "Restklassen.h"
class Körper{
private:
	Restklasse rk1;
	Restklasse rk2;
	const char* Typ;
public:
	bool Endlich;
	bool Kommutativ;
	bool mit_Eins;
	bool Null_frei;
	Körper();
	Körper(Restklasse rk);
	Körper(Restklasse rk1, Restklasse rk2);
	void addRestklasse(Restklasse rk);
	void endlich();
	void kommutativ();
	void mit_eins();
	void null_frei();
};