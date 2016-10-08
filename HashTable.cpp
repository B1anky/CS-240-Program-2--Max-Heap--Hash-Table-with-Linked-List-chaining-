//Adapted by Brett Sackstein
//Created by Kar Beringer on June 18, 2014.

#include "HashTable.h"

// Constructs the empty Hash Table object.
HashTable::HashTable()
{
	array = std::unique_ptr<LinkedList[]>();
	length = 0;
}

HashTable::HashTable(int tableLength)
{
	array = std::unique_ptr<LinkedList[]>(new LinkedList[tableLength]);
	length = tableLength;
}

// Returns an array location for a given item key.
int HashTable::hash(std::string itemKey)
{
	int value = 0;
	for (int i = 0; i < itemKey.length(); i++)
		value += itemKey[i];
	return (value * itemKey.length()) % length;
}

// Adds an item to the Hash Table.
void HashTable::insertItem(Item *newItem){
	int index = hash(newItem->key->getTitle());
	array[index].insertItem(newItem);
}

// Returns an item from the Hash Table by key.
// If the item isn't found, a null pointer is returned.
Item * HashTable::getItemByKey(std::string itemKey){
	int index = hash(itemKey);
	return array[index].getItem(itemKey);
}

// Returns the number of locations in the Hash Table.
int HashTable::getLength(){
	return length;
}

// Returns the number of Items in the Hash Table.
int HashTable::getNumberOfItems(){
	int itemCount = 0;
	for (int i = 0; i < length; i++)
	{
		itemCount += array[i].getLength();
	}
	return itemCount;
}
