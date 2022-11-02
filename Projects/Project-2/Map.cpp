//
//  Map.cpp
//  Homework-1
//
//  Created by Ashvin Bondada on 1/17/22.
//
 
#include "Map.h"
#include <iostream>
#include <string>
using namespace std;
 
Map::Map() {
    
    head = nullptr;
    // creates an empty Map
    
}


Map::Map(const Map& old) {
    head = nullptr;
    m_Node * p = old.head;
    while (p != nullptr) {          //  creates a new map using insert function by traversing thru old map
        KeyType a = p->key;         //  copying over old key,value pair into temp variables
        ValueType b = p->value;
        insert(a, b);               //   automatically initializes m_nNodes to right value (no need to copy it over)
        p = p->next;
    }
}


Map& Map::operator=(const Map& src) {
    if (this != &src)
    {
        Map temp(src);          //  create a temp map and swap it into target map
        swap(temp);
    }
    return *this;
}                               //  temp is deleted by destructor at end of function (no memory leak)

 
Map::~Map() {                   //  From Nachenberg's lecture
    m_Node *p;
    p = head;
    while (p != nullptr) {      //  delete one node after the next
        m_Node *n = p->next;
        delete p;
        p = n;
    }
}


bool Map::empty() const{
    if (head == nullptr) {       //  Checks if linked list is empty, returns false if not
        return true;
    }
    return false;
}
 

//  Returns number of nodes (key/value) pairs in map
int Map::size() const{
    return m_nNodes;
}
 
// If key is not equal to any key currently in the map, and if the
// key/value pair can be added to the map, then do so and return true.
// Otherwise, make no change to the map and return false (indicating
// that either the key is already in the map, or the map has a fixed
// capacity and is full).
 
bool Map::insert(const KeyType& key, const ValueType& value) {
    
    if (head == nullptr) {  // if its empty, add first node,
        m_Node * a = new m_Node;
        a->key = key;
        a->value = value;
        a->next = head;             //  initialize a to point towards prev head(null) and then dummy head to point to a
        head = a;
        a->prev = nullptr;          //  set prev pointer to null to signify beginning of list
        m_nNodes++;
        return true;
        
    }
    
    //  check if key is already in list
    m_Node *p;
    p = head;
    while (p != nullptr) {      //  traverse until key parameter matches some key possibly in list
        if (key == p->key)
            return false;
        p = p->next;
    }
    
    //  BEGINNING OF LIST
    if (key > head->key) {          //  if key parameter has greatest ascii value, enter at the top
        m_Node * a = new m_Node;
        a->key = key;
        a->value = value;
        head->prev = a;             //  must set old head's prev to new head's address, rest is unchanged from add to empty list code
        a->prev = nullptr;
        a->next = head;
        head = a;
        m_nNodes++;
        return true;
    }
    
    // END OF LIST
    m_Node * endList;
    endList = head;
    while (endList != nullptr && endList->next != nullptr) {  //  traverse to the last node of the list and set endList  eaual to last node's addr
        endList = endList->next;
    }
    
    if (key < endList->key) {               //  check if key parameter is a lower ascii value than current last, then add it
        m_Node * addMe = new m_Node;
        addMe->key = key;                   //  copy in the parameters into a new node
        addMe->value = value;
        endList->next = addMe;              // connect old end's next ptr to new end
        addMe->prev = endList;              // connect new end's prev to old end's address
        addMe->next = nullptr;              // set new end's next ptr to null
        m_nNodes++;
        return true;
    }

    // MIDDLE OF LIST
    else {
        m_Node * n = head;
        while (n != nullptr) {              //   traverse list to find the node just above where node must be inserted
            if (key > n->next->key) {
                break;
            }
            n = n->next;
        }
        m_Node * addMe = new m_Node;       //   create a new node to copy key/value parameters into
        addMe->key = key;
        addMe->value = value;
                                            //   switching pointers..
        addMe->next = n->next;              //  connect new node next ptr to addr of node which will be below it, which is stored in n->next
        n->next->prev = addMe;              //  connect new node to prev pointer of node below it
        n->next = addMe;                    //  connect next ptr in node above new node to addr of addMe
        addMe->prev = n;                    //  connect new node's prev ptr to node above it
        
        m_nNodes++;
        return true;
    }
}


// If key is equal to a key currently in the map, then make that key no
// longer map to the value that it currently maps to, but instead map to
// the value of the second parameter; return true in this case.
// Otherwise, make no change to the map and return false.
bool Map::update(const KeyType& key, const ValueType& value) {
    
    m_Node *p = head;
    while (p != nullptr) {      //  traverse list to see if key parameters matches possible key in list
        if (key == p->key) {
            p->value = value;
            return true;
        }
        p = p->next;
    }
    return false;
    
}
 
 
bool Map::insertOrUpdate(const KeyType& key, const ValueType& value) {      //  should always return true -> no limit on linked list
    if (insert(key, value))
        return true;
    else if (update(key, value))
        return true;
    return false;
}
 
 
bool Map::erase(const KeyType& key) {       // adapted from Nachenberg slides
    if (head == nullptr)    //  if the list is empty, cant delete anything
        return false;
    if (head->key == key) {     // if node must be deleted from top, allocate a temp node to delete data at head ptr and redefine head node
            m_Node *killMe = head;
            head = killMe->next;
            if (m_nNodes > 1)                  //  if only 1 node in list, killMe->next ptr = nullptr so just delete the entire node instead, else
                killMe->next->prev = nullptr;  //     set prev ptr of new head node(used to be second node) to null to signify new beginning of list
            delete killMe;
            m_nNodes--;     //  sub from running total
            return true;
        }
    
    m_Node *p = head;
    while (p != nullptr) {          //  Traverse to find key/value pair in MIDDLE/END of list to delete, then break out
        
        if (p->next != nullptr && p->next->key == key) {
            break;
            }
            p = p->next;
        }
    
        if (p != nullptr) {     // if  found a duplicate while not passing thru end of the list, then allocate killMe ptr and delete data
            m_Node * killMe = p->next;
            
            if (p->next->next != nullptr && p->next->key == key) {  //  update the prev pointer if and only if node being deleted is not the last node and key
                p->next->next->prev = p;                            //  matches, because if its the last node, the new last node (current second to last node)
            }                                                       //  will correctly point back to previous node after deletion. Instead, program will delete
                                                                    //  current last's node prev pointer along with other data
                
            
            p->next = p->next->next;    //  regular deletion: set p to point towards node below one that is being deleted
            delete killMe;
            m_nNodes--;
            return true;
        }
        return false;       //  if no key is found in the loop, return false
    }
 
 
 
// Return true if key is equal to a key currently in the map, otherwise
// false.
bool Map::contains(const KeyType& key) const {
    m_Node *p = head;
    while (p != nullptr) {
        if (key == p->key) {    //  check if key is already in list, return true else return false
            return true;
        }
        p = p->next;
    }
    return false;
}
 
 
// If key is equal to a key currently in the map, set value to the
// value in the map which that key maps to, and return true.  Otherwise,
// make no change to the value parameter of this function and return
// false.
bool Map::get(const KeyType& key, ValueType& value) const {
    m_Node *p = head;
    while (p != nullptr) {          //  traverse linked list to find match
        if (key == p->key) {
            value = p->value;
            return true;
        }
        p = p->next;
    }
    return false;
}
 
 
// If 0 <= i < size(), copy into the key and value parameters the
// key and value of the key/value pair in the map whose key is strictly
// greater than exactly i keys in the map and return true.  Otherwise,
// leave the key and value parameters unchanged and return false.
bool Map::get(int i, KeyType& key, ValueType& value) const {
    m_Node * p = head;
    if (0 <= i && i < size()) {
        for (int j = 0; j + 1 < m_nNodes - i; j++ ){    //  Use (i + 1) to traverse the list up until last node (not past it) or else  p can be nullptr (bad!)
            p = p->next;                                //  List is ordered from Z-A (greater ascii to lower), so subtract i from m_nNodes to find correct pair
        }                                               //      Ex: In a list of 3, find i = 2 (pair greater than exactly 2 keys), program will do 3 - 2 = 1
        key = p->key;                                   //      and selects 1st node (head node which is greater than other 2 in the list of 3)
        value = p->value;
        return true;
    }
    else {
        return false;
    }
}
 
 
// Exchange the contents of this map with the other one.
void Map::swap(Map& other) {

    m_Node * swaphead;              //  create a temporary pointer to hold this head value and swap dummy head ptrs
    swaphead = head;
    head = other.head;
    other.head = swaphead;
    
    
    int temp_nNodes = m_nNodes;     //  simply swap the m_nodes
    m_nNodes = other.m_nNodes;
    other.m_nNodes = temp_nNodes;
}
 
 
 
void Map::Dump() const{     //  prints using prev and next ptrs to validate doubly-linked functionality
    // printing using next pointer
    m_Node * p;
    p = head;
    while (p != nullptr) {    //  traversing through list
        cerr << p->key << ", " << p->value << endl;
        p = p->next;
    }
    
    cerr << "\n=====\n" << endl;
    
    //  printing using prev pointer
    m_Node * endList;
    endList = head;
    while (endList != nullptr && endList->next != nullptr) {  //  traverse to end of list
        endList = endList->next;
    }
    while (endList != nullptr) {   //   traverse from bottom to top using prev pointer
        cerr << endList->key << ", " << endList->value << endl;
        endList = endList->prev;
    }

}
 

bool merge(const Map& m1, const Map& m2, Map& result) {
    // insert m2 into m1
    KeyType a;
    ValueType b, c;
    int dupCounter = 0;
    Map temp;
    

    for (int i = 0; i < m2.size(); i++) {
        m2.get(i, a, b);                    //  get a' values from m2 and a's corresponding value in m1
        m1.get(a, c);
        if ((m1.contains(a)) && (m2.contains(a)) && (b != c)) { //  if m2's key matches m1's key, but values are DIFF, then skip adding it to list
            dupCounter++;                   //  keep track of duplicates found
            continue;
        }
        temp.insert(a, b);
    }
        
    for (int i = 0; i < m1.size(); i++) {       //  do the same thing but compare m1 to m2 map instead of previously comparing m2 to m1 map
        m1.get(i, a, b);
        m2.get(a, c);
        if ((m1.contains(a)) && (m2.contains(a)) && (b != c)) {
            dupCounter++;
            continue;
            }
            temp.insert(a, b);
        }
    result = temp;      //  inserting in temp map and then assigning to result, clears all data in result no matter what
    if (dupCounter > 0) //  if matching keys's but diff corresponding values were found, return false
        return false;
    else
        return true;
}

void reassign(const Map& m, Map& result) {          //  STRATEGY: shift each value one space over and move head's value into tail node
    KeyType a, tempk;
    ValueType b, c, tempv;
    Map temp(m);           //  create a temporary map, because m and result point to same map and if m is altered then
                                //      data from Map m will not be right for future swaps
    if (m.size() > 1) {
        m.get(0, tempk, tempv);             //  temporarily store tail node's key (tempk) and head's value (tempv) for head to tail insertion at end of func
        m.get(m.size() - 1, a, tempv);
        
        for (int i = 0; i + 1 < m.size(); i++) {    //  Starting from the bottom, get a node's key and the node above its' value
                                                    //      and insert it into a temp map until reaching the top of list
            m.get(i, a, b);
            m.get(i + 1, a, c);
            temp.insertOrUpdate(a, b);
        }

        temp.insertOrUpdate(tempk, tempv);      //  Insert previously stored tail node key and head value into tail of temp list and copy into result
        result = temp;
    }
    else {      //  assuming size of map is 1 or even 0, just return original map,
        result = temp;
    }
}
