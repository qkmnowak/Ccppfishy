#include "Bot.h"

Bot::Bot()
{
	Nazwa = "Bot1";
	ResetPozycji();
	GraSkonczona = false;
	Delay = 50;
}

Bot::~Bot()
{
	Nazwa.erase(Nazwa.begin(), Nazwa.end());
}

Bot & Bot::operator=(const Bot & _bot)
{
	if (&_bot == this) return *this;
	Nazwa.erase(Nazwa.begin(), Nazwa.end());
	Pozycja = _bot.Pozycja;
	PozW = _bot.PozW;
	PozA = _bot.PozA;
	PozS = _bot.PozS;
	PozD = _bot.PozD;
	GraSkonczona = _bot.GraSkonczona;
	Delay = _bot.Delay;
	Nazwa = _bot.Nazwa;
	return *this;
}

void Bot::setNazwa()
{
	string _ID;
	while (1)
	{
		std::cout << std::endl << "Podaj nazwe bota: ";
		std::cin >> _ID;
		if (std::cin.fail() == true)
		{
			std::cout << "Blad wprowadzania!" << std::endl;
			std::cin.clear();
			std::cin.ignore(256, '\n');
		}
		else
		{
			Nazwa.erase(Nazwa.begin(), Nazwa.end());
			Nazwa = _ID;
			break;
		}
	}
}

void Bot::setPoziomTrudnosci()
{
	try 
	{
		int _poziom;
		while (1)
		{
			std::cout << "Podaj poziom trudnosci bota <1-3>, gdzie: " << std::endl << "1. Wolny" << std::endl << "2. Normalny " << std::endl << "3. Szybki " << std::endl << std::endl;
			std::cin >> _poziom;
			if (std::cin.fail() == true)
			{
				std::cout << "Blad wprowadzania!" << std::endl;
				std::cin.clear();
				std::cin.ignore(256, '\n');
			}
			else
			{
				setDelay(_poziom);
				break;
			}
		}
		if (_poziom < 1) throw 1;
		if (_poziom > 3) throw 'a';
	}
	catch (int kodbledu)
	{
		std::cout << "Blad! Automatyczne ustawianie poziomu trudnosci na '1'..." << std::endl;
		setDelay(1);
	}
	catch (char kodbledu)
	{
		std::cout << "Blad! Automatyczne ustawianie poziomu trudnosci na '3'..." << std::endl;
		setDelay(3);
	}
}

void Bot::setDelay(int _PozomTrudnosci)
{
	if (_PozomTrudnosci == 1) Delay = 15;
	if (_PozomTrudnosci == 2) Delay = 5;
	if (_PozomTrudnosci == 3) Delay = 1;
	else Delay = 50;
}

int Bot::getDelay()
{
	return Delay;
}

char * Bot::ZwrocPozycje(int _sprawdzana)
{
	if (_sprawdzana == 1) return PozA;
	if (_sprawdzana == 2) return PozW;
	if (_sprawdzana == 3) return PozS;
	if (_sprawdzana == 4) return PozD;
	else return 0;
}

void Bot::Ruch()
{
	int x;
	char kierunek;
	x = rand() % 4 + 1;
	
	if (ZwrocPozycje(x) == 0)
	{  
		std::cout << "Krytyczny blad! " << std::endl;
	}

	else while (*ZwrocPozycje(x) == '4')
		{
			x = rand() % 4 + 1;
		}

	if (x == 1) kierunek = 'a';
	if (x == 2) kierunek = 'w';
	if (x == 3) kierunek = 's';
	if (x == 4) kierunek = 'd';

	if (kierunek == 'a')
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

	if (kierunek == 'w')
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

	if (kierunek == 's')
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

	if (kierunek == 'd')
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
	ResetPozycji();
}