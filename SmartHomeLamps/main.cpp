#include <iostream>
#include "Lamp.h"
#include "DimmableLamp.h"

using namespace std;

int main() {
	Lamp l1;
	Lamp l2("LED", "Tungsramm", 60, "W");
	DimmableLamp l3;
	DimmableLamp l4("classic", "Phillips", 100, "W", 70, 80);
	cout << l1.toString() << endl;
	cout << l2.toString() << endl;
	cout << l3.toString() << endl;
	cout << l4.toString() << endl;
	l1.setState(true);
	l2.setState(1);
	l3.setBrightness(20);
	l3.setState(1);
	l4.setBrightness(-15);
	cout << l1.toString() << endl;
	cout << l2.toString() << endl;
	cout << l3.toString() << endl;
	cout << l4.toString() << endl;
	return 0;
}