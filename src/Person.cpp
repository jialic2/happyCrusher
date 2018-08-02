#include "Person.h"

Person::Person() {
	hp = 300;
	mp = 0;
	hasShield = false;
}
Person::Person(string s) {
	name = s;
	hp = 300;
	mp = 0;
	hasShield = false;
	
}

int Person::getHp() {
	return hp;
}

void Person::setHp(int i) {
	hp = i;
}

int Person::getMp() {
	return mp;
}

void Person::setMp(int i) {
	mp = i;
}