#pragma once

#include "WeaponNode.h"

// Manages WeaponNode - doubly-linked list
class WeaponWheel
{
private:
	WeaponNode* firstWeapon;
	WeaponNode* selected;
	int totalWeapons;

public:
	// Constructor and Destructor
	WeaponWheel() {
		firstWeapon = nullptr;
		selected = nullptr;
		totalWeapons = 0;
	}

	virtual ~WeaponWheel() {
		WeaponNode* deleteNext = nullptr;
		WeaponNode* deleteCurrent = firstWeapon;
		for (int i = 0; i < totalWeapons; i++) {
			if (i == 0)
			{
				deleteNext = deleteCurrent->getNext();

				delete deleteCurrent;
			}
			else {
				deleteCurrent = deleteNext;
				deleteNext = deleteCurrent->getNext();

				delete deleteCurrent;
			}
		}
	}

	// Append a new node after selected node
	void addWeaponsAfterSelected(int i, int r, string n) {
		if (totalWeapons == 0) {
			firstWeapon = new WeaponNode(i, r, n);
			selected = firstWeapon;
			totalWeapons++;
		}
		else {
			selected->append(new WeaponNode(i, r, n));
			totalWeapons++;
		}
	}

	// Append a new node before selected node
	void addWeaponsBeforeSelected(int i, int r, string n) {
		if (totalWeapons == 0) {
			firstWeapon = new WeaponNode(i, r, n);
			selected = firstWeapon;
			totalWeapons++;
		}
		else {
			selected->prepend(new WeaponNode(i, r, n));
			if (selected == firstWeapon)
			{
				firstWeapon = selected->getPrevious();
			}
			totalWeapons++;
		}
	}

	// Move selected to next node
	void selectNext() {
		if (selected->getNext() != nullptr)
		{
			selected = selected->getNext();
		}
	}

	// Move selected to previous node
	void selectPrevious() {
		if (selected->getPrevious() != nullptr)
		{
			selected = selected->getPrevious();
		}
	}

	// Read selected node data
	int readID() { return selected->getWeapon(); }
	int readRate() { return selected->getRate(); }
	string readName() { return selected->getName(); }
};

