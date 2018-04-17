
class HashNode{
    public:
    int key;
    long long value;
    HashNode *next;
    HashNode(int key, long long value);
    HashNode(int key, long long value, HashNode* next);
    int getKey();
    long long getValue();
    void setValue(long long value);
    HashNode* getNext();
    void setNext(HashNode* next);
};