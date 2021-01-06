#pragma once
#include <string>
#include "Lamp.h"
#include "DimmableLamp.h"


class LightList							// a láncolt lista elemei
{
public:
	LightList(Lamp& lamptoadd);			// default konstruktor

	void setLamp(Lamp item);			// lámpa elhelyezése az adott láncelembõl
	Lamp getLamp() const;				// lámpa kiolvasása az adott láncelembõl
	void setNext(LightList* nextitem);	// a következõ láncelem címének beállítása
	LightList* getNext() const;			// a következõ láncelem címének kiolvasása

private:
	Lamp lampItem;						// a lámpa
	int index;							// a lámpa sorszáma a láncban
	LightList* nextLampItem;			// hivatkozás a következõ láncelemre
};


class Storage
{
	Storage(Lamp& firstlamp);					// default konstruktor
	~Storage();									// destruktor
	Storage(const Storage& other);				// copy konstruktor
	Storage& operator=(const Storage& other);	// copy assignment

	void addLamp(Lamp& lamptoadd);				// lámpa hozzáadása a listához
	void removeLampByCount(int c);				// lámpa törlése léptetéssel számolva
	void removeLampByIndex(int index);			// adott indexû lámpa törlése
	void removeLampByLamp(Lamp& lamp);			// egy adott lámpa törlése
	int countLamps();							// lámpák összeszámlálása
	std::string toString() const;				// lista szöveggé alakítása kiíráshoz


private:
	LightList* rootLamp;						// hivatkozás az elsõ láncelemre
};

