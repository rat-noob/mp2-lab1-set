#pragma once
#include <iostream>
#include "tset.h"
using namespace std;
class TrafficLight {
	/*int lights;*/
	int light;
	/*TSet l2;*/
public:
	virtual void ChangeLight() = 0;
	virtual int GetColor() = 0;
	virtual void PrintColor() = 0;
};

class HuTrafficLight:public TrafficLight {
	TSet l2(int r = 2);

	/*TSet l2(2);*/
	int color[2] = { 0,1 };
	int light = 0;
public:
	HuTrafficLight();
	void ChangeLight();
	int GetColor();
	void PrintColor();
};
class CarTrafficLight :public TrafficLight {
	
	TSet l2(int r = 3);

	/*TSet l2(3);*/
	int color[3] = { 0,1,2 };
	int light = 1;
public:
	CarTrafficLight();
	void ChangeLight();
	int GetColor();
	void PrintColor();
};
