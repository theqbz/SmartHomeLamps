#pragma once
#include <string>

struct Power {
	const int value;						// a lámpa teljesítményének mérõszáma
	const std::string unit;					// a lámpa teljesítményének mértékegysége
	Power(int val, std::string unitName);
};


class Lamp
{
public:
	Lamp();
	Lamp(std::string type, std::string brand, int pwrValue, std::string pwrUnit);
	Lamp& operator=(Lamp& other);

	void setState(bool OnOff);				// ki-be kapcsoló
	bool getState();						// ki-be kapcsolt állapot lekérdezése
	void setRoom(std::string);				// a lámpa helyének beállítása
	std::string getRoom() const;			// a lámpa helyének lekérdezése
	std::string getType() const;			// típus kiolvasása
	std::string getBrand() const;			// márka kiolvasása
	int getPower() const;					// teljesítmény kiolvasása
	virtual std::string toString() const;	// adatok egyben szövegként kiíráshoz

protected:
	bool state;						// ki-be kapcsolt állapot
	std::string room;				// lámpa helye
	const std::string lampName;			// a lámpa tipusa
	const std::string brand;		// a lámpa márkája
	const Power pwr;				// teljesítmény
};

