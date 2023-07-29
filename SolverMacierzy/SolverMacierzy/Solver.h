#pragma once
#include "Macierz.h"

template <typename T>
class Solver {
	Macierz<T>& mat;
	const int n;

	void skalujWiersz(int ktory, T skala);
	void addWiersze(int ktory, int do_ktorego, T skala = 1.0);

public:
	Solver(Macierz<T>& mat_) : mat(mat_), n(mat.getIleWierszy()) {}

	void rozwiaz();
};

template <typename T>
void Solver<T>::skalujWiersz(int ktory, T skala) {
	// mnozy kazdy element wiersza przez skalar
	for (int i = 0; i < n + 1; ++i) {
		mat.element(ktory, i) *= skala;
	}
}

template <typename T>
void Solver<T>::addWiersze(int ktory, int do_ktorego, T skala) {
	// dodaje pierwszy rzad do drugiego, mnozac wczesniej jego wartosci przez skalar
	for (int i = 0; i < n + 1; ++i) {
		mat.element(do_ktorego, i) += skala * mat.element(ktory, i);
	}
}

template <typename T>
void Solver<T>::rozwiaz() {
	try 
	{// rozwiazuj kazda kolumne z osobna
		for (int i = 0; i < n; ++i) {
			// znormalizuj dany wiersz (na diagonalnej musza byc same 1)
			T pierwszy = mat.element(i, i);
			if (pierwszy == 0) throw 'b';
			skalujWiersz(i, 1.0 / pierwszy);
			// uzyj i-tego wiersza do wyeliminowania wszystkich pozostalych
			for (int j = 0; j < n; ++j) {
				if (i == j) continue; // nie wyeliminuj siebie
				// przemnoz wiersz przez te wartosc, by wyeliminowac element na i-tym miejscu
				T skala = -1.0 * mat.element(j, i);
				addWiersze(i, j, skala);
			}
		}
	}
	catch (char KodBledu)
	{
		std::cout << "Blad dzielenia przez '0'!" << std::endl;
	}
}
