#pragma once
#include <string>

struct Power {
	const int value;						// a l�mpa teljes�tm�ny�nek m�r�sz�ma
	const std::string unit;					// a l�mpa teljes�tm�ny�nek m�rt�kegys�ge
	Power(int val, std::string unitName);
};


class Lamp
{
public:
	Lamp();
	Lamp(std::string type, std::string brand, int pwrValue, std::string pwrUnit);

	void setState(bool OnOff);				// ki-be kapcsol�
	bool getState();						// ki-be kapcsolt �llapot lek�rdez�se
	std::string getType() const;			// t�pus kiolvas�sa
	std::string getBrand() const;			// m�rka kiolvas�sa
	int getPower() const;					// teljes�tm�ny kiolvas�sa
	virtual std::string toString() const;	// adatok egyben sz�vegk�nt ki�r�shoz

protected:
	bool state;						// ki-be kapcsolt �llapot
	const std::string type;			// a l�mpa tipusa/markaja
	const std::string brand;		// a l�mpa m�rk�ja
	const Power pwr;				// teljes�tm�ny
};

