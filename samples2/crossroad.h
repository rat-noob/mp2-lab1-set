#pragma once
#include "trafficlight.h"

class Crossroad {
	HuTrafficLight hulight;
	CarTrafficLight carlight;
public:
	void Start();
};