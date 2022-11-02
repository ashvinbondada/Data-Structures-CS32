
//
//  Map.cpp
//  Homework-1-copy
//
//  Created by Ashvin Bondada on 1/17/22.
//
 
#include "newMap.h"
#include <string>
#include <iostream>
using namespace std;


Map::Map(int x)
{
    if (x < 0) {
        x = DEFAULT_MAX_ITEMS;
    }
    m_nNodes = 0;
    m_x = x;
    m_Items = new m_Node[x];
}

Map::Map(const Map& old){
    m_nNodes = old.m_nNodes;
    m_x = old.m_x;
    m_Items = new m_Node[m_nNodes];
    for (int i = 0; i< m_nNodes; i++){
        m_Items[i] = old.m_Items[i];
    }
}

Map& Map::operator= (const Map &src) {
 if (&src == this)
     {
         return *this;
     }
    delete [] m_Items;
    m_nNodes = src.m_nNodes;
    m_Items = new m_Node[m_nNodes];
    for (int i = 0; i < m_nNodes; i++) {
        m_Items[i] = src.m_Items[i];
    }
    return *this;
}

Map::~Map() {
    delete [] m_Items;
}

bool Map::empty() const {
    
    if (m_nNodes == 0) {
        return true;
    }
    return false;
}
 
int Map::size() const {
    return m_nNodes;
}
 
bool Map::insert(const KeyType& key, const ValueType& value) {
    
    if (m_nNodes >= m_x)      //  If list is already full
        return false;
    
    for (int i = 0; i < m_nNodes; i++) {        //  checks if there is a duplicate
        if (m_Items[i].key == key) {
            return false;
        }
    }
    
    m_Items[m_nNodes].value = value;
    m_Items[m_nNodes].key = key;
    m_nNodes++;
    m_Node temp;
    
    for (int i = 0; i < m_nNodes; i++ ) {
        for (int j = i + 1; j < m_nNodes; j++) {
            if (m_Items[i].key > m_Items[j].key){ // A to Z
                temp = m_Items[j];
                m_Items[j] = m_Items[i];
                m_Items[i] = temp;
            }
        }
    }
    
    return true;
}
 
// If key is equal to a key currently in the map, then make that key no
// longer map to the value that it currently maps to, but instead map to
// the value of the second parameter; return true in this case.
// Otherwise, make no change to the map and return false.
bool Map::update(const KeyType& key, const ValueType& value) {
    
    for (int i = 0; i < m_nNodes; i++) {        //  checks if there is a duplicate
        if (m_Items[i].key == key) {
            m_Items[i].value = value;
            return true;
        }
    }
    return false;
}
 
bool Map::insertOrUpdate(const KeyType& key, const ValueType& value) {
    if (update(key, value))
        return true;
    else if (insert(key, value))
        return true;
    return false;
}
 
// If key is equal to a key currently in the map, remove the key/value
// pair with that key from the map and return true.  Otherwise, make
// no change to the map and return false.
bool Map::erase(const KeyType& key) {
    
    for (int i = 0; i < m_nNodes; i++) {        //  checks if there is a duplicate
        if (m_Items[i].key == key) {
            for (int j = i; j < m_nNodes; j++) {        //  deletes the struct data by overwriting w/ rest of structs in array
                m_Items[j] = m_Items[j + 1];
            }
            m_nNodes--;
            return true;
        }
    }
    return false;
}
 
// Return true if key is equal to a key currently in the map, otherwise
// false.
bool Map::contains(const KeyType& key) const {
    for (int i = 0; i < m_nNodes; i++) {        //  checks if there is a duplicate
        if (m_Items[i].key == key) {
            return true;
        }
    }
    return false;
}
 
// If key is equal to a key currently in the map, set value to the
// value in the map which that key maps to, and return true.  Otherwise,
// make no change to the value parameter of this function and return
// false.
bool Map::get(const KeyType& key, ValueType& value) const {
    for (int i = 0; i < m_nNodes; i++) {        //  checks if there is a duplicate
        if (m_Items[i].key == key) {
            value = m_Items[i].value;
            return true;
        }
    }
    return false;
}
 
// If 0 <= i < size(), copy into the key and value parameters the
// key and value of the key/value pair in the map whose key is strictly
// greater than exactly i keys in the map and return true.  Otherwise,
// leave the key and value parameters unchanged and return false.
bool Map::get(int i, KeyType& key, ValueType& value) const {
    if (0 <= i && i < m_nNodes) {
        key = m_Items[i].key;
        value = m_Items[i].value;
        return true;
    }
    return false;
}
 
// Exchange the contents of this map with the other one.
void Map::swap(Map& other) {
    //Map temp(other);
    m_Node * temp = other.m_Items;
    int temp_m_x = other.m_x;
    int temp_m_nNodes = other.m_nNodes;
    
    other.m_nNodes = m_nNodes;      //   int
    other.m_x = m_x;                //   int
    other.m_Items = m_Items;        //  pointer to an array
    
    
    m_nNodes = temp_m_nNodes;
    m_x = temp_m_x;
    m_Items = temp;

}



 
void Map::Dump() const{
    
    for (int i = 0; i < m_nNodes; i++) {
        std::cerr << m_Items[i].key << ", " << m_Items[i].value << std::endl;
       
    }
    std::cerr << m_nNodes << endl;
    
}

