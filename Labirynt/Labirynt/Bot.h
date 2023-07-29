#pragma once
#include "Gracz.h"
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
class Bot : public Gracz
{
private:
	int Delay; // opoznienie w ms
public:
	Bot();
	~Bot();
	Bot& operator=(const Bot& _bot);
	void setNazwa();
	void Ruch();
	char * ZwrocPozycje(int _sprawdzana);
	void setPoziomTrudnosci();
	void setDelay(int _PoziomTrudnosci);
	int getDelay();
};