#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;


/* ADT Bag – represented as a dynamic array of frequencies.
 For example, the bag [5, 10, -1, 2, 3, 10, 5, 5, -5] will be represented 
 as [1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 3, 0, 0, 0, 0, 2], built in the following way:
    - the interval of values [-5, 10] is translated into the interval [0, 16] of positions
    - at position 0 we have the frequency of -5 (minimum element), on position 1 we have the frequency of -4, …, on position 15 we have the frequency of 10 (maximum element). */

Bag::Bag() {
    int capacityArr = 32;
    mainArray = new TElem[capacityArr]();
    minElem = 0;
    
}


void Bag::add(TElem elem) {
	//if new minimum
    if (elem < minElem) {
        //calc new minimum and difference between old (for shifting pos)
        int newMinElem = elem;
        int shiftDifference = minElem - newMinElem;
        
        //resize and init
        int newCapacity = capacityArr + shiftDifference;
        TElem* tempArray = new TElem[newCapacity];
        for (int i = 0; i < newCapacity; i++) {
            tempArray[i] = 0;
        }
        
        //shift and copy old elems in new resized array
        for (int i = 0; i < capacityArr; i++) {
            tempArray[i + shiftDifference] = mainArray[i];
        }
        
        //del and update vars
        delete [] mainArray;
        mainArray = tempArray;
        capacityArr = newCapacity;
        minElem = newMinElem;
    }
    
    //else just increment index
    mainArray[elem - minElem]++;
}


bool Bag::remove(TElem elem) {
	//search
    bool found = false;

    if (mainArray[elem - minElem] >= 1) {
        found = true;
    }
    
    if (!found) {
        return false; //element not found, nothing removed
    }
    
    mainArray[elem - minElem]--;
	return true;
}


bool Bag::search(TElem elem) const {
	return mainArray[elem - minElem] >= 1;
}

int Bag::nrOccurrences(TElem elem) const {
	return mainArray[elem - minElem];
}


int Bag::size() const {
    int counter = 0;
    for (int i = 0; i < capacityArr; i++) {
        counter += mainArray[i];
    }
	return counter;
}


bool Bag::isEmpty() const {
    for (int i = 0; i < capacityArr; i++) {
        if (mainArray[i] > 0) {
            return false;
        }
    }
    return true;
}

BagIterator Bag::iterator() const {
	return BagIterator(*this);
}


Bag::~Bag() {
    delete [] mainArray;
}

