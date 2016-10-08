//Adapted by Brett Sackstein
//Created by Karlina Beringer on June 16, 2014.

#include "LinkedList.h"

// Constructs the empty linked list object.
// Creates the head node and sets length to zero.
LinkedList::LinkedList()
{
	head = NULL;
	tail = NULL;
	length = 0;
}

void LinkedList::clear(){
	while (head != NULL){ // first empty list
		Item* tmp = head->next; // tmp to remember pointer to 2nd element
		delete head; // deletes first link from memory
		head = tmp;
	}
	tail = NULL;
}


LinkedList::~LinkedList(){
	clear();
}


// Inserts an item at the end of the list.
void LinkedList::insertItem(Item* newItem){
	if (!head)
	{	
		this->head = newItem;
		tail = head;
		length++;
		return;
	}
	tail->next = newItem;
	tail = tail->next;
	length++;
}


// Searches for an item by its key.
// Returns a reference to first match.
// Returns a NULL pointer if no match is found.
Item * LinkedList::getItem( std::string itemKey ){
	Item * p =head;
	Item * q = head;
	while (q){
		p =q;
		if (p->key->getTitle() == itemKey)
			return p;
		q = p -> next;
	}
	return NULL;
}

// Returns the length of the list.
int LinkedList::getLength(){
	return length;
}
