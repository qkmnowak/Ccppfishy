// funkcja: y = Asin(Bx) + C
#define _CRT_SECURE_NO_WARNINGS
#define LICZBAWSPOLCZYNNIKOW 3
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

void generuj(double x1, double x2, double *tablicawsp, double *tablicawynikow, int liczbawynikow);
void ustawDziedzine(double *ptr1, double *ptr2);
void ustawWspolczynniki(double *tablicawsp);
void zaszum(double *tablicawynikow, double *tablicaszumow, int liczbawynikow);
void zapisz(double *tablica, int liczbawynikow);
void posortuj(double *tablica, int rozmiar);
int ustawRozmiarTablicyWynikowej();
double *wczytaj(int *RozmiarWczytany);
double *filtruj(double *zaszumiona);


int main()
{
	srand(time(NULL));
	//setlocale(LC_ALL, "polish_poland");
	double x1, x2;
	double *ptr1, *ptr2;
	ptr1 = &x1;
	ptr2 = &x2;
	//do dziedziny

	double tablicawsp[LICZBAWSPOLCZYNNIKOW]; //niezmienna

	int LiczbaWynikow = ustawRozmiarTablicyWynikowej();
	int PoczatkowaLiczbaWynikow = LiczbaWynikow;
	double *tablicawynikow;
	tablicawynikow = malloc(LiczbaWynikow * sizeof(*tablicawynikow));
	double *tablicaszumow;
	tablicaszumow = malloc(LiczbaWynikow * sizeof(*tablicawynikow));
	double *tablicawczytywana; // alokowana przy wczytywaniu
	
	int RozmiarWczytany;
	int *RozmiarWczytanyPTR;
	RozmiarWczytanyPTR = &RozmiarWczytany;
	//do rozmiaru wczytywanej tablicy

	
	int wybor = 0; //do menu
	int wyniki = 0; //czy wygenerowano/wczytano wyniki?
	int szum = 0; //czy wygenerowano szum?
	int filtr = 0; //czy przefiltrowano sygnal?
	int petla = 1; // do obracania menu

	while (petla)
	{
		printf("Menu:\n 1. Generowanie sygnalu\n 2. Wczytanie sygnalu z pliku\n 3. Zaszumienie sygnalu\n 4. Filtracja sygnalu\n 5. Zapisanie sygnalu \n 6. Wyjscie z programu \n \n UWAGA: Wybranie jakiejkolwiek innej opcji poza (1-5) spowoduje automatyczne wyjscie z programu!\n\n Podaj swoj wybor: \n");
		scanf("%d", &wybor);
		switch (wybor)
		{
		case 1:	
			system("cls");
			LiczbaWynikow = PoczatkowaLiczbaWynikow;
			ustawWspolczynniki(tablicawsp);
			ustawDziedzine(ptr1, ptr2);
			generuj(x1, x2, tablicawsp, tablicawynikow, LiczbaWynikow);
			wyniki = 1;
			break;
		case 2:
			system("cls");
			tablicawczytywana = wczytaj(RozmiarWczytanyPTR);
			printf("Wczytano dane z pliku \n");
			wyniki = 2;
			break;
		case 3:
			system("cls");
			if (wyniki == 1)
			{
				zaszum(tablicawynikow, tablicaszumow, LiczbaWynikow);
				szum = 1;
			}
			else if (wyniki == 2)
			{
				LiczbaWynikow = RozmiarWczytany;
				zaszum(wczytaj(RozmiarWczytanyPTR), tablicaszumow, LiczbaWynikow);
				szum = 1;
			}
			else printf("Blad! Brak wynikow, ktore mozna zaszumiec - wygeneruj lub wczytaj funkcje! \n");
			break;
		case 4:
			system("cls");
			if (szum == 1)
			{
				 //filtruj, gdy napiszesz zmien printfa
				printf("Funkcja do filtracji nie istnieje \n");
			}
			else printf("Blad! Nie wygenerowano szumu - brak mozliwosci filtracji! \n");
			break;
		case 5:
			system("cls");
			int x;
			printf("Co chcesz zapisac do pliku .csv? \n 1. Sygnal \n 2. Szum \n 3. Sygnal odfiltrowany \n");
			scanf("%d", &x);
			if (x < 1) x = 1;
			if (x > 3) x = 3;
			if (x == 1)
			{ 
				if (wyniki == 1)
				{
					zapisz(tablicawynikow, LiczbaWynikow);
					printf("Zapis wykonany poprawnie \n");
				}
				else printf("Blad! Nie wygenerowano sygnalu - brak mozliwosci zapisu! \n");
			}
			if (x == 2)
			{
				if (szum == 1)
				{
					zapisz(tablicaszumow, LiczbaWynikow);
					printf("Zapis wykonany poprawnie \n");
				}
				else printf("Blad! Nie wygenerowano szumu - brak mozliwosci zapisu! \n");
			}
			if (x == 3)
			{
				if (filtr == 1)
				{
					printf("Zapis wykonany poprawnie \n");
				}
				else printf("Blad! Nie przefiltrowano sygnalu - brak mozliwosci zapisu! \n");
			}
			break;
		default:
			petla = 0;
			printf("Zamykanie programu... \n");
			break;
		}
	}

	free(tablicawynikow);
	free(tablicaszumow);
	
	system("pause");

	return 0;
}

void generuj(double x1, double x2, double *tablicawsp, double *tablicawynikow, int liczbawynikow)
{
	double x = x1;
	double krok = (x2-x1)/liczbawynikow;
	// funkcja: y = Asin(Bx) + C
	int i = 0;
	do
	{
		tablicawynikow[i] = (tablicawsp[0])*sin(tablicawsp[1] * (x)) + tablicawsp[2];
		printf("SYGNAL: %lf \n", tablicawynikow[i]);
		if (i == liczbawynikow - 1) break;
		else i++;
		x = x + krok;
	} while (x <= x2);
}

void ustawDziedzine(double *ptr1, double *ptr2)
{
	double x1, x2;
	printf("Podaj dziedzine funkcji (x1<x2) w kolejnosci: x1, x2: \n");
	scanf("%lf", &x1);
	scanf("%lf", &x2);

	while (x1 == x2)
	{
		printf("Blad! x1 i x2 nie moga przyjmowac tej samej wartosci! Wprowadz zakres dziedziny ponownie: \n");
		scanf("%lf", &x1);
		scanf("%lf", &x2);
	}
	if (x1 < x2);
	else if (x2 < x1)
	{
		double temp;
		temp = x1;
		x1 = x2;
		x2 = temp;
	}
	*ptr1 = x1;
	*ptr2 = x2;
}


void ustawWspolczynniki(double *tablicawsp)
{
	double A, B, C;
	printf("Podaj wspolczynniki w kolejnosci: A, B, C (dla funkcji y = Asin(Bx) + C) \n");
	scanf("%lf", &A);
	if (A == 0) A = 1; //niekoniecznie
	tablicawsp[0] = A;
	scanf("%lf", &B);
	if (B == 0) B = 1; //niekoniecznie
	tablicawsp[1] = B;
	scanf("%lf", &C);
	tablicawsp[2] = C;
}

void zaszum(double *tablicawynikow, double *tablicaszumow, int liczbawynikow)
{
	realloc(tablicaszumow, (liczbawynikow*sizeof(double)));
	double amplituda;
	double temp;
	int x;
	for (int i = 0; i < liczbawynikow; i++)
	{
		x = rand() % 100 + 1;
		if (x < 20)
		{
			temp = (rand() % 13 + 7);
			amplituda = temp / 10;
			tablicaszumow[i] = tablicawynikow[i] * amplituda;
		}
		else tablicaszumow[i] = tablicawynikow[i];
		printf("ZASZUMIONY: %lf \n", tablicaszumow[i]);
	}
}

void zapisz(double *tablica, int liczbawynikow)
{
		FILE* plik;
		plik = fopen("plik.csv", "w");
		if (plik == NULL)
		{
			printf("Blad otwierania pliku! \n");
		}
		else
		{
			for (int i = 0; i < liczbawynikow; i++)
			{
				fprintf(plik, "%lf \n", tablica[i]);
			}
			fclose(plik);
		}
}

int ustawRozmiarTablicyWynikowej()
{
	int rozmiar;
	printf("Podaj rozmiar tablicy wynikowej (z zakresu <100;2000>): \n");
	scanf("%d", &rozmiar);
	if (rozmiar < 100) rozmiar = 100;
	if (rozmiar > 2000) rozmiar = 2000;
	return rozmiar;
}

double* wczytaj(int *RozmiarWczytany)
{
	double CzyEOF;
	double *tablica;
	int rozmiarTablicy = 0;
	int i = 0;	
	tablica = malloc(1 * sizeof(*tablica)); 
	FILE* plik;
	plik = fopen("plik.csv", "r");
	if (plik == NULL)
	{
		printf("Blad otwierania pliku! \n");
	}
	else
	{
		while (fscanf(plik, "%lf", &CzyEOF) != EOF)
		{
			rozmiarTablicy++;
			*RozmiarWczytany = rozmiarTablicy;
			double *temp;
			temp = realloc(tablica, (rozmiarTablicy * sizeof(*tablica)));
			if (temp != NULL)
			{
				tablica = temp;
				tablica[i] = CzyEOF;
				i++;
			}
			else
			{
				printf("Blad alokacji tablicy! Nie wszystkie dane zostana skopiowane z pliku! \n");
				free (temp);
				break;
			}
		}
	}
	fclose(plik);

	return tablica;
}

void posortuj(double *tablica, int rozmiar)
{
	int i, n;
	double temp;
	for (i = 0; i < rozmiar-1; i++)
	{
		for (n = 0; n < rozmiar - 1 - i; n++)
		{
			if (tablica[n] > tablica[n + 1])
			{
				temp = tablica[n + 1];
				tablica[n + 1] = tablica[n];
				tablica[n] = temp;
			}
		}
	}
}

double *filtruj(double *zaszumiona)
{

}