//Adapted by Brett Sackstein
//Created by Karlina Beringer on June 18, 2014.

#ifndef HashTable_h
#define HashTable_h

#include "LinkedList.h"
#include <memory>

class HashTable
{
private:
	
	// Array is a reference to an array of Linked Lists.
	std::unique_ptr<LinkedList[]> array;
	
	// Length is the size of the Hash Table array.
	int length;
	
	// Returns an array location for a given item key.
	int hash(std::string itemKey);
	
public:
	
	HashTable();

	// Constructs the empty Hash Table object.
	// Array length is set to 13 by default.
	HashTable(int tableLength);
	
	// Adds an item to the Hash Table.
	void insertItem(Item* newItem);
	
	// Returns an item from the Hash Table by key.
	// If the item isn't found, a null pointer is returned.
	Item* getItemByKey(std::string itemKey);
	
	// Returns the number of locations in the Hash Table.
	int getLength();
	
	// Returns the number of Items in the Hash Table.
	int getNumberOfItems();
};

#endif
