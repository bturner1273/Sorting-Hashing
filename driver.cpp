#include <iostream>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include "HashMap.cpp"
using namespace std;


void printArray(long long* arr, int n);
long long* initRandomArray();
long long* copyArray(long long* arr);
void heapSort(long long a[], int size);
void heapify(long long a[], int size, int root);
int partition(long long arr[], int l, int h);
void quickSort(long long arr[], int l, int h);
long double mean(long long arr[], int size);
long double stdev(long long a[], int size);

int size  = 5000;
long long qsCount, hsCount, qsData[30], hsData[30];

int main(){
//Final Driver
    //driving sorting/searching statistics
    srand(time(NULL));
    for(int i = 0; i < 30; i++){
        long long *arr = initRandomArray();
        long long *arrCopy = copyArray(arr);
        quickSort(arr,0,size-1);
        heapSort(arrCopy,size);
        qsData[i] = qsCount;
        hsData[i] = hsCount;
        qsCount = 0;
        hsCount = 0;
    }    
    quickSort(qsData,0,29);
    quickSort(hsData,0,29); //finally before computing averaging data
                            //we will quickSort both the hsData comparison set
                            //and the qsData comparison set because we have found
                            //that quickSort is generally faster
    cout << "For HeapSort the number of comparisons in each case were:" << endl;
    printArray(hsData,30);
    cout << "The minimum number of comparisons that took place in HeapSort was: " << hsData[0] << endl;
    cout << "The maximum number of comparisons that took place in HeapSort was: " << hsData[29] << endl;
    cout << "The average number of comparisons that took place in HeapSort was: " << mean(hsData,30) << endl;
    cout << "The median number of comparisons that took place in HeapSort was: " << hsData[14] << endl;
    cout << "The standard deviation for the number of comparisons in HeapSort was: " << stdev(hsData,30) << endl;
    cout << endl << endl;
    cout << "For QuickSort the number of comparisons in each case were:" << endl;
    printArray(qsData,30);
    cout << "The minimum number of comparisons that took place in QuickSort was: " << qsData[0] << endl;
    cout << "The maximum number of comparisons that took place in QuickSort was: " << qsData[29] << endl;
    cout << "The average number of comparisons that took place in QuickSort was: " << mean(qsData,30) << endl;
    cout << "The median number of comparisons that took place in QuickSort was: " << qsData[14] << endl;
    cout << "The standard deviation for the number of comparisons in QuickSort was: " << stdev(qsData,30) << endl;
    
    //driving Hash Table
    long long colData[10];
    long long compData[10];
    for(int i = 0; i < 10; i++){
        HashMap *hashMap = new HashMap();
        long long *elements = initRandomArray();
        for(int j = 0; j < size; j++){
            hashMap->put(j, elements[j]);
        }
        colData[i] = hashMap->collisions;
        compData[i] = hashMap->comparisons;
    }
    quickSort(colData,0,9);
    quickSort(compData,0,9);
    cout << endl << endl;
    cout << "HashMap statistics: " << endl;
    cout << "Comparison average: " << mean(compData,10) << endl;
    cout << "Collision average: " << mean(colData,10) << endl;
    
    

//TESTING 
// MEAN TEST WORKS
    // long long arr[] = {1,2,3,4,5};
    // cout << mean(arr,5) << endl;

// HEAPSORT TEST WORKS 
    // long long *arr = initRandomArray();
    // heapSort(arr,size);
    // printArray(arr,size);
    // cout << endl << endl << "HEAPSORT^" << endl;
    // cout << "hsCount = " << hsCount << endl;
// QUICKSORT TEST WORKS
    // long long *arr = initRandomArray();
    // quickSort(arr,0,size-1);
    // printArray(arr,size);
    // cout << endl << endl << "QUICKSORT^" << endl;
    // cout << "qsCount = " << qsCount << endl;
    
    
    return 0;
}

long double mean(long long arr[], int size){
    long double sum = 0;
    for(int i = 0; i < size; i++){
        sum  += arr[i];
    }
    return (long double)sum/size;
}

long double stdev(long long a[], int size) {
	double standardDev = 0.0;
	long long sum = 0;
	long double tempMean = mean(a,size);
	for (int i = 0; i < size; i++) {
		standardDev += pow(a[i] - tempMean, 2);
	}
	return (long double)sqrt((standardDev / size));
}


//quick sort uses a pivot and this function is used
//by quick sort to do all the shifting around the pivot

//my function always uses the last element of the array
//as the pivot and places all smaller elements to the left
//of the pivot and all larger elements to the right of the
//pivot
int partition(long long arr[], int l, int h){
    long long pivot = arr[h]; //we always pivot on the last element
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
        qsCount+=2; //one comparison for j<=h-1 one for arr[j] <= pivot
        if(arr[j] <= pivot){
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i+1], arr[h]);
    return i+1;
}

//basically quickSort just passes the last array element long longo
//the partition function, and resorts the list before and
//after partitioning every time
void quickSort(long long arr[], int l, int h){
    if(l < h){
        qsCount++; //one comparison to see if low < high
        int partitionIndex = partition(arr,l,h);
        quickSort(arr,l,partitionIndex-1);
        quickSort(arr,partitionIndex+1, h);
    }
}

//heapify an array, i.e. find largest element and 
//add it as the root node
void heapify(long long a[], int size, int root) {
	int tempRoot = root;//initialize largest (l) element in subheap as root
	int leftChild = 2 * tempRoot + 1; //left child is its parents position*2 + 1
	int rightChild = 2 * tempRoot + 2;//right child is its parents position*2 + 2
    hsCount++; //from the for loop comparison to call heapify in heapSort
    //finding largest element 
    //check if left child is greater than root
	if ((leftChild < size) /*make sure we are in the array*/ && (a[leftChild] > a[tempRoot])) tempRoot = leftChild;
    hsCount++;
    //check if right child is greater than 
    //max(largest,leftChild)
	if ((rightChild < size) && (a[rightChild] > a[tempRoot])) tempRoot = rightChild;
    hsCount++;
    //now we have figured out the largest of the root
    //node and its right and left child so we need to swap
    //the current root data with arr[l]
    //(unless given root was already the largest)
    hsCount++;
	if (tempRoot != root) {
		unsigned long long temp = a[root];
		a[root] = a[tempRoot];
		a[tempRoot] = temp;
		heapify(a, size, tempRoot);//recall on sub-heap
	}
}

//heapsort basically just heapifies all subtrees of the array
//by taking one element at a time, reinserting as the root and 
//re-heapifying the array
void heapSort(long long a[], int size) {
	//build heap
    for (int i = size / 2; i >= 0; i--) heapify(a, size, i);
    //swap the root with the last element of the heap 
        //and re-heapify for every element
        //to make sure heap is sorted
	for (int i = size - 1; i >= 0; i--) {
	    swap(a[0],a[i]);
		heapify(a, i, 0);
	}
}


//swap two elements of an array
void swap(long long e1, long long e2){
    long long temp = e1;
    e1 = e2;
    e2 = temp;
}


//prints specified array
void printArray(long long* arr, int n){
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

//returns a random array containing 5000 long longs
//between zero and one million
long long* initRandomArray(){
    long long* arr = new long long[size];
    for(int i = 0; i < size; i++){
        arr[i] = (long long)(rand()%1000000);
    }
    return arr;
}

//returns deep copy of array
long long* copyArray(long long* arr){
    long long* copy = new long long[size];
    for(int i = 0; i < size; i++){
        copy[i] = arr[i];
    }
    return copy;
}