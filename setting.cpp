#include<iostream>
#include"classes.h"
using namespace std;
Mover* movers = new Mover[10];
void setup() {
	// generate the map;
	for (int i(0); i < 10; ++i) {
		// generate the exact mover
	}
	return;
}
void draw() {
	for (int i(0); i < 10; ++i) {
		(movers + i)->update();
		(movers + i)->checkpos();
		(movers + i)->display();
	}
	return;
}