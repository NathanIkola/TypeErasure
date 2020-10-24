//**************************************
// item.h
//
// Contains the type erasure definition
// for the item interface
//
// Author: Nathan Ikola
// nathan.ikola@gmail.com
//**************************************

//**************************************
// The first thing to do is to decide
// on an interface that items MUST
// conform to
//
// I don't think all items should be
// responsible for maintaining behavior
// that they do not rely on. For example
// swords are equippable but not
// consumable, and potions are consumable
// but not equippable; if they inherit
// from an Item interface, they are
// forced to have an implementation for
// these behaviors (even if empty) even
// though they do not possess them.
//
// Using type erasure here allows
// for each item type to ONLY ever
// have behaviors associated with them
// which they actually implement.
//
// However, tight coupling is required
// for each of the different types to
// test if they are related to a
// specific class of items (consumable,
// equippable, etc...). This is not
// ideal, but a similar method would
// be required in the Item interface
// using inheritance, only this way
// does not require Consumable
// derived classes to implement a
// method stating that they are a
// Consumable. Whether that is a
// good idea or not, I don't know.
// This way Consumable doesn't need
// to know anything about an
// Equippable class' existence
//**************************************
#pragma once

#include <memory>

// forward declare a consumables class
class Consumable;

// forward declare an equippable class
class Equippable;

class Item
{
	struct ItemConcept
	{
		inline virtual ~ItemConcept() { }
		inline virtual bool IsConsumable() const = 0;
		inline virtual bool IsEquippable() const = 0;
	};

	template<typename T>
	struct ItemModel : ItemConcept
	{
		inline ItemModel(const T& item) : m_item(item) { }

		inline virtual bool IsConsumable() const { return std::is_base_of<Consumable, T>::value; }
		inline virtual bool IsEquippable() const { return std::is_base_of<Equippable, T>::value; }

		T m_item;
	};
public:
	template<typename T>
	inline Item(const T& item) : m_item(new ItemModel<T>(item)) { }

	inline bool IsConsumable() const { return m_item->IsConsumable(); }
	inline bool IsEquippable() const { return m_item->IsEquippable(); }
private:
	std::shared_ptr<ItemConcept> m_item;
};