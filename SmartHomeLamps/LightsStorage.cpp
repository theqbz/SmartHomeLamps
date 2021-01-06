#include "LightsStorage.h"

Storage::Storage(Lamp& firstlamp)
	:rootLamp(new LightList(firstlamp)) {}

Storage::~Storage() {
	LightList* LampToDelete;						// mutat� az aktu�lisan t�rlend� l�ncelemre
	LampToDelete = rootLamp;						// a mutat� be�ll�t�sa a lista els� elem�re
	while (LampToDelete != nullptr) {				// am�g l�tezik "aktu�lisan t�rlend� l�ncelem" azaz van r� mutat� hivatkoz�s...
		LightList* next = LampToDelete->getNext();	// ...a k�vetkez� l�ncelemre mutat� hivatkoz�s elt�rol�sa t�rl�s el�tt
		delete LampToDelete;						// ...aktu�lis l�ncelem t�rl�se
		LampToDelete = next;						// ...mutat� �t�ll�t�sa a k�vetkez� l�ncelemre
	}
}

void Storage::addLamp(Lamp& lamptoadd) {
	LightList* lastLamp;							// mutat� az aktu�lis listaelemre
	lastLamp = rootLamp;							// a mutat�t az els� listaelemre �ll�tjuk
	while (lastLamp->getNext() != nullptr) {		// am�g "van elem az aktu�lis listaelem ut�n" azaz van a k�vetkez�re mutat� hivatkoz�s...
		lastLamp = lastLamp->getNext();				// ...az aktu�lis listaelem legyen a k�vetkez�
	}
	lastLamp->setNext(new LightList(lamptoadd));	// az utols� listaelem "k�vetkez�" �rt�k�t be�ll�tjuk egy �jonan l�trehozott listaelemre
}

void Storage::removeLampByCount(int c) {
	if (c <= countLamps()) {						// csak akkor kezdjen bele, ha a k�rt sz�m nem nagyobb mint a listaelemek sz�ma
		int i = 0;									// sz�ml�l�
		LightList* previous = nullptr;				// mutat� a "t�rlend� el�tti" listalemre
		LightList* toDelete;						// mutat� a "t�rlend�" listaelemre
		toDelete = rootLamp;						// "t�rlend�" be�ll�t�sa az els� listaelemre
		while (toDelete != nullptr || i < c) {		// am�g a "t�rlend�" elem l�tezik vagy a sz�ml�l� m�g nem �rte el az indexet...
			previous = toDelete;					// a "t�rlend� el�tti" l�ptet�se azaz be�ll�t�sa az aktu�lsian t�rlend�re
			toDelete = toDelete->getNext();			// a "t�rlend�" l�ptet�se azaz be�ll�t�sa a k�vetkez� listaelemre
			i++;									// sz�ml�l� l�ptet�se
		}
		if (toDelete != nullptr) {					// ha nem az�rt l�pett ki a ciklusb�l, mert el�rte az utols� elemet...
			previous->setNext(toDelete->getNext());	// ...akkor a "t�rlend� el�tti" listaelemhez be�ll�tjuk a t�rlend� ut�ni listalelem c�m�t
			delete toDelete;						// ...azt�n t�r�lj�k a t�rlend� listaelemet
		}
		else {										// ha a ciklusban el�rte a lista v�g�t...
			delete toDelete;						// ...akkor az utols�� elemet kell t�r�lni
		}
	}
}

void Storage::removeLampByIndex(int index) {
	if (index <= countLamps()) {					// csak akkor kezdjen bele, ha a k�rt index nem nagyobb mint a listaelemek sz�ma
		int i = 0;									// sz�ml�l�
		LightList* previous = nullptr;				// mutat� a "t�rlend� el�tti" listalemre
		LightList* toDelete;						// mutat� a "t�rlend�" listaelemre
		toDelete = rootLamp;						// "t�rlend�" be�ll�t�sa az els� listaelemre
		while (i < index) {							// am�g el nem �ri a keresett indexet...
			previous = toDelete;					// a "t�rlend� el�tti" l�ptet�se azaz be�ll�t�sa az aktu�lsian t�rlend�re
			toDelete = toDelete->getNext();			// a "t�rlend�" l�ptet�se azaz be�ll�t�sa a k�vetkez� listaelemre
			i++;									// sz�ml�l� l�ptet�se
		}
		delete toDelete;							// a megtal�lt elem t�rl�se
	}
}

int Storage::countLamps() {
	int c = 0;										// sz�ml�l�
	LightList* toCount;								// mutat� az aktu�lisan sz�ml�land� l�ncelemre
	toCount = rootLamp;								// mutat� be�ll�t�sa az els� l�ncelemre
	while (toCount != nullptr) {					// am�g az aktu�lisan sz�ml�land� l�ncelem l�tezik...
		c++;										// ...sz�ml�l� l�ptet�se
		toCount = toCount->getNext();				// ...mutat� �t�ll�t�sa a k�vetkez� l�ncelemre
	}
	return c;
}

std::string Storage::toString() const
{
	std::string toReturn = "\0";					// ebbe gy�lik a l�mpalista a ki�r�shoz
	int i = 0;										// sorsz�moz�s
	LightList* nextToString;						// mutat� az aktu�lis l�ncelemre
	nextToString = rootLamp;						// a mutat� be�ll�t�sa az els� l�ncelemre
	while (nextToString != nullptr) {				// am�g l�tezik az "aktu�lsan hozz�adand� l�ncelem" azaz van r� mutat� hivatkoz�s...
		toReturn += std::to_string(i + 1) + ". "	// ...sorsz�m hozz�ad�sa
			+ nextToString->getLamp().toString()	// ...az aktu�lis l�ncelem hozz�ad�sa (a saj�t toString met�dus�val)
			+ "\n";									// ...�j sor hozz�ad�sa
		nextToString = nextToString->getNext();		// a mutat� be�ll�t�sa a k�vetkez� elemre
	}
	return toReturn;
}




LightList::LightList(Lamp& lamptoadd)
	:lampItem(lamptoadd), nextLampItem(nullptr) {}

void LightList::setLamp(Lamp item) { lampItem = item; }

Lamp LightList::getLamp() const { return lampItem; }

void LightList::setNext(LightList* nextitem) { nextLampItem = nextitem; }

LightList* LightList::getNext() const { return nextLampItem; }

