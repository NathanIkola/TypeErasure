//**************************************
// inventory.h
//
// Contains a simple inventory class
//
// Author: Nathan Ikola
// nathan.ikola@gmail.com
//**************************************
#pragma once

#include <vector>
#include "item.h"

class Inventory
{
public:
	inline const std::vector<Item>& GetItems() const { return m_items; }
	inline void AddItem(Item item) { m_items.push_back(item); }

	template<typename T>
	inline void AddItem(const T& item) { m_items.push_back(Item(item)); }
private:
	std::vector<Item> m_items;
};