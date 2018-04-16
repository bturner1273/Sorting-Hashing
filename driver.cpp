#include <iostream>
#include <cstdlib>
using namespace std;


void printArray(int* arr, int n);
int* initRandomArray();
int* copyArray(int* arr);
void heapSort(int arr[], int n);
void heapify(int arr[], int n, int i);
int partition(int arr[], int l, int h);
void quickSort(int arr[], int l, int h);
int size  = 5000;


int main(){


//TESTING  
    // int* a = initRandomArray();
    // int n = sizeof(a)/sizeof(a[0]);
    // quickSort(a,0,n-1);
    
    // printArray(a, 10);




    // heapSort test

    // int arr[] = {12, 11, 13, 5, 6, 7};
    // int n = sizeof(arr)/sizeof(arr[0]);
    // heapSort(arr, n);
    // printArray(arr, n);

    // quickSort test

    // int arr1[] = {10, 7, 8, 9, 1, 5};
    // int n1 = sizeof(arr1)/sizeof(arr1[0]);
    // quickSort(arr1, 0, n1-1);
    // printArray(arr1, n1);
    
    
    
    return 0;
}

//quick sort uses a pivot and this function is used
//by quick sort to do all the shifting around the pivot

//my function always uses the last element of the array
//as the pivot and places all smaller elements to the left
//of the pivot and all larger elements to the right of the
//pivot
int partition(int arr[], int l, int h){
    int pivot = arr[h]; //we always pivot on the last element
    int i = l-1; //needed because we preincrement i to make
                    //make the algorithm shorter and get 
                    //rid of extraneous if-statement
    for(int j = l; j <= h-1; j++){
        //if the array element at j is less than
        //the pivot we want to increment i (so we don't)
        //start at -1 at the beginning and so memory
        //isn't being overwritten in later states,
        //then we want to swap the elements so that 
        //we know the array element previously stored
        //at j is now indexed to the left of the pivot 
        if(arr[j] <= pivot){
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i+1], arr[h]);
    return i+1;
}

//basically quickSort just passes the last array element into
//the partition function, and resorts the list before and
//after partitioning every time
void quickSort(int arr[], int l, int h){
    if(l < h){
        int partitionIndex = partition(arr,l,h);
        quickSort(arr,l,partitionIndex-1);
        quickSort(arr,partitionIndex+1, h);
    }
}

//heapsort basically just heapifies all subtrees of the array
//by taking one element at a time, reinserting as the root and 
//re-heapifying the array
void heapSort(int arr[], int n){
    //build heap
    for(int i=n/2-1; i >= 0; i--){
        heapify(arr,n,i);
    }

    //swap the root with the last element of the heap 
    //and re-heapify for every element
    //to make sure heap is sorted
    for(int i=n-1; i>=0; i--){
        swap(arr[0],arr[i]); //swap root for last element
        heapify(arr,i,0); //reheapify
    }
}

//heapify an array, i.e. find largest element and 
//add it as the root node
void heapify(int arr[], int n, int i){
    int l = i;    //initialize largest (l) element in subheap as root
    int leftChild = 2*i+1;  //left child is its parents position*2 + 1
    int rightChild = 2*i+2; //right child is its parents position*2 + 2

    //finding largest element 
    //check if left child is greater than root
    if(leftChild < n /*make sure we are in the array*/ && arr[leftChild] > arr[l]){
        l = leftChild;
    }

    //check if right child is greater than 
    //max(largest,leftChild)
    if(rightChild < n && arr[rightChild] > arr[l]){
        l = rightChild;
    }

    //now we have figured out the largest of the root
    //node and its right and left child so we need to swap
    //the current root data with arr[l]
    //(unless given root was already the largest)
    if(l != i){
        swap(arr[i], arr[l]);
        heapify(arr,i,0); //recall on heap
    }
}

//swap two elements of an array
void swap(int e1, int e2){
    int temp = e1;
    e1 = e2;
    e2 = temp;
}


//prints specified array
void printArray(int* arr, int n){
    for(int i = 0; i < n; i++){
        if(i == 0){
            cout << "[" << arr[i] << ", ";
        }else if(i != n-1){
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