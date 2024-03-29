#include "HashNode.cpp"

int SIZE = 1024;

class HashMap{
    private:
    HashNode **table;
    public:
    long long collisions, comparisons;
    HashMap();
    long long get(int key);
    void put(int key, long long value);
    void remove(int key);
    void sortedInsert(HashNode **head_ref, HashNode *new_node);
    void insertionSort(HashNode **headRef);
    ~HashMap();
};