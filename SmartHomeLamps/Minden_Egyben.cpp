#include <string>

struct Power {
	const int value;						// a lámpa teljesítményének mérõszáma
	const std::string unit;					// a lámpa teljesítményének mértékegysége
	Power(int val, std::string unitName);
};

class Lamp {
public:
	Lamp(std::string lampname) :lampName(lampname) {
		state = false;
	}

	void flip() {
		if (state) {
			state = false;
		}
		else {
			state = true;
		}
	}

	std::string isOn() {
		return lampName + "turned " + (state ? "ON" : "OFF");
	}

	//Lamp(std::string lampname);
	//Lamp& operator=(Lamp& other);


	//void setRoom(std::string);				// a lámpa helyének beállítása
	//std::string getRoom() const;			// a lámpa helyének lekérdezése
	//std::string getType() const;			// típus kiolvasása
	//std::string getBrand() const;			// márka kiolvasása
	//int getPower() const;					// teljesítmény kiolvasása
	//virtual std::string toString() const;	// adatok egyben szövegként kiíráshoz

protected:
	bool state;						// ki-be kapcsolt állapot
	const std::string lampName;			// a lámpa tipusa

	//std::string room;				// lámpa helye
	//const std::string brand;		// a lámpa márkája
	//const Power pwr;				// teljesítmény
};

class DimmableLamp : public Lamp {
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



Power::Power(int val, std::string unitName) :value(val), unit(unitName) {}

//Lamp::Lamp() : pwr(100, "W"), lampName("LED"), brand("n/a") {
//	state = false;
//}

//Lamp& Lamp::operator=(Lamp& other) { return *this; }


//void Lamp::setRoom(std::string r) { room = r; }
//
//std::string Lamp::getRoom() const { return room; }
//
//std::string Lamp::getType() const { return lampName; }
//
//std::string Lamp::getBrand() const { return brand; }
//
//int Lamp::getPower() const { return pwr.value; }
//
//std::string Lamp::toString() const {
//	return brand + " " + lampName
//		+ " (" + std::to_string(pwr.value) + pwr.unit + "): "
//		+ (state ? "be" : "ki");
//}

DimmableLamp::DimmableLamp()
	: Lamp("LED", "n/a", 100, "W"), range(100) {
	setBrightness(1);
}

DimmableLamp::DimmableLamp(int dimRange, int dimBrightness)
	: Lamp("LED", "n/a", 100, "W"), range(dimRange) {
	setBrightness(dimBrightness);
}

DimmableLamp::DimmableLamp(std::string type, std::string brand, int pwrValue, std::string pwrUnit, int dimRange, int dimBrightness)
	: Lamp(type, brand, pwrValue, pwrUnit), range(dimRange) {
	setBrightness(dimBrightness);
}

void DimmableLamp::setBrightness(int value) {
	if (value > 0 && value <= range) { brightness = value; }
	else if (value < 0) { brightness = 1; }
	else if (value > range) { brightness = range; }
}

int DimmableLamp::getBrightness() { return brightness; }

std::string DimmableLamp::toString() const {
	return brand + " " + lampName
		+ " (" + std::to_string(pwr.value) + pwr.unit + "): "
		+ (state ? "be" : "ki") + " [dim is: " + std::to_string(brightness) + "/" + std::to_string(range) + "]";


	Storage::Storage(Lamp & firstlamp)
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

	void Storage::addLamp(Lamp & lamptoadd) {
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




	LightList::LightList(Lamp & lamptoadd)
		:lampItem(lamptoadd), nextLampItem(nullptr) {}

	void LightList::setLamp(Lamp item) { lampItem = item; }

	Lamp LightList::getLamp() const { return lampItem; }

	void LightList::setNext(LightList * nextitem) { nextLampItem = nextitem; }

	LightList* LightList::getNext() const { return nextLampItem; }

