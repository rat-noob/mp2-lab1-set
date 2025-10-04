#include "trafficlight.h"

HuTrafficLight::HuTrafficLight() {
	/*TSet l2(2);*/
	l2.InsElem(1);
}															//1-красный    2-зеленый   
int HuTrafficLight::GetColor() {
	return light;
}
void HuTrafficLight::ChangeLight() {
	light = color[++light] % 2;
	/*int l = l2.GetMaxPower();
	for (int i = 0; i < l; i++)
	{
		if (l2.IsMember(i + 1) != 0) {
			l2.DelElem(i + 1);
			l2.InsElem(i+2);
		}
	}*/
	if (l2.IsMember(1)) {
		l2.DelElem(1); l2.InsElem(2);
	}
	else {
		l2.InsElem(1);
		l2.DelElem(2);
	}
	

}
void HuTrafficLight::PrintColor() {
	/*switch (light) {
	case(0):
		cout << "Hu: Red\n";
		break;
	case(1):
		cout << "Hu: Green\n";
		break;

	}*/

	/*if (l2.IsMember(1)) cout << "Hu: Red\n";
	else cout << "Hu: Green\n";*/
}



CarTrafficLight::CarTrafficLight() {					//1-красный    2-зеленый   3-желтый
	/*TSet l2(3);*/
	l2.InsElem(2);
}
int CarTrafficLight::GetColor() {
	return light;
}
void CarTrafficLight::ChangeLight() {
	light = color[++light] % 3;
}
void CarTrafficLight::PrintColor() {
	switch (light) {
	case(0):
		cout << "Car: Red\n";
		break;
	case(1):
		cout << "Car: Green\n";
		break;
	case(2):
		cout << "Car: Yellow\n";
		break;

	}
}