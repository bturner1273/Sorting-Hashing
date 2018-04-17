#include "HashMap.hpp"
#include <iostream>
using namespace std;

HashMap :: HashMap(){
    //initialize table as an array of HashNode pointers
    table = new HashNode*[SIZE];
    //initialize all HashNodes in table to NULL
    for(int i = 0; i < SIZE; i++){
        table[i] = NULL;
    }
    collisions = 0;
    comparisons = 0;
}

long long HashMap :: get(int key){
    int hash = key%SIZE;
    //if the specified key does not exist we return -1
    if(table[hash] == NULL){
        return -1;
    }else{
        HashNode *entry = table[hash]; //point to the first element chained 
                                       //to list head table[hash]
        while(entry->getKey() != key && entry != NULL){
            entry = entry->getNext();
        }
        //if we got to the end of the linked list
        //and never found the key return -1
        if(entry == NULL){
            return -1;
        }else return entry->getValue(); //we found it
    }
}

void HashMap :: put(int key, long long value){
    int hash = key%SIZE;
    if(table[hash] == NULL){
        table[hash] = new HashNode(key,value);
    }else{
        HashNode *entry = table[hash]; //set entry to point to the head of the chain
        while(entry->next != NULL){
            entry = entry->getNext();
            collisions++; //collisions every link we hit in the chain
        }
        if(entry->getKey() == key){
            collisions++; //collision if the same key occurs twice
            entry->setValue(value);
        }else{
            entry->setNext(new HashNode(key, value));
        }
        //Sort the whole chain at table[hash]
        //as prescribed in the project description
        insertionSort(&table[hash]);
    }

}

void HashMap :: remove(int key){
    int hash = key%SIZE;
    //can't remove from an empty chain
    if(table[hash] != NULL){
        HashNode *prev = NULL;
        HashNode *current = table[hash];
        while(current->getNext() != NULL and current->getKey() != key){
            prev = current;
            current = current->next;
        }
        if(current->getKey() == key){
            //if we are at the head (table[hash])
            if(prev == NULL){
                HashNode *next = current->next;
                delete current;
                table[hash] = next;
            }else{
                HashNode *next = current->next;
                delete current;
                prev->setNext(next);
            }
        }
    }
}

HashMap :: ~HashMap(){
    for(int i = 0; i < SIZE; i++){
        if(table[i] != NULL){   
            HashNode* prev = NULL;
            HashNode* current = table[i];
            while(current != NULL){
                prev = current;
                current = current->next;
                delete prev;
            }

        }
    }
}

//used by insertion sort
void HashMap :: sortedInsert(HashNode **head_ref, HashNode *new_node){
    HashNode *current;
    if (*head_ref == NULL || (*head_ref)->key <= new_node->key){
        comparisons+=2;
        new_node->next = *head_ref;
        *head_ref = new_node;
    }
    else{
        current = *head_ref;
        while (current->next!=NULL && current->next->key > new_node->key){
            comparisons += 2;
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}

void HashMap :: insertionSort(HashNode **headRef){
    HashNode *sorted = NULL;
    HashNode *current = *headRef;
    while (current != NULL)
    {
        comparisons++;//for current != null
        HashNode *next = current->next;
        sortedInsert(&sorted, current);
        current = next;
    }
    *headRef = sorted;
}