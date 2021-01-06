#include <string>

struct Power {
	const int value;						// a l�mpa teljes�tm�ny�nek m�r�sz�ma
	const std::string unit;					// a l�mpa teljes�tm�ny�nek m�rt�kegys�ge
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


	//void setRoom(std::string);				// a l�mpa hely�nek be�ll�t�sa
	//std::string getRoom() const;			// a l�mpa hely�nek lek�rdez�se
	//std::string getType() const;			// t�pus kiolvas�sa
	//std::string getBrand() const;			// m�rka kiolvas�sa
	//int getPower() const;					// teljes�tm�ny kiolvas�sa
	//virtual std::string toString() const;	// adatok egyben sz�vegk�nt ki�r�shoz

protected:
	bool state;						// ki-be kapcsolt �llapot
	const std::string lampName;			// a l�mpa tipusa

	//std::string room;				// l�mpa helye
	//const std::string brand;		// a l�mpa m�rk�ja
	//const Power pwr;				// teljes�tm�ny
};

class DimmableLamp : public Lamp {
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
		LightList* LampToDelete;						// mutat� az aktu�lisan t�rlend� l�ncelemre
		LampToDelete = rootLamp;						// a mutat� be�ll�t�sa a lista els� elem�re
		while (LampToDelete != nullptr) {				// am�g l�tezik "aktu�lisan t�rlend� l�ncelem" azaz van r� mutat� hivatkoz�s...
			LightList* next = LampToDelete->getNext();	// ...a k�vetkez� l�ncelemre mutat� hivatkoz�s elt�rol�sa t�rl�s el�tt
			delete LampToDelete;						// ...aktu�lis l�ncelem t�rl�se
			LampToDelete = next;						// ...mutat� �t�ll�t�sa a k�vetkez� l�ncelemre
		}
	}

	void Storage::addLamp(Lamp & lamptoadd) {
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




	LightList::LightList(Lamp & lamptoadd)
		:lampItem(lamptoadd), nextLampItem(nullptr) {}

	void LightList::setLamp(Lamp item) { lampItem = item; }

	Lamp LightList::getLamp() const { return lampItem; }

	void LightList::setNext(LightList * nextitem) { nextLampItem = nextitem; }

	LightList* LightList::getNext() const { return nextLampItem; }

