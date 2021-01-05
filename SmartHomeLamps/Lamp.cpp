#include "Lamp.h"

Power::Power(int val, std::string unitName) :value(val), unit(unitName) {}

Lamp::Lamp() : pwr(100, "W"), type("LED"), brand("n/a") {
	state = false;
}

Lamp::Lamp(std::string type, std::string brand, int pwrVal, std::string pwrUnit)
	: pwr(pwrVal, pwrUnit), type(type), brand(brand) {
	state = false;
}

void Lamp::setState(bool OnOff) { state = OnOff; }

bool Lamp::getState() { return state; }

std::string Lamp::getType() const { return type; }

std::string Lamp::getBrand() const { return brand; }

int Lamp::getPower() const { return pwr.value; }

std::string Lamp::toString() const {
	return brand + " " + type
		+ " (" + std::to_string(pwr.value) + pwr.unit + "): "
		+ (state ? "be" : "ki");
}

