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
	void setBrightness(int value);                  // fényerõ beállítása
	int getBrightness();							// fényerõ lekérdezése
	std::string toString() const override;			// adatok kiíráshoz

private:
	const int range;    // fényerõ intervallum: [0; range]
	int brightness;     // aktuális fényerõ
};