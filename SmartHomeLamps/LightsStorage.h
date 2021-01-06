#pragma once
#include <string>
#include "Lamp.h"
#include "DimmableLamp.h"


class LightList							// a l�ncolt lista elemei
{
public:
	LightList(Lamp& lamptoadd);			// default konstruktor

	void setLamp(Lamp item);			// l�mpa elhelyez�se az adott l�ncelemb�l
	Lamp getLamp() const;				// l�mpa kiolvas�sa az adott l�ncelemb�l
	void setNext(LightList* nextitem);	// a k�vetkez� l�ncelem c�m�nek be�ll�t�sa
	LightList* getNext() const;			// a k�vetkez� l�ncelem c�m�nek kiolvas�sa

private:
	Lamp lampItem;						// a l�mpa
	int index;							// a l�mpa sorsz�ma a l�ncban
	LightList* nextLampItem;			// hivatkoz�s a k�vetkez� l�ncelemre
};


class Storage
{
	Storage(Lamp& firstlamp);					// default konstruktor
	~Storage();									// destruktor
	Storage(const Storage& other);				// copy konstruktor
	Storage& operator=(const Storage& other);	// copy assignment

	void addLamp(Lamp& lamptoadd);				// l�mpa hozz�ad�sa a list�hoz
	void removeLampByCount(int c);				// l�mpa t�rl�se l�ptet�ssel sz�molva
	void removeLampByIndex(int index);			// adott index� l�mpa t�rl�se
	void removeLampByLamp(Lamp& lamp);			// egy adott l�mpa t�rl�se
	int countLamps();							// l�mp�k �sszesz�ml�l�sa
	std::string toString() const;				// lista sz�vegg� alak�t�sa ki�r�shoz


private:
	LightList* rootLamp;						// hivatkoz�s az els� l�ncelemre
};

