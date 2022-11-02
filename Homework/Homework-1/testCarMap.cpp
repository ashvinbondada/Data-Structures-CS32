//
//  testCarMap.cpp
//  Homework-2-copy-1
//
//  Created by Ashvin Bondada on 1/17/22.
//

//#include "Map.h"
#include "CarMap.h"

#include <iostream>
#include <cassert>
using namespace std;

int main() {
    
    CarMap a;

    //  add Car and drive
    a.addCar("Ashvin");
    a.drive("Ashvin", 25);
    a.addCar("Zion");
    a.drive("Zion", 34);
    a.addCar("Bella");
    a.drive("Bella", 15);
    a.addCar("+19fh");
    a.drive("+19fh", 30);
    a.addCar("");               //  empty string
    assert(a.miles("+19fh") == 30);
    assert(!a.drive("Landon", 3));    //  Zion dont exist
    assert(!a.addCar("Ashvin"));        //  duplicate
    //  check if capacity is full
    
    // miles
    assert(a.miles("Ashvin") == 25 && a.miles("Zion") == 34 && a.miles("Bella") == 15);
    assert(a.miles("Tony") == -1);
    
    //  drive
    ValueType v = 5;
    a.drive("Ashvin", v);
    assert(a.miles("Ashvin") == 30);
    
    
    //  fleetsize
    assert(a.fleetSize() == 5);
    
    //  print
    //a.print();
    cout << "Passed" << endl;

    return 0;
}
