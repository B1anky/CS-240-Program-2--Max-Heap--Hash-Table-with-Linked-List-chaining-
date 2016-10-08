//Adapted by Brett Sackstein
//Reference: Dr. Rick Coleman at http://www.cs.uah.edu/~rcoleman/Common/CodeVault/Code/Code211_Heap.html
#include "MaxHeap.h"

int MaxHeap::getLeftInd(int nodeInd){
	return 2 * nodeInd + 1;
}

int MaxHeap::getRightInd(int nodeInd){
	return 2  * nodeInd + 2;
}

int MaxHeap::getParentInd(int nodeInd){
	return (nodeInd - 1)/2;
}

MaxHeap::MaxHeap(){
	data = NULL;
	numElements = 0;
	heapLength = 0;
	lastPlayed = NULL;
}

MaxHeap::MaxHeap(int size){
	data = new Song*[size];
	numElements = 0;
	heapLength = size;
	lastPlayed = NULL;
}

MaxHeap::MaxHeap(MaxHeap& otherHeap){
	MaxHeap* dummy = this;
	dummy->numElements = otherHeap.getHeapSize();
	dummy->heapLength = otherHeap.getArraySize();
	dummy->data = otherHeap.getAllData();
	for(int i = 0; i < numElements; i++){
		dummy->data[i] = otherHeap.getData(i);
	}
}

MaxHeap& MaxHeap::operator=(MaxHeap &otherHeap){
	MaxHeap* dummy = this;
	dummy->numElements = otherHeap.getHeapSize();
	dummy->heapLength = otherHeap.getArraySize();
	dummy->data = otherHeap.getAllData();
	for(int i = 0; i < numElements; i++){
		dummy->data[i] = otherHeap.getData(i);
	}
	return *dummy;
}

MaxHeap::~MaxHeap(){
	delete []data;
}

//Will return the first index in the heap array is successful
int MaxHeap::getMaximum(){
	if(numElements == 0)
		return -1;
	else
		return 0;
}

Song* MaxHeap::getData(int index){
	return data[index];
}

Song** MaxHeap::getAllData(){
	return data;
}

int MaxHeap::getHeapSize(){
	return numElements;
}

int MaxHeap::getArraySize(){
	return heapLength;
}

void MaxHeap::ReheapDown(int root, int bottom, int currentClockTime)
{
	int maxChild;
	int rightChild;
	int leftChild;
	Song *temp;

	leftChild = root * 2 + 1;          // Get index of root's left child
	rightChild = root * 2 + 2;          // Get index of root's right child

	// Check base case in recursive calls.  If leftChild's index is less
	// than or equal to the bottom index we have not finished recursively 
	// reheaping.
	if(leftChild <= bottom)               
	{
		if(leftChild == bottom)          // If this root has no right child then 
		{
			maxChild = leftChild;     //     leftChild must hold max key
		}
		else
		{     // Get the one lowest in the tree (highest index in the array)
			if(currentClockTime - data[leftChild]->getTimeLastPlayed() + data[leftChild]->getPriority() <= currentClockTime - data[rightChild]->getTimeLastPlayed() + data[rightChild]->getPriority())
				maxChild = rightChild;
			else
				maxChild = leftChild;
		}
		if(currentClockTime - data[root]->getTimeLastPlayed() + data[root]->getPriority() < currentClockTime - data[maxChild]->getTimeLastPlayed() + data[maxChild]->getPriority())
		{
			// Swap these two elements
			temp = data[root];
			data[root] = data[maxChild];
			data[maxChild] = temp;
			// Make recursive call till reheaping completed
			ReheapDown(maxChild, bottom, currentClockTime);
		}
	}
}

//---------------------------------------
// Reheap after inserting item
//---------------------------------------
void MaxHeap::ReheapUp(int root, int bottom, int currentClockTime)
{
	int parent;
	Song *temp;

	// Check base case in recursive calls.  If bottom's index is greater
	// than the root index we have not finished recursively reheaping.
	if(bottom > root)
	{
		parent = (bottom -1) / 2;
		if(currentClockTime - data[parent]->getTimeLastPlayed() + data[parent]->getPriority() < currentClockTime - data[bottom]->getTimeLastPlayed() + data[bottom]->getPriority())
		{
			// Swap these two elements
			temp = data[parent];
			data[parent] = data[bottom];
			data[bottom] = temp;
			// Make recursive call till reheaping completed
			ReheapUp(root, parent, currentClockTime);
		}
	}
}

//---------------------------------------
// Add an item to the heap
//---------------------------------------
bool MaxHeap::Enqueue(Song *item, int currentClockTime)
{
	if(numElements < heapLength)
	{
		data[numElements] = item; // Copy item into array
		ReheapUp(0, numElements, currentClockTime);
		numElements++;
		return true;
	}
	return false;
}

//---------------------------------------
// Get item at the root
//---------------------------------------
Song *MaxHeap::Dequeue(int currentClockTime)
{
	if(data[0]){
		Song *temp = data[0];
		numElements--;
		// Copy last item into root
		data[0] = data[numElements];
		// Reheap the tree
		ReheapDown(0, numElements - 1, currentClockTime);
		if(numElements == 0)
		    return NULL;
		else{
			setLastPlayed(temp);
			std::cout << "Playing " << temp->getAllInfo() << std::endl;
		return temp;
		}
	}else{
		return NULL;
	}
}

void MaxHeap::setLastPlayed(Song* toPlay){
	lastPlayed = toPlay;
}

Song* MaxHeap::getLastPlayed(){
	if(lastPlayed){
		return lastPlayed;
	}else{
		return NULL;
	}
}
