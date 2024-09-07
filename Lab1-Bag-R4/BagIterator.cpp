#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;


BagIterator::BagIterator(const Bag& c): bag(c)
{
    currentPosition = 0;
    freqCount = 1;
}

void BagIterator::first() {
    currentPosition = 0;
    freqCount = 1;
}


void BagIterator::next() {
    if (!valid()) {
        throw exception();
    }
    freqCount++;
    
    if (freqCount > bag.mainArray[currentPosition]) {
        currentPosition ++;
        freqCount = 1;
        // GPT: Skip over elements with 0 occurrences
        while (currentPosition < bag.capacityArr && bag.mainArray[currentPosition] == 0) {
            currentPosition++;
        }
    }
}


bool BagIterator::valid() const {
    return currentPosition < bag.capacityArr;
}



TElem BagIterator::getCurrent() const
{
    if (!valid()) {
        throw exception();
    }
    return currentPosition + bag.minElem;
}
