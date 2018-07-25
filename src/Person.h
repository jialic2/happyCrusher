#pragma once

#include <string>
using namespace std;

class Person {
	int hp;
	int mp;
public:
	bool hasShield;
	Person();
	Person(string);
	int getHp();
	void setHp(int);
	int getMp();
	void setMp(int);
	string name;
};