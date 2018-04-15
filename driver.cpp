#include <iostream>
#include <cstdlib>
using namespace std;


void printArray(int* arr);
int* initRandomArray();
int* copyArray(int* arr);
int size  = 5000;


int main(){
   int* arr = initRandomArray();
   int* b = copyArray(arr);
   b[size-1] = 123;
   printArray(b);
   printArray(arr);
}

//prints specified array
void printArray(int* arr){
    for(int i = 0; i < size; i++){
        if(i == 0){
            cout << "[" << arr[i] << ", ";
        }else if(i != size-1){
            cout << arr[i] << ", ";
        }else{
            cout << arr[i];
        }
    }
    cout << "]" << endl;
}

//returns a random array containing 5000 integers
//between zero and one million
int* initRandomArray(){
    int* arr = new int[size];
    for(int i = 0; i < size; i++){
        arr[i] = (int)(rand()%1000000);
    }
    return arr;
}

//returns deep copy of array
int* copyArray(int* arr){
    int* copy = new int[size];
    for(int i = 0; i < size; i++){
        copy[i] = arr[i];
    }
    return copy;
}