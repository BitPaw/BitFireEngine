#include "Koerper.h"
#include <iostream>

Koerper::Koerper()
{
	Koerper::rk1 = Restklasse();
	Koerper::rk2 = Restklasse();
	Koerper::Endlich = false;
	Koerper::Kommutativ = false;
	Koerper::mit_Eins = false;
	Koerper::Null_frei = false;
	Koerper::Typ = "Initialisiert";
}

Koerper::Koerper(Restklasse rk)
{
	/* TODO: Not compilable
	if (rk.Operation == "Initialisiert")
	{
		std::cout << "Bitte rufe diese Funktion nur mit einer Restklasse mit Operanten auf \n";
		Koerper::rk1 = Restklasse::Restklasse();
	}
	else
	{
		Koerper::rk1 = rk;
	}
	Koerper::rk2 = Restklasse::Restklasse();*/
}

Koerper::Koerper(Restklasse rk1, Restklasse rk2)
{
	/*
	if (rk1.Operation == "Initialisiert")
	{
		std::cout << "Bitte rufe diese Funktion nur mit einer Restklasse(1. Parameter) mit Operanten auf \n";
		Koerper::rk1 = Restklasse::Restklasse();
	}
	else
	{
		Koerper::rk1 = rk1;
	}
	if (rk2.Operation == "Initialisiert")
	{
		std::cout << "Bitte rufe diese Funktion nur mit einer Restklasse(2. Parameter) mit Operanten auf \n";
		Koerper::rk2 = Restklasse::Restklasse();
	}
	else
	{
		Koerper::rk2 = rk2;
	}
	*/
}

void Koerper::addRestklasse(Restklasse rk)
{
	/*
	if (Koerper::rk1.Operation == "Initialisiert" && rk.Operation != "Initialisiert")
	{
		Koerper::rk1 = rk;
	}
	else if (Koerper::rk2.Operation == "Initialisiert" && rk.Operation != "Initialisiert")
	{
		Koerper::rk2 = rk;
	}
	else if (rk.Operation == "Initialisiert")
	{
		std::cout << "Bitte rufe diese Funktion nur mit einer Restklasse mit Operanten auf \n";
		return;
	}
	std::cout << "Dieser Koerper hat schon 2 von 2 Restklassen \n";*/
}

void Koerper::endlich()
{
}

void Koerper::kommutativ()
{
}

void Koerper::mit_eins()
{
}

void Koerper::null_frei()
{
}
