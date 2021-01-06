#include "LightsStorage.h"

Storage::Storage(Lamp& firstlamp)
	:rootLamp(new LightList(firstlamp)) {}

Storage::~Storage() {
	LightList* LampToDelete;						// mutató az aktuálisan törlendõ láncelemre
	LampToDelete = rootLamp;						// a mutató beállítása a lista elsõ elemére
	while (LampToDelete != nullptr) {				// amíg létezik "aktuálisan törlendõ láncelem" azaz van rá mutató hivatkozás...
		LightList* next = LampToDelete->getNext();	// ...a következõ láncelemre mutató hivatkozás eltárolása törlés elõtt
		delete LampToDelete;						// ...aktuális láncelem törlése
		LampToDelete = next;						// ...mutató átállítása a következõ láncelemre
	}
}

void Storage::addLamp(Lamp& lamptoadd) {
	LightList* lastLamp;							// mutató az aktuális listaelemre
	lastLamp = rootLamp;							// a mutatót az elsõ listaelemre állítjuk
	while (lastLamp->getNext() != nullptr) {		// amíg "van elem az aktuális listaelem után" azaz van a következõre mutató hivatkozás...
		lastLamp = lastLamp->getNext();				// ...az aktuális listaelem legyen a következõ
	}
	lastLamp->setNext(new LightList(lamptoadd));	// az utolsó listaelem "következõ" értékét beállítjuk egy újonan létrehozott listaelemre
}

void Storage::removeLampByCount(int c) {
	if (c <= countLamps()) {						// csak akkor kezdjen bele, ha a kért szám nem nagyobb mint a listaelemek száma
		int i = 0;									// számláló
		LightList* previous = nullptr;				// mutató a "törlendõ elõtti" listalemre
		LightList* toDelete;						// mutató a "törlendõ" listaelemre
		toDelete = rootLamp;						// "törlendõ" beállítása az elsõ listaelemre
		while (toDelete != nullptr || i < c) {		// amíg a "törlendõ" elem létezik vagy a számláló még nem érte el az indexet...
			previous = toDelete;					// a "törlendõ elõtti" léptetése azaz beállítása az aktuálsian törlendõre
			toDelete = toDelete->getNext();			// a "törlendõ" léptetése azaz beállítása a következõ listaelemre
			i++;									// számláló léptetése
		}
		if (toDelete != nullptr) {					// ha nem azért lépett ki a ciklusból, mert elérte az utolsó elemet...
			previous->setNext(toDelete->getNext());	// ...akkor a "törlendõ elõtti" listaelemhez beállítjuk a törlendõ utáni listalelem címét
			delete toDelete;						// ...aztán töröljük a törlendõ listaelemet
		}
		else {										// ha a ciklusban elérte a lista végét...
			delete toDelete;						// ...akkor az utolsóó elemet kell törölni
		}
	}
}

void Storage::removeLampByIndex(int index) {
	if (index <= countLamps()) {					// csak akkor kezdjen bele, ha a kért index nem nagyobb mint a listaelemek száma
		int i = 0;									// számláló
		LightList* previous = nullptr;				// mutató a "törlendõ elõtti" listalemre
		LightList* toDelete;						// mutató a "törlendõ" listaelemre
		toDelete = rootLamp;						// "törlendõ" beállítása az elsõ listaelemre
		while (i < index) {							// amíg el nem éri a keresett indexet...
			previous = toDelete;					// a "törlendõ elõtti" léptetése azaz beállítása az aktuálsian törlendõre
			toDelete = toDelete->getNext();			// a "törlendõ" léptetése azaz beállítása a következõ listaelemre
			i++;									// számláló léptetése
		}
		delete toDelete;							// a megtalált elem törlése
	}
}

int Storage::countLamps() {
	int c = 0;										// számláló
	LightList* toCount;								// mutató az aktuálisan számlálandó láncelemre
	toCount = rootLamp;								// mutató beállítása az elsõ láncelemre
	while (toCount != nullptr) {					// amíg az aktuálisan számlálandó láncelem létezik...
		c++;										// ...számláló léptetése
		toCount = toCount->getNext();				// ...mutató átállítása a következõ láncelemre
	}
	return c;
}

std::string Storage::toString() const
{
	std::string toReturn = "\0";					// ebbe gyûlik a lámpalista a kiíráshoz
	int i = 0;										// sorszámozás
	LightList* nextToString;						// mutató az aktuális láncelemre
	nextToString = rootLamp;						// a mutató beállítása az elsõ láncelemre
	while (nextToString != nullptr) {				// amíg létezik az "aktuálsan hozzáadandó láncelem" azaz van rá mutató hivatkozás...
		toReturn += std::to_string(i + 1) + ". "	// ...sorszám hozzáadása
			+ nextToString->getLamp().toString()	// ...az aktuális láncelem hozzáadása (a saját toString metódusával)
			+ "\n";									// ...új sor hozzáadása
		nextToString = nextToString->getNext();		// a mutató beállítása a következõ elemre
	}
	return toReturn;
}




LightList::LightList(Lamp& lamptoadd)
	:lampItem(lamptoadd), nextLampItem(nullptr) {}

void LightList::setLamp(Lamp item) { lampItem = item; }

Lamp LightList::getLamp() const { return lampItem; }

void LightList::setNext(LightList* nextitem) { nextLampItem = nextitem; }

LightList* LightList::getNext() const { return nextLampItem; }

