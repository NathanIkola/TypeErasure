//**************************************
// main.cpp
//
// Driver code for my type erasure
// motivation examples
//
// Author: Nathan Ikola
// nathan.ikola@gmail.com
//**************************************

#include <iostream>
#include "inventory.h"
#include "item.h"
#include "consumable.h"
#include "equippable.h"

//**************************************
// dummy classes to test type erasure
class Potion : Consumable
{
public:
	void Consume() override {}
};

class Sword : Equippable
{
public:
	void Equip() override {}
};

class CandyNecklace : Consumable, Equippable
{
public:
	void Consume() override {}
	void Equip() override {}
};

class PocketLint { };
// end dummy classes
//**************************************

int main()
{
	Inventory inventory;

	std::cout << "Item 0 is a potion" << std::endl << std::endl;
	// add an existing item using the Item ctor
	Potion potion;
	inventory.AddItem(Item{ potion });

	std::cout << "Item 1 is a sword" << std::endl << std::endl;
	// add an existing item without using the Item ctor
	Sword sword;
	inventory.AddItem(sword);

	std::cout << "Item 2 is a candy necklace" << std::endl << std::endl;
	// insert temporary item using the Item ctor
	inventory.AddItem(Item{ CandyNecklace{} });

	std::cout << "Item 3 is pocket lint" << std::endl << std::endl;
	// insert temporary item without using the Item ctor
	inventory.AddItem(PocketLint{});

	std::vector<Item> items = inventory.GetItems();

	for (int item{ 0 }; item < items.size(); ++item)
	{
		std::cout << "Item " << item << " has the following attributes:" << std::endl;
		std::cout << "Consumable: " << items[item].IsConsumable() << std::endl;
		std::cout << "Equippable: " << items[item].IsEquippable() << std::endl << std::endl;
	}

	return 0;
}