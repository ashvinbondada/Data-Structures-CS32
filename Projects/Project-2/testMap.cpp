////
////
//////
//////  testMap.cpp
//////  Homework-1-copy
//////
//////  Created by Ashvin Bondada on 1/17/22.
//////
////
#include <iostream>
#include <string>
#include <cassert>
#include "Map.h"
using namespace std;

int main() {

    Map a, b;

    // test insert function
    a.insert("Ashvin", 3.999);        //    tests adding to empty list
    a.insert("Aaron", 4.890);        //    tests adding to front of list
    a.insert("Zion", 3.556);        //    tests adding to end of list
    a.insert("Bella", 3.987);        //    test adding to middle of list
    assert(!a.insert("Ashvin", 3.098));      //   fail, ashvin already exists
    a.Dump();
    //  pass: a.Dump() prints in order of Zion, Bella, Ashvin, Aaron using next ptr and list in order of Aaron, Ashvin, Bella, Zion using prev ptr to verify doubly linked functionality
    //test size and contains functionality
    assert((a.size() == 4) && a.contains("Ashvin") && a.contains("Zion") && a.contains("Bella") && a.contains("Aaron"));
    //should compile successfully showing size and contains work

    //test get(KeyType, ValueType)
    ValueType u = 6;
    assert(a.get("Zion", u) && u == 3.556);     //  pass:  testing get head node, Zion is 3.556
    assert(a.get("Aaron", u) && u == 4.890);     //   pass: testing get tail node, Aaron is 3.556
    assert(a.get("Bella", u) && u == 3.987);     //   pass: testing get middle node, Bella is 3.556
//test update function
    ValueType v = 5;
    ValueType w = 6;
    a.update("Zion", v);                    //  tests updating head of list - Zion currently 3.556
    a.update("Aaron", v);                   //  tests updating tail of list - Aaron currently 4.890
    a.update("Bella", v);                   //  tests updating middle of list - Bella currently 3.987
    assert(!a.update("Aishu", 3.456));      //  fail to update "Aishu" not in map
    assert(a.get("Zion", w) && w == 5);     //  pass if function updated -> Zion is 5
   assert(a.get("Aaron", w) && w == 5);     //  pass if function updated -> Aaron is 5
    assert(a.get("Bella", w) && w == 5);     //  pass if function updated  -> Bella is 5
//test insertOrUpdate function
    v = 10;
    ValueType k;
    a.insertOrUpdate("Landon", 4.000);      //  insert of update middle
    a.insertOrUpdate("Ashvin", v);        //    update ashvin from 3.999 -> 10
    a.insertOrUpdate("", 2.897);        //    inserts empty string, 2.987
    a.insertOrUpdate("Johnny Appleseed", 2.900);    // inserts new string
    a.insertOrUpdate("Johnny Appleseed", 3.011);    // Johnny Appleseed should be 3.011 now
    assert(a.get("Johnny Appleseed", w) && w == 3.011);    // pass if “update”  and insert works
    assert(a.get("Ashvin", k) && k == 10);            // pass if just “update” works
    assert(a.contains("Landon") && a.contains(""));        // pass if update works
    assert(a.size() == 7);      //  tests running total of nodes
//test erase function
    a.insert("Aaron", 4.989);
    a.insert("Zzedd", 4.000);
    assert(!a.erase("zzedd"));      //   fail -> case sensitive
    assert(a.erase(""));            //  tests erase works for empty string
    a.erase("Aaron");               //  test erase for tail node
    a.erase("Johnny Appleseed");    //  test erase for middle node
    a.erase("Zzedd");               //  test erase for head node
    assert(a.size() == 4 && (!a.contains("")) && (!a.contains("Aaron")) && (!a.contains("Johnny Appleseed")));      //  pass if delete works
//test 2nd get function
    a.insert("", 2.897);            //  test if insert takes empty string and sorts it to tail
    KeyType j;
    a.get(0, j, k);                 //  tests “get” for tail node of linked list
    assert(j == "" && k == 2.897);  // pass
    a.get(2, j, k);                 //  tests “get” for middle node of linked list
    assert(j == "Bella" && k == 5);  //  pass
    a.get(4, j, k);                 //  tests “get” for head node of linked list
    assert(j == "Zion" && k == 5);  //  pass
    assert(!a.get(5, j, k));        //  should fail because there are only 5 nodes in the map

//test swap function
    b.insert("Amanda", 2.895);
    b.insert("John", 3.348);
    b.insert("Abu", 2.136);

    assert(a.size() == 5 && a.contains("") && a.contains("Ashvin") && a.contains("Bella") && a.contains("Landon") && a.contains("Zion"));
    assert(b.size() == 3 && b.contains("Amanda") && b.contains("John") && b.contains("Abu"));
    a.swap(b);  //  swaps a and b
    assert(b.size() == 5 && b.contains("") && b.contains("Ashvin") && b.contains("Bella") && b.contains("Landon") && b.contains("Zion"));
    assert(a.size() == 3 && a.contains("Amanda") && a.contains("John") && a.contains("Abu"));

    b.swap(a);  //  should swap back into original form, assert below should pass if true
    assert(a.size() == 5 && a.contains("") && a.contains("Ashvin") && a.contains("Bella") && a.contains("Landon") && a.contains("Zion"));
    assert(b.size() == 3 && b.contains("Amanda") && b.contains("John") && b.contains("Abu"));
// test copy constructor
    Map c(b);
    b.erase("Amanda");
    //  assert tests if b does not contain Amanda but c does contain Amanda and size func
    assert(b.size() == 2 && (!b.contains("Amanda")) && b.contains("John") && b.contains("Abu"));
    assert(c.size() == 3 && c.contains("Amanda") && c.contains("John") && c.contains("Abu"));

Map e;      //   testing empty map
    Map f(e);
    assert((e.size() == 0) && f.size() == 0);    //    both sizes should be 0

 // test assignment operator
    assert(c.size() == 3 && c.contains("Amanda") && c.contains("John") && c.contains("Abu"));   // verify c not equal to a
    c = a;        //    test for 2 typical maps
    // test a and c with the same arguments -> both should pass if c = a
    assert(a.size() == 5 && a.contains("") && a.contains("Ashvin") && a.contains("Bella") && a.contains("Landon") && a.contains("Zion"));
    assert(c.size() == 5 && c.contains("") && c.contains("Ashvin") && c.contains("Bella") && c.contains("Landon") && c.contains("Zion"));

    Map g;  //   trying empty map
    assert(g.size() == 0);  // verify g is empty
    c = g;
    assert((c.size() == 0) && g.size() == 0);   //  test passes if g is copied over

//test merge function
    Map o, p, finalmap;

    o.insert("Widow", 1);      //  tests head node in "o" with EQUAL key in "p", UNEQUAL value
    o.insert("Banner", 1);     //  tests tail node in "o"  with EQUAL key in "p", UNEQUAL value
    o.insert("Purple", 1);     //  tests middle node in "o" with EQUAL key in "p", UNEQUAL value
    o.insert("Caillou", 1);
    o.insert("Neo", 3.987);    //  tests node in 'o' with EQUAL key & same EQUAL in "p"
    o.insert("Youtube", 1);
    o.insert("Friends", 1);
    o.insert("Power", 1);

    p.insert("Widow", 0);       //  equal in key "o"
    p.insert("Banner", 0);      //  equal in key "o"
    p.insert("Purple", 0);      //  equal in key "o"
    p.insert("Chris", 0);
    p.insert("Neo", 3.987);     //  equal in key and pair in "o"
    p.insert("Tony", 0);

    finalmap.insert("Bruce", 2);    // final map is not empty for this test
    finalmap.insert("Natasha", 2);
    finalmap.insert("Pratt", 2);
    finalmap.insert("ashvin", 2);

    merge(o, p, finalmap);    //  tests merge if 1)same key/pair value in m1 & m2, 2)same key &
        //       diff value pair, 3)result is not empty
    ValueType neo;
       //  finalmap should not have Widow, Purple, Banner, but have Neo, 3.987 pair, and should
       //      NOT have finalmap's original pairs too
    assert(finalmap.contains("Youtube") && finalmap.contains("Tony") && finalmap.contains("Power") && finalmap.get("Neo", neo) && neo == 3.987 && finalmap.contains("Friends") && finalmap.contains("Chris") && finalmap.contains("Caillou") && !finalmap.contains("Widow") && !finalmap.contains("Purple") && !finalmap.contains("Banner") );

    Map r;  //  test merge if result map is empty
    merge(o, p, r);
    assert(r.contains("Youtube") && r.contains("Tony") && r.contains("Power") && r.get("Neo", neo) && neo == 3.987 && r.contains("Friends") && r.contains("Chris") && r.contains("Caillou") && !r.contains("Widow") && !r.contains("Purple") && !r.contains("Banner") );

    Map h;  //  test merge if m1 = m2 = result = Map h
    h.insert("Bruce", 2);
    h.insert("Natasha", 2);
    h.insert("Pratt", 2);
    // verify h is same as h after reassign
    assert(h.contains("Bruce") && h.contains("Natasha") && h.contains("Pratt"));
    merge(h, h, h); //  test all parameters point to same func
    assert(h.contains("Bruce") && h.contains("Natasha") && h.contains("Pratt"));

//test reassign function
    Map t;

    t.insert("Banner", 0);
    t.insert("Power", 4);
    t.insert("Caillou", 1);
    t.insert("Friends", 2);
    t.insert("Neo", 3);

    ValueType z;
    assert(t.get("Power", z) && z == 4);    //  values are in order from 4 -> 0
    assert(t.get("Neo", z) && z == 3);
    assert(t.get("Friends", z) && z == 2);
    assert(t.get("Caillou", z) && z == 1);
    assert(t.get("Banner", z) && z == 0);
    reassign(t, t);             //  reassign function programmed to swap every value by shifting up
    assert(t.get("Power", z) && z == 3);    //  values have now shifted up 1
    assert(t.get("Neo", z) && z == 2);
    assert(t.get("Friends", z) && z == 1);
    assert(t.get("Caillou", z) && z == 0);
    assert(t.get("Banner", z) && z == 4);
    reassign(t, t);             //  test reassign again
    assert(t.get("Power", z) && z == 2);    //  values shifted up 1 again
    assert(t.get("Neo", z) && z == 1);
    assert(t.get("Friends", z) && z == 0);
    assert(t.get("Caillou", z) && z == 4);
    assert(t.get("Banner", z) && z == 3);


    Map y;                  //  test reassign for just one pair
    y.insert("Bose", 3);
    reassign(y, y);
    assert(y.contains("Bose"));

    Map q;              //  checking for empty map
    reassign(q, q);
    assert(q.size() == 0);


    cerr << "All tests worked" << endl;


    return 0;
}
////
////
////// smallberg tests
/////*
////#include "Map.h"
////#include <type_traits>
////
////       #define CHECKTYPE(f, t) (void(static_cast<t>(f)))
////
////       static_assert(std::is_default_constructible<Map>::value,
////               "Map must be default-constructible.");
////       static_assert(std::is_copy_constructible<Map>::value,
////               "Map must be copy-constructible.");
////       static_assert(std::is_copy_assignable<Map>::value,
////               "Map must be assignable.");
////
////       void thisFunctionWillNeverBeCalled()
////       {
////           CHECKTYPE(&Map::operator=,      Map& (Map::*)(const Map&));
////           CHECKTYPE(&Map::empty,          bool (Map::*)() const);
////           CHECKTYPE(&Map::size,           int  (Map::*)() const);
////           CHECKTYPE(&Map::insert,         bool (Map::*)(const KeyType&, const ValueType&));
////           CHECKTYPE(&Map::update,         bool (Map::*)(const KeyType&, const ValueType&));
////           CHECKTYPE(&Map::insertOrUpdate, bool (Map::*)(const KeyType&, const ValueType&));
////           CHECKTYPE(&Map::erase,          bool (Map::*)(const KeyType&));
////           CHECKTYPE(&Map::contains,       bool (Map::*)(const KeyType&) const);
////           CHECKTYPE(&Map::get,            bool (Map::*)(const KeyType&, ValueType&) const);
////           CHECKTYPE(&Map::get,            bool (Map::*)(int, KeyType&, ValueType&) const);
////           CHECKTYPE(&Map::swap,           void (Map::*)(Map&));
////
////           CHECKTYPE(merge,  bool (*)(const Map&, const Map&, Map&));
////           CHECKTYPE(reassign, void (*)(const Map&, Map&));
////       }
////
////       int main()
////       {}
////*/
/////*
////#include "Map.h"
////#include <iostream>
////#include <cassert>
////       using namespace std;
////
////       void test()
////       {
////           Map m;
////           assert(m.insert("Fred", 123));
////           assert(m.insert("Ethel", 456));
////           assert(m.size() == 2);
////           ValueType v = 42;
////           assert(!m.get("Lucy", v)  &&  v == 42);
////           assert(m.get("Fred", v)  &&  v == 123);
////           v = 42;
////           KeyType x = "Lucy";
////           assert(m.get(0, x, v)  &&
////                  ((x == "Fred"  &&  v == 123)  ||  (x == "Ethel"  &&  v == 456)));
////           KeyType x2 = "Ricky";
////           assert(m.get(1, x2, v)  &&
////                  ((x2 == "Fred"  &&  v == 123)  ||  (x2 == "Ethel"  &&  v == 456))  &&
////                  x != x2);
////       }
////
////       int main()
////       {
////           test();
////           cout << "Passed all tests" << endl;
////       }
////*/
/////*
////#include "Map.h"
////#include <iostream>
////#include <cassert>
////        using namespace std;
////
////        void test()
////        {
////            Map m;
////            assert(m.insert(10, "diez"));
////            assert(m.insert(20, "veinte"));
////            assert(m.size() == 2);
////            ValueType v = "cuarenta y dos";
////            assert(!m.get(30, v)  &&  v == "cuarenta y dos");
////            assert(m.get(10, v)  &&  v == "diez");
////            v = "cuarenta y dos";
////            KeyType x = 30;
////            assert(m.get(0, x, v)  &&
////                   ((x == 10  &&  v == "diez")  ||  (x == 20  &&  v == "veinte")));
////            KeyType x2 = 40;
////            assert(m.get(1, x2, v)  &&
////                   ((x2 == 10  &&  v == "diez")  ||  (x2 == 20  &&  v == "veinte"))  &&
////                   x != x2);
////        }
////
////        int main()
////        {
////            test();
////            cout << "Passed all tests" << endl;
////        }
////*/
//////
//////#define TESTNEW
//////
//////#ifdef TESTNEW
//////#include "Map.h"
//////#else
//////#include "Map.h"
//////#endif
//////
//////#include <iostream>
//////#include <cstdlib>
//////#include <cassert>
//////#include <type_traits>
//////using namespace std;
//////
//////const KeyType DUMMY = "junk";
//////const KeyType DEFAULT = "";
//////const KeyType ARRAY[6] = {
//////    "alfa", "baker", "charlie", "delta", "echo", "foxtrot"
//////};
//////
//////const ValueType DUMMYV = 123;
//////const ValueType DEFAULTV = 0;
//////const ValueType ARRAYV[6] = { 10, 20, 30, 40, 50, 60 };
//////
//////bool has(const Map& m, const KeyType& k, const ValueType& v)
//////{
//////    ValueType v2 = DEFAULTV;
//////    m.get(k, v2);
//////    ValueType v3 = DUMMYV;
//////    m.get(k, v3);
//////    return v2 == v  &&  v3 == v;
//////}
//////
//////const int SPEC_MAX = 260;
//////
//////bool get2type(bool (Map::*)(const KeyType&, ValueType&) const) { return true; }
//////bool get2type(bool (Map::*)(const KeyType&, ValueType&)) { return false; }
//////bool get2type(...) { return false; }
//////bool get3type(bool (Map::*)(int, KeyType&, ValueType&) const) { return true; }
//////bool get3type(bool (Map::*)(int, KeyType&, ValueType&)) { return false; }
//////bool get3type(...) { return false; }
//////
//////void testone(int n)
//////{
//////    if (n <= 5)
//////    {
//////        switch (n)
//////        {
//////                 default: {
//////        cout << "Bad argument" << endl;
//////            } break; case  1: {
//////        assert((is_same<decltype(&Map::empty), bool (Map::*)() const>::value));
//////            } break; case  2: {
//////        assert((is_same<decltype(&Map::size), int (Map::*)() const>::value));
//////            } break; case  3: {
//////        assert((is_same<decltype(&Map::contains), bool (Map::*)(const KeyType&) const>::value));
//////            } break; case  4: {
//////        assert(get2type(&Map::get));
//////            } break; case  5: {
//////        assert(get3type(&Map::get));
//////            }
//////        }
//////        return;
//////    }
//////    Map m;
//////    switch (n)
//////    {
//////                 default: {
//////        cout << "Bad argument" << endl;
//////            } break; case  1: {
//////        assert((is_same<decltype(&Map::empty), bool (Map::*)() const>::value));
//////            } break; case  2: {
//////        assert((is_same<decltype(&Map::size), int (Map::*)() const>::value));
//////            } break; case  3: {
//////        assert((is_same<decltype(&Map::contains), bool (Map::*)(const KeyType&) const>::value));
//////            } break; case  4: {
//////        assert(get2type(&Map::get));
//////            } break; case  5: {
//////        assert(get3type(&Map::get));
//////            } break; case  6: {
//////        assert(m.empty());
//////            } break; case  7: {
//////        assert(m.size() == 0);
//////            } break; case  8: {
//////        assert(!m.update(DEFAULT, DUMMYV)  &&  m.size() == 0);
//////            } break; case  9: {
//////        assert(!m.erase(DEFAULT)  &&  m.size() == 0);
//////            } break; case 10: {
//////        assert(!m.contains(DEFAULT));
//////            } break; case 11: {
//////        ValueType v = DUMMYV;
//////        assert(!m.get(DEFAULT, v)  &&  v == DUMMYV);
//////            } break; case 12: {
//////        KeyType k = DEFAULT;
//////        ValueType v = DUMMYV;
//////        assert(!m.get(0, k, v)  &&  k == DEFAULT  &&  v == DUMMYV);
//////            } break; case 13: {
//////        assert(m.insert(DUMMY, DUMMYV));
//////            } break; case 14: {
//////        m.insert(DUMMY, DUMMYV);
//////        assert(!m.empty());
//////            } break; case 15: {
//////        m.insert(DUMMY, DUMMYV);
//////        assert(m.size() == 1);
//////            } break; case 16: {
//////        m.insert(DUMMY, DUMMYV);
//////        assert(m.contains(DUMMY));
//////            } break; case 17: {
//////        m.insert(DUMMY, DUMMYV);
//////        ValueType v = DEFAULTV;
//////        assert(m.get(DUMMY, v));
//////            } break; case 18: {
//////        m.insert(DUMMY, DUMMYV);
//////        ValueType v = DEFAULTV;
//////        m.get(DUMMY, v);
//////        assert(v == DUMMYV);
//////            } break; case 19: {
//////        m.insert(ARRAY[1], DUMMYV);
//////        ValueType v = DEFAULTV;
//////        assert(!m.get(ARRAY[0], v)  &&  !m.get(ARRAY[2], v));
//////            } break; case 20: {
//////        m.insert(ARRAY[1], ARRAYV[1]);
//////        ValueType v = DUMMYV;
//////        m.get(ARRAY[0], v);
//////        assert(v == DUMMYV);
//////        m.get(ARRAY[2], v);
//////        assert(v == DUMMYV);
//////            } break; case 21: {
//////        m.insert(DUMMY, DUMMYV);
//////        KeyType k = DEFAULT;
//////        ValueType v = DEFAULTV;
//////        assert(m.get(0, k, v));
//////            } break; case 22: {
//////        m.insert(DUMMY, DUMMYV);
//////        KeyType k = DEFAULT;
//////        ValueType v = DEFAULTV;
//////        m.get(0, k, v);
//////        assert(k == DUMMY  &&  v == DUMMYV);
//////            } break; case 23: {
//////        m.insert(ARRAY[0], ARRAYV[0]);
//////        m.insert(ARRAY[1], ARRAYV[1]);
//////        assert(!m.empty()   &&  m.size() == 2);
//////            } break; case 24: {
//////        m.insert(ARRAY[0], ARRAYV[0]);
//////        m.insert(ARRAY[1], ARRAYV[1]);
//////        assert(m.contains(ARRAY[0])  &&  m.contains(ARRAY[1]));
//////            } break; case 25: {
//////        m.insert(ARRAY[1], ARRAYV[1]);
//////        m.insert(ARRAY[0], ARRAYV[0]);
//////        assert(has(m, ARRAY[0], ARRAYV[0])  &&  has(m, ARRAY[1], ARRAYV[1]));
//////            } break; case 26: {
//////        m.insert(ARRAY[0], DUMMYV);
//////        m.insert(ARRAY[1], DUMMYV);
//////        assert(has(m, ARRAY[0], DUMMYV)  &&  has(m, ARRAY[1], DUMMYV));
//////            } break; case 27: {
//////        assert(m.insert(ARRAY[1], ARRAYV[1]));
//////        assert(m.insert(ARRAY[0], ARRAYV[0]));
//////            } break; case 28: {
//////        m.insert(ARRAY[0], ARRAYV[0]);
//////        m.insert(ARRAY[1], ARRAYV[1]);
//////        m.insert(ARRAY[0], ARRAYV[2]);
//////        assert(m.size() == 2);
//////            } break; case 29: {
//////        m.insert(ARRAY[1], ARRAYV[1]);
//////        m.insert(ARRAY[0], ARRAYV[0]);
//////        m.insert(ARRAY[1], ARRAYV[2]);
//////        assert(has(m, ARRAY[0], ARRAYV[0])  &&  has(m, ARRAY[1], ARRAYV[1]));
//////            } break; case 30: {
//////        assert(m.insert(ARRAY[0], ARRAYV[0]));
//////        assert(m.insert(ARRAY[1], ARRAYV[1]));
//////        assert(!m.insert(ARRAY[0], ARRAYV[2]));
//////            } break; case 31: {
//////        assert(m.insert(ARRAY[1], ARRAYV[1]));
//////        assert(m.insert(ARRAY[0], ARRAYV[0]));
//////        assert(!m.insert(ARRAY[1], ARRAYV[1]));
//////            } break; case 32: {
//////        m.insert(ARRAY[0], ARRAYV[0]);
//////        m.insert(ARRAY[1], ARRAYV[1]);
//////        m.insert(ARRAY[2], ARRAYV[2]);
//////        m.update(ARRAY[1], DUMMYV);
//////        assert(m.size() == 3  &&  m.contains(ARRAY[0])  &&
//////            m.contains(ARRAY[1])  &&  m.contains(ARRAY[2]));
//////            } break; case 33: {
//////        m.insert(ARRAY[0], ARRAYV[0]);
//////        m.insert(ARRAY[1], ARRAYV[1]);
//////        m.insert(ARRAY[2], ARRAYV[2]);
//////        m.update(ARRAY[1], DUMMYV);
//////        assert(has(m, ARRAY[0], ARRAYV[0])  &&  has(m, ARRAY[1], DUMMYV)  &&
//////                        has(m, ARRAY[2], ARRAYV[2]));
//////            } break; case 34: {
//////        m.insert(ARRAY[0], ARRAYV[0]);
//////        m.insert(ARRAY[1], ARRAYV[1]);
//////        m.insert(ARRAY[2], ARRAYV[2]);
//////        assert(m.update(ARRAY[1], DUMMYV));
//////            } break; case 35: {
//////        m.insert(ARRAY[0], ARRAYV[0]);
//////        m.insert(ARRAY[1], ARRAYV[1]);
//////        m.update(ARRAY[2], ARRAYV[0]);
//////        assert(m.size() == 2  &&  has(m, ARRAY[0], ARRAYV[0])  &&
//////            has(m, ARRAY[1], ARRAYV[1])  &&  !m.contains(ARRAY[2]));
//////            } break; case 36: {
//////        m.insert(ARRAY[0], ARRAYV[0]);
//////        m.insert(ARRAY[1], ARRAYV[1]);
//////        assert(!m.update(ARRAY[2], ARRAYV[2])  &&  !m.update(ARRAY[3], ARRAYV[0]));
//////            } break; case 37: {
//////        m.insert(ARRAY[1], ARRAYV[1]);
//////        m.insertOrUpdate(ARRAY[0], ARRAYV[0]);
//////        assert(!m.empty()   &&  m.size() == 2);
//////            } break; case 38: {
//////        m.insert(ARRAY[0], ARRAYV[0]);
//////        m.insertOrUpdate(ARRAY[1], ARRAYV[1]);
//////        assert(has(m, ARRAY[0], ARRAYV[0])  &&  has(m, ARRAY[1], ARRAYV[1]));
//////            } break; case 39: {
//////        m.insert(ARRAY[0], DUMMYV);
//////        m.insertOrUpdate(ARRAY[1], DUMMYV);
//////        assert(has(m, ARRAY[0], DUMMYV)  &&  has(m, ARRAY[1], DUMMYV));
//////            } break; case 40: {
//////        assert(m.insert(ARRAY[1], ARRAYV[1]));
//////        assert(m.insertOrUpdate(ARRAY[0], ARRAYV[0]));
//////            } break; case 41: {
//////        m.insert(ARRAY[0], ARRAYV[0]);
//////        m.insert(ARRAY[1], ARRAYV[1]);
//////        m.insertOrUpdate(ARRAY[0], ARRAYV[2]);
//////        assert(m.size() == 2  &&  has(m, ARRAY[0], ARRAYV[2])  &&
//////                        has(m, ARRAY[1], ARRAYV[1]));
//////            } break; case 42: {
//////        assert(m.insert(ARRAY[0], ARRAYV[0]));
//////        assert(m.insert(ARRAY[1], ARRAYV[1]));
//////        assert(m.insertOrUpdate(ARRAY[0], ARRAYV[2]));
//////            } break; case 43: {
//////        m.insert(ARRAY[0], ARRAYV[0]);
//////        m.insert(ARRAY[1], ARRAYV[1]);
//////        m.insert(ARRAY[2], ARRAYV[2]);
//////        m.insertOrUpdate(ARRAY[1], DUMMYV);
//////        assert(m.size() == 3  &&  has(m, ARRAY[0], ARRAYV[0])  &&
//////            has(m, ARRAY[1], DUMMYV)  &&  has(m, ARRAY[2], ARRAYV[2]));
//////            } break; case 44: {
//////        m.insert(ARRAY[0], ARRAYV[0]);
//////        m.insert(ARRAY[1], ARRAYV[1]);
//////        m.insert(ARRAY[2], ARRAYV[2]);
//////        assert(m.insertOrUpdate(ARRAY[1], DUMMYV));
//////            } break; case 45: {
//////        m.insert(ARRAY[0], ARRAYV[0]);
//////        m.insert(ARRAY[1], ARRAYV[1]);
//////        m.insertOrUpdate(ARRAY[2], ARRAYV[0]);
//////        assert(m.size() == 3  &&  has(m, ARRAY[0], ARRAYV[0])  &&
//////            has(m, ARRAY[1], ARRAYV[1])  &&  has(m, ARRAY[2], ARRAYV[0]));
//////            } break; case 46: {
//////        m.insert(ARRAY[0], ARRAYV[0]);
//////        m.insert(ARRAY[1], ARRAYV[1]);
//////        assert(m.insertOrUpdate(ARRAY[2], ARRAYV[2]));
//////            } break; case 47: {
//////        m.insert(ARRAY[0], ARRAYV[0]);
//////        m.insert(ARRAY[1], ARRAYV[1]);
//////        assert(m.erase(ARRAY[1]));
//////            } break; case 48: {
//////        m.insert(ARRAY[0], ARRAYV[0]);
//////        m.insert(ARRAY[1], ARRAYV[1]);
//////        m.erase(ARRAY[1]);
//////        assert(!m.empty()  &&  m.size() == 1  &&  has(m, ARRAY[0], ARRAYV[0])  &&
//////                            !m.contains(ARRAY[1]));
//////            } break; case 49: {
//////        m.insert(ARRAY[0], ARRAYV[0]);
//////        m.insert(ARRAY[1], ARRAYV[1]);
//////        m.erase(ARRAY[0]);
//////        assert(!m.empty()  &&  m.size() == 1  &&  has(m, ARRAY[1], ARRAYV[1])  &&
//////                            !m.contains(ARRAY[0]));
//////            } break; case 50: {
//////        m.insert(ARRAY[0], ARRAYV[0]);
//////        m.insert(ARRAY[1], ARRAYV[1]);
//////        m.erase(ARRAY[0]);
//////        m.erase(ARRAY[1]);
//////        assert(m.size() == 0);
//////            } break; case 51: {
//////        m.insert(ARRAY[3], ARRAYV[3]);
//////        m.insert(ARRAY[0], ARRAYV[0]);
//////        m.insert(ARRAY[4], ARRAYV[4]);
//////        m.erase(ARRAY[0]);
//////        m.insert(ARRAY[1], ARRAYV[1]);
//////        m.erase(ARRAY[4]);
//////        m.insert(ARRAY[5], ARRAYV[5]);
//////        m.erase(ARRAY[3]);
//////        m.insert(ARRAY[2], ARRAYV[2]);
//////        assert(m.size() == 3  &&  has(m, ARRAY[1], ARRAYV[1])  &&
//////            has(m, ARRAY[2], ARRAYV[2])  &&  has(m, ARRAY[5], ARRAYV[5])  &&
//////            !m.contains(ARRAY[0])  &&  !m.contains(ARRAY[3])  &&
//////            !m.contains(ARRAY[4]));
//////            } break; case 52: {
//////        m.insert(ARRAY[3], ARRAYV[3]);
//////        m.insert(ARRAY[0], ARRAYV[0]);
//////        m.insert(ARRAY[3], ARRAYV[3]);
//////        m.insert(ARRAY[4], ARRAYV[4]);
//////        m.insert(ARRAY[0], ARRAYV[0]);
//////        m.insert(ARRAY[4], ARRAYV[4]);
//////        m.erase(ARRAY[0]);
//////        m.insert(ARRAY[1], ARRAYV[1]);
//////        m.erase(ARRAY[4]);
//////        m.insert(ARRAY[5], ARRAYV[5]);
//////        m.erase(ARRAY[3]);
//////        m.insert(ARRAY[2], ARRAYV[2]);
//////        m.insert(ARRAY[1], ARRAYV[1]);
//////        assert(m.size() == 3  &&  has(m, ARRAY[1], ARRAYV[1])  &&
//////            has(m, ARRAY[2], ARRAYV[2])  &&  has(m, ARRAY[5], ARRAYV[5])  &&
//////            !m.contains(ARRAY[0])  &&  !m.contains(ARRAY[3])  &&
//////            !m.contains(ARRAY[4]));
//////            } break; case 53: {
//////        m.insert(ARRAY[0], ARRAYV[0]);
//////        m.insert(ARRAY[1], ARRAYV[1]);
//////        assert(!m.erase(ARRAY[2])  &&  m.size() == 2);
//////            } break; case 54: {
//////        m.insert(ARRAY[0], ARRAYV[0]);
//////        m.insert(ARRAY[1], ARRAYV[1]);
//////        KeyType k;
//////        ValueType v;
//////        assert(!m.get(-1, k, v));
//////            } break; case 55: {
//////        m.insert(ARRAY[0], ARRAYV[0]);
//////        m.insert(ARRAY[1], ARRAYV[1]);
//////        KeyType k = DUMMY;
//////        ValueType v = DUMMYV;
//////        m.get(-1, k, v);
//////        assert(k == DUMMY  &&  v == DUMMYV);
//////            } break; case 56: {
//////        m.insert(ARRAY[0], ARRAYV[0]);
//////        m.insert(ARRAY[1], ARRAYV[1]);
//////        KeyType k;
//////        ValueType v;
//////        assert(!m.get(2, k, v));
//////            } break; case 57: {
//////        m.insert(ARRAY[0], ARRAYV[0]);
//////        m.insert(ARRAY[1], ARRAYV[1]);
//////        KeyType k = DUMMY;
//////        ValueType v = DUMMYV;
//////        m.get(2, k, v);
//////        assert(k == DUMMY  &&  v == DUMMYV);
//////            } break; case 58: {
//////        m.insert(ARRAY[0], ARRAYV[0]);
//////        m.insert(ARRAY[1], ARRAYV[1]);
//////        KeyType k = DUMMY;
//////        ValueType v = DUMMYV;
//////        m.get(0, k, v);
//////        assert(k == ARRAY[0]);
//////            } break; case 59: {
//////        m.insert(ARRAY[1], ARRAYV[1]);
//////        m.insert(ARRAY[0], ARRAYV[0]);
//////        KeyType k = DUMMY;
//////        ValueType v = DUMMYV;
//////        m.get(0, k, v);
//////        assert(k == ARRAY[0]);
//////            } break; case 60: {
//////        m.insert(ARRAY[1], ARRAYV[1]);
//////        m.insert(ARRAY[0], ARRAYV[0]);
//////        KeyType k0 = DUMMY;
//////        ValueType v0 = DUMMYV;
//////        m.get(0, k0, v0);
//////        KeyType k1 = DUMMY;
//////        ValueType v1 = DUMMYV;
//////        m.get(1, k1, v1);
//////        assert(k0 == ARRAY[0]  &&  v0 == ARRAYV[0]  &&  k1 == ARRAY[1]  &&  v1 == ARRAYV[1]);
//////            } break; case 61: {
//////        m.insert(ARRAY[3], ARRAYV[3]);
//////        m.insert(ARRAY[1], ARRAYV[1]);
//////        m.insert(ARRAY[0], ARRAYV[0]);
//////        m.insert(ARRAY[4], ARRAYV[4]);
//////        m.insert(ARRAY[2], ARRAYV[2]);
//////        assert(m.size() == 5);
//////        KeyType k;
//////        ValueType v;
//////        for (int i = 0; i < 5; i++)
//////        {
//////        m.get(i, k, v);
//////        assert(k == ARRAY[i]);
//////        }
//////            } break; case 62: {
//////        m.insert(ARRAY[1], ARRAYV[1]);
//////        m.insert(ARRAY[1], ARRAYV[1]);
//////        m.insert(ARRAY[0], ARRAYV[0]);
//////        m.insert(ARRAY[1], ARRAYV[1]);
//////        m.insert(ARRAY[0], ARRAYV[0]);
//////        assert(m.size() == 2);
//////        KeyType k;
//////        ValueType v;
//////        for (int i = 0; i < 2; i++)
//////        {
//////        m.get(i, k, v);
//////        assert(k == ARRAY[i]);
//////        }
//////            } break; case 63: {
//////        m.insert(DEFAULT, DUMMYV);
//////        assert(m.size() == 1  &&  has(m, DEFAULT, DUMMYV));
//////            } break; case 64: {
//////        m.update(DEFAULT, DUMMYV);
//////        assert(m.size() == 0  &&  !m.contains(DEFAULT));
//////            } break; case 65: {
//////        m.insertOrUpdate(DEFAULT, DUMMYV);
//////        assert(m.size() == 1  &&  has(m, DEFAULT, DUMMYV));
//////            } break; case 66: {
//////        m.insert(DEFAULT, DUMMYV);
//////        m.erase(DEFAULT);
//////        assert(m.size() == 0  &&  !m.contains(DEFAULT));
//////            } break; case 67: {
//////        m.insert(ARRAY[0], ARRAYV[0]);
//////        m.insert(ARRAY[1], ARRAYV[1]);
//////        {
//////        Map m2;
//////        m2.insert(ARRAY[2], ARRAYV[2]);
//////        m2.insert(ARRAY[3], ARRAYV[3]);
//////        m2.insert(ARRAY[1], ARRAYV[1]);
//////        m.swap(m2);
//////        assert(m.size() == 3);
//////        }
//////            } break; case 68: {
//////        m.insert(ARRAY[0], ARRAYV[0]);
//////        m.insert(ARRAY[1], ARRAYV[1]);
//////        {
//////        Map m2;
//////        m2.insert(ARRAY[2], ARRAYV[2]);
//////        m2.insert(ARRAY[3], ARRAYV[3]);
//////        m2.insert(ARRAY[1], ARRAYV[1]);
//////        m.swap(m2);
//////        assert(has(m, ARRAY[1], ARRAYV[1])  &&  has(m, ARRAY[2], ARRAYV[2])  &&
//////            has(m, ARRAY[3], ARRAYV[3])  &&  !m.contains(ARRAY[0]));
//////        }
//////            } break; case 69: {
//////        m.insert(ARRAY[0], ARRAYV[0]);
//////        m.insert(ARRAY[1], ARRAYV[1]);
//////        {
//////        Map m2;
//////        m2.insert(ARRAY[2], ARRAYV[2]);
//////        m2.insert(ARRAY[3], ARRAYV[3]);
//////        m2.insert(ARRAY[1], ARRAYV[1]);
//////        m.swap(m2);
//////        assert(m2.size() == 2);
//////        }
//////            } break; case 70: {
//////        m.insert(ARRAY[0], ARRAYV[0]);
//////        m.insert(ARRAY[1], ARRAYV[1]);
//////        {
//////        Map m2;
//////        m2.insert(ARRAY[2], ARRAYV[2]);
//////        m2.insert(ARRAY[3], ARRAYV[3]);
//////        m2.insert(ARRAY[1], ARRAYV[1]);
//////        m.swap(m2);
//////        assert(has(m2, ARRAY[0], ARRAYV[0])  &&  has(m2, ARRAY[1], ARRAYV[1])  &&
//////            !m2.contains(ARRAY[2])  &&  !m2.contains(ARRAY[3]));
//////        }
//////            } break; case 71: {
//////        KeyType k;
//////        for (int n = 0; n < SPEC_MAX; n++)
//////        {
//////        assert(m.insert(k, DUMMYV));
//////        k += 'x';
//////        }
//////        assert(m.size() == SPEC_MAX);
//////            } break; case 72: {
//////        KeyType k;
//////        for (int n = 0; n < SPEC_MAX; n++)
//////        {
//////        assert(m.insert(k, DUMMYV));
//////        k += 'x';
//////        }
//////        assert(!m.insert(k, DUMMYV)  &&  m.size() == SPEC_MAX  &&  !m.contains(k));
//////            } break; case 73: {
//////        assert(m.insert(DUMMY, DUMMYV));
//////        for (int n = 0; n < 10*SPEC_MAX; n++)
//////        assert(m.insertOrUpdate(DUMMY, DUMMYV));
//////        assert(m.size() == 1);
//////            } break; case 74: {
//////        KeyType k;
//////        KeyType kfirst;
//////        for (int n = 0; n < SPEC_MAX; n++)
//////        {
//////        if (n == 0)
//////        {
//////            kfirst = k;
//////            assert(m.insert(kfirst, DUMMYV));
//////        }
//////        else
//////            assert(m.insert(k, DUMMYV));
//////        k += 'x';
//////        }
//////        assert(!m.insert(k, DUMMYV));
//////        m.erase(kfirst);
//////        assert(m.insert(k, DUMMYV));
//////        k += 'x';
//////        assert(!m.insert(k, DUMMYV));
//////#ifdef TESTNEW
//////                    } break; case 75: {
//////          // This test checked that swap takes the same amount of time
//////          // no matter how many items are in the Maps.
//////            } break; /*case 76: {
//////        const int CAPACITY = 2;
//////        Map m2(CAPACITY);
//////        KeyType k;
//////        for (int n = 0; n < CAPACITY; n++)
//////        {
//////        assert(m2.insert(k, DUMMYV));
//////        k += 'x';
//////        }
//////        assert(!m2.insert(k, DUMMYV));
//////            } break; case 77: {
//////        const int CAPACITY = SPEC_MAX*2;
//////        Map m2(CAPACITY);
//////        KeyType k;
//////        for (int n = 0; n < CAPACITY; n++)
//////        {
//////        assert(m2.insert(k, DUMMYV));
//////        k += 'x';
//////        }
//////        assert(!m2.insert(k, DUMMYV));
//////            } break;*/ case 78: {
//////          // This test checked that the destructor deletes the dynamic array.
//////            } break; case 79: {
//////          // This test checked that empty Maps can be copied and properly
//////          // destroyed.
//////            } break; case 80: {
//////        m.insert(ARRAY[0], ARRAYV[0]);
//////        m.insert(ARRAY[1], ARRAYV[1]);
//////        m.insert(ARRAY[2], ARRAYV[2]);
//////        {
//////        Map m2(m);
//////        m2.insert(ARRAY[3], ARRAYV[3]);
//////        assert(m2.size() == m.size()+1);
//////        }
//////            } break; case 81: {
//////        m.insert(ARRAY[0], ARRAYV[0]);
//////        m.insert(ARRAY[1], ARRAYV[1]);
//////        m.insert(ARRAY[2], ARRAYV[2]);
//////        {
//////        Map m2(m);
//////        m2.insert(ARRAY[3], ARRAYV[3]);
//////        assert(m2.size() == 4);
//////        for (int n = 0; n < m2.size(); n++)
//////        {
//////            KeyType k;
//////            ValueType v;
//////            m2.get(n, k, v);
//////            assert(k == ARRAY[n]);
//////        }
//////        }
//////            } break; case 82: {
//////        m.insert(ARRAY[0], ARRAYV[0]);
//////        m.insert(ARRAY[1], ARRAYV[1]);
//////        m.insert(ARRAY[2], ARRAYV[2]);
//////        {
//////        Map m2(m);
//////        m2.insert(ARRAY[3], ARRAYV[3]);
//////        assert(m.size() == 3);
//////        for (int n = 0; n < m.size(); n++)
//////        {
//////            KeyType k;
//////            ValueType v;
//////            m.get(n, k, v);
//////            assert(k == ARRAY[n]);
//////        }
//////        }
//////            } break; case 83: {
//////        {
//////        Map m2;
//////        Map m3(m2);
//////        assert(m2.size() == 0  &&  m3.size() == 0);
//////        m2.insert(ARRAY[0], ARRAYV[0]);
//////        m3.insert(ARRAY[1], ARRAYV[1]);
//////        assert(m2.size() == 1  &&  m3.size() == 1);
//////        KeyType k;
//////        ValueType v;
//////        m2.get(0, k, v);
//////        assert(k == ARRAY[0]);
//////        m3.get(0, k, v);
//////        assert(k == ARRAY[1]);
//////
//////        }
//////            } break;/* case 84: {
//////        {
//////        Map m2(2);
//////        m2.insert(ARRAY[0], ARRAYV[0]);
//////        m2.insert(ARRAY[1], ARRAYV[1]);
//////        Map m3(m2);
//////        assert(!m3.insert(ARRAY[2], ARRAYV[2]));
//////        }
//////            } break;*/ case 85: {
//////          // This test checked that the assignment operator doesn't just
//////          // copy a pointer.
//////            } break; case 86: {
//////        {
//////        Map m2;
//////        Map m3;
//////        m3.insert(ARRAY[0], ARRAYV[0]);
//////        m3.insert(ARRAY[1], ARRAYV[1]);
//////        m3 = m2;
//////        m2.insert(ARRAY[2], ARRAYV[2]);
//////        m3.insert(ARRAY[3], ARRAYV[3]);
//////        assert(m2.size() == 1  &&  m3.size() == 1);
//////        KeyType k;
//////        ValueType v;
//////        m2.get(0, k, v);
//////        assert(k == ARRAY[2]);
//////        m3.get(0, k, v);
//////        assert(k == ARRAY[3]);
//////        }
//////            } break; case 87: {
//////        {
//////        Map m2;
//////        Map m3;
//////        m3.insert(ARRAY[0], ARRAYV[0]);
//////        m3.insert(ARRAY[1], ARRAYV[1]);
//////        assert(m3.size() == 2);
//////        m2 = m3;
//////        assert(m2.size() == 2  &&  m3.size() == 2);
//////        m2.insert(ARRAY[2], ARRAYV[2]);
//////        m3.insert(ARRAY[3], ARRAYV[3]);
//////        assert(m2.size() == 3  &&  m3.size() == 3);
//////        for (int n = 0; n < m2.size(); n++)
//////        {
//////            KeyType k;
//////            ValueType v;
//////            m2.get(n, k, v);
//////            assert(k == ARRAY[n]);
//////        }
//////        KeyType ka[3] = { ARRAY[0], ARRAY[1], ARRAY[3] };
//////        for (int n = 0; n < m3.size(); n++)
//////        {
//////            KeyType k;
//////            ValueType v;
//////            m3.get(n, k, v);
//////            assert(k == ka[n]);
//////        }
//////        }
//////            } break; case 88: {
//////          // This test checked that the assignment operator doesn't just
//////          // copy a pointer.
//////            } break; case 89: {
//////        m.insert(ARRAY[0], ARRAYV[0]);
//////        m.insert(ARRAY[1], ARRAYV[1]);
//////        {
//////        Map m2;
//////        m2.insert(ARRAY[2], ARRAYV[2]);
//////        m2.insert(ARRAY[3], ARRAYV[3]);
//////        m2.insert(ARRAY[4], ARRAYV[4]);
//////        m2 = m;
//////        m2.insert(ARRAY[5], ARRAYV[5]);
//////        assert(m2.size() == m.size()+1);
//////        }
//////            } break; case 90: {
//////        m.insert(ARRAY[0], ARRAYV[0]);
//////        m.insert(ARRAY[1], ARRAYV[1]);
//////        {
//////        Map m2;
//////        m2.insert(ARRAY[3], ARRAYV[3]);
//////        m2.insert(ARRAY[4], ARRAYV[4]);
//////        m2.insert(ARRAY[5], ARRAYV[5]);
//////        m2 = m;
//////        m2.insert(ARRAY[2], ARRAYV[2]);
//////        assert(m2.size() == 3);
//////        for (int n = 0; n < m2.size(); n++)
//////        {
//////            KeyType k;
//////            ValueType v;
//////            m2.get(n, k, v);
//////            assert(k == ARRAY[n]);
//////        }
//////        }
//////            } break; case 91: {
//////        m.insert(ARRAY[0], ARRAYV[0]);
//////        m.insert(ARRAY[1], ARRAYV[1]);
//////        {
//////        Map m2;
//////        m2.insert(ARRAY[3], ARRAYV[3]);
//////        m2.insert(ARRAY[4], ARRAYV[4]);
//////        m2.insert(ARRAY[5], ARRAYV[5]);
//////        m2 = m;
//////        m2.insert(ARRAY[2], ARRAYV[2]);
//////        assert(m.size() == 2);
//////        for (int n = 0; n < m.size(); n++)
//////        {
//////            KeyType k;
//////            ValueType v;
//////            m.get(n, k, v);
//////            assert(k == ARRAY[n]);
//////        }
//////        }
//////            } break; case 92: {
//////        {
//////        // This test checked that self-assignment doesn't change the
//////        // number of items in existence.
//////        }
//////            } break; case 93: {
//////        {
//////        Map m2;
//////        m2.insert(ARRAY[0], ARRAYV[0]);
//////        m2.insert(ARRAY[1], ARRAYV[1]);
//////        m2.insert(ARRAY[2], ARRAYV[2]);
//////        m2 = m2;
//////        m2.insert(ARRAY[3], ARRAYV[3]);
//////        assert(m2.size() == 4);
//////        for (int n = 0; n < m2.size(); n++)
//////        {
//////            KeyType k;
//////            ValueType v;
//////            m2.get(n, k, v);
//////            assert(k == ARRAY[n]);
//////        }
//////        }
//////#endif
//////            }
//////    }
//////}
//////
//////#include <iostream>
//////#include <cassert>
//////#include "Map.h"
//////using namespace std;
//////
//////
//////int main()
//////{
//////    int n = 1;
//////    while (n < 94) {
//////        if (n == 72 || n == 74 || n == 76 || n == 77 || n == 84) {
//////            n++;
//////            continue;
//////        }
//////        testone(n);
//////        n++;
//////    }
//////    cout << "Passed all " << n - 1 << " tests." << endl;
//////}
//#include "Map.h"
//#include <iostream>
//#include <cassert>
//using namespace std;
//
//void test()
//{
//    //default constructor
//    Map a;
//    //tests empty
//    assert(a.empty());
//
//    //tests insert
//    a.insert("Ironman", 4.2);
//    a.insert("Thor", 3.6);
//    a.insert("The Incredible Hulk", 2.3);
//
//    //tests update
//    a.update("The Incredible Hulk", 2.6);
//
//    //tests insertOrUpdate
//    a.insertOrUpdate("Ironman 2", 4.3);
//
//    //tests size and contains to make sure everything was asserted right
//    assert(a.size() == 4 && a.contains("Ironman") && a.contains("Thor") && a.contains("The Incredible Hulk") && a.contains("Ironman 2"));
//
//    //tests erase
//    assert(a.erase("Thor"));
//    a.insert("Captain America 1", 4.3);
//    a.insert("The Avengers", 4.5);
//
//    //tests get with 2 parameters
//    KeyType x;
//    ValueType y;
//    assert(a.get("The Incredible Hulk", y) && y==2.6);
//
//    //tests get with 3 parameters
//    assert(a.contains("The Avengers"));
//    a.get(0, x, y);
//    assert(x == "Captain America 1");
//    assert(y == 4.3);
//    a.get(4, x, y);
//    assert(x == "The Incredible Hulk");
//    assert(y == 2.6);
//
//    //tests size and makes sure inserts/erase worked properly
//    assert(a.size() == 5 && a.contains("Ironman") && a.contains("Captain America 1") && a.contains("The Incredible Hulk") && a.contains("Ironman 2")
//           && a.contains("The Avengers"));
//
//    Map b;
//    b.insert("Ironman 3", 4.3);
//    b.insert("Thor 2", 3.3);
//    b.insert("Captain America 2", 4.6);
//
//    //tests swap
//    a.swap(b);
//
//    //tests get to make sure that swap works properly
//    a.get(2, x, y);
//    assert(y==3.3);
//
//    //checks contents of the two maps to make sure they swapped correctly
//    assert(a.size() == 3 && a.contains("Ironman 3") && a.contains("Thor 2") && a.contains("Captain America 2") && b.size() == 5 && b.contains("Ironman") && b.contains("Captain America 1") && b.contains("The Incredible Hulk") && b.contains("Ironman 2")
//           && b.contains("The Avengers"));
//
//    //test copy constructor
//    Map c = a;
//    assert(c.size() == 3);
//    assert(c.get(1, x, y) && x == "Ironman 3" && y == 4.3);
//    assert(c.contains("Ironman 3") && c.contains("Thor 2") && c.contains("Captain America 2"));
//
//    //test assignment operator
//    Map d;
//    assert(d.size() == 0);
//    d = b;
//    assert(d.size() == 5);
//    d.erase("Ironman");
//    d.update("Captain America 1", 4.7);
//    d.insertOrUpdate("The Incredible Hulk", 2.2);
//    assert(d.get(0, x, y) && x == "Captain America 1" && y == 4.7);
//    assert(d.get(3, x, y) && x == "The Incredible Hulk" && y == 2.2);
//    assert(d.get("Ironman 2", y) && y == 4.3);
//    assert(d.size() == 4);
//    assert(d.contains("Captain America 1") && d.contains("The Incredible Hulk") && d.contains("Ironman 2") && d.contains("The Avengers"));
//
//    //test merge if result is empty and m1 and m2 have different keys
//    Map e;
//    merge(a, b, e);
//    assert(e.size() == 8 && e.contains("Ironman 3") && e.contains("Thor 2") && e.contains("Captain America 2") && e.contains("Ironman") && e.contains("Captain America 1") && e.contains("The Incredible Hulk") && e.contains("Ironman 2")
//           && e.contains("The Avengers"));
//
//    //test merge if m1 and m2 have a common key with different values
//    Map f;
//    f.insert("Guardians of the Galaxy", 3.8);
//    f.insert("The Avengers 2", 4.1);
//    f.insert("Ant-Man", 4.1);
//    f.insert("Captain America 3", 4.7);
//    f.insert("The Incredible Hulk", 4.3);
//    Map g;
//    assert(!merge(b, f, g));
//
//
//    //test merge if result has key pairs in it
//    Map h;
//    h.insert("Doctor Strange", 4.0);
//    h.insert("Guardians of the Galaxy 2", 4.1);
//    h.insert("Spiderman 1", 4.6);
//    h.insert("Thor 3", 3.7);
//    h.insert("Black Panther", 4.7);
//    assert(merge(h, a, f));
//    assert(f.size() == 8);
//    assert(f.contains("Doctor Strange") && f.contains("Guardians of the Galaxy 2") && f.contains("Spiderman 1") && f.contains("Thor 3") && f.contains("Black Panther") && f.contains("Ironman 3") && f.contains("Thor 2") && f.contains("Captain America 2"));
//
//    //test merge if m1 and result are the same
//    merge(a, b, a);
//    assert(a.size() == 8 && a.contains("Ironman 3") && a.contains("Thor 2") && a.contains("Captain America 2") && a.contains("Ironman") && a.contains("Captain America 1") && a.contains("The Incredible Hulk") && a.contains("Ironman 2")
//           && a.contains("The Avengers"));
//
//    //test reassign for normal map
//    Map i;
//    reassign(h, i);
//    ValueType z;
//    for (int j = 0; j < i.size(); j++){
//        h.get(j, x, y);
//        assert(i.get(j, x, z) && z!=y);
//    }
//
//    //test reassign for map with only one value;
//    Map j;
//    Map k;
//    j.insert("The Avengers 3", 4.7);
//    reassign(j, k);
//    assert(k.get("The Avengers 3", y) && y == 4.7);
//    assert(k.size() == 1);
//
//    //test reassign for map with no values;
//    Map l;
//    reassign (l, l);
//    assert(l.size() == 0);
//
//}
//
//int main()
//{
//    test();
//    cout << "Passed all tests" << endl;
//}
