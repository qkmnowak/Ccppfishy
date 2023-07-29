#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>



struct Obraz
{
	char format[2];
	int szerokosc;
	int wysokosc;
	int szaroscMax;
	int** piksele;
	char nazwa[50];
};

void wczytajObraz(struct Obraz *picture);
void zapiszObraz(struct Obraz *picture, int KtoryAktywny);
struct Obraz* DodajObraz(struct Obraz *BazaObrazow, int *LiczbaObrazow);
void wyswietlListeObrazow(struct Obraz *BazaObrazow, int LiczbaObrazow, int KtoryAktywny);
int wybierzAktywnyObraz(int LiczbaObrazow);
void usunObraz(struct Obraz** picture, int *LiczbaObrazow);
void progowanie(struct Obraz *picture, int KtoryAktywny);
void SoliPieprz(struct Obraz *picture, int KtoryAktywny);
void Histogram(struct Obraz *picture, int KtoryAktywny);
void Obrot(struct Obraz *picture, int KtoryAktywny);


int main()
{
	srand((unsigned int)time(NULL));
	int KtoryAktywny = -1;
	struct Obraz *BazaObrazow;
	int LiczbaObrazow = 0; 
	BazaObrazow = calloc(1, sizeof(struct Obraz)); 


	int menu = 1, wybor = 0;
	while (menu)
	{
		printf("Menu: \n 1 - Wczytywanie obrazu \n 2 - Zapisywanie obrazu \n 3 - Wyswietlanie listy obrazow w bazie \n 4 - Wybieranie aktywnego obrazu \n 5 - Usuwanie obrazu z bazy \n 6 - Progoawnie aktywnego obrazu \n 7 - Zaszumianie obrazu ('sol i pieprz') \n 8 - Stworzenie histogramu obrazu i zapis do pliku .csv \n 9 - Obrot obrazu \n 10 - Zamykanie programu \n Podaj swoj wybor: \n");
		while (!scanf("%d", &wybor))
		{
			while ('\n' != getchar());
			printf("Wprowadz liczbe, nie znak: \n");
		}
		switch (wybor)
		{
		case 1:
			system("cls");
			BazaObrazow = DodajObraz(BazaObrazow, &LiczbaObrazow);
			wczytajObraz(&BazaObrazow[LiczbaObrazow-1]); 
			break;
		case 2:
			system("cls");
			if (KtoryAktywny > 0) zapiszObraz(BazaObrazow, KtoryAktywny);
			else printf("Brak aktywnego obrazu do zapisu! Wybierz ponownie obraz, ktory ma byc zapisywany do pliku .pgm! \n");
			break;
		case 3: 
			system("cls");
			wyswietlListeObrazow(BazaObrazow, LiczbaObrazow, KtoryAktywny);
			break;
		case 4:
			system("cls");
			wyswietlListeObrazow(BazaObrazow, LiczbaObrazow, KtoryAktywny);
			KtoryAktywny = wybierzAktywnyObraz(LiczbaObrazow); 
			break;
		case 5:
			system("cls");
			if (LiczbaObrazow > 0)
			{
				wyswietlListeObrazow(BazaObrazow, LiczbaObrazow, KtoryAktywny);
				usunObraz(&BazaObrazow, &LiczbaObrazow);
				KtoryAktywny = -1;
			}
			else printf("Brak obrazow w bazie! Najpierw dodaj obrazy, jesli chcesz jakis usunac \n");
			break;
		case 6:
			system("cls");
			if (KtoryAktywny > 0) progowanie(BazaObrazow, KtoryAktywny);
			else printf("Brak aktywnego obrazu do progowania! Wybierz aktywny obraz aby kontynuowac \n");
			break;
		case 7:
			system("cls");
			if (KtoryAktywny > 0) SoliPieprz(BazaObrazow, KtoryAktywny);
			else printf("Brak aktywnego obrazu do zaszumienia! Wybierz aktywny obraz aby kontynuowac \n");
			break;
		case 8:
			system("cls");
			if (KtoryAktywny > 0) Histogram(BazaObrazow, KtoryAktywny);
			else printf("Brak aktywnego obrazu na ktorego podstawie moznaby stworzyc histogram! Wybierz aktywny obraz aby kontynuowac \n");
			break;
		case 9:
			system("cls");
			if (KtoryAktywny > 0)
			{
				printf("Podaj kat obrotu (90/180/270 stopni) (w przypadku podania innego kata zostanie on ustawiony na 90 stopni): \n");
				int obrot, k = 1;
				while (!scanf("%d", &obrot))
				{
					while ('\n' != getchar());
					printf("Wprowadz liczbe, nie znak: \n");
				}
				if (obrot == 90) k = 1;
				if (obrot == 180) k = 2;
				if (obrot == 270) k = 3;
				for (int i = 0; i < k; i++)
				{
					Obrot(BazaObrazow, KtoryAktywny);
				}
			}
			else printf("Brak aktywnego obrazu ktory moznaby obrocic! Wybierz aktywny obraz aby kontynuowac \n");
			break;
		default:
			system("cls");
			menu = 0;
			for (int j = 0; j < LiczbaObrazow; j++)
			{
				for (int i = 0; i < BazaObrazow[j].szerokosc; i++)
				{
					free(BazaObrazow[j].piksele[i]);
				}
				free(BazaObrazow[j].piksele);
			}
			free(BazaObrazow);
			printf("Zamykanie programu... \n");
			break;
		}
	}

	return 0;
}

void wczytajObraz(struct Obraz *picture)
{
	char pgm[] = ".pgm";
	char nazwaPliku[50];
	printf("Podaj nazwe pliku .pgm, ktory chcesz wczytac: \n");
	scanf("%s", nazwaPliku);
	strncat(nazwaPliku, pgm, 4);
	strncpy(picture->nazwa, nazwaPliku, 50);

	FILE* obraz;
	obraz = fopen(nazwaPliku, "r");
	while (obraz == NULL)
	{
		printf("Blad wczytywania obrazu! Plik o podanej nazwie nie istnieje - sprobuj jeszcze raz. \n");
		scanf("%s", nazwaPliku);
		strncat(nazwaPliku, pgm, 4); 
		strncpy(picture->nazwa, nazwaPliku, 50);
		obraz = fopen(nazwaPliku, "r");
	}
	if (obraz !=NULL)
	{
		fgets(picture->format, 4, obraz); 
	
		while (fgetc(obraz) == '#')
		{
			while (fgetc(obraz) != '\n');
		}
		fseek(obraz, -1, SEEK_CUR);
		fscanf(obraz, "%d", &picture->szerokosc);
		while (fgetc(obraz) == '#')
		{
			while (fgetc(obraz) != '\n');
		}
		fseek(obraz, -1, SEEK_CUR);
		fscanf(obraz, "%d", &picture->wysokosc);
		while (fgetc(obraz) == '#')
		{
			while (fgetc(obraz) != '\n');
		}
		fseek(obraz, -1, SEEK_CUR);
		fscanf(obraz, "%d", &picture->szaroscMax);
		while (fgetc(obraz) == '#')
		{
			while (fgetc(obraz) != '\n');
		}
		fseek(obraz, -1, SEEK_CUR);

		//ALOKACJA TABLICY Z PIKSELAMI
		picture->piksele = calloc(picture->szerokosc, sizeof(*picture->piksele)	);
		if (picture->piksele != NULL)
		{
			for (int i = 0; i < picture->szerokosc; i++)
			{
				picture->piksele[i] = calloc(picture->wysokosc, sizeof(picture->piksele));
				if (picture->piksele[i] == NULL)
				{
					for (int j = 0; j < i; j++)
					{
						free(picture->piksele[j]);
					}
					free (picture->piksele);
				}
			}	
		}

		for (int i = 0; i < picture->szerokosc; i++)
		{
			for (int j = 0; j < picture->wysokosc; j++)
			{
				while (fgetc(obraz) == '#')
				{
					while (fgetc(obraz) != '\n');
				}
				fseek(obraz, -1, SEEK_CUR);
				fscanf(obraz, "%d", &picture->piksele[i][j]);
			}
		}

		fclose(obraz);
	}
}

void zapiszObraz(struct Obraz *picture, int KtoryAktywny)
{

	char pgm[] = ".pgm";
	char nazwaPliku[100]; 
	printf("Podaj nazwe, pod ktora plik ma byc zapisany: \n");
	scanf("%s", nazwaPliku);
	strncat(nazwaPliku, pgm, 4);

	FILE* obraz;
	obraz = fopen(nazwaPliku, "w");
	while (obraz == NULL)
	{
		printf("Blad zapisywania obrazu! Podaj inna nazwe \n");
		scanf("%s", nazwaPliku);
		strncat(nazwaPliku, pgm, 4); //!!
		obraz = fopen(nazwaPliku, "w");
	}
	if (obraz != NULL)
	{
		fprintf(obraz, "%c", (picture + (KtoryAktywny - 1))->format[0]);
		fprintf(obraz, "%c", (picture + (KtoryAktywny - 1))->format[1]);
		fprintf(obraz, "%c", (picture + (KtoryAktywny - 1))->format[2]); //wypisz format
		fprintf(obraz, "%d %d \n", (picture + (KtoryAktywny - 1))->szerokosc, (picture + (KtoryAktywny - 1))->wysokosc);
		fprintf(obraz, "%d \n", (picture + (KtoryAktywny - 1))->szaroscMax);

		for (int i = 0; i < (picture + (KtoryAktywny - 1))->szerokosc; i++)
		{
			for (int j = 0; j < (picture + (KtoryAktywny - 1))->wysokosc; j++)
			{
				fprintf(obraz, "%d ", (picture + (KtoryAktywny - 1))->piksele[i][j]);
			}
		}
		printf("Obraz zapisano pomyslnie. \n");
		fclose(obraz);
	}
}

struct Obraz* DodajObraz(struct Obraz *BazaObrazow, int *LiczbaObrazow)
{
	(*LiczbaObrazow)++;
	struct Obraz *temp;
	temp = realloc(BazaObrazow, ((*LiczbaObrazow) * sizeof(struct Obraz)));
	if (temp != NULL)
	{
		BazaObrazow = temp;
	}
	//w przeciwnym wypadku nie rob nic - nie powiekszaj tablicy
	return BazaObrazow;
}

void wyswietlListeObrazow(struct Obraz *BazaObrazow, int LiczbaObrazow, int KtoryAktywny)
{
	printf("Lista obrazow dostepnych w bazie: \n");
	for (int i = 0; i < LiczbaObrazow; i++)
	{
		printf("%d. %s " , (i+1), BazaObrazow[i].nazwa);
		if (i+1 == KtoryAktywny) printf("(aktywny)");
		printf("\n");
	}
}

int wybierzAktywnyObraz(int LiczbaObrazow)
{	
	if (LiczbaObrazow < 1)
	{
		printf("Brak obrazow w bazie! Wczytaj jakis obraz, by moc wybrac aktywny! \n");
		return -1;
	}
	else 
	{
		int wybor = 0;
		printf("Wybierz obraz, ktory ma byc traktowany jako aktywny: \n");
		while (!scanf("%d", &wybor))
		{
			while ('\n' != getchar());
			printf("Wprowadz liczbe, nie znak: \n");
		};
		if (wybor < 1) wybor = 1;
		if (wybor > LiczbaObrazow) wybor = LiczbaObrazow;
		return wybor;
	}
	printf("Obraz zostal wybrany \n");
}

void usunObraz(struct Obraz** picture, int *LiczbaObrazow)
{
	int numerUsuwanego;
	printf("Podaj numer obrazu do usuniecia: \n");
	while (!scanf("%d", &numerUsuwanego))
	{
		while ('\n' != getchar());
		printf("Wprowadz liczbe, nie znak: \n");
	}
	while ((numerUsuwanego < 1) || (numerUsuwanego > *LiczbaObrazow))
	{
		printf("Blad! Podaj numer ponownie! \n");
		while (!scanf("%d", &numerUsuwanego))
		{
			while ('\n' != getchar());
			printf("Wprowadz liczbe, nie znak: \n");
		}
	}

	struct Obraz *temp;
	for (int i = (numerUsuwanego-1); i < *(LiczbaObrazow); i++)
	{
		(*picture)[i] = (*picture)[i + 1]; 
	}

	temp = realloc(*picture, (*LiczbaObrazow - 1) * sizeof(**picture));
	*picture = temp;

	(*LiczbaObrazow)--;

	printf("Obraz usunieto. Prosze ponownie wybrac obraz aktywny w celu kontynuacji pracy \n");
}

void progowanie(struct Obraz *picture, int KtoryAktywny)
{
	int prog;
	printf("Podaj wartosc progu (max %d): \n", ((picture + (KtoryAktywny - 1))->szaroscMax));
	while (!scanf("%d", &prog))
	{
		while ('\n' != getchar());
		printf("Wprowadz liczbe, nie znak: \n");
	}
	if (prog < 1) prog = 1;
	if (prog > ((picture + (KtoryAktywny - 1))->szaroscMax)) prog = ((picture + (KtoryAktywny - 1))->szaroscMax);

	for (int i = 0; i < ((picture + (KtoryAktywny - 1))->szerokosc); i++)
	{
		for (int j = 0; j < ((picture + (KtoryAktywny - 1))->wysokosc); j++)
		{
			if (((picture + (KtoryAktywny - 1))->piksele[i][j]) > prog) ((picture + (KtoryAktywny - 1))->piksele[i][j]) = ((picture + (KtoryAktywny - 1))->szaroscMax);
			if (((picture + (KtoryAktywny - 1))->piksele[i][j]) <= prog) ((picture + (KtoryAktywny - 1))->piksele[i][j]) = 0;
		}
	}
	printf("Progowanie wykonane poprawnie - zapisz obraz by zobaczyc efekt \n");
}

void SoliPieprz(struct Obraz *picture, int KtoryAktywny)
{
	int PikselMax = ((picture + (KtoryAktywny - 1))->szaroscMax);
	
	int StopienZaszumienia;
	printf("Jak wysoki ma byc stopien zaszumienia 1proc - 100proc? \n");
	while (!scanf("%d", &StopienZaszumienia))
	{
		while ('\n' != getchar());
		printf("Wprowadz liczbe, nie znak: \n");
	}
	if (StopienZaszumienia < 1) StopienZaszumienia = 1;
	if (StopienZaszumienia > 100) StopienZaszumienia = 100;


	int y;
	for (int i = 0; i < ((picture + (KtoryAktywny - 1))->szerokosc); i++)
	{
		for (int j = 0; j < ((picture + (KtoryAktywny - 1))->wysokosc); j++)
		{
			int x = rand() % 100;
			if (x < StopienZaszumienia)
			{
				y = rand() % 100;
				if (y < 50) ((picture + (KtoryAktywny - 1))->piksele[i][j]) = ((picture + (KtoryAktywny - 1))->szaroscMax);
				else ((picture + (KtoryAktywny - 1))->piksele[i][j]) = 0;
			}
		}
	}
}

void Histogram(struct Obraz *picture, int KtoryAktywny)
{
	int PikselMax = ((picture + (KtoryAktywny - 1))->szaroscMax);
	int *Histogram;
	int k;
	Histogram = calloc(((picture + (KtoryAktywny - 1))->szaroscMax), sizeof(int));
	
	for (int i = 0; i < ((picture + (KtoryAktywny - 1))->szerokosc); i++)
	{
		for (int j = 0; j < ((picture + (KtoryAktywny - 1))->wysokosc); j++)
		{
			k = ((picture + (KtoryAktywny - 1))->piksele[i][j]);
			Histogram[k]++;
		}
	}
	char csv[] = ".csv";
	char nazwaPliku[100];
	printf("Podaj nazwe, pod ktora plik ma byc zapisany: \n");
	scanf("%s", nazwaPliku);
	strncat(nazwaPliku, csv, 4);

	FILE* plik;
	plik = fopen(nazwaPliku, "w");
	while (plik == NULL)
	{
		printf("Blad zapisywania obrazu! Podaj inna nazwe \n");
		scanf("%s", nazwaPliku);
		strncat(nazwaPliku, csv, 4);
		plik = fopen(nazwaPliku, "w");
	}
	if (plik != NULL)
	{
		for (int i = 0; i < ((picture + (KtoryAktywny - 1))->szaroscMax); i++)
		{
			fprintf(plik, "%d \n", Histogram[i]);
		}
		fprintf(plik, "\n");
		for (int i = 0; i < ((picture + (KtoryAktywny - 1))->szaroscMax); i++)
		{
			fprintf(plik, "%d \n", i);
		}
		printf("Histogram zapisano pomyslnie. \n");
		fclose(plik);
	}
}

void Obrot(struct Obraz *picture, int KtoryAktywny)
{
	struct Obraz *temp;
	int nowaszerokosc = ((picture + (KtoryAktywny - 1))->wysokosc);
	int nowawysokosc = ((picture + (KtoryAktywny - 1))->szerokosc);
	temp = calloc(1, sizeof(struct Obraz));

	temp->piksele = calloc(nowaszerokosc, sizeof(*temp->piksele));
	if (temp->piksele != NULL)
	{
		for (int i = 0; i < nowaszerokosc; i++)
		{
			temp->piksele[i] = calloc(nowawysokosc, sizeof(temp->piksele));
			if (temp->piksele[i] == NULL)
			{
				for (int j = 0; j < i; j++)
				{
					free(temp->piksele[j]);
				}
				free(temp->piksele);
			}
		}
	}

	for (int j = 0; j < (nowaszerokosc); j++)
	{
		for (int i = 0; i < (nowawysokosc); i++)
		{
			temp->piksele[j][i] = ((picture + (KtoryAktywny - 1))->piksele)[nowawysokosc - i - 1][j];
		}
	}

	for (int i = 0; i < ((picture + (KtoryAktywny - 1))->szerokosc); i++)
	{
		free((picture + (KtoryAktywny - 1))->piksele[i]);
	}
	free((picture + (KtoryAktywny - 1))->piksele);
	(picture + (KtoryAktywny - 1))->piksele = temp->piksele;
	(picture + (KtoryAktywny - 1))->szerokosc = nowaszerokosc;
	(picture + (KtoryAktywny - 1))->wysokosc = nowawysokosc;
}