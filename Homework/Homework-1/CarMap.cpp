//
//  carMap.cpp
//  Homework-2-copy-1
//
//  Created by Ashvin Bondada on 1/17/22.
//

#include "CarMap.h"
#include "Map.h"
#include <iostream>
using namespace std;

CarMap::CarMap() {
    
}

CarMap::~CarMap() {
}


// If a car with the given license plate is not currently in the map,
// and there is room in the map, add an entry for that car recording
// that it has been driven 0 miles, and return true.  Otherwise,
// make no change to the map and return false.
bool CarMap::addCar(KeyType license) {
    if (cMap.insert(license, 0))
        return true;
    return false;
}

// If a car with the given license plate is in the map, return how
// many miles it has been driven; otherwise, return -1.
double CarMap::miles(KeyType license) const {
    ValueType tempValue;
    if(cMap.get(license, tempValue)) {
        return tempValue;
    }
    else
        return -1;
}

// If no car with the given license plate is in the map or if
// distance is negative, make no change to the map and return
// false.  Otherwise, increase by the distance parameter the number
// of miles the indicated car has been driven and return true.
bool CarMap::drive(KeyType license, ValueType distance){
    if (!cMap.contains(license) || distance < 0) {
        return false;
    }
    else{
        ValueType tempDist;
        cMap.get(license, tempDist);
        tempDist = tempDist + distance;
        cMap.update(license, tempDist);
        return true;
    }
    
        
    }

// Return the number of cars in the CarMap.
int CarMap::fleetSize() const{
    return cMap.size();
}

// Write to cout one line for every car in the map.  Each line
// consists of the car's license plate, followed by one space,
// followed by the number of miles that car has been driven.  Write
// no other text.  The lines need not be in any particular order.
void CarMap::print() const {
    KeyType tlicense;
    ValueType tmiles;
    for (int i = 0; i < cMap.size(); i++) {
        
        cMap.get(i, tlicense, tmiles);
        cout << tlicense << " " << tmiles << endl;
    }
    
}


