/** CS515 Assignment 6
 * File: set.cpp
 * Name: Mily Pagan
 * Section: 02
 * Date: 10/19/20
 * Collaboration Declaration: piazza*/

#include "set.h"
#include <iostream>

//set constructor
Set::Set(){
    _size = 0; //default size when created
    _head = new Elem; //dummy head
    _tail = new Elem; //dummy tail
    _head->next = _tail;
    _head->prev = NULL;
    _tail->next = NULL;
    _tail->prev = _head;
}
//set copy constructor
Set::Set(const Set &rhs) {
    _head = new Elem;
    _tail = new Elem;
    _size = 0;
    _head->next = _tail;
    _head->prev = NULL;
    _tail->next = NULL;
    _tail->prev = _head;
    copyCode(rhs);
}
//set destructor
Set::~Set() {
    destructCode();
}
//assignment operator
Set& Set::operator=(const Set &rhs) {
    if (this == &rhs) {
        return *this;
    }
    if (_size != 0) {
        Elem *cur = _head->next;
        Elem *temp = cur;
        while (temp->next != NULL) {
            temp = cur->next;
            delete cur;
            cur = temp;
        }
        delete _head;
        delete temp;
    }else {
        delete _head;
        delete _tail;
    }
    _head = new Elem;
    _tail = new Elem;
    _size = 0;
    _head->next = _tail;
    _head->prev = NULL;
    _tail->next = NULL;
    _tail->prev = _head;
    copyCode(rhs);
    return *this;
}
//insert
void Set::insert(ELEMENT_TYPE value) {
    Elem *n = new Elem;
    n -> info = value;
    n -> next = NULL;
    n -> prev = NULL;
    if (_size == 0) {
        _head -> next = n;
        _tail -> prev = n;
        n->next = _tail;
        n->prev = _head;
        _size++;
    } else {
        Elem *cur = _head->next;
        while(cur->next != NULL) {
            if (cur->info == value) {
                delete n;
                break;
            }
            if (cur->info < value) {
                cur = cur->next;
            } else {
                n->prev = cur->prev;
                n->next = cur;
                (cur->prev)->next = n;
                cur->prev = n;
                _size++;
                break;
            }
            if (cur == _tail) {
                n->next = _tail;
                n->prev = _tail->prev;
                (_tail->prev)->next = n;
                _tail->prev = n;
                _size++;
                break;
            }
        }
    }
}
//erase
void Set::erase(ELEMENT_TYPE value) {
    Elem *cur = _head->next;
    while (cur->next != NULL) {
        if (cur->info == value) {
            (cur->prev)->next = cur->next;
            (cur->next)->prev = cur->prev;
            _size--;
            delete cur;
            break;
        }
        cur = cur->next;
    }
}
//clear
void Set::clear() {
    Elem *cur = _head->next;
    Elem *n = cur;
    while (n->next != NULL) {
        n = cur->next;
        delete cur;
        _size--;
        cur = n;
    }
    _head->next = _tail;
    _tail->prev = _head;
}
//size
int Set::size() const {
    return _size;
}
//returns an iterator to corresponding value if found
Set::Iterator Set::find(ELEMENT_TYPE value) const {
    Iterator i = begin();
    while (i != end()) {
        if (*i == value) {
            return i;
        }
        i++;
    }
    return i;
}
// returns an iterator at the beginning
Set::Iterator Set::begin() const {
    Elem *b = _head->next;
    Iterator i(b);
    return i;
}
// returns an iterator at the end
Set::Iterator Set::end() const {
    Elem *e = _tail;
    Iterator i(e);
    return i;
}
//returns a reverse iterator at the beginning
Set::Reverse_Iterator Set::rbegin() const {
    Elem *b = _tail->prev;
    Reverse_Iterator i(b);
    return i;
}
//returns a reverse iterator at the end
Set::Reverse_Iterator Set::rend() const {
    Elem *e = _head;
    Reverse_Iterator i(e);
    return i;
}
//copy code
void Set::copyCode(const Set & v) {
    Elem *cur = v._head->next;
    while (cur->next != NULL) {
        insert(cur->info);
        cur = cur->next;
    }
}
//destruct
void Set::destructCode() {
    if (_size != 0) {
        Elem *cur = _head->next;
        Elem *temp = cur;
        while (temp->next != NULL) {
            temp = cur->next;
            delete cur;
            cur = temp;
        }
        delete _head;
        delete temp;
    }else {
        delete _head;
        delete _tail;
    }
}
//overloading << operator
ostream& operator<<(ostream& out, Set &v){
    return v.dump(out,v);
}
//dump
ostream& Set::dump(ostream& out, const Set &v) {
    Elem *cur = _head->next;
    for (int i = 0; i < _size; i++) {
        out << cur->info;
        if (i != _size-1) {
            out << " ";
        }
        cur = cur->next;
    }
    return out;
}
//overload intersect & operator
Set operator&(const Set& s1, const Set& s2) {
    Set intersectSet;
    Set::Iterator i2 = s2.begin();
    while (i2 != s2.end()) {
        if(s1.find(*i2) != s1.end()) {
            intersectSet.insert(*i2);
        }
        i2++;
    }
    return intersectSet;
}
//overload union | operator
Set operator|(const Set& s1, const Set& s2) {
    Set unionSet;
    Set::Iterator i1 = s1.begin();
    while (i1 != s1.end()) {
        unionSet.insert(*i1);
        i1++;
    }
    Set::Iterator i2 = s2.begin();
    while (i2 != s2.end()) {
        unionSet.insert(*i2);
        i2++;
    }
    return unionSet;
}
//overload set difference
Set operator-(const Set& s1, const Set&s2) {
    Set differenceSet;
    Set::Iterator i1 = s1.begin();
    while (i1 != s1.end()) {
        if (s2.find(*i1) == s2.end()) {
            differenceSet.insert(*i1);
        }
        i1++;
    }
    return differenceSet;
}
//overload set equality
bool operator==(const Set& s1, const Set& s2) {
    if (s1.size() != s2.size()) {
        return false;
    }
    Set::Iterator i1 = s1.begin();
    Set::Iterator i2 = s2.begin();
    while (i1 != s1.end()) {
        if (*i1 != *i2) {
            return false;
        }
        i1++;
        i2++;
    }
    return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////
//iterator constructor default
Set::Iterator::Iterator() {
    _cur = new Elem;
    _cur->next = NULL;
    _cur->prev = NULL;
}
//iterator constructor given pointer
Set::Iterator::Iterator(Elem *cur) {
    _cur = cur;
    _cur->next = cur->next;
    _cur->prev = cur->prev;
    _cur->info = cur->info;
}
//dereference * operator
ELEMENT_TYPE& Set::Iterator::operator*() {
    return _cur->info;
}
//post increment ++ operator
Set::Iterator Set::Iterator::operator++(int value) {
    Iterator result = *this;
    _cur = _cur->next;
    return result;
}
//post decrement -- operator
Set::Iterator Set::Iterator::operator--(int value) {
    Iterator result = *this;
    _cur = _cur->prev;
    return result;
}
//equality == operator
bool Set::Iterator::operator==(Iterator it) const {
    return _cur == it._cur;
}
//inequality != operator
bool Set::Iterator::operator!=(Iterator it) const {
    return _cur != it._cur;
}
////////////////////////////////////////////////////////////////////////////////////////////////
//reverse iterator constructor
Set::Reverse_Iterator::Reverse_Iterator() {
    _cur = new Elem;
    _cur->next = NULL;
    _cur->prev = NULL;
}
//reverse iterator constructor given pointer
Set::Reverse_Iterator::Reverse_Iterator(Elem *cur) {
    _cur = cur;
    _cur->next = cur->next;
    _cur->prev = cur->prev;
    _cur->info = cur->info;
}
//dereference * operator
ELEMENT_TYPE& Set::Reverse_Iterator::operator*() {
    return _cur->info;
}
//post increment ++ operator
Set::Reverse_Iterator Set::Reverse_Iterator::operator++(int) {
    Reverse_Iterator result = *this;
    _cur = _cur->prev;
    return result;
}
//post decrement -- operator
Set::Reverse_Iterator Set::Reverse_Iterator::operator--(int) {
    Reverse_Iterator result = *this;
    _cur = _cur->next;
    return result;
}
//equality == operator
bool Set::Reverse_Iterator::operator==(Reverse_Iterator it) const {
    return _cur == it._cur;
}
//inequality != operator
bool Set::Reverse_Iterator::operator!=(Reverse_Iterator it) const {
    return _cur != it._cur;
}
