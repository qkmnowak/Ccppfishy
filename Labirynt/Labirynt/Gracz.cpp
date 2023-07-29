#include "Gracz.h"

Gracz::Gracz()
{
	Nazwa = "Gracz1";
	ResetPozycji();
	GraSkonczona = false;
}

Gracz::~Gracz()
{
	Nazwa.erase(Nazwa.begin(), Nazwa.end());
}

Gracz & Gracz::operator=(const Gracz & _gracz)
{
	if (&_gracz == this) return *this;
	Nazwa.erase(Nazwa.begin(), Nazwa.end());
	Pozycja = _gracz.Pozycja;
	PozW = _gracz.PozW;
	PozA = _gracz.PozA;
	PozS = _gracz.PozS;
	PozD = _gracz.PozD;
	GraSkonczona = _gracz.GraSkonczona;
	Nazwa = _gracz.Nazwa;
	return *this;
}

void Gracz::ResetPozycji()
{
	Pozycja = nullptr;
	PozW = nullptr;
	PozA = nullptr;
	PozS = nullptr;
	PozD = nullptr;
}

bool Gracz::getGraSkonczona()
{
	return GraSkonczona;
}

string Gracz::getNazwa()
{
	return Nazwa;
}

void Gracz::setNazwa()
{
	string _name;
	while (1)
	{
		std::cout << std::endl << "Podaj swoja nazwe gracza: ";
		std::cin >> _name;
		if (std::cin.fail() == true)
		{
			std::cout << "Blad wprowadzania!" << std::endl;
			std::cin.clear();
			std::cin.ignore(256, '\n');
		}
		else
		{
			Nazwa.erase(Nazwa.begin(), Nazwa.end());
			Nazwa = _name;
			break;
		}
	}
}

void Gracz::setPozycja(char* _pozycja)
{ 
	Pozycja = _pozycja;
}

void Gracz::setPozW(char* _pozycja)
{
	PozW = _pozycja;
}

void Gracz::setPozA(char* _pozycja)
{
	PozA = _pozycja;
}

void Gracz::setPozS(char* _pozycja)
{
	PozS = _pozycja;
}

void Gracz::setPozD(char* _pozycja)
{
	PozD = _pozycja;
}

void Gracz::Ruch(char _kierunek)
{
		if (_kierunek == 'a')
		{
			if (*PozA == '4');
			else if (*PozA == '3')
			{
				*PozA = 'g';
				*Pozycja = '3';
			}
			else if (*PozA == 'w')
			{
				*PozA = 'g';
				GraSkonczona = true;
				//wygrana!
			}
			else if (*PozA == 'b')
			{
				*PozA = '2';
			}
		}

		if (_kierunek == 'w')
		{
			if (*PozW == '4');
			else if (*PozW == '3')
			{
				*PozW = 'g';
				*Pozycja = '3';
			}
			else if (*PozW == 'w')
			{
				*PozW = 'g';
				GraSkonczona = true;
				//wygrana!
			}
			else if (*PozW == 'b')
			{
				*PozW = '2';
			}
		}

		if (_kierunek == 's')
		{
			if (*PozS == '4');
			else if (*PozS == '3')
			{
				*PozS = 'g';
				*Pozycja = '3';
			}
			else if (*PozS == 'w')
			{
				*PozW = 'g';
				GraSkonczona = true;
				//wygrana!
			}
			else if (*PozS == 'b')
			{
				*PozS = '2';
			}
		}

		if (_kierunek == 'd')
		{
			if (*PozD == '4');
			else if (*PozD == '3')
			{
				*PozD = 'g';
				*Pozycja = '3';
				
			}
			else if (*PozD == 'w')
			{
				*PozD = 'g';
				GraSkonczona = true;
				//wygrana!
			}
			else if (*PozD == 'b')
			{
				*PozD = '2';
			}
		}
		//wypelnij
		ResetPozycji();
}

void Gracz::test()
{
	cout << "Poz: " << *Pozycja << endl << "W: " << *PozW << endl << "A: " << *PozA << endl << "S: " << *PozS << endl << "D: " << *PozD << endl;
}