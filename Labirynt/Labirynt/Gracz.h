#pragma once
#include <iostream>
#include <string>
using namespace std;

class Gracz 
{
protected:
	string Nazwa;
	char * Pozycja;
	char * PozW;
	char * PozA;
	char * PozS;
	char * PozD;
	bool GraSkonczona;
public:
	Gracz();
	~Gracz();
	Gracz& operator=(const Gracz& _gracz);
	void ResetPozycji();
	void setPozW(char * _pozycja);
	void setPozA(char * _pozycja);
	void setPozS(char * _pozycja);
	void setPozD(char * _pozycja);
	void setPozycja(char * _pozycja);
	string getNazwa();
	void setNazwa();
	void Ruch(char _kierunek);
	void test();
	bool getGraSkonczona();
};
