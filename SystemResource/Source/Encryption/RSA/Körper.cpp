#include "K�rper.h"
#include <iostream>

K�rper::K�rper()
{
	K�rper::rk1 = Restklasse::Restklasse();
	K�rper::rk2 = Restklasse::Restklasse();
	K�rper::Endlich = false;
	K�rper::Kommutativ = false;
	K�rper::mit_Eins = false;
	K�rper::Null_frei = false;
	K�rper::Typ = "Initialisiert";
}

K�rper::K�rper(Restklasse rk)
{
	/* TODO: Not compilable
	if (rk.Operation == "Initialisiert")
	{
		std::cout << "Bitte rufe diese Funktion nur mit einer Restklasse mit Operanten auf \n";
		K�rper::rk1 = Restklasse::Restklasse();
	}
	else
	{
		K�rper::rk1 = rk;
	}
	K�rper::rk2 = Restklasse::Restklasse();*/
}

K�rper::K�rper(Restklasse rk1, Restklasse rk2)
{
	/*
	if (rk1.Operation == "Initialisiert")
	{
		std::cout << "Bitte rufe diese Funktion nur mit einer Restklasse(1. Parameter) mit Operanten auf \n";
		K�rper::rk1 = Restklasse::Restklasse();
	}
	else 
	{
		K�rper::rk1 = rk1;
	}
	if (rk2.Operation == "Initialisiert")
	{
		std::cout << "Bitte rufe diese Funktion nur mit einer Restklasse(2. Parameter) mit Operanten auf \n";
		K�rper::rk2 = Restklasse::Restklasse();
	}
	else 
	{
		K�rper::rk2 = rk2;
	}
	*/
}

void K�rper::addRestklasse(Restklasse rk)
{
	/*
	if (K�rper::rk1.Operation == "Initialisiert" && rk.Operation != "Initialisiert") 
	{
		K�rper::rk1 = rk;
	}
	else if (K�rper::rk2.Operation == "Initialisiert" && rk.Operation != "Initialisiert") 
	{
		K�rper::rk2 = rk;
	}
	else if (rk.Operation == "Initialisiert") 
	{
		std::cout << "Bitte rufe diese Funktion nur mit einer Restklasse mit Operanten auf \n";
		return;
	}
	std::cout << "Dieser K�rper hat schon 2 von 2 Restklassen \n";*/
}

void K�rper::endlich()
{
}

void K�rper::kommutativ()
{
}

void K�rper::mit_eins()
{
}

void K�rper::null_frei()
{
}