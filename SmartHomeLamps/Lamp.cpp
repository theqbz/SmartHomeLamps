#include "Lamp.h"

Power::Power(int val, std::string unitName) :value(val), unit(unitName) {}

Lamp::Lamp() : pwr(100, "W"), lampName("LED"), brand("n/a") {
	state = false;
}

Lamp::Lamp(std::string type, std::string brand, int pwrVal, std::string pwrUnit)
	: pwr(pwrVal, pwrUnit), lampName(type), brand(brand) {
	state = false;
}

Lamp& Lamp::operator=(Lamp& other) { return *this; }

void Lamp::setState(bool OnOff) { state = OnOff; }

bool Lamp::getState() { return state; }

void Lamp::setRoom(std::string r) { room = r; }

std::string Lamp::getRoom() const { return room; }

std::string Lamp::getType() const { return lampName; }

std::string Lamp::getBrand() const { return brand; }

int Lamp::getPower() const { return pwr.value; }

std::string Lamp::toString() const {
	return brand + " " + lampName
		+ " (" + std::to_string(pwr.value) + pwr.unit + "): "
		+ (state ? "be" : "ki");
}

