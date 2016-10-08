//Adapted by Brett Sackstein
//Created by Karlina Beringer on June 16, 2014.

#include "Song.h"
#ifndef LinkedList_h
#define LinkedList_h
#include <iostream>
#include <string>

struct Item
{
	Song* key;
	Item * next;
	Item() {
		key = NULL;
		next = NULL;
	};
};

class LinkedList{
private:
	// Head is a reference to a list of data nodes.
	Item * head;
	Item * tail;
	
	// Length is the number of data nodes.
	int length;
	
public:
	// Constructs the empty linked list object.
	// Creates the head node and sets length to zero.
	LinkedList();
	~LinkedList();
	void clear();

	// Inserts an item at the end of the list.
	void insertItem(Item* newItem);
	
	// Searches for an item by its key.
	// Returns a reference to first match.
	// Returns a NULL pointer if no match is found.
	Item * getItem(std::string itemKey);
	
	// Returns the length of the list.
	int getLength();
	
};

#endif
