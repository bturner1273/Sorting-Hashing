#include "HashNode.hpp"
#include <iostream>
using namespace std;
HashNode :: HashNode(int key, long long value){
    this->key = key;
    this->value = value;
    this->next = NULL;
}

HashNode :: HashNode(int key, long long value, HashNode* next){
    this->key = key;
    this->value = value;
    this->next = next;
}

int HashNode :: getKey() { 
    return key;
}

long long HashNode :: getValue(){
    return value;
}

void HashNode :: setValue(long long value){
    this->value = value;
}

HashNode* HashNode :: getNext(){
    return next;
}

void HashNode :: setNext(HashNode* next){
    this->next = next;
}