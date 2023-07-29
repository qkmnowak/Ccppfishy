#include <iostream>
#include "Macierz.h"
#include "Solver.h"
#include <fstream>
#include <string>
#include <vector>
#include <exception>
using namespace std;

void demo3(Macierz<double>& m) {
	m.element(0, 0) = 2.2;
	m.element(0, 1) = -1.5;
	m.element(0, 2) = 0.6;
	m.wolny(0) = 1.3;
	m.element(1, 0) = -0.7;
	m.element(1, 1) = 1.2;
	m.element(1, 2) = 1.8;
	m.wolny(1) = 1.85;
	m.element(2, 0) = 1.2;
	m.element(2, 1) = 0.8;
	m.element(2, 2) = -2.1;
	m.wolny(2) = -4.55;
}

void demo4(Macierz<double>& m) {
	m.element(0, 0) = -0.2;
	m.element(0, 1) = 1.1;
	m.element(0, 2) = 0.1;
	m.element(0, 3) = 0.9;
	m.wolny(0) = 1.95;
	m.element(1, 0) = -1.2;
	m.element(1, 1) = 3.5;
	m.element(1, 2) = -2.6;
	m.element(1, 3) = 1.9;
	m.wolny(1) = 5.43;
	m.element(2, 0) = 0.8;
	m.element(2, 1) = -2.3;
	m.element(2, 2) = 1.2;
	m.element(2, 3) = -0.8;
	m.wolny(2) = -3.28;
	m.element(3, 0) = 0.2;
	m.element(3, 1) = -1.7;
	m.element(3, 2) = 1.9;
	m.element(3, 3) = 1.3;
	m.wolny(3) = -0.05;
}


string SprawdzTypMacierzy(ifstream& _plik)
{
	std::string typ;
	getline(_plik, typ);
	return typ;
}

int ObliczLiczbeWierszy(std::string _nazwa)  
{
	fstream plik;
	string odczyt;
	vector<string> wiersze;
	int LiczbaWierszy = 0;

	plik.close(); 
	try
	{
		plik.open(_nazwa, std::ifstream::in);
		if (plik.good() == false) throw "Plik nie istnieje!";
		getline(plik, odczyt); //typ to nie czesc macierzy
		while (getline(plik, odczyt))
		{
			wiersze.push_back(odczyt);
			LiczbaWierszy++;
		}
		plik.close();
		plik.open(_nazwa, std::ifstream::in);
		if (plik.good() == false) throw "Plik nie istnieje!";
		return LiczbaWierszy;
	}
	catch (const char* KodBledu)
	{
		std::cout << KodBledu << std::endl;
	}
}

template<typename T>
void UstawMacierz(int _rozmiar)
{
	Macierz<T> m(_rozmiar);
	try
	{
		m.AlokujPamiec();
	}
	catch (int KodBledu)
	{
		std::cout << "Blad alokacji!" << std::endl;
	}

	m.pokaz();
	std::cout << std::endl;

	Solver<T> s(m);
	s.rozwiaz();
	m.pokaz(); 
}

int main() {
	/*Macierz<double> m(3);
	try
	{
		m.AlokujPamiec();
	}
	catch(int KodBledu)
	{
		std::cout << "Blad alokacji!" << std::endl;
	}
	demo3(m);
	m.pokaz();
	std::cout << std::endl;

	Solver<double> s(m);
	s.rozwiaz();
	m.pokaz();*/
	
	string TypMacierzy;
	string NazwaPliku;
	string RozszerzeniePliku(".txt");
	ifstream plik;
	int WielkoscMacierzy;

	cout << "Podaj nazwe pliku do odczytu: " << endl;
	cin >> NazwaPliku;
	NazwaPliku = NazwaPliku + RozszerzeniePliku;
	plik.open(NazwaPliku, std::ifstream::in);
	if (plik.good() == false)
	cout << "Wystapil blad!" <<endl;
	else
	{
		TypMacierzy = SprawdzTypMacierzy(plik);
		WielkoscMacierzy = ObliczLiczbeWierszy(NazwaPliku);
		if (TypMacierzy == "F") 
		{
			UstawMacierz<float>(WielkoscMacierzy);
		}
		else if (TypMacierzy == "D")
		{
			UstawMacierz<double>(WielkoscMacierzy);
		}
	}
	plik.close();
	
	system("pause");
	return 0;
}
