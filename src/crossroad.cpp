#include "crossroad.h"


void Crossroad::Start() {

	for (int i = 0; i < 5; i++) {
		if (carlight.GetColor() != 0) {
			carlight.PrintColor();
			hulight.PrintColor();
			carlight.ChangeLight();

		}
		else {
			hulight.ChangeLight();
			carlight.PrintColor();
			hulight.PrintColor();
			carlight.ChangeLight();
			hulight.ChangeLight();
		}
	}
}