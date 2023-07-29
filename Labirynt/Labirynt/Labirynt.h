#pragma once
#include <iostream>
#include <fstream>
#include "Gracz.h"
#include "Bot.h" 


class Labirynt 
{
private:
	int w, k; //wiersze, kolumny
	char **plansza;
	int NumerLabiryntu;
	Gracz Gracz1;
	Bot Bot1;
	char BotCzyGracz;
	bool CzyLabiryntOk;
public:
	Labirynt();
	~Labirynt();
	Labirynt& operator=(const Labirynt& _lab);
	Labirynt(const Labirynt& _stary);
	void WiadomoscPowitalna();
	void WybierzLabirynt();
	void WczytajLabirynt();
	void ZnajdzPozycje();
	void PodajPozycje(int _w, int _k);
	void WyswietlPlansze();
	void WyczyscEkran();
	void Graj();
	void WylonZwyciezce(time_t CzasDoZakonczeniaObslugiMenu, time_t CzasDoZakonczeniaGryGracza, time_t CzasDoZakonczeniaGryBota);
	template <typename T> T Porownaj(T _pierwszy, T _drugi);
};

/*
legenda w pliku tekstowym:
g - Gracz
w - wyjscie
4 - sciana
3 - ' '
*/

