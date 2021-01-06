#pragma once
#include <string>
#include "Lamp.h"

class DimmableLamp :
	public Lamp
{
public:
	DimmableLamp();
	DimmableLamp(int dimRange, int dimBrightness);
	DimmableLamp(std::string type, std::string brand, int pwrValue, std::string pwrUnit, int dimRange, int dimBrightness);
	void setBrightness(int value);                  // f�nyer� be�ll�t�sa
	int getBrightness();							// f�nyer� lek�rdez�se
	std::string toString() const override;			// adatok ki�r�shoz

private:
	const int range;    // f�nyer� intervallum: [0; range]
	int brightness;     // aktu�lis f�nyer�
};