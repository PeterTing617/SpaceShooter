#pragma once

#include <string>
using namespace std;

// Doubly linked list
class WeaponNode
{
private:
	int weaponID;
	int weaponFireRate;
	string weaponName;
	WeaponNode* fNext;
	WeaponNode* fPrevious;

	WeaponNode()
	{
		weaponID = int();
		weaponFireRate = int();
		weaponName = string();
		fNext = nullptr;
		fPrevious = nullptr;
	}

public:
	WeaponNode(const int id, int rate, string name) {
		weaponID = id;
		weaponFireRate = rate;
		weaponName = name;
		fNext = nullptr;
		fPrevious = nullptr;
	}

	// Doubly Linked List Functions
	void prepend(WeaponNode* node) {
		node->fNext = this;

		if (fPrevious != nullptr) {
			node->fPrevious = fPrevious;
			fPrevious->fNext = &*node;
		}
		fPrevious = &*node;
	}

	void append(WeaponNode* node) {
		node->fPrevious = this; 

		if (fNext != nullptr) {
			node->fNext = fNext;
			fNext->fPrevious = &*node;
		}

		fNext = &*node;
	}

	// getters
	const int& getWeapon() const { return weaponID; }
	const int& getRate() const { return weaponFireRate; }
	const string& getName() const { return weaponName; }

	//returns the address of fNext/fPrevious
	WeaponNode* getNext() { return fNext; }
	WeaponNode* getPrevious() { return fPrevious; }
};

