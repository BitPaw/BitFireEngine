#include "Körper.h"
#include <iostream>

Körper::Körper()
{
	Körper::rk1 = Restklasse::Restklasse();
	Körper::rk2 = Restklasse::Restklasse();
	Körper::Endlich = false;
	Körper::Kommutativ = false;
	Körper::mit_Eins = false;
	Körper::Null_frei = false;
	Körper::Typ = "Initialisiert";
}

Körper::Körper(Restklasse rk)
{
	/* TODO: Not compilable
	if (rk.Operation == "Initialisiert")
	{
		std::cout << "Bitte rufe diese Funktion nur mit einer Restklasse mit Operanten auf \n";
		Körper::rk1 = Restklasse::Restklasse();
	}
	else
	{
		Körper::rk1 = rk;
	}
	Körper::rk2 = Restklasse::Restklasse();*/
}

Körper::Körper(Restklasse rk1, Restklasse rk2)
{
	/*
	if (rk1.Operation == "Initialisiert")
	{
		std::cout << "Bitte rufe diese Funktion nur mit einer Restklasse(1. Parameter) mit Operanten auf \n";
		Körper::rk1 = Restklasse::Restklasse();
	}
	else 
	{
		Körper::rk1 = rk1;
	}
	if (rk2.Operation == "Initialisiert")
	{
		std::cout << "Bitte rufe diese Funktion nur mit einer Restklasse(2. Parameter) mit Operanten auf \n";
		Körper::rk2 = Restklasse::Restklasse();
	}
	else 
	{
		Körper::rk2 = rk2;
	}
	*/
}

void Körper::addRestklasse(Restklasse rk)
{
	/*
	if (Körper::rk1.Operation == "Initialisiert" && rk.Operation != "Initialisiert") 
	{
		Körper::rk1 = rk;
	}
	else if (Körper::rk2.Operation == "Initialisiert" && rk.Operation != "Initialisiert") 
	{
		Körper::rk2 = rk;
	}
	else if (rk.Operation == "Initialisiert") 
	{
		std::cout << "Bitte rufe diese Funktion nur mit einer Restklasse mit Operanten auf \n";
		return;
	}
	std::cout << "Dieser Körper hat schon 2 von 2 Restklassen \n";*/
}

void Körper::endlich()
{
}

void Körper::kommutativ()
{
}

void Körper::mit_eins()
{
}

void Körper::null_frei()
{
}