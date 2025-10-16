#include "trafficlight.h"

HuTrafficLight::HuTrafficLight() {
	l2 = new TSet(2);
	l2->InsElem(1);
}															//1-красный    2-зеленый   
int HuTrafficLight::GetColor() {
	return light;
}
void HuTrafficLight::ChangeLight() {
	/*light = color[++light] % 2;*/
	
	if (l2->IsMember(1)) {
		l2->DelElem(1); l2->InsElem(2);
	}
	else {
		l2->InsElem(1);
		l2->DelElem(2);
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

	if (l2->IsMember(1)) cout << "Hu: Red\n";
	else cout << "Hu: Green\n";
}



CarTrafficLight::CarTrafficLight() {					//1-красный    2-зеленый   3-желтый
	/*TSet l2(3);*/
	l2 = new TSet(3);
	l2->InsElem(2);
}
int CarTrafficLight::GetColor() {
	/*return light;*/
	for (int i = 1; i < l2->GetMaxPower()+1; i++)
	{
		if (l2->IsMember(i)) return i;
	}
}
void CarTrafficLight::ChangeLight() {
	/*light = color[++light] % 3;*/
	if (l2->IsMember(1)) {
		l2->DelElem(1);
		l2->InsElem(2);
	}
	else {
		if (l2->IsMember(2)) {
			l2->DelElem(2);
			l2->InsElem(3);
		}
		else {
			l2->DelElem(3);
			l2->InsElem(1);
		}
	}

}
void CarTrafficLight::PrintColor() {
	/*switch (light) {
	case(0):
		cout << "Car: Red\n";
		break;
	case(1):
		cout << "Car: Green\n";
		break;
	case(2):
		cout << "Car: Yellow\n";
		break;

	}*/

	if(l2->IsMember(1)) cout<< "Car: Red\n";
	else {
		if(l2->IsMember(2))cout << "Car: Green\n";
		else cout << "Car: Yellow\n";
	}
}