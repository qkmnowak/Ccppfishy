#pragma once

#include <iomanip>
#include <vector>
#include <iostream>
using namespace std;

template <typename T>
class Macierz {
	const int ile_wierszy;
	const int dlugosc_wiersza;
	T* dane = nullptr;
	T** wiersze = nullptr;


public:
	Macierz(int _wiersze = 0) : ile_wierszy(_wiersze), dlugosc_wiersza(_wiersze + 1) {}
	~Macierz();
	// Usuniety konstruktor kopiujacy i operator przypisania powoduje,
	// ze obiektow tej klasy nie da sie przekazywac przez wartosc.
	// Jest to rowniez sposob dotrzymania zasady trzech.
	void operator=(const Macierz& other_) = delete;
	Macierz(const Macierz& other_) = delete;

	void zeruj();
	void pokaz() const;
	void AlokujPamiec();

	int getIleWierszy() { return ile_wierszy; }
	T& element(int i, int j);
	T& wolny(int i);
	void OdczytajZPliku(string _nazwa);
};

template<typename T>
Macierz<T>::~Macierz()
{
	delete[] wiersze;
	delete[] dane;
}

template <typename T>
void Macierz<T>::zeruj() {
	for (int i = 0; i < ile_wierszy*dlugosc_wiersza; ++i) {
		dane[i] = 0;
	}
}

template <typename T>
void Macierz<T>::AlokujPamiec()
{
	int i, j = 0;
	dane = new T[ile_wierszy * dlugosc_wiersza];
	wiersze = new T*[ile_wierszy];
	for (i = 0; i < ile_wierszy; i++)
	{
		wiersze[i] = &dane[j];
		j += dlugosc_wiersza;
	}

}

template <typename T>
void Macierz<T>::pokaz() const {
	using std::cout;
	using std::endl;
	using std::setw;
	using std::fixed;
	using std::setprecision;
	for (int i = 0; i < ile_wierszy; ++i) {
		for (int j = 0; j < dlugosc_wiersza - 1; ++j) {
			cout << setw(8) << setprecision(4) << fixed << wiersze[i][j];
		}
		cout << "  |" << setw(8) << setprecision(4) << wiersze[i][dlugosc_wiersza - 1] << endl;
	}
}

template <typename T>
T& Macierz<T>::wolny(int i)
{
	try
	{
		if (i < 0) throw 1;
		return wiersze[i][dlugosc_wiersza - 1];
	}
	catch (int KodBledu)
	{
		std::cout << "Element macierzy nie moze byc ujemny lub wykraczac poza rozmiar macierzy!" << std::endl;
	}
}

template <typename T>
T& Macierz<T>::element(int i, int j)
{
	try
	{
		if (i > ile_wierszy || i < 0) throw 1;
		if (j > dlugosc_wiersza || j < 0) throw 2;
		return wiersze[i][j];
	}
	catch (int KodBledu)
	{
		if (KodBledu == 1)
			std::cout << "Wiersze macierzy nie moga byc ujemne i wykraczac poza rozmiar macierzy!" << std::endl;
		if (KodBledu == 2)
			std::cout << "Elemety macierzy nie moga byc ujemne i wykraczac poza rozmiar macierzy!" << std::endl;
	}

}

/*template <typename T>
void Macierz<T>::OdczytajZPliku(string _nazwa)
{
	vector <char> dane;
	string odczyt;
	fstream plik;

	plik.open(_nazwa, ifstream::in);
	if (plik.good() == false) std::cout << "Wybrany plik nie istnieje! " << endl;
	else
	{


	}
}
*/