#include "Labirynt.h"

Labirynt::Labirynt()
{
	w = 10;
	k = 10;
	plansza = new char *[w];
	for (int i = 0; i < w; i++)
	{
		plansza[i] = new char[k];
	}
	NumerLabiryntu = 1;
	BotCzyGracz = 'g';
	CzyLabiryntOk = true;
}

Labirynt::~Labirynt()
{
	for (int i = 0; i < w; i++)
		delete[] plansza[i];
	delete[] plansza;
}

Labirynt & Labirynt::operator=(const Labirynt & _lab)
{
	if (&_lab == this) return *this;
	for (int i = 0; i < w; i++)
		delete[] plansza[i];
	delete[] plansza;
	w = _lab.w;
	k = _lab.k;
	NumerLabiryntu = _lab.NumerLabiryntu;
	BotCzyGracz = _lab.BotCzyGracz;
	CzyLabiryntOk = _lab.CzyLabiryntOk;
	plansza = new char *[w];
	for (int i = 0; i < w; i++)
	{
		plansza[i] = new char[k];
	}

	return *this;
}

Labirynt::Labirynt(const Labirynt & _stary)
{
	w = _stary.w;
	k = _stary.k;
	NumerLabiryntu = _stary.NumerLabiryntu;
	BotCzyGracz = _stary.BotCzyGracz;
	CzyLabiryntOk = _stary.CzyLabiryntOk;
	plansza = new char*[w];
	for (int i = 0; i < w; i++)
	{
		plansza[i] = new char[k];
	}
	for (int i = 0; i < w; ++i)
	{
		for (int j = 0; j < k; ++j)
		{
			plansza[i][j] = _stary.plansza[i][j];
		}
	}
}

void Labirynt::WiadomoscPowitalna()
{
	std::cout << "Witaj w grze 'Labirynt'! Twoim zadaniem jest dojscie do wyjscia z labiryntu szybciej, niz zrobi to bot. " << endl;
	Sleep(2000);
	std::cout << "Twoja aktualna pozycje wskazuje litera 'g' na wygenerowanej planszy. " << endl;
	Sleep(2000);
	std::cout << "Po planszy poruszasz sie z wykorzystaniem klawiszy W (gora), A (lewo), S (dol), D (prawo). Kazdy wybor kierunku nalezy potwierdzic klawiszem 'enter'." << endl;
	Sleep(2000);
	std::cout << "Powodzenia!" << endl << endl;
	Sleep(3000);
}

void Labirynt::WybierzLabirynt()
{
	try
	{
		while (1) 
		{
			std::cout << "Podaj numer labiryntu, ktory chcesz wczytac <1-3>" << std::endl;
			std::cin >> NumerLabiryntu;
			if (std::cin.fail() == true)
			{
				std::cout << "Blad wprowadzania!" << std::endl;
				std::cin.clear();
				std::cin.ignore(256, '\n');
			}
			else break;
		}
		if (NumerLabiryntu < 1) throw 1;
		if (NumerLabiryntu > 3) throw 'a';
	}
	catch (int kodbledu)
	{
		std::cout << "Automatyczne ustawianie numeru na '1'..." << std::endl;
		NumerLabiryntu = 1;
	}
	catch (char kodbledu)
	{
		std::cout << "Automatyczne ustawianie numeru na '3'..." << std::endl;
		NumerLabiryntu = 3;
	}
	WczytajLabirynt();
}

void Labirynt::ZnajdzPozycje()
{
	for (int i = 0; i < w; ++i)
	{
		for (int j = 0; j < k; ++j)
		{
			if (plansza[i][j] == 'g')
			{
				PodajPozycje(i, j);
			}
		}
	}
}

void Labirynt::PodajPozycje(int _w, int _k)
{
	if (BotCzyGracz == 'g')
	{
		Gracz1.setPozycja(&plansza[_w][_k]);
		Gracz1.setPozW(&plansza[_w - 1][_k]);
		Gracz1.setPozA(&plansza[_w][_k - 1]);
		Gracz1.setPozS(&plansza[_w + 1][_k]);
		Gracz1.setPozD(&plansza[_w][_k + 1]);
	}
	else if (BotCzyGracz == 'b')
	{
		Bot1.setPozycja(&plansza[_w][_k]);
		Bot1.setPozW(&plansza[_w - 1][_k]);
		Bot1.setPozA(&plansza[_w][_k - 1]);
		Bot1.setPozS(&plansza[_w + 1][_k]);
		Bot1.setPozD(&plansza[_w][_k + 1]);
	}
}

void Labirynt::WczytajLabirynt()
{
	std::fstream plik;
	
	if (NumerLabiryntu == 1)
	{
		plik.open("Labirynt1.txt", std::ifstream::in);
		if (plik.good() == false)
		{
			std::cout << "Blad otwierania pliku!" << std::endl;
			CzyLabiryntOk = false;
		}
		else
		{
			for (int i = 0; i < w; ++i)
			{
				for (int j = 0; j < k; ++j)
				{
					plik >> plansza[i][j];
					if (plansza[i][j] == 'g')
					{
						PodajPozycje(i, j);
					}
				}
			}
			plik.close();
		}
	}
	if (NumerLabiryntu == 2)
	{
		plik.open("Labirynt2.txt", std::ifstream::in);
		if (plik.good() == false)
		{
			std::cout << "Blad otwierania pliku!" << std::endl;
			CzyLabiryntOk = false;
		}
		else
		{
			for (int i = 0; i < w; ++i)
			{
				for (int j = 0; j < k; ++j)
				{
					plik >> plansza[i][j];
					if (plansza[i][j] == 'g')
					{
						PodajPozycje(i, j);
					}
				}
			}
			plik.close();
		}
	}
	if (NumerLabiryntu == 3)
	{
		plik.open("Labirynt3.txt", std::ifstream::in);
		if (plik.good() == false) 
		{
			std::cout << "Blad otwierania pliku!" << std::endl;
			CzyLabiryntOk = false;
		}
		else
		{
			for (int i = 0; i < w; ++i)
			{
				for (int j = 0; j < k; ++j)
				{
					plik >> plansza[i][j];
					if (plansza[i][j] == 'g')
					{
						PodajPozycje(i, j);
					}
				}
			}
			plik.close();
		}
	}

	try
	{
		if (CzyLabiryntOk == false) throw 'f';
	}
	catch(...)
	{
		std::cout << endl << "Blad krytyczny! Zamykanie programu! " << endl;
		Sleep(3000);
		exit(0);
	}
}

void Labirynt::WyswietlPlansze()
{
	for (int i = 0; i < w; ++i) 
	{
		for (int j = 0; j < k; ++j)
		{
			if (plansza[i][j] == '3')std::cout << ' ';
			if (plansza[i][j] == '4')std::cout << '#';
			if (plansza[i][j] == 'g')std::cout << 'g';
			if (plansza[i][j] == 'b')std::cout << 'b';
			if (plansza[i][j] == 'w')std::cout << ' ';
		}
		std::cout << std::endl;
	}
}

void Labirynt::WyczyscEkran()
{
	system("cls");
}

void Labirynt::Graj()
{
	WiadomoscPowitalna();

	WybierzLabirynt();

	Gracz1.setNazwa();
	Bot1.setNazwa();
	Bot1.setPoziomTrudnosci();
	Sleep(3000);
	WyczyscEkran();
	WyswietlPlansze();

	time_t CzasDoZakonczeniaObslugiMenu = clock();

	//GRACZ
	BotCzyGracz = 'g';
	char _kierunek;
	while (1)
	{
		while (1)
		{
			std::cout << std::endl << "Podaj kierunek (WASD): ";
			std::cin >> _kierunek;
			if (std::cin.fail() == true)
			{
			std::cout << "Blad wprowadzania!" << std::endl;
			std::cin.clear();
			std::cin.ignore(256, '\n');
			}
			else break;
		}
	WyczyscEkran();
	Gracz1.Ruch(_kierunek);
	if (Gracz1.getGraSkonczona() == true)
	{
		std::cout << "Dotarles do konca labiryntu. Gratulacje, " << Gracz1.getNazwa() << "!" << std::endl;
		std::cout << "Teraz czas na bota! " << std::endl;
		Sleep(3000);
		break;
	}
	WyswietlPlansze();
	ZnajdzPozycje();
	}
	
	time_t CzasDoZakonczeniaGryGracza = clock();

	//BOT

	BotCzyGracz = 'b';
	WczytajLabirynt();
	WyswietlPlansze();
	while (1)
	{
		Sleep(Bot1.getDelay());
		WyczyscEkran();
		Bot1.Ruch();
		if (Bot1.getGraSkonczona() == true)
		{
			std::cout << "Dotarles do konca labiryntu. Gratulacje, " << Bot1.getNazwa() << "!" << std::endl;
			break;
		}
		WyswietlPlansze();
		ZnajdzPozycje();
	}

	time_t CzasDoZakonczeniaGryBota = clock();

	WylonZwyciezce(CzasDoZakonczeniaObslugiMenu, CzasDoZakonczeniaGryGracza, CzasDoZakonczeniaGryBota);
}

void Labirynt::WylonZwyciezce(time_t CzasDoZakonczeniaObslugiMenu, time_t CzasDoZakonczeniaGryGracza, time_t CzasDoZakonczeniaGryBota)
{
	time_t CzasGryGracza = (CzasDoZakonczeniaGryGracza - CzasDoZakonczeniaObslugiMenu - (3*CLOCKS_PER_SEC));
	time_t CzasGryBota = (CzasDoZakonczeniaGryBota - CzasDoZakonczeniaGryGracza);

	//std::cout << "Czas obslugi menu: " << CzasDoZakonczeniaObslugiMenu/CLOCKS_PER_SEC << "s" << std::endl; /// do testowania 
	std::cout << "Czas gry gracza: " << CzasGryGracza / CLOCKS_PER_SEC << "s" << std::endl;
	std::cout << "Czas gry bota: " << CzasGryBota / CLOCKS_PER_SEC << "s" << std::endl << std::endl;
	
	if (Porownaj<time_t>(CzasGryGracza, CzasGryBota) == CzasGryGracza)
	{ 
		std::cout << "Zwyciezyl gracz '" << Gracz1.getNazwa() << "' z czasem " << CzasGryGracza / CLOCKS_PER_SEC << "s. Gratulacje!" << endl << endl;
	}
	else if (Porownaj<time_t>(CzasGryGracza, CzasGryBota) == CzasGryBota)
	{
		std::cout << "Zwyciezyl bot '" << Bot1.getNazwa() << "' z czasem " << CzasGryBota / CLOCKS_PER_SEC << "s. Przykro mi!" << endl << endl;
	}
	else if (Porownaj<time_t>(CzasGryGracza, CzasGryBota) == 0)
	{
		std::cout << "Remis! " << "Czas przejscia labiryntu wynosil " << CzasGryBota / CLOCKS_PER_SEC << "s." << endl << endl;
	}

}

template<typename T>
T Labirynt::Porownaj(T _pierwszy, T _drugi)
{
	if (_pierwszy < _drugi) return _pierwszy;
	else if (_drugi < _pierwszy) return _drugi;
	else if (_drugi == _pierwszy) return 0;
	else return 0;
}
