#include "DimmableLamp.h"

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
	return brand + " " + type
		+ " (" + std::to_string(pwr.value) + pwr.unit + "): "
		+ (state ? "be" : "ki") + " [dim is: " + std::to_string(brightness) + "/" + std::to_string(range) + "]";
}
